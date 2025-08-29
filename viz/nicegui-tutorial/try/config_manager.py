# configs.py

import toml
from pathlib import Path
from typing import Dict, Any, Optional

class ConfigManager:
    """
    Manages configuration settings for the client.
    Reads from and writes to a TOML configuration file.
    """
    def __init__(self, config_file: str = 'config.toml'):
        self.config_file = Path(config_file)
        self._config: Dict[str, Any] = {}
        self._load_config() # Load config on initialization

    def _load_config(self) -> None:
        """Loads configuration from the TOML file."""
        if self.config_file.exists():
            try:
                self._config = toml.loads(self.config_file.read_text())
            except Exception as e:
                print(f"Error loading config file {self.config_file}: {e}")
                self._config = {}
        else:
            print(f"Config file {self.config_file} not found. Using empty config.")
            self._config = {} # Initialize with empty config if file doesn't exist

    def _save_config(self) -> None:
        """Saves the current configuration to the TOML file."""
        try:
            self.config_file.write_text(toml.dumps(self._config))
            print(f"Config saved to {self.config_file}")
        except Exception as e:
            print(f"Error saving config file {self.config_file}: {e}")

    def get(self, key: str, default: Any = None) -> Any:
        """
        Retrieves a configuration value using a dot-separated key (e.g., "

        server.host").

        Args:
            key (str): The dot-separated key for the configuration value.
            default (Any): The default value to return if the key is not found.

        Returns:
            Any: The configuration value or the default value.
        """
        parts = key.split('.')
        current_config = self._config
        for part in parts:
            if isinstance(current_config, dict) and part in current_config:
                current_config = current_config.get(part)
            else:
                return default
        return current_config if current_config is not None else default

    def set(self, key: str, value: Any) -> None:
        """Sets a configuration value using a dot-separated key and saves the config."""
        parts = key.split('.')
        current_config = self._config
        for i, part in enumerate(parts):
            if i == len(parts) - 1:
                current_config[part] = value
            else:
                if part not in current_config or not isinstance(current_config[part], dict):
                    current_config[part] = {}
                current_config = current_config[part]
        self._save_config()