#ifndef __SENIVERSE_WEATHER_H__
#define __SENIVERSE_WEATHER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "seniverse_weather_def.h"
#include "seniverse_weather_location.h"
#include "seniverse_weather_now.h"
#include "seniverse_weather_daily.h"
#include "seniverse_weather_hourly.h"

enum SENIVERSE_WEATHER_DATA_TYPE{
    SENIVERSE_WEATHER_NOW,
    SENIVERSE_WEATHER_DAILY,
    SENIVERSE_WEATHER_HOURLY,
};

struct seniverse_weather_obj {
    union {
        struct seniverse_weather_common common;
        struct weather_now now;
        struct weather_daily daily;
        struct weather_hourly hourly;
    };
    uint8_t items[];
};

struct seniverse_weather_obj *creat_weather_data(enum SENIVERSE_WEATHER_DATA_TYPE type, int count);
void destroy_weather_data(struct seniverse_weather_obj *data);

int seniverse_get_url_api();
int seniverse_parse_resp(enum SENIVERSE_WEATHER_DATA_TYPE type, const char *buf, void *data, int *count);

#ifdef __cplusplus
}
#endif

#endif