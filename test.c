#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "example_weather_now.h"


int CJSON_CDECL main(void)
{
    struct weather_now now;
    /* print the version */
    printf("Version: %s\n", cJSON_Version());
    parse_weather_now(weather_now_example, &now);
    dump_weather_now(&now);
    memset(&now, 0, sizeof(now));
    parse_weather_now(example_real, &now);
    dump_weather_now(&now);
    return 0;
}