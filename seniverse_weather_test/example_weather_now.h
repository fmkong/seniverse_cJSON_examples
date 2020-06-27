#ifndef EXAMPLE_WEATHER_NOW
#define EXAMPLE_WEATHER_NOW

#include <stdint.h>
/*
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

#define WEATHER_NOW_SUMMARY_MAX_LEN      16
#define WEATHER_NOW_UPDATE_TIME_MAX_LEN  32

struct weather_now {
    uint8_t last_update[WEATHER_NOW_UPDATE_TIME_MAX_LEN];
    uint8_t summary[WEATHER_NOW_SUMMARY_MAX_LEN];
    uint8_t wind_direction[WEATHER_NOW_SUMMARY_MAX_LEN];
    float temperature;
    float feels_like;
    float pressure;
    float visibility;
    float wind_speed;
    float wind_scale;
    float dew_point;
    float code;
    float wind_direction_degree;
    float clouds;
    float humidity;
};

extern const char *weather_now_example;
extern const char *example_real;

int parse_weather_now(const char *buf, struct weather_now *now);
int dump_weather_now(const struct weather_now *now);
#endif