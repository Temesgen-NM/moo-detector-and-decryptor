#!/usr/bin/env python3

import os
import hashlib
import shutil

# Folder to scan
search_path = "."

# Quarantine folder will be created if it doesn't exist
quarantine_path = "./quarantine"
os.makedirs(quarantine_path, exist_ok=True)

known_hash = "881ab996e1641d4008da0a48764c1424ff6d25fd0624332ac6eb9591ace00103"  # <-- replace with the real hash

def calculate_sha256(file_path):
    sha256 = hashlib.sha256()
    with open(file_path, "rb") as f:
        while True:
            chunk = f.read(4096)  # read 4k b at a time
            if not chunk:
                break
            sha256.update(chunk)
    return sha256.hexdigest()

for file in os.listdir(search_path):
    file_path = os.path.join(search_path, file)
 
    if os.path.isfile(file_path) and file == "moo":
        file_hash = calculate_sha256(file_path)

        if file_hash == known_hash:
            print(f"[!] Detected 'moo' at: {file_path}")

            # Move to quarantine
            destination = os.path.join(quarantine_path, "moo")
            shutil.move(file_path, destination)
            print(f"[+] Quarantined to: {destination}")