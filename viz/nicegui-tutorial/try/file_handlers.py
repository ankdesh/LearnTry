# file_handlers.py
import base64
import csv as csv_lib # to avoid conflict with pandas.csv
import io
import zipfile as zip_lib # to avoid conflict with zipfile module
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Optional, List, Dict, Any, Tuple, Union

from nicegui import ui # For ui.notify, if needed directly by handlers (though better in UI layer)
from content_manager import Content, TextContent, TableContent, CodeContent

# Optional imports for specific handlers
try:
    import pandas as pd
except ImportError:
    pd = None

try:
    from PyPDF2 import PdfReader
except ImportError:
    PdfReader = None

import logging
_logger = logging.getLogger(__name__)


class AbstractFileHandler(ABC):
    """
    Abstract base class for handling different file types.
    Provides methods to encode file content to base64, decode from base64,
    and get a UI-renderable content representation.
    """
    def __init__(self, file_content: io.BytesIO, file_name: str, file_type: str):
        """
        Args:
            file_content (io.BytesIO): The content of the file as a BytesIO stream.
            file_name (str): The original name of the file.
            file_type (str): The MIME type of the file.
        """
        self.file_content = file_content
        self.file_name = file_name
        self.file_type = file_type # MIME type

    async def _read_file_bytes(self) -> bytes:
        """Helper to read bytes from the BytesIO stream."""
        self.file_content.seek(0) # Ensure reading from the beginning
        return self.file_content.read()

    async def encode_to_base64(self) -> str:
        """Encodes the raw file content to a base64 string."""
        file_bytes = await self._read_file_bytes()
        return base64.b64encode(file_bytes).decode('utf-8')

    async def decode_from_base64(self, base64_content: str) -> bytes:
        """Decodes a base64 string back to bytes."""
        return base64.b64decode(base64_content.encode('utf-8'))

    @abstractmethod
    async def get_content_representation(self) -> Content:
        """
        Returns a Content object (e.g., TextContent, TableContent)
        that can be displayed in the UI.
        """
        pass

    def get_default_name(self) -> str:
        """Generates a default name for the content item based on file name."""
        return f"File: {self.file_name}"


class TextFileHandler(AbstractFileHandler):
    """Handles plain text files (.txt, .md, .py, .js, etc.)."""
    async def get_content_representation(self) -> Content:
        file_bytes = await self._read_file_bytes()
        try:
            text_content = file_bytes.decode('utf-8')
        except UnicodeDecodeError:
            _logger.warning(f"Could not decode {self.file_name} as UTF-8, trying latin-1.")
            try:
                text_content = file_bytes.decode('latin-1')
            except UnicodeDecodeError:
                _logger.error(f"Could not decode {self.file_name} as UTF-8 or latin-1.")
                return TextContent(name=self.get_default_name(), text=f"[Could not decode text file: {self.file_name}]")

        code_extensions = ('.py', '.js', '.html', '.css', '.json', '.yaml', '.yml', '.sh', '.java', '.c', '.cpp', '.h', '.hpp', '.cs', '.go', '.rs', '.rb', '.php', '.swift', '.kt', '.kts', '.scala', '.pl', '.pm')
        file_ext = Path(self.file_name).suffix.lower()

        if file_ext == '.md':
            return TextContent(name=self.get_default_name(), text=text_content)
        elif file_ext in code_extensions:
            language = file_ext[1:]
            lang_map = {"js": "javascript", "yml": "yaml", "html": "html", "css": "css", "py": "python"}
            return CodeContent(name=self.get_default_name(), code=text_content, language=lang_map.get(language, language))
        else:
            return TextContent(name=self.get_default_name(), text=text_content)


class CSVFileHandler(AbstractFileHandler):
    """Handles CSV files."""
    async def get_content_representation(self) -> Content:
        file_bytes = await self._read_file_bytes()
        try:
            text_content = file_bytes.decode('utf-8-sig') # Handle BOM
        except UnicodeDecodeError:
            _logger.warning(f"Could not decode CSV {self.file_name} as UTF-8-SIG, trying UTF-8.")
            text_content = file_bytes.decode('utf-8')


        if pd:
            try:
                df = pd.read_csv(io.StringIO(text_content))
                headers = df.columns.tolist()
                rows = df.values.tolist()[:20] # Limit rows
                if len(df) > 20:
                    ui.notify("CSV has more than 20 rows. Displaying first 20.", type='info')
                return TableContent(name=self.get_default_name(), headers=headers, rows=rows)
            except Exception as e:
                _logger.error(f"Pandas could not parse CSV {self.file_name}: {e}. Falling back to text.")
                return TextContent(name=self.get_default_name(), text=text_content[:2000] + "...")
        else:
            try:
                reader = csv_lib.reader(io.StringIO(text_content))
                rows = list(reader)
                if not rows: return TextContent(name=self.get_default_name(), text="[Empty CSV File]")
                headers = rows[0]
                data_rows = rows[1:21]
                if len(rows) > 21: ui.notify("CSV has more than 20 data rows. Displaying first 20.", type='info')
                return TableContent(name=self.get_default_name(), headers=headers, rows=data_rows)
            except Exception as e:
                _logger.error(f"Basic CSV parsing failed for {self.file_name}: {e}. Displaying raw text.")
                return TextContent(name=self.get_default_name(), text=text_content[:2000] + "...")


class ExcelFileHandler(AbstractFileHandler):
    """Handles Excel files (.xls, .xlsx)."""
    async def get_content_representation(self) -> Content:
        if not pd:
            return TextContent(name=self.get_default_name(), text="[Excel file - pandas not available to parse]")
        file_bytes = await self._read_file_bytes()
        try:
            excel_file = pd.ExcelFile(io.BytesIO(file_bytes))
            sheet_names = excel_file.sheet_names
            if not sheet_names: return TextContent(name=self.get_default_name(), text="[Excel file with no sheets]")
            first_sheet_name = sheet_names[0]
            df = excel_file.parse(first_sheet_name)
            headers = df.columns.tolist()
            rows = df.values.tolist()[:20] # Limit rows
            if len(df) > 20: ui.notify(f"Sheet '{first_sheet_name}' has >20 rows. Displaying first 20.", type='info')
            return TableContent(name=f"{self.get_default_name()} ({first_sheet_name})", headers=headers, rows=rows)
        except Exception as e:
            _logger.error(f"Pandas could not parse Excel {self.file_name}: {e}.")
            return TextContent(name=self.get_default_name(), text=f"[Could not parse Excel: {e}]")


class PDFFileHandler(AbstractFileHandler):
    """Handles PDF files."""
    async def get_content_representation(self) -> Content:
        if not PdfReader:
            return TextContent(name=self.get_default_name(), text="[PDF file - PyPDF2 not available to parse]")
        file_bytes = await self._read_file_bytes()
        try:
            reader = PdfReader(io.BytesIO(file_bytes))
            text_parts = [page.extract_text() for i, page in enumerate(reader.pages) if i < 5] # Limit pages
            if len(reader.pages) > 5: text_parts.append("\n[...truncated after 5 pages...]")
            extracted_text = "\n".join(filter(None, text_parts)) or "[PDF content could not be extracted or is empty]"
            return TextContent(name=self.get_default_name(), text=extracted_text[:5000] + "...")
        except Exception as e:
            _logger.error(f"PyPDF2 could not parse PDF {self.file_name}: {e}.")
            return TextContent(name=self.get_default_name(), text=f"[Could not parse PDF: {e}]")


class ZipFileHandler(AbstractFileHandler):
    """Handles ZIP files."""
    async def get_content_representation(self) -> Content:
        file_bytes = await self._read_file_bytes()
        try:
            with zip_lib.ZipFile(io.BytesIO(file_bytes), 'r') as zip_ref:
                file_list = zip_ref.namelist()
                if not file_list: return TextContent(name=self.get_default_name(), text="[Empty ZIP archive]")
                display_list = file_list[:20] # Limit files listed
                content_text = "Files in archive:\n" + "\n".join(f"- {f}" for f in display_list)
                if len(file_list) > 20: content_text += f"\n...and {len(file_list) - 20} more files."
                return TextContent(name=self.get_default_name(), text=content_text)
        except Exception as e:
            _logger.error(f"Error processing ZIP {self.file_name}: {e}")
            return TextContent(name=self.get_default_name(), text=f"[Error processing ZIP: {e}]")


class GenericFileHandler(AbstractFileHandler):
    """Handles generic binary files or files with unhandled MIME types."""
    async def get_content_representation(self) -> Content:
        b64_preview = await self.encode_to_base64()
        text = (
            f"File: {self.file_name}\n"
            f"Type: {self.file_type or 'unknown/binary'}\n"
            f"Base64 Encoded (preview):\n{b64_preview[:200]}..."
        )
        return CodeContent(name=self.get_default_name(), code=text, language="text")


class FileHandlerFactory:
    """Factory class to get the appropriate file handler based on MIME type or extension."""
    @staticmethod
    def get_handler(file_content: io.BytesIO, file_name: str, mime_type: Optional[str]) -> AbstractFileHandler:
        ext = Path(file_name).suffix.lower()
        mime_type = mime_type.lower() if mime_type else ''

        if mime_type == 'application/pdf' or ext == '.pdf':
            return PDFFileHandler(file_content, file_name, mime_type or 'application/pdf')
        if mime_type == 'text/csv' or ext == '.csv':
            return CSVFileHandler(file_content, file_name, mime_type or 'text/csv')
        if mime_type in ['application/vnd.ms-excel', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'] or ext in ['.xls', '.xlsx']:
            return ExcelFileHandler(file_content, file_name, mime_type or 'application/vnd.ms-excel')
        if mime_type == 'application/zip' or ext == '.zip':
            return ZipFileHandler(file_content, file_name, mime_type or 'application/zip')
        if mime_type.startswith('text/') or \
           ext in ['.txt', '.py', '.js', '.md', '.html', '.css', '.json', '.log', '.yaml', '.yml', '.sh', '.java', '.c', '.cpp', '.h', '.hpp', '.cs', '.go', '.rs', '.rb', '.php', '.swift', '.kt', '.kts', '.scala', '.pl', '.pm']:
            return TextFileHandler(file_content, file_name, mime_type or f"text/{ext[1:] if ext else 'plain'}")

        _logger.info(f"No specific handler for MIME '{mime_type}' or ext '{ext}'. Using GenericFileHandler for {file_name}.")
        return GenericFileHandler(file_content, file_name, mime_type or 'application/octet-stream')