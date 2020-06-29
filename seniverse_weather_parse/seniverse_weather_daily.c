
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "seniverse_weather_daily.h"
#include "seniverse_cJson_utils.h"

#define LOG_TAG "seniverse_daily"

static int parse_weather_daily_item_object(cJSON *json_daily_item, struct weather_daily_item *daily_item)
{
    // Get the daily weather data from the daily item object
    if (json_daily_item == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "json_daily_item is null\n");
        return -1;
    }

    parse_object_string_value(json_daily_item, "date", daily_item->date, WEATHER_DAILY_SUMMARY_MAX_LEN);
    parse_object_string_value(json_daily_item, "text_day", daily_item->text_day, WEATHER_DAILY_SUMMARY_MAX_LEN);
    daily_item->code_day = parse_object_string_to_int(json_daily_item, "code_day");
    parse_object_string_value(json_daily_item, "text_night", daily_item->text_night, WEATHER_DAILY_SUMMARY_MAX_LEN);
    daily_item->code_night = parse_object_string_to_int(json_daily_item, "code_night");

    daily_item->high_temp = parse_object_string_to_float(json_daily_item, "high");
    daily_item->low_temp = parse_object_string_to_float(json_daily_item, "low");
    daily_item->precip = parse_object_string_to_float(json_daily_item, "precip");

    parse_object_string_value(json_daily_item, "wind_direction", daily_item->wind_direction, WEATHER_DAILY_SUMMARY_MAX_LEN);
    daily_item->wind_direction_degree = parse_object_string_to_float(json_daily_item, "wind_direction_degree");
    daily_item->wind_speed = parse_object_string_to_float(json_daily_item, "wind_speed");
    daily_item->wind_scale = parse_object_string_to_float(json_daily_item, "wind_scale");
    daily_item->rainfall = parse_object_string_to_float(json_daily_item, "rainfall");
    daily_item->humidity = parse_object_string_to_float(json_daily_item, "humidity");

    return 0;
}

static int parse_weather_daily_array(cJSON *json_daily_array, struct weather_daily *daily, int *count)
{
    // Get the current weather data from the daily array object
    if (json_daily_array == NULL) {
        SENIVERSE_LOGE(LOG_TAG, "json_daily_array is null\n");
        return -1;
    }
    int array_size = get_object_array_size(json_daily_array);
    SENIVERSE_LOGD(LOG_TAG, "json_daily_array size is %d\n", array_size);
    if (daily->count < array_size) {
        SENIVERSE_LOGE(LOG_TAG, "daily items buffer is not enough: count %d, array size %d\n", daily->count, array_size);
    }
    for (int index = 0; index < (daily->count < array_size ? daily->count : array_size); index++) {
        parse_weather_daily_item_object(get_object_with_index_in_array(json_daily_array, index), &daily->items[index]);
    }
    *count = daily->count < array_size ? daily->count : array_size;
    return 0;
}

int parse_weather_daily(const char *buf, struct weather_daily *daily, int *count)
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

    cJSON *json_daily = get_object_with_key_in_array(json_results, "daily");
    if (json_daily)
        parse_weather_daily_array(json_daily, daily, count);

    cJSON *json_last_update = get_object_with_key_in_array(json_results, "last_update");
    if (json_last_update && cJSON_IsString(json_last_update) && (json_last_update->valuestring != NULL))
            snprintf(daily->last_update, WEATHER_DAILY_UPDATE_TIME_MAX_LEN, "%s", json_last_update->valuestring);

    if (json)
        cJSON_Delete(json);
    return 0;
}

struct weather_daily *creat_weather_daily(int count)
{
    struct weather_daily *daily = SENIVERSE_MALLOC(sizeof(struct weather_daily) + sizeof(struct weather_daily_item) * count);
    if (!daily) {
        SENIVERSE_LOGE(LOG_TAG, "Failed to alloc mem for daily data.");
        return daily;
    }
    daily->count = count;
    memset(daily->last_update, 0, WEATHER_DAILY_UPDATE_TIME_MAX_LEN);
    memset(daily->items, 0, sizeof(struct weather_daily_item) * count);
    return daily;
}

void destroy_weather_daily(struct weather_daily *daily)
{
    if (daily)
        SENIVERSE_FREE(daily);
}