CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER "gcc")

PROJECT(cJsonTest)

INCLUDE_DIRECTORIES(
        cJSON
        seniverse_weather_test)

ADD_EXECUTABLE(
        cJsonTest
        cJSON/cJSON.c
        cJSON/cJSON_Utils.c
        seniverse_weather_test/example_weather_now.c
        test.c)