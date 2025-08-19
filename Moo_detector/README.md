# Moo Detector

## Overview

**Moo Detector** is a Python-based utility designed to detect and handle the malicious `moo` program on your system. The `moo` program is a simple file encryption tool that can modify files without user consent. This detector identifies the `moo` executable and safely quarantines it to prevent further harm.

> ⚠️ **Note:** This tool targets the `moo` executable only, not the files it may have encrypted.

---

## Features

* Scans a specified directory (and subdirectories) for the `moo` executable.
* Verifies the executable using SHA-256 hash to avoid false positives.
* Quarantines detected `moo` binaries to a safe folder.
* Simple, lightweight Python implementation.

---

## Requirements

* Python 3.x
* Standard Python libraries: `os`, `hashlib`, `shutil` (no external packages required)

---

## Setup & Usage

### 1. Prepare the Script

Save the Python code as `detect_moo.py`.

### 2. Get the Hash of `moo`

Compile the `moo.c` program:

```bash
gcc moo.c -o moo
```

Compute the SHA-256 hash:

```bash
sha256sum moo
```

Copy the hash and replace the placeholder in the script:

```python
known_hash = "your_moo_binary_hash_here"
```

### 3. Configure Search & Quarantine Paths

By default, the script searches in your home directory and quarantines files in `./quarantine`. Update the paths in the script if needed:

```python
search_path = "/path/to/search"
quarantine_path = "/path/to/quarantine"
```

### 4. Run the Detector

```bash
python3 detect_moo.py
```

The script will:

1. Scan the directory for a file named `moo`.
2. Verify the file hash.
3. Move confirmed `moo` binaries to the quarantine folder.

---

## Example Output

```
[+] Found moo at: /home/user/malware/moo
[!] moo detected! Hash matches.
[+] moo has been quarantined to: /home/user/quarantine/moo
```

---

## Notes

* This tool only detects the `moo` program itself, not the files it may have encrypted.
* Make sure to run with sufficient permissions to access the target directories.
* The quarantine folder can be reviewed and safely deleted if desired.

---


