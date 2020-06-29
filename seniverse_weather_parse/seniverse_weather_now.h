#ifndef __SENIVERSE_WEATHER_NOW_H__
#define __SENIVERSE_WEATHER_NOW_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#define WEATHER_NOW_SUMMARY_MAX_LEN      16
#define WEATHER_NOW_UPDATE_TIME_MAX_LEN  32

struct weather_now {
    uint8_t last_update[WEATHER_NOW_UPDATE_TIME_MAX_LEN];
    uint8_t summary[WEATHER_NOW_SUMMARY_MAX_LEN];
    uint8_t wind_direction[WEATHER_NOW_SUMMARY_MAX_LEN];
    float temperature;
    float feels_like;
    float pressure;
    float visibility;
    float wind_speed;
    float wind_scale;
    float dew_point;
    float wind_direction_degree;
    float clouds;
    float humidity;
    int8_t code;
};

int parse_weather_now(const char *buf, struct weather_now *now);

#ifdef __cplusplus
}
#endif
#endif