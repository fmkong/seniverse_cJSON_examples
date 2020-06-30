CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER "gcc")

PROJECT(cJsonTest)

set(CMAKE_BUILD_TYPE "Debug")

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror -Wno-unused-variable -pthread")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -g -Wall -Werror -Wno-unused-variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -fopenmp")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11  -Wall -Werror -O2 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )
message("Build Type:"${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

INCLUDE_DIRECTORIES(
        cJSON
        seniverse_weather_parse/include
        seniverse_weather_test/include)

ADD_EXECUTABLE(
        cJsonTest
        cJSON/cJSON.c
        cJSON/cJSON_Utils.c
        seniverse_weather_parse/src/seniverse_cJson_utils.c
        seniverse_weather_parse/src/seniverse_status.c
        seniverse_weather_parse/src/seniverse_weather_location.c
        seniverse_weather_parse/src/seniverse_weather_now.c
        seniverse_weather_parse/src/seniverse_weather_daily.c
        seniverse_weather_parse/src/seniverse_weather_hourly.c
        seniverse_weather_parse/src/seniverse_weather.c
        seniverse_weather_test/src/test_weather_now.c
        seniverse_weather_test/src/test_weather_daily.c
        seniverse_weather_test/src/test_weather_hourly.c
        test.c)