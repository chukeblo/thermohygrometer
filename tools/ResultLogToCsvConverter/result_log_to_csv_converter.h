#ifndef _RESULT_LOG_TO_CSV_CONVERTER_H_
#define _RESULT_LOG_TO_CSV_CONVERTER_H_

// return values from methods
#define SUCCESS 0
#define FAILURE 1

typedef struct
{
    FILE* input_file;
    FILE* output_file;
} log_file_info_t;

#endif  // _RESULT_LOG_TO_CSV_CONVERTER_H_