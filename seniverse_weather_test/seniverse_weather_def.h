
#ifndef __SENIVERSE_WEATHER_DEF__
#define __SENIVERSE_WEATHER_DEF__

enum seniverse_weather_code {
    Sunny                      = 0, //晴（国内城市白天晴）
    Clear                      = 1, //晴（国内城市夜晚晴）
    Fair_Daytime               = 2, //晴（国外城市白天晴）
    Fair_Night                 = 3, //晴（国外城市夜晚晴）
    Cloudy                     = 4, //多云
    Partly_Cloudy_Daytime      = 5, //晴间多云
    Partly_Cloudy_Night        = 6, //晴间多云
    Mostly_Cloudy_Daytime      = 7, //大部多云
    Mostly_Cloudy_Night        = 8, //大部多云
    Overcast                   = 9, //阴
    Shower                     = 10, //阵雨
    Thundershower              = 11, //雷阵雨
    Thundershower_with_Hail    = 12, //雷阵雨伴有冰雹
    Light_Rain                 = 13, //小雨
    Moderate_Rain              = 14, //中雨
    Heavy_Rain                 = 15, //大雨
    Storm                      = 16, //暴雨
    Heavy_Storm                = 17, //大暴雨
    Severe_Storm               = 18, //特大暴雨
    Ice_Rain                   = 19, //冻雨
    Sleet                      = 20, //雨夹雪
    Snow_Flurry                = 21, //阵雪
    Light_Snow                 = 22, //小雪
    Moderate_Snow              = 23, //中雪
    Heavy_Snow                 = 24, //大雪
    Snowstorm                  = 25, //暴雪
    Dust                       = 26, //浮尘
    Sand                       = 27, //扬沙
    Duststorm                  = 28, //沙尘暴
    Sandstorm                  = 29, //强沙尘暴
    Foggy                      = 30, //雾
    Haze                       = 31, //霾
    Windy                      = 32, //风
    Blustery                   = 33, //大风
    Hurricane                  = 34, //飓风
    Tropical_Storm             = 35, //热带风暴
    Tornado                    = 36, //龙卷风
    Cold                       = 37, //冷
    Hot                        = 38, //热
    Unknown                    = 99, //未知
};

#endif