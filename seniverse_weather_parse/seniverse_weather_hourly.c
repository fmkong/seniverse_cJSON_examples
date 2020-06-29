
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "seniverse_weather_hourly.h"
#include "seniverse_cJson_utils.h"

#define LOG_TAG "seniverse_hourly"

static int parse_weather_hourly_item_object(cJSON *json_hourly_item, struct weather_hourly_item *hourly_item)
{
    // Get the hourly weather data from the hourly item object
    if (json_hourly_item == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "json_hourly_item is null\n");
        return -1;
    }

    parse_object_string_value(json_hourly_item, "time", hourly_item->time, WEATHER_HOURLY_UPDATE_TIME_MAX_LEN);
    parse_object_string_value(json_hourly_item, "text", hourly_item->text, WEATHER_HOURLY_SUMMARY_MAX_LEN);
    hourly_item->code = parse_object_string_to_int(json_hourly_item, "code");
    hourly_item->temperature = parse_object_string_to_float(json_hourly_item, "temperature");
    parse_object_string_value(json_hourly_item, "wind_direction", hourly_item->wind_direction, WEATHER_HOURLY_SUMMARY_MAX_LEN);
    hourly_item->wind_speed = parse_object_string_to_float(json_hourly_item, "wind_speed");
    hourly_item->humidity = parse_object_string_to_float(json_hourly_item, "humidity");

    return 0;
}

static int parse_weather_hourly_array(cJSON *json_hourly_array, struct weather_hourly *hourly, int *count)
{
    // Get the current weather data from the hourly array object
    if (json_hourly_array == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "json_hourly_array is null\n");
        return -1;
    }
    int array_size = get_object_array_size(json_hourly_array);
    SENIVERSE_LOGD(LOG_TAG, "json_hourly_array size is %d\n", array_size);
    if (hourly->common.count < array_size) {
        SENIVERSE_LOGE(LOG_TAG, "hourly items buffer is not enough: count %d, array size %d\n", hourly->common.count, array_size);
    }
    for (int index = 0; index < (hourly->common.count < array_size ? hourly->common.count : array_size); index++) {
        parse_weather_hourly_item_object(get_object_with_index_in_array(json_hourly_array, index), &hourly->items[index]);
    }
    *count = hourly->common.count < array_size ? hourly->common.count : array_size;
    return 0;
}

int parse_weather_hourly(const char *buf, struct weather_hourly *hourly, int *count)
{
    // Data can be found after the HTTP header, get te offset to get the data
    char* data_offset = strstr(buf, "\n");

    SENIVERSE_LOGD(LOG_TAG, "get resp: %s\n", data_offset);

    cJSON *json = cJSON_Parse(data_offset);
    if (json == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "Error in cJSON_Parse: [%s]\n", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *json_results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (json_results == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "Error in get item result: [%s]\n", cJSON_GetErrorPtr());
    }

    cJSON *json_location = get_object_with_key_in_array(json_results, "location");
    if (json_location == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "Error in get item location: [%s]\n", cJSON_GetErrorPtr());
    }
    parse_weather_location(json_location, &hourly->common.location);

    cJSON *json_hourly = get_object_with_key_in_array(json_results, "hourly");
    if (json_hourly)
        parse_weather_hourly_array(json_hourly, hourly, count);

    cJSON *json_last_update = get_object_with_key_in_array(json_results, "last_update");
    if (json_last_update && cJSON_IsString(json_last_update) && (json_last_update->valuestring != NULL))
            snprintf(hourly->common.last_update, WEATHER_HOURLY_UPDATE_TIME_MAX_LEN, "%s", json_last_update->valuestring);

    if (json)
        cJSON_Delete(json);
    return 0;
}