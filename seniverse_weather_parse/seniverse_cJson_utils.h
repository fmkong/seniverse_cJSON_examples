#ifndef __SENIVERSE_CJSON_H__
#define __SENIVERSE_CJSON_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "cJSON.h"

#define DEBUG_ENABLE 1

#ifdef __GNUC__
    #define SENIVERSE_LOGE(TAG, fmt, ...) do{\
        printf("E: %s: " fmt, TAG, ##__VA_ARGS__);\
    } while(0)
    #define SENIVERSE_LOGI(TAG, fmt, ...) do{\
        printf("I: %s: " fmt, TAG, ##__VA_ARGS__);\
    } while(0)
    #define SENIVERSE_LOGD(TAG, fmt, ...)  do{\
        if (DEBUG_ENABLE)\
            printf("D: %s: " fmt, TAG, ##__VA_ARGS__);\
    } while(0)
    #define SENIVERSE_MALLOC(size) malloc(size)
    #define SENIVERSE_FREE(p) free(p)
#else
    #define SENIVERSE_LOGE(TAG, fmt, ...)
    #define SENIVERSE_LOGI(TAG, fmt, ...)
    #define SENIVERSE_LOGD(TAG, fmt, ...)
    #define SENIVERSE_MALLOC(size) malloc(size)
    #define SENIVERSE_FREE(p) free(p)
#endif

#define MAX_STRING_OBJ_BUFFER_LEN 32

int parse_object_string_value(cJSON *obj, char *key, char *value, int len);
int parse_object_string_to_int(cJSON *obj, char *key);
float parse_object_string_to_float(cJSON *obj, char *key);
cJSON *get_object_with_key_in_array(cJSON *array, char *key);
int get_object_array_size(cJSON *array);
cJSON *get_object_with_index_in_array(cJSON *array, int index);

#ifdef __cplusplus
}
#endif

#endif