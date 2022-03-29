@echo off
gcc -Wall -o result_log_to_csv_converter.exe main.c convert_to_csv.c
result_log_to_csv_converter.exe %1 %2