from docx import Document
from docx.enum.section import WD_ORIENTATION, WD_SECTION_START
from docx.shared import Inches


def create_sample_document(filename="sample_document_with_sections.docx"):
    """Creates a sample .docx file with multiple sections."""
    document = Document()

    # --- Section 1 (default) ---
    document.add_paragraph("This is the first section.")
    document.add_paragraph(
        "It uses the default portrait orientation and margins."
    )
    # The first section's properties are the document's defaults.

    # --- Section 2 ---
    # Add a new section with a page break.
    section2 = document.add_section(WD_SECTION_START.NEW_PAGE)
    # Change properties for the new section
    section2.orientation = WD_ORIENTATION.LANDSCAPE
    section2.page_width = Inches(11)
    section2.page_height = Inches(8.5)
    section2.left_margin = Inches(1.5)
    section2.right_margin = Inches(1.5)

    # Add content to the second section.
    document.add_paragraph(
        "This is the second section. It's in landscape orientation."
    )

    # Add a unique header and footer to the second section
    header = section2.header
    p_header = header.paragraphs[0]
    p_header.text = "Section 2 Header"

    footer = section2.footer
    p_footer = footer.paragraphs[0]
    p_footer.text = "Section 2 Footer"

    # --- Section 3 ---
    # Add a third section that starts on the same page if there's space
    section3 = document.add_section(WD_SECTION_START.CONTINUOUS)
    document.add_paragraph("This is the third section.")
    document.add_paragraph(
        "It starts continuously and has its own header, but inherits the footer."
    )

    # It inherits properties from section 2, so let's change them back
    section3.orientation = WD_ORIENTATION.PORTRAIT
    section3.page_width = Inches(8.5)
    section3.page_height = Inches(11)
    section3.left_margin = Inches(1)

    # Give section 3 its own header. The footer will be inherited from section 2.
    section3.header.is_linked_to_previous = False
    section3.header.paragraphs[0].text = "Section 3 has a unique header."

    document.save(filename)
    print(f"Created sample document: {filename}")
    return filename


def parse_and_print_sections(doc_path):
    """Parses a .docx file and prints information about its sections."""
    document = Document(doc_path)
    print(f"\n--- Parsing sections for {doc_path} ---")
    print(f"Total sections: {len(document.sections)}")

    # for i, section in enumerate(document.sections):
    #     print(f"\n--- Section {i+1} ---")
    #     print(f"  Start type: {section.start_type}")
    #     print(f"  Orientation: {section.orientation}")
    #     print(f"  Page width: {section.page_width.inches:.2f} inches" if section.page_width else "Default")
    #     print(f"  Page height: {section.page_height.inches:.2f} inches" if section.page_height else "Default")
    #     print(f"  Left margin: {section.left_margin.inches:.2f} inches" if section.left_margin else "Default")
    #     print(f"  Header is linked to previous: {section.header.is_linked_to_previous}")
    #     if not section.header.is_linked_to_previous and section.header.paragraphs[0].text:
    #         print(f"  Header text: '{section.header.paragraphs[0].text}'")
    #     print(f"  Footer is linked to previous: {section.footer.is_linked_to_previous}")
    #     if not section.footer.is_linked_to_previous and section.footer.paragraphs[0].text:
    #         print(f"  Footer text: '{section.footer.paragraphs[0].text}'")


    for i, paragraph in enumerate(document.paragraphs):
        print(f"\n--- Paragraph {i+1} ---")
        print(paragraph.text)

if __name__ == "__main__":
    #sample_doc_path = create_sample_document()
    parse_and_print_sections("/home/ankdesh/Downloads/Sample-gdocs.docx")