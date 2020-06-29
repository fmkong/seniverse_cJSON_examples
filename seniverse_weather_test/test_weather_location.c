#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "seniverse_weather_location.h"

int dump_weather_location(const struct weather_location *location)
{
    printf("location: \n");
    printf("\t id: %s\n", location->id);
    printf("\t name: %s\n", location->name);
    printf("\t country: %s\n", location->country);
    printf("\t path: %s\n", location->path);
    printf("\t timezone: %s\n", location->timezone);
    printf("\t timezone_offset: %s\n", location->timezone_offset);
}