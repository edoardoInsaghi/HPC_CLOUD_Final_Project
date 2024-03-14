#!/bin/bash

DIR="test_files"
mkdir -p "$DIR"

for (( size=1; size<=32; size++ )); do
  bytes=$((2**size))
  dd if=/dev/zero of="$DIR/test_file_${bytes}B" bs=$bytes count=1
done
