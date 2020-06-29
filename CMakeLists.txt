CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER "gcc")

PROJECT(cJsonTest)

INCLUDE_DIRECTORIES(
        cJSON
        seniverse_weather_parse
        seniverse_weather_test)

ADD_EXECUTABLE(
        cJsonTest
        cJSON/cJSON.c
        cJSON/cJSON_Utils.c
        seniverse_weather_parse/seniverse_cJson_utils.c
        seniverse_weather_parse/seniverse_weather_now.c
        seniverse_weather_parse/seniverse_weather_daily.c
        seniverse_weather_test/test_weather_now.c
        seniverse_weather_test/test_weather_daily.c
        test.c)