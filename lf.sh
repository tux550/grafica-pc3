#!/bin/bash

# Directory to start from (current directory by default)
directory="${1:-.}"

# Find all .ply and .off files recursively
find "$directory" \( -name "*.ply" -o -name "*.off" \) -type f | while read -r file; do
  # Convert file from CRLF to LF using dos2unix
  echo "Converting: $file"
  dos2unix "$file"
done

echo "Conversion complete."