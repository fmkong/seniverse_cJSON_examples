#ifndef __SENIVERSE_WEATHER_LOCATION_H__
#define __SENIVERSE_WEATHER_LOCATION_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "cJSON.h"

#define WEATHER_LOCATION_MAX_LEN      32

struct weather_location {
    uint8_t id[WEATHER_LOCATION_MAX_LEN];
    uint8_t name[WEATHER_LOCATION_MAX_LEN];
    uint8_t country[WEATHER_LOCATION_MAX_LEN];
    uint8_t path[WEATHER_LOCATION_MAX_LEN];
    uint8_t timezone[WEATHER_LOCATION_MAX_LEN];
    uint8_t timezone_offset[WEATHER_LOCATION_MAX_LEN];
};

int parse_weather_location(cJSON *location_obj, struct weather_location *location);

#ifdef __cplusplus
}
#endif

#endif