#ifndef __SENIVERSE_WEATHER_HOURLY_H__
#define __SENIVERSE_WEATHER_HOURLY_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "seniverse_weather_def.h"

#define WEATHER_HOURLY_SUMMARY_MAX_LEN      16
#define WEATHER_HOURLY_UPDATE_TIME_MAX_LEN  WEATHER_UPDATE_TIME_MAX_LEN

struct weather_hourly_item {
    uint8_t time[WEATHER_HOURLY_UPDATE_TIME_MAX_LEN];
    uint8_t text[WEATHER_HOURLY_SUMMARY_MAX_LEN];
    uint8_t wind_direction[WEATHER_HOURLY_SUMMARY_MAX_LEN];
    float temperature;
    float wind_speed;
    float humidity;
    int8_t code;
};

struct weather_hourly {
    struct seniverse_weather_common common;
    struct weather_hourly_item items[];
};

int parse_weather_hourly(const char *buf, struct weather_hourly *hourly, int *count);

#ifdef __cplusplus
}
#endif
#endif