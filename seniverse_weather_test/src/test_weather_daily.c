#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"
#include "seniverse_weather.h"
#include "seniverse_cJson_utils.h"
#include "test_weather_location.h"

/*
#API:
北京今天和未来 4 天的预报 https://api.seniverse.com/v3/weather/daily.json?key=S-nc7Ea36Sthm8mGn&location=beijing&language=zh-Hans&unit=c&start=0&days=5
北京的昨日天气、今天和未来 3 天的预报（昨日天气独立于逐日天气预报，需要单独购买） https://api.seniverse.com/v3/weather/daily.json?key=S-nc7Ea36Sthm8mGn&location=beijing&language=zh-Hans&unit=c&start=-1&days=5

#参数
参数名          类型            默认值              必须            备注
key            String         无                是              你的 API 密钥
location       Location       无                是              所查询的位置
language       Language       zh-Hans           否              语言
unit           Unit           c                 否              单位
start          Start          0                 否              起始时间
days           Int            权限允许的最多天数   否              天数

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
    "daily": [{                          //返回指定days天数的结果
      "date": "2015-09-20",              //日期
      "text_day": "多云",                //白天天气现象文字
      "code_day": "4",                  //白天天气现象代码
      "text_night": "晴",               //晚间天气现象文字
      "code_night": "0",                //晚间天气现象代码
      "high": "26",                     //当天最高温度
      "low": "17",                      //当天最低温度
      "precip": "0",                    //降水概率，范围0~100，单位百分比（目前仅支持国外城市）
      "wind_direction": "",             //风向文字
      "wind_direction_degree": "255",   //风向角度，范围0~360
      "wind_speed": "9.66",             //风速，单位km/h（当unit=c时）、mph（当unit=f时）
      "wind_scale": "",                 //风力等级
      "rainfall": "0.0",                //降水量，单位mm
      "humidity": "76"                  //相对湿度，0~100，单位为百分比
    }, {
      "date": "2015-09-21",
      "text_day": "晴",
      "code_day": "0",
      "text_night": "晴",
      "code_night": "0",
      "high": "27",
      "low": "17",
      "precip": "0",
      "wind_direction": "",
      "wind_direction_degree": "157",
      "wind_speed": "17.7",
      "wind_scale": "3",
      "rainfall": "0.0",
      "humidity": "76"
    }, {
      ...                               //更多返回结果
    }],
    "last_update": "2015-09-20T18:00:00+08:00" //数据更新时间（该城市的本地时间）
  }]
}
*/

const char *weather_daily_example = "\
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
    \"daily\": [{\
      \"date\": \"2015-09-20\",\
      \"text_day\": \"多云\",\
      \"code_day\": \"4\",\
      \"text_night\": \"晴\",\
      \"code_night\": \"0\",\
      \"high\": \"26\",\
      \"low\": \"17\",\
      \"precip\": \"0\",\
      \"wind_direction\": \"\",\
      \"wind_direction_degree\": \"255\",\
      \"wind_speed\": \"9.66\",\
      \"wind_scale\": \"\",\
      \"rainfall\": \"0.0\",\
      \"humidity\": \"76\"\
    }, {\
      \"date\": \"2015-09-21\",\
      \"text_day\": \"晴\",\
      \"code_day\": \"0\",\
      \"text_night\": \"晴\",\
      \"code_night\": \"0\",\
      \"high\": \"27\",\
      \"low\": \"17\",\
      \"precip\": \"0\",\
      \"wind_direction\": \"\",\
      \"wind_direction_degree\": \"157\",\
      \"wind_speed\": \"17.7\",\
      \"wind_scale\": \"3\",\
      \"rainfall\": \"0.0\",\
      \"humidity\": \"76\"\
    }],\
    \"last_update\": \"2015-09-20T18:00:00+08:00\"\
  }]\
}\
";

#define KEY "S-nc7Ea36Sthm8mGn"
#define LOCATION "beijing"

int test_weather_daily()
{
    struct seniverse_weather_obj *daily = creat_weather_data(SENIVERSE_WEATHER_DAILY, 3);
    int count = 0;
    char url[1024];

    count = seniverse_get_url_api(SENIVERSE_WEATHER_DAILY, url, 1024, KEY, LOCATION, SENIVERSE_LANGUAGE_CHINESE_SIMP, SENIVERSE_UNIT_METRIC, 0, 5);

    /* print the version */
    printf("\n\n\n>>>>>>>weather daily test.>>>>>>>>>>\n");
    printf("get url %s,  %d\n", url, count);

    seniverse_parse_resp(SENIVERSE_WEATHER_DAILY, weather_daily_example, daily, &count);
    printf("weather daily data has %d items.\n", count);
    dump_weather_location(&daily->common.location);
    dump_weather_daily(&daily->daily);
    destroy_weather_data(daily);
    daily = NULL;
    return 0;
}