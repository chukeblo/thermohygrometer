#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "result_log_to_csv_converter.h"

#define MAX_LINE_DATA_SIZE 200

// constant strings for validation
#define RESULT_LOG_SUFFIX "[DEBUG] ThermohygroDataMeasurer::ReadThermohygroData() measurement result: time="
#define TEMPERATURE_LABEL ", temperature="
#define HUMIDITY_LABEL ", humidity="

typedef struct
{
    char time[20];
    double temperature;
    double humidity;
} csv_data_t;

static int is_result_log(char* line_data)
{
    char* tmp = line_data;
    if (!(tmp = strstr(tmp, RESULT_LOG_SUFFIX))) return FAILURE;
    if (!(tmp = strstr(tmp, TEMPERATURE_LABEL))) return FAILURE;
    if (!(tmp = strstr(tmp, HUMIDITY_LABEL))) return FAILURE;
    return SUCCESS;
}

static int get_csv_data(char* line_data, int size, csv_data_t* data)
{
    char* tmp = line_data + strlen(RESULT_LOG_SUFFIX);
    int counts = 0;
    for (; tmp[counts] != ','; counts++)
    {
        data->time[counts] = tmp[counts];
    }
    data->time[counts] = '\0';
    
    tmp = tmp + strlen(TEMPERATURE_LABEL) + counts;
    counts = 0;
    char temperature[10];
    for (; tmp[counts] != ','; counts++)
    {
        temperature[counts] = tmp[counts];
    }
    temperature[counts] = '\0';
    data->temperature = (double)atof(temperature);

    tmp = tmp + strlen(HUMIDITY_LABEL) + counts;
    counts = 0;
    char humidity[10];
    for (; tmp[counts] != '\r' && tmp[counts] != '\n' && tmp[counts] != '\0'; counts++)
    {
        humidity[counts] = tmp[counts];
    }
    humidity[counts] = '\0';
    data->humidity = (double)atof(humidity);

    return SUCCESS;
}

int convert_to_csv(log_file_info_t* info)
{
    char line_data[MAX_LINE_DATA_SIZE] = { 0 };
    for (;;)
    {
        if (fgets(line_data, MAX_LINE_DATA_SIZE, info->input_file) == NULL)
        {
            // return success if reaching the end of file
            if (feof(info->input_file)) return SUCCESS;

            // return failure if some error occurred
            if (!ferror(info->input_file))
            {
                printf("failed to read data from input file.\n");
                return FAILURE;
            }
        }

        // skip loop if read line data is not of result log
        if (is_result_log(line_data) == FAILURE) continue;

        csv_data_t data = { "", 0.0, 0.0 };
        // return failure if result log has some issue
        if (get_csv_data(line_data, strlen(line_data), &data) == FAILURE)
        {
            printf("failed to get csv data from line data. line data=%s\n", line_data);
            return FAILURE;
        }
        printf("csv data: time = %s, temp = %5.2f, humi = %5.2f\n", data.time, data.temperature, data.humidity);
    }
}