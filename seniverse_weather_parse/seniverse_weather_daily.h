#ifndef __SENIVERSE_WEATHER_DAILY_H__
#define __SENIVERSE_WEATHER_DAILY_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#define WEATHER_DAILY_SUMMARY_MAX_LEN      16
#define WEATHER_DAILY_UPDATE_TIME_MAX_LEN  32

struct weather_daily_item {
    uint8_t date[WEATHER_DAILY_SUMMARY_MAX_LEN];
    uint8_t text_day[WEATHER_DAILY_SUMMARY_MAX_LEN];
    uint8_t text_night[WEATHER_DAILY_SUMMARY_MAX_LEN];
    uint8_t wind_direction[WEATHER_DAILY_SUMMARY_MAX_LEN];
    float high_temp;
    float low_temp;
    float precip;
    float wind_direction_degree;
    float wind_speed;
    float wind_scale;
    float rainfall;
    float humidity;
    int8_t code_day;
    int8_t code_night;
};

struct weather_daily {
    uint8_t last_update[WEATHER_DAILY_UPDATE_TIME_MAX_LEN];
    int count;
    struct weather_daily_item items[];
};

struct weather_daily *creat_weather_daily(int count);
void destroy_weather_daily(struct weather_daily *daily);

int parse_weather_daily(const char *buf, struct weather_daily *daily, int *count);

#ifdef __cplusplus
}
#endif
#endif