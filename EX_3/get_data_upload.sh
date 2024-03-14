#!/bin/bash

files=(
"test_file_2B"
"test_file_4B"
"test_file_8B"
"test_file_16B"
"test_file_32B"
"test_file_64B"
"test_file_128B"
"test_file_256B"
"test_file_512B"
"test_file_1024B"
"test_file_2048B"
"test_file_4096B"
"test_file_8192B"
"test_file_16384B"
"test_file_32768B"
"test_file_65536B"
"test_file_131072B"
"test_file_262144B"
"test_file_524288B"
"test_file_1048576B"
"test_file_2097152B"
"test_file_4194304B"
"test_file_8388608B"
"test_file_16777216B"
"test_file_33554432B"
"test_file_67108864B"
"test_file_134217728B"
"test_file_268435456B"
"test_file_536870912B"
"test_file_1073741824B"
)

echo "File Name,Upload Time" > upload_times.csv

for file in "${files[@]}"; do
    start_time=$(gdate +%s%N)
    curl -k -u "USERNAME:PASSWORD" -T "test_files/$file" "localhost:8080/remote.php/webdav/$file.txt"
    end_time=$(gdate +%s%N)
    elapsed_time=$(echo "$end_time - $start_time" | bc)
    echo "$file,$elapsed_time" >> upload_times.csv
done

