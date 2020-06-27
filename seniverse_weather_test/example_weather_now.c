#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "example_weather_now.h"

#define MAX_STRING_OBJ_BUFFER_LEN 32
/*
API: https://api.seniverse.com/v3/weather/now.json?key=your_api_key&location=beijing&language=zh-Hans&unit=c

参数名          类型        默认值        必须         备注
key            String     无            是           你的 API 密钥
location       Location   无            是           所查询的位置
language       Language   zh-Hans       否           语言
unit           Unit       c             否           单位

返回结果:
{
  "results": [
    {
      "location": {
        "id": "C23NB62W20TF",
        "name": "西雅图",
        "country": "US",
        "path": "西雅图,华盛顿州,美国",
        "timezone": "America/Los_Angeles",
        "timezone_offset": "-07:00"
      },
      "now": {
        "text": "多云", //天气现象文字
        "code": "4", //天气现象代码
        "temperature": "14", //温度，单位为c摄氏度或f华氏度
        "feels_like": "14", //体感温度，单位为c摄氏度或f华氏度
        "pressure": "1018", //气压，单位为mb百帕或in英寸
        "humidity": "76", //相对湿度，0~100，单位为百分比
        "visibility": "16.09", //能见度，单位为km公里或mi英里
        "wind_direction": "西北", //风向文字
        "wind_direction_degree": "340", //风向角度，范围0~360，0为正北，90为正东，180为正南，270为正西
        "wind_speed": "8.05", //风速，单位为km/h公里每小时或mph英里每小时
        "wind_scale": "2", //风力等级，请参考：http://baike.baidu.com/view/465076.htm
        "clouds": "90", //云量，单位%，范围0~100，天空被云覆盖的百分比 #目前不支持中国城市#
        "dew_point": "-12" //露点温度，请参考：http://baike.baidu.com/view/118348.htm #目前不支持中国城市#
      },
      "last_update": "2015-09-25T22:45:00-07:00" //数据更新时间（该城市的本地时间）
    }
  ]
}
*/
const char *weather_now_example = "\
\r\n\r\n\
{\
\"results\": [\
{\
\"location\": {\
\"id\": \"C23NB62W20TF\",\
\"name\": \"西雅图\",\
\"country\": \"US\",\
\"path\": \"西雅图,华盛顿州,美国\",\
\"timezone\": \"America/Los_Angeles\",\
\"timezone_offset\": \"-07:00\"\
},\
\"now\": {\
\"text\": \"多云\",\
\"code\": \"4\",\
\"temperature\": \"14\",\
\"feels_like\": \"14\",\
\"pressure\": \"1018\",\
\"humidity\": \"76\",\
\"visibility\": \"16.09\",\
\"wind_direction\": \"西北\",\
\"wind_direction_degree\": \"340\",\
\"wind_speed\": \"8.05\",\
\"wind_scale\": \"2\",\
\"clouds\": \"90\",\
\"dew_point\": \"-12\"\
},\
\"last_update\": \"2015-09-25T22:45:00-07:00\"\
}\
]\
}\
";

const char *example_real = "\n\n{\"results\":[{\"location\":{\"id\":\"WX4FBXXFKE4F\",\"name\":\"北京\",\"country\":\"CN\",\"path\":\"北京,北京,中国\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"多云\",\"code\":\"4\",\"temperature\":\"27\"},\"last_update\":\"2020-06-28T21:00:00+08:00\"}]}";

static int parse_object_string_value(cJSON *obj, char *key, char *value, int len)
{
    cJSON *obj_item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsString(obj_item) && (obj_item->valuestring != NULL)) {
        if (value)
            snprintf(value, len, "%s", obj_item->valuestring);
    } else {
        printf("Error in get item %s: [%s]\n", key, cJSON_GetErrorPtr());
        return -1;
    }
    return 0;
}

static int parse_object_string_to_int(cJSON *obj, char *key)
{
    char buffer[MAX_STRING_OBJ_BUFFER_LEN];
    int ret = 0;

    if (!parse_object_string_value(obj, key, buffer, WEATHER_NOW_SUMMARY_MAX_LEN))
        ret = atoi(buffer);
    return ret;
}

static float parse_object_string_to_float(cJSON *obj, char *key)
{
    char buffer[MAX_STRING_OBJ_BUFFER_LEN];
    float ret = 0;
    if (!parse_object_string_value(obj, key, buffer, WEATHER_NOW_SUMMARY_MAX_LEN))
        ret = atof(buffer);
    return ret;
}

static int parse_weather_now_object(cJSON *json_now, struct weather_now *now)
{
    // Get the current weather data from the now object
    if (json_now == NULL) {
        printf("json_now is null\n");
        return -1;
    }

    parse_object_string_value(json_now, "text", now->summary, WEATHER_NOW_SUMMARY_MAX_LEN);
    now->code = parse_object_string_to_float(json_now, "code");
    now->temperature = parse_object_string_to_float(json_now, "temperature");
    now->feels_like = parse_object_string_to_float(json_now, "feels_like");
    now->pressure = parse_object_string_to_float(json_now, "pressure");
    now->humidity = parse_object_string_to_float(json_now, "humidity");
    now->visibility = parse_object_string_to_float(json_now, "visibility");
    parse_object_string_value(json_now, "wind_direction", now->wind_direction, WEATHER_NOW_SUMMARY_MAX_LEN);
    now->wind_direction_degree = parse_object_string_to_float(json_now, "wind_direction_degree");
    now->wind_speed = parse_object_string_to_float(json_now, "wind_speed");
    now->wind_scale = parse_object_string_to_float(json_now, "wind_scale");
    now->clouds = parse_object_string_to_float(json_now, "clouds");
    now->dew_point = parse_object_string_to_float(json_now, "dew_point");
    return 0;
}

int parse_weather_now(const char *buf, struct weather_now *now)
{
        // Data can be found after the HTTP header, get te offset to get the data
    char* data_offset = strstr(buf, "\n");

    printf("get resp: %s\n", data_offset);

    cJSON *json = cJSON_Parse(data_offset);

    if (json == NULL) {
        printf("Error in cJSON_Parse: [%s]\n", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *json_results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (json_results == NULL) {
        printf("Error in get item result: [%s]\n", cJSON_GetErrorPtr());
    }

    int results_array_size = cJSON_GetArraySize(json_results);

    printf("results item num: %d\n", results_array_size);

    for(int cnt = 0; cnt < results_array_size; cnt++)
    {
        cJSON *array_sub = cJSON_GetArrayItem(json_results, cnt);
        if(array_sub == NULL)
        {
            continue;
        }

        cJSON *json_currently = NULL;
        if((json_currently = cJSON_GetObjectItem(array_sub, "now")) == NULL)
        {
            printf("Could not find object now\n");
            if (json)
                cJSON_Delete(json);
            return -1;
        }
        parse_weather_now_object(json_currently, now);

        cJSON *json_last_update = cJSON_GetObjectItemCaseSensitive(array_sub, "last_update");
        if (cJSON_IsString(json_last_update) && (json_last_update->valuestring != NULL)) {
            snprintf(now->last_update, WEATHER_NOW_UPDATE_TIME_MAX_LEN, "%s", json_last_update->valuestring);
        }
    }
    if (json)
        cJSON_Delete(json);
    return 0;
}

int dump_weather_now(const struct weather_now *now)
{
    printf("Weather Now: %s\n", now->last_update);
    printf("summary: %s\n", now->summary);
    printf("wind_direction: %s\n", now->wind_direction);

    printf("temperature: %f\n", now->temperature);
    printf("feels_like: %f\n", now->feels_like);
    printf("pressure: %f\n", now->pressure);
    printf("visibility: %f\n", now->visibility);
    printf("wind_speed: %f\n", now->wind_speed);
    printf("wind_scale: %f\n", now->wind_scale);
    printf("dew_point: %f\n", now->dew_point);
    printf("code: %f\n", now->code);
    printf("wind_direction_degree: %f\n", now->wind_direction_degree);
    printf("clouds: %f\n", now->clouds);
    printf("humidity: %f\n", now->humidity);
}