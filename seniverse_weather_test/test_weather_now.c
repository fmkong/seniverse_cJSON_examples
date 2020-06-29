#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "seniverse_weather.h"
#include "seniverse_cJson_utils.h"
#include "test_weather_location.h"

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
static const char *weather_now_example = "\
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

static const char *example_real = "\n\n{\"results\":[{\"location\":{\"id\":\"WX4FBXXFKE4F\",\"name\":\"北京\",\"country\":\"CN\",\"path\":\"北京,北京,中国\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"多云\",\"code\":\"4\",\"temperature\":\"27\"},\"last_update\":\"2020-06-28T21:00:00+08:00\"}]}";

static int dump_weather_now(const struct weather_now *now)
{
    dump_weather_location(&(now->common.location));
    printf("weather now: %s\n", now->common.last_update);
    printf("\t summary: %s\n", now->items->summary);
    printf("\t wind_direction: %s\n", now->items->wind_direction);
    printf("\t temperature: %f\n", now->items->temperature);
    printf("\t feels_like: %f\n", now->items->feels_like);
    printf("\t pressure: %f\n", now->items->pressure);
    printf("\t visibility: %f\n", now->items->visibility);
    printf("\t wind_speed: %f\n", now->items->wind_speed);
    printf("\t wind_scale: %f\n", now->items->wind_scale);
    printf("\t dew_point: %f\n", now->items->dew_point);
    printf("\t code: %d\n", now->items->code);
    printf("\t wind_direction_degree: %f\n", now->items->wind_direction_degree);
    printf("\t clouds: %f\n", now->items->clouds);
    printf("\t humidity: %f\n", now->items->humidity);
}

int test_weather_now()
{
    struct seniverse_weather_obj *now = creat_weather_data(SENIVERSE_WEATHER_NOW, 1);
    int count = 0;
    /* print the version */
    printf("Version: %s\n", cJSON_Version());
    printf("\n\n\n>>>>>>>weather now test.>>>>>>>>>>\n");

    seniverse_parse_resp(SENIVERSE_WEATHER_NOW, weather_now_example, now, &count);
    printf("weather now data has %d items.\n", count);
    dump_weather_now(&now->now);
    destroy_weather_data(now);
    now = NULL;
}