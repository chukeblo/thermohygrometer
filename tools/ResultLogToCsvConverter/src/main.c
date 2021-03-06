#include <stdio.h>

#include "result_log_to_csv_converter.h"

// constants for InitLogFileInfo()
#define EXPECTED_ARGUMENT_COUNTS 3

int initialize(int argc, char* argv[], log_file_info_t* info)
{
    // initialize LogFileInfo variable
    info->input_file = NULL;
    info->output_file = NULL;

    // check if argument counts are valid
    if (argc != EXPECTED_ARGUMENT_COUNTS)
    {
        printf("argument counts are invalid. argument counts=%d\n", argc);
        return FAILURE;
    }

    // check if given input file path is valid
    info->input_file = fopen(argv[1], "r");
    if (info->input_file == NULL)
    {
        printf("cannot open file with given input file path. input file path=%s\n", argv[1]);
        return FAILURE;
    }

    // check if given output file path is valid
    info->output_file = fopen(argv[2], "w");
    if (info->output_file == NULL)
    {
        printf("cannot open file with given output file path. output file path=%s\n", argv[2]);
        fclose(info->input_file);
        return FAILURE;
    }

    return SUCCESS;
}

int finalize(log_file_info_t* info)
{
    fclose(info->input_file);
    info->input_file = NULL;
    fclose(info->output_file);
    info->output_file = NULL;
    return SUCCESS;
}


int main(int argc, char* argv[])
{
    printf("result log to csv converter started.\n");
    log_file_info_t info;
    if (initialize(argc, argv, &info) == FAILURE)
    {
        printf("initialization failed.");
        return FAILURE;
    }
    if (convert_to_csv(&info) == FAILURE)
    {
        printf("conversion failed.");
        return FAILURE;
    }

    finalize(&info);

    printf("result log to csv converter succeeded.\n");
    return SUCCESS;
}