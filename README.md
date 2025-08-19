# Moo-Detector and Decryptor – Multilanguage Demo Suite

This repository contains three related components written in C and Python:

| Folder | Language | Purpose |
| ------ | -------- | ------- |
| [Boo](Boo/README.md) | C | Decrypts files encrypted by `moo`; can also encrypt files for testing |
| [Moo](moo/README.md) | C | A minimal “ransomware-ish” sample that encrypts files (educational only) |
| [Moo_detector](Moo_detector/README.md) | Python | Scans directories, detects the `moo` binary by hash, and quarantines it |

---
## Quick Start
1. Clone or download the project.
2. Pick the component you need and follow its specific README (links above).
3. If you only want to test the detector:
   ```bash
   python Moo_detector/moo_detector.py
   ```

---
## Building C Components (Boo & Moo)
Both `Boo` and `Moo` include a `Makefile` for easy compilation on Linux-like systems:
```bash
cd Boo   && make   # builds boo
cd ../moo && make  # builds moo
```
For Windows users, the individual READMEs describe using **MSYS2** or **Cygwin** to provide the necessary POSIX headers.

---
## License
All code in this repository is released into the public domain. See the full text in [`moo/UNLICENSE`](moo/UNLICENSE).

---
*Happy exploring, hacking, and learning!* :cow: :lock: