@echo off
gcc -Wall -o result_log_to_csv_converter.exe src/main.c src/convert_to_csv.c
result_log_to_csv_converter.exe %1 %2