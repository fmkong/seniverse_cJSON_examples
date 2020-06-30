#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "seniverse_weather.h"
#include "seniverse_cJson_utils.h"
#include "test_weather_location.h"

/*
#请求地址示例
https://api.seniverse.com/v3/weather/hourly.json?key=S-nc7Ea36Sthm8mGn&location=beijing&language=zh-Hans&unit=c&start=0&hours=24

#参数
参数名        类型      默认值      必须      备注
key         String    无          是        你的API密钥
location    Location  无          是        所查询的位置
language    Language  zh-Hans     否        语言
unit        Unit      c           否        单位
start       Int       0           否        起始时间（0 代表这个小时，1 代表下个小时）
hours       Int       权限允许的最多小时数    否  小时数

#返回结果
{
  "results": [{
    "location": {
      "id": "WX4FBXXFKE4F",
      "name": "北京",
      "country": "CN",
      "path": "北京,北京,中国",
      "timezone": "Asia/Shanghai",
      "timezone_offset": "+08:00"
    },
    "hourly": [{           //逐小时天气预报数组，数量可由start和hours参数控制，最多24个对象。
      "time": "2016-02-19T14:00:00+08:00",  //时间
      "text": "多云",      //天气现象文字
      "code": "4",        //天气现象代码
      "temperature": "7",     //温度，单位为c摄氏度或f华氏度
      "humidity": "35",       //相对湿度，0~100，单位为百分比
      "wind_direction": "北", //风向
      "wind_speed": "18.0"    //风速，单位为km/h公里每小时或mph英里每小时
    }, {                  //下一个小时预报
      "time": "2016-02-19T15:00:00+08:00",
      "text": "多云",
      "code": "4",
      "temperature": "6",
      "humidity": "37",
      "wind_direction": "西北",
      "wind_speed": "12.0"
    }, {
      ...                 //后面的就省略了
    }]
  }]
}
*/

const char *weather_hourly_example = "\
\r\n\r\n\
{\
  \"results\": [{\
    \"location\": {\
      \"id\": \"WX4FBXXFKE4F\",\
      \"name\": \"北京\",\
      \"country\": \"CN\",\
      \"path\": \"北京,北京,中国\",\
      \"timezone\": \"Asia/Shanghai\",\
      \"timezone_offset\": \"+08:00\"\
    },\
    \"hourly\": [{\
      \"time\": \"2016-02-19T14:00:00+08:00\",\
      \"text\": \"多云\",\
      \"code\": \"4\",\
      \"temperature\": \"7\",\
      \"humidity\": \"35\",\
      \"wind_direction\": \"北\",\
      \"wind_speed\": \"18.0\"\
    }, {\
      \"time\": \"2016-02-19T15:00:00+08:00\",\
      \"text\": \"多云\",\
      \"code\": \"4\",\
      \"temperature\": \"6\",\
      \"humidity\": \"37\",\
      \"wind_direction\": \"西北\",\
      \"wind_speed\": \"12.0\"\
    }]\
  }]\
}\
";

#define KEY "S-nc7Ea36Sthm8mGn"
#define LOCATION "beijing"

int test_weather_hourly()
{
    struct seniverse_weather_obj *hourly = creat_weather_data(SENIVERSE_WEATHER_HOURLY, 3);
    int count = 0;
    char url[1024];

    count = seniverse_get_url_api(SENIVERSE_WEATHER_HOURLY, url, 1024, KEY, LOCATION, SENIVERSE_LANGUAGE_CHINESE_SIMP, SENIVERSE_UNIT_METRIC, 0, 24);

    /* print the version */
    printf("\n\n\n>>>>>>>weather hourly test.>>>>>>>>>>\n");
    printf("get url %s,  %d\n", url, count);
    seniverse_parse_resp(SENIVERSE_WEATHER_HOURLY, weather_hourly_example, hourly, &count);
    printf("weather hourly data has %d items.\n", count);
    dump_weather_location(&hourly->common.location);
    dump_weather_hourly(&hourly->hourly);
    destroy_weather_data(hourly);
    hourly = NULL;
    return 0;
}