#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "test_weather_now.h"
#include "test_weather_daily.h"
#include "test_weather_hourly.h"

int CJSON_CDECL main(void)
{
    test_weather_now();
    test_weather_daily();
    test_weather_hourly();
    return 0;
}