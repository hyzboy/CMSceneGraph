#include <hgl/geo/GeoLocation.h>
#include <cmath>

namespace hgl::geo
{
    namespace
    {
        // 以下所有数据均来自于Github Copilot自动生成，仅供参考。若有错误，概不负责，请自行修正。

        static const CountryInfo kCountries[] =
        {
            { CountryID::PRC,    Continent::Asia,        CityID::BeiJing,      "China",                   U16_TEXT("中国") },
            { CountryID::USA,    Continent::NorthAmerica,CityID::WashingtonDC, "United States",           U16_TEXT("美国") },
            { CountryID::UK,     Continent::Europe,      CityID::London,       "United Kingdom",          U16_TEXT("英国") },

            { CountryID::CAN,    Continent::NorthAmerica,CityID::Ottawa,       "Canada",                  U16_TEXT("加拿大") },
            { CountryID::DEU,    Continent::Europe,      CityID::Berlin,       "Germany",                 U16_TEXT("德国") },
            { CountryID::FRA,    Continent::Europe,      CityID::Paris,        "France",                  U16_TEXT("法国") },
            { CountryID::JPN,    Continent::Asia,        CityID::Tokyo,        "Japan",                   U16_TEXT("日本") },
            { CountryID::KOR,    Continent::Asia,        CityID::Seoul,        "South Korea",             U16_TEXT("韩国") },
            { CountryID::IND,    Continent::Asia,        CityID::Delhi,        "India",                   U16_TEXT("印度") },
            { CountryID::RUS,    Continent::Europe,      CityID::Moscow,       "Russia",                  U16_TEXT("俄罗斯") },
            { CountryID::AUS,    Continent::Oceania,     CityID::Canberra,     "Australia",               U16_TEXT("澳大利亚") },
            { CountryID::NZL,    Continent::Oceania,     CityID::Wellington,   "New Zealand",             U16_TEXT("新西兰") },
            { CountryID::BRA,    Continent::SouthAmerica,CityID::Brasilia,     "Brazil",                  U16_TEXT("巴西") },
            { CountryID::MEX,    Continent::NorthAmerica,CityID::MexicoCity,   "Mexico",                  U16_TEXT("墨西哥") },
            { CountryID::ESP,    Continent::Europe,      CityID::Madrid,       "Spain",                   U16_TEXT("西班牙") },
            { CountryID::ITA,    Continent::Europe,      CityID::Rome,         "Italy",                   U16_TEXT("意大利") },
            { CountryID::NLD,    Continent::Europe,      CityID::Unknow,       "Netherlands",             U16_TEXT("荷兰") },
            { CountryID::SWE,    Continent::Europe,      CityID::Unknow,       "Sweden",                  U16_TEXT("瑞典") },
            { CountryID::NOR,    Continent::Europe,      CityID::Unknow,       "Norway",                  U16_TEXT("挪威") },
            { CountryID::DNK,    Continent::Europe,      CityID::Unknow,       "Denmark",                 U16_TEXT("丹麦") },
            { CountryID::FIN,    Continent::Europe,      CityID::Unknow,       "Finland",                 U16_TEXT("芬兰") },
            { CountryID::POL,    Continent::Europe,      CityID::Unknow,       "Poland",                  U16_TEXT("波兰") },
            { CountryID::CZE,    Continent::Europe,      CityID::Unknow,       "Czechia",                 U16_TEXT("捷克") },
            { CountryID::AUT,    Continent::Europe,      CityID::Unknow,       "Austria",                 U16_TEXT("奥地利") },
            { CountryID::CHE,    Continent::Europe,      CityID::Unknow,       "Switzerland",             U16_TEXT("瑞士") },
            { CountryID::BEL,    Continent::Europe,      CityID::Unknow,       "Belgium",                 U16_TEXT("比利时") },
            { CountryID::PRT,    Continent::Europe,      CityID::Unknow,       "Portugal",                U16_TEXT("葡萄牙") },
            { CountryID::TUR,    Continent::Asia,        CityID::Ankara,       "Turkey",                  U16_TEXT("土耳其") },
            { CountryID::GRC,    Continent::Europe,      CityID::Athens,       "Greece",                  U16_TEXT("希腊") },
            { CountryID::EGY,    Continent::Africa,      CityID::Cairo,        "Egypt",                   U16_TEXT("埃及") },
            { CountryID::ZAF,    Continent::Africa,      CityID::CapeTown,     "South Africa",            U16_TEXT("南非") },
            { CountryID::NGA,    Continent::Africa,      CityID::Abuja,        "Nigeria",                 U16_TEXT("尼日利亚") },
            { CountryID::GHA,    Continent::Africa,      CityID::Accra,        "Ghana",                   U16_TEXT("加纳") },
            { CountryID::KEN,    Continent::Africa,      CityID::Nairobi,      "Kenya",                   U16_TEXT("肯尼亚") },
            { CountryID::MAR,    Continent::Africa,      CityID::Rabat,        "Morocco",                 U16_TEXT("摩洛哥") },
            { CountryID::SAU,    Continent::Asia,        CityID::Riyadh,       "Saudi Arabia",            U16_TEXT("沙特阿拉伯") },
            { CountryID::ARE,    Continent::Asia,        CityID::AbuDhabi,     "United Arab Emirates",    U16_TEXT("阿联酋") },
            { CountryID::ISR,    Continent::Asia,        CityID::Jerusalem,    "Israel",                  U16_TEXT("以色列") },
            { CountryID::IRN,    Continent::Asia,        CityID::Tehran,       "Iran",                    U16_TEXT("伊朗") },
            { CountryID::IRQ,    Continent::Asia,        CityID::Baghdad,      "Iraq",                    U16_TEXT("伊拉克") },
            { CountryID::PAK,    Continent::Asia,        CityID::Islamabad,    "Pakistan",                U16_TEXT("巴基斯坦") },
            { CountryID::IDN,    Continent::Asia,        CityID::Jakarta,      "Indonesia",               U16_TEXT("印度尼西亚") },
            { CountryID::VNM,    Continent::Asia,        CityID::Hanoi,        "Vietnam",                 U16_TEXT("越南") },
            { CountryID::THA,    Continent::Asia,        CityID::Bangkok,      "Thailand",                U16_TEXT("泰国") },
            { CountryID::MYS,    Continent::Asia,        CityID::KualaLumpur,  "Malaysia",                U16_TEXT("马来西亚") },
            { CountryID::SGP,    Continent::Asia,        CityID::Singapore,    "Singapore",               U16_TEXT("新加坡") },
            { CountryID::PHL,    Continent::Asia,        CityID::Manila,       "Philippines",             U16_TEXT("菲律宾") },
            { CountryID::KHM,    Continent::Asia,        CityID::PhnomPenh,    "Cambodia",                U16_TEXT("柬埔寨") },
            { CountryID::LAO,    Continent::Asia,        CityID::Vientiane,    "Laos",                    U16_TEXT("老挝") },
            { CountryID::MMR,    Continent::Asia,        CityID::Yangon,       "Myanmar",                 U16_TEXT("缅甸") },
            { CountryID::NPL,    Continent::Asia,        CityID::Kathmandu,    "Nepal",                   U16_TEXT("尼泊尔") },
            { CountryID::BGD,    Continent::Asia,        CityID::Dhaka,        "Bangladesh",              U16_TEXT("孟加拉国") },
            { CountryID::LKA,    Continent::Asia,        CityID::Colombo,      "Sri Lanka",               U16_TEXT("斯里兰卡") },
            { CountryID::ARE_QA, Continent::Asia,        CityID::Doha,         "Qatar (alias)",          U16_TEXT("卡塔尔(别名)") },
            { CountryID::QAT,    Continent::Asia,        CityID::Doha,         "Qatar",                   U16_TEXT("卡塔尔") },
            { CountryID::KWT,    Continent::Asia,        CityID::KuwaitCity,   "Kuwait",                  U16_TEXT("科威特") },
            { CountryID::OMN,    Continent::Asia,        CityID::Muscat,       "Oman",                    U16_TEXT("阿曼") },
            { CountryID::JOR,    Continent::Asia,        CityID::Amman,        "Jordan",                  U16_TEXT("约旦") },
            { CountryID::LBN,    Continent::Asia,        CityID::Beirut,       "Lebanon",                 U16_TEXT("黎巴嫩") },
            { CountryID::SDN,    Continent::Africa,      CityID::Khartoum,     "Sudan",                   U16_TEXT("苏丹") },
            { CountryID::ETH,    Continent::Africa,      CityID::AddisAbaba,   "Ethiopia",                U16_TEXT("埃塞俄比亚") },
            { CountryID::DZA,    Continent::Africa,      CityID::Algiers,      "Algeria",                 U16_TEXT("阿尔及利亚") },
            { CountryID::TUN,    Continent::Africa,      CityID::Tunis,        "Tunisia",                 U16_TEXT("突尼斯") },
            { CountryID::ARG,    Continent::SouthAmerica,CityID::BuenosAires,  "Argentina",               U16_TEXT("阿根廷") },
            { CountryID::CHL,    Continent::SouthAmerica,CityID::Santiago,     "Chile",                   U16_TEXT("智利") },
            { CountryID::COL,    Continent::SouthAmerica,CityID::Bogota,       "Colombia",                U16_TEXT("哥伦比亚") },
            { CountryID::PER,    Continent::SouthAmerica,CityID::Lima,         "Peru",                    U16_TEXT("秘鲁") },
            { CountryID::VEN,    Continent::SouthAmerica,CityID::Caracas,      "Venezuela",               U16_TEXT("委内瑞拉") },
            { CountryID::URY,    Continent::SouthAmerica,CityID::Montevideo,   "Uruguay",                 U16_TEXT("乌拉圭") },
            { CountryID::PRY,    Continent::SouthAmerica,CityID::Asuncion,     "Paraguay",                U16_TEXT("巴拉圭") },
            { CountryID::BOL,    Continent::SouthAmerica,CityID::LaPaz,        "Bolivia",                 U16_TEXT("玻利维亚") },
            { CountryID::ECU,    Continent::SouthAmerica,CityID::Quito,        "Ecuador",                 U16_TEXT("厄瓜多尔") },
            { CountryID::CRI,    Continent::NorthAmerica,CityID::Unknow,       "Costa Rica",              U16_TEXT("哥斯达黎加") },
            { CountryID::PAN,    Continent::NorthAmerica,CityID::Unknow,       "Panama",                  U16_TEXT("巴拿马") },
            { CountryID::CUB,    Continent::NorthAmerica,CityID::Unknow,       "Cuba",                    U16_TEXT("古巴") },
            { CountryID::DOM,    Continent::NorthAmerica,CityID::Unknow,       "Dominican Republic",      U16_TEXT("多米尼加") },
            { CountryID::JAM,    Continent::NorthAmerica,CityID::Unknow,       "Jamaica",                 U16_TEXT("牙买加") },
            { CountryID::ISL,    Continent::Europe,      CityID::Reykjavik,    "Iceland",                 U16_TEXT("冰岛") },
            { CountryID::IRL,    Continent::Europe,      CityID::Dublin,       "Ireland",                 U16_TEXT("爱尔兰") },
            { CountryID::UKR,    Continent::Europe,      CityID::Kyiv,         "Ukraine",                 U16_TEXT("乌克兰") },
            { CountryID::BLR,    Continent::Europe,      CityID::Minsk,        "Belarus",                 U16_TEXT("白俄罗斯") },
            { CountryID::ROU,    Continent::Europe,      CityID::Bucharest,    "Romania",                 U16_TEXT("罗马尼亚") },
            { CountryID::BGR,    Continent::Europe,      CityID::Sofia,        "Bulgaria",                U16_TEXT("保加利亚") },
            { CountryID::HUN,    Continent::Europe,      CityID::Budapest,     "Hungary",                 U16_TEXT("匈牙利") },
            { CountryID::SRB,    Continent::Europe,      CityID::Belgrade,     "Serbia",                  U16_TEXT("塞尔维亚") },
            { CountryID::HRV,    Continent::Europe,      CityID::Zagreb,       "Croatia",                 U16_TEXT("克罗地亚") },
            { CountryID::SVN,    Continent::Europe,      CityID::Ljubljana,    "Slovenia",                U16_TEXT("斯洛文尼亚") },
            { CountryID::SVK,    Continent::Europe,      CityID::Bratislava,   "Slovakia",                U16_TEXT("斯洛伐克") },
            { CountryID::EST,    Continent::Europe,      CityID::Tallinn,      "Estonia",                 U16_TEXT("爱沙尼亚") },
            { CountryID::LVA,    Continent::Europe,      CityID::Riga,         "Latvia",                  U16_TEXT("拉脱维亚") },
            { CountryID::LTU,    Continent::Europe,      CityID::Vilnius,      "Lithuania",               U16_TEXT("立陶宛") },
            { CountryID::MLT,    Continent::Europe,      CityID::Valletta,     "Malta",                   U16_TEXT("马耳他") },
            { CountryID::CYP,    Continent::Europe,      CityID::Nicosia,      "Cyprus",                  U16_TEXT("塞浦路斯") },
            { CountryID::GEO,    Continent::Asia,        CityID::Tbilisi,      "Georgia",                 U16_TEXT("格鲁吉亚") },
            { CountryID::KAZ,    Continent::Asia,        CityID::Astana,       "Kazakhstan",              U16_TEXT("哈萨克斯坦") },
            { CountryID::UZB,    Continent::Asia,        CityID::Tashkent,     "Uzbekistan",              U16_TEXT("乌兹别克斯坦") },
            { CountryID::AZE,    Continent::Asia,        CityID::Baku,         "Azerbaijan",              U16_TEXT("阿塞拜疆") },
            { CountryID::ARM,    Continent::Asia,        CityID::Yerevan,      "Armenia",                 U16_TEXT("亚美尼亚") },
            { CountryID::MNG,    Continent::Asia,        CityID::Ulaanbaatar,  "Mongolia",                U16_TEXT("蒙古") },
            { CountryID::BHR,    Continent::Asia,        CityID::Manama,       "Bahrain",                 U16_TEXT("巴林") },
        };


        static CityInfo kCities[] =
        {
            // China - major cities (all UTC+8 => 480 minutes)
            { CountryID::PRC, Continent::Asia, CityID::BeiJing,      "Beijing",            U16_TEXT("北京"),            39.9042f, 116.4074f, 44.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ShangHai,     "Shanghai",           U16_TEXT("上海"),            31.2304f, 121.4737f, 4.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::TianJin,      "Tianjin",            U16_TEXT("天津"),            39.3434f, 117.3616f, 5.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ChongQing,    "Chongqing",          U16_TEXT("重庆"),            29.5630f, 106.5516f, 350.0f, 480 },

            { CountryID::PRC, Continent::Asia, CityID::GuangZhou,    "Guangzhou",          U16_TEXT("广州"),            23.1291f, 113.2644f, 21.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ShenZhen,     "Shenzhen",           U16_TEXT("深圳"),            22.5431f, 114.0579f, 6.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ChengDu,      "Chengdu",            U16_TEXT("成都"),            30.5728f, 104.0668f, 500.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::HangZhou,     "Hangzhou",           U16_TEXT("杭州"),            30.2741f, 120.1551f, 9.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::NanJing,      "Nanjing",            U16_TEXT("南京"),            32.0603f, 118.7969f, 20.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::WuHan,        "Wuhan",              U16_TEXT("武汉"),            30.5928f, 114.3055f, 37.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::XiAn,         "Xi'an",              U16_TEXT("西安"),            34.3416f, 108.9398f, 400.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::SuZhou,       "Suzhou",             U16_TEXT("苏州"),            31.2989f, 120.5853f, 5.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::QingDao,      "Qingdao",            U16_TEXT("青岛"),            36.0671f, 120.3826f, 77.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::JiNan,        "Jinan",              U16_TEXT("济南"),            36.6512f, 117.1201f, 23.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::HeFei,        "Hefei",              U16_TEXT("合肥"),            31.8206f, 117.2272f, 22.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ChangSha,     "Changsha",           U16_TEXT("长沙"),            28.2282f, 112.9388f, 44.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::NanChang,     "Nanchang",           U16_TEXT("南昌"),            28.6829f, 115.8582f, 24.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::FuZhou,       "Fuzhou",             U16_TEXT("福州"),            26.0745f, 119.2965f, 14.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::Xiamen,       "Xiamen",             U16_TEXT("厦门"),            24.4798f, 118.0894f, 10.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::KunMing,      "Kunming",            U16_TEXT("昆明"),            25.0389f, 102.7183f, 1892.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::GuiYang,      "Guiyang",            U16_TEXT("贵阳"),            26.6470f, 106.6302f, 1100.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::LanZhou,      "Lanzhou",            U16_TEXT("兰州"),            36.0611f, 103.8343f, 1518.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::Urumqi,       "Ürümqi",             U16_TEXT("乌鲁木齐"),         43.8256f, 87.6168f, 800.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::HarBin,       "Harbin",             U16_TEXT("哈尔滨"),          45.8038f, 126.5349f, 150.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ChangChun,    "Changchun",          U16_TEXT("长春"),            43.8171f, 125.3235f, 222.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::Shenyang,     "Shenyang",           U16_TEXT("沈阳"),            41.8057f, 123.4315f, 55.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::NingBo,       "Ningbo",             U16_TEXT("宁波"),            29.8683f, 121.5440f, 4.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::Wuxi,         "Wuxi",               U16_TEXT("无锡"),            31.4912f, 120.3119f, 5.0f, 480 },

            { CountryID::PRC, Continent::Asia, CityID::ShiJiaZhuang, "Shijiazhuang",       U16_TEXT("石家庄"),          38.0428f, 114.5149f, 83.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::TaiYuan,      "Taiyuan",            U16_TEXT("太原"),            37.8706f, 112.5489f, 800.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::HuHeHaoTe,    "Hohhot",             U16_TEXT("呼和浩特"),        40.8426f, 111.7490f, 1065.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ZhengZhou,    "Zhengzhou",          U16_TEXT("郑州"),            34.7466f, 113.6254f, 110.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::NanNing,      "Nanning",            U16_TEXT("南宁"),            22.8170f, 108.3669f, 80.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::HaiKou,       "Haikou",             U16_TEXT("海口"),            20.0440f, 110.1983f, 4.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::LaSa,         "Lhasa",              U16_TEXT("拉萨"),             29.6520f,  91.1721f, 3650.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::XiNing,       "Xining",             U16_TEXT("西宁"),            36.6171f, 101.7782f, 2275.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::YinChuan,     "Yinchuan",           U16_TEXT("银川"),            38.4872f, 106.2309f, 1110.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::GuiLin,       "Guilin",             U16_TEXT("桂林"),            25.2742f, 110.2950f, 152.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::DaLian,       "Dalian",             U16_TEXT("大连"),            38.9140f, 121.6147f, 29.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::ZhuHai,       "Zhuhai",             U16_TEXT("珠海"),            22.2707f, 113.5767f, 6.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::SanYa,        "Sanya",              U16_TEXT("三亚"),            18.2528f, 109.5119f, 7.0f, 480 },
            { CountryID::PRC, Continent::Asia, CityID::LiJiang,      "Lijiang",            U16_TEXT("丽江"),            26.8721f, 100.2382f, 2418.0f, 480 },

            // Capitals and notable cities
            { CountryID::USA, Continent::NorthAmerica, CityID::WashingtonDC, "Washington, D.C.",   U16_TEXT("华盛顿"),          38.9072f,  -77.0369f, 7.0f, -300 },
            { CountryID::UK,  Continent::Europe,       CityID::London,       "London",             U16_TEXT("伦敦"),            51.5072f,   -0.1276f, 11.0f, 0 },
            { CountryID::FRA, Continent::Europe,       CityID::Paris,        "Paris",              U16_TEXT("巴黎"),            48.8566f,    2.3522f, 35.0f, 60 },
            { CountryID::DEU, Continent::Europe,       CityID::Berlin,       "Berlin",             U16_TEXT("柏林"),            52.5200f,   13.4050f, 34.0f, 60 },
            { CountryID::ITA, Continent::Europe,       CityID::Rome,         "Rome",               U16_TEXT("罗马"),            41.9028f,   12.4964f, 21.0f, 60 },
            { CountryID::ESP, Continent::Europe,       CityID::Madrid,       "Madrid",             U16_TEXT("马德里"),          40.4168f,   -3.7038f, 667.0f, 60 },
            { CountryID::JPN, Continent::Asia,         CityID::Tokyo,        "Tokyo",              U16_TEXT("东京"),            35.6762f,  139.6503f, 40.0f, 540 },
            { CountryID::KOR, Continent::Asia,         CityID::Seoul,        "Seoul",              U16_TEXT("首尔"),            37.5665f,  126.9780f, 38.0f, 540 },
            { CountryID::IND, Continent::Asia,         CityID::Delhi,        "New Delhi",          U16_TEXT("新德里"),          28.6139f,   77.2090f, 216.0f, 330 },
            { CountryID::RUS, Continent::Europe,       CityID::Moscow,       "Moscow",             U16_TEXT("莫斯科"),          55.7558f,   37.6173f, 156.0f, 180 },
            { CountryID::CAN, Continent::NorthAmerica, CityID::Ottawa,       "Ottawa",             U16_TEXT("渥太华"),          45.4215f,  -75.6972f, 70.0f, -300 },
            { CountryID::AUS, Continent::Oceania,      CityID::Canberra,     "Canberra",           U16_TEXT("堪培拉"),          -35.2809f, 149.1300f, 577.0f, 600 },
            { CountryID::NZL, Continent::Oceania,      CityID::Wellington,   "Wellington",         U16_TEXT("惠灵顿"),          -41.2866f, 174.7756f, 12.0f, 720 },
            { CountryID::BRA, Continent::SouthAmerica, CityID::Brasilia,     "Brasilia",           U16_TEXT("巴西利亚"),        -15.7939f, -47.8828f, 1172.0f, -180 },
            { CountryID::MEX, Continent::NorthAmerica, CityID::MexicoCity,   "Mexico City",        U16_TEXT("墨西哥城"),        19.4326f,  -99.1332f, 2240.0f, -360 },
            { CountryID::TUR, Continent::Asia,         CityID::Ankara,       "Ankara",             U16_TEXT("安卡拉"),          39.9334f,   32.8597f, 938.0f, 180 },
            { CountryID::GRC, Continent::Europe,       CityID::Athens,       "Athens",             U16_TEXT("雅典"),            37.9838f,   23.7275f, 70.0f, 120 },
            { CountryID::EGY, Continent::Africa,       CityID::Cairo,        "Cairo",              U16_TEXT("开罗"),            30.0444f,   31.2357f, 23.0f, 120 },
            { CountryID::ZAF, Continent::Africa,       CityID::Pretoria,     "Pretoria",           U16_TEXT("比勒陀利亚"),      -25.7479f,  28.2293f, 1350.0f, 120 },
            { CountryID::ZAF, Continent::Africa,       CityID::CapeTown,     "Cape Town",          U16_TEXT("开普敦"),          -33.9249f,  18.4241f, 25.0f, 120 },
            { CountryID::SAU, Continent::Asia,         CityID::Riyadh,       "Riyadh",             U16_TEXT("利雅得"),          24.7136f,   46.6753f, 612.0f, 180 },
            { CountryID::ARE, Continent::Asia,         CityID::AbuDhabi,     "Abu Dhabi",          U16_TEXT("阿布扎比"),        24.4539f,   54.3773f, 5.0f, 240 },
            { CountryID::ISR, Continent::Asia,         CityID::Jerusalem,    "Jerusalem",          U16_TEXT("耶路撒冷"),        31.7683f,   35.2137f, 754.0f, 120 },
            { CountryID::IRN, Continent::Asia,         CityID::Tehran,       "Tehran",             U16_TEXT("德黑兰"),          35.6892f,   51.3890f, 1191.0f, 210 },
            { CountryID::IRQ, Continent::Asia,         CityID::Baghdad,      "Baghdad",            U16_TEXT("巴格达"),          33.3152f,   44.3661f, 34.0f, 180 },
            { CountryID::PAK, Continent::Asia,         CityID::Islamabad,    "Islamabad",          U16_TEXT("伊斯兰堡"),        33.6844f,   73.0479f, 540.0f, 300 },
            { CountryID::IDN, Continent::Asia,         CityID::Jakarta,      "Jakarta",            U16_TEXT("雅加达"),          -6.2088f,  106.8456f, 8.0f, 420 },
            { CountryID::VNM, Continent::Asia,         CityID::Hanoi,        "Hanoi",              U16_TEXT("河内"),            21.0278f,  105.8342f, 16.0f, 420 },
            { CountryID::THA, Continent::Asia,         CityID::Bangkok,      "Bangkok",            U16_TEXT("曼谷"),            13.7563f,  100.5018f, 2.0f, 420 },
            { CountryID::MYS, Continent::Asia,         CityID::KualaLumpur,  "Kuala Lumpur",       U16_TEXT("吉隆坡"),          3.1390f,   101.6869f, 21.0f, 480 },
            { CountryID::SGP, Continent::Asia,         CityID::Singapore,    "Singapore",          U16_TEXT("新加坡"),          1.3521f,   103.8198f, 15.0f, 480 },
            { CountryID::PHL, Continent::Asia,         CityID::Manila,       "Manila",             U16_TEXT("马尼拉"),          14.5995f,  120.9842f, 16.0f, 480 },
            { CountryID::PRC, Continent::Asia,         CityID::Taipei,       "Taipei",             U16_TEXT("台北"),            25.0330f,  121.5654f, 10.0f, 480 },
            { CountryID::PRC, Continent::Asia,         CityID::HongKong,     "Hong Kong",          U16_TEXT("香港"),            22.3193f,  114.1694f, 9.0f, 480 },
            { CountryID::KHM, Continent::Asia,         CityID::PhnomPenh,    "Phnom Penh",         U16_TEXT("金边"),            11.5564f,  104.9282f, 12.0f, 420 },
            { CountryID::LAO, Continent::Asia,         CityID::Vientiane,    "Vientiane",          U16_TEXT("万象"),            17.9757f,  102.6331f, 174.0f, 420 },
            { CountryID::MMR, Continent::Asia,         CityID::Yangon,       "Yangon",             U16_TEXT("仰光"),            16.8409f,   96.1735f, 23.0f, 390 },
            { CountryID::NPL, Continent::Asia,         CityID::Kathmandu,    "Kathmandu",          U16_TEXT("加德满都"),        27.7172f,   85.3240f, 1400.0f, 345 },
            { CountryID::BGD, Continent::Asia,         CityID::Dhaka,        "Dhaka",              U16_TEXT("达卡"),            23.8103f,   90.4125f, 4.0f, 360 },
            { CountryID::LKA, Continent::Asia,         CityID::Colombo,      "Colombo",            U16_TEXT("科伦坡"),          6.9271f,    79.8612f, 1.0f, 330 },
            { CountryID::QAT, Continent::Asia,         CityID::Doha,         "Doha",               U16_TEXT("多哈"),            25.2769f,   51.5210f, 10.0f, 180 },
            { CountryID::KWT, Continent::Asia,         CityID::KuwaitCity,   "Kuwait City",        U16_TEXT("科威特城"),        29.3759f,   47.9774f, 15.0f, 180 },
            { CountryID::OMN, Continent::Asia,         CityID::Muscat,       "Muscat",             U16_TEXT("马斯喀特"),        23.5880f,   58.3829f, 15.0f, 240 },
            { CountryID::JOR, Continent::Asia,         CityID::Amman,        "Amman",              U16_TEXT("安曼"),            31.9454f,   35.9284f, 777.0f, 120 },
            { CountryID::LBN, Continent::Asia,         CityID::Beirut,       "Beirut",             U16_TEXT("贝鲁特"),          33.8938f,   35.5018f, 40.0f, 120 },
            { CountryID::DZA, Continent::Africa,       CityID::Algiers,      "Algiers",            U16_TEXT("阿尔及尔"),        36.7538f,    3.0588f, 0.0f, 60 },
            { CountryID::TUN, Continent::Africa,       CityID::Tunis,        "Tunis",              U16_TEXT("突尼斯"),          36.8065f,   10.1815f, 4.0f, 60 },
            { CountryID::ARG, Continent::SouthAmerica, CityID::BuenosAires,  "Buenos Aires",       U16_TEXT("布宜诺斯艾利斯"),  -34.6037f,  -58.3816f, 25.0f, -180 },
            { CountryID::CHL, Continent::SouthAmerica, CityID::Santiago,     "Santiago",           U16_TEXT("圣地亚哥"),        -33.4489f,  -70.6693f, 570.0f, -240 },
            { CountryID::COL, Continent::SouthAmerica, CityID::Bogota,       "Bogota",             U16_TEXT("波哥大"),          4.7110f,   -74.0721f, 2640.0f, -300 },
            { CountryID::PER, Continent::SouthAmerica, CityID::Lima,         "Lima",               U16_TEXT("利马"),            -12.0464f,  -77.0428f, 154.0f, -300 },
            { CountryID::VEN, Continent::SouthAmerica, CityID::Caracas,      "Caracas",            U16_TEXT("加拉加斯"),        10.4806f,  -66.9036f, 900.0f, -240 },
            { CountryID::URY, Continent::SouthAmerica, CityID::Montevideo,   "Montevideo",         U16_TEXT("蒙得维的亚"),      -34.9011f,  -56.1645f, 43.0f, -180 },
            { CountryID::PRY, Continent::SouthAmerica, CityID::Asuncion,     "Asuncion",           U16_TEXT("亚松森"),          -25.2637f,  -57.5759f, 43.0f, -240 },
            { CountryID::BOL, Continent::SouthAmerica, CityID::LaPaz,        "La Paz",             U16_TEXT("拉巴斯"),          -16.4897f,  -68.1193f, 3640.0f, -240 },
            { CountryID::ECU, Continent::SouthAmerica, CityID::Quito,        "Quito",              U16_TEXT("基多"),            -0.1807f,   -78.4678f, 2850.0f, -300 },
            { CountryID::ISL, Continent::Europe,       CityID::Reykjavik,    "Reykjavik",          U16_TEXT("雷克雅未克"),      64.1466f,  -21.9426f, 61.0f, 0 },
            { CountryID::IRL, Continent::Europe,       CityID::Dublin,       "Dublin",             U16_TEXT("都柏林"),          53.3498f,   -6.2603f, 20.0f, 0 },
            { CountryID::UKR, Continent::Europe,       CityID::Kyiv,         "Kyiv",               U16_TEXT("基辅"),            50.4501f,   30.5234f, 179.0f, 120 },
            { CountryID::BLR, Continent::Europe,       CityID::Minsk,        "Minsk",              U16_TEXT("明斯克"),          53.9006f,   27.5590f, 220.0f, 180 },
            { CountryID::ROU, Continent::Europe,       CityID::Bucharest,    "Bucharest",          U16_TEXT("布加勒斯特"),      44.4268f,   26.1025f, 70.0f, 120 },
            { CountryID::BGR, Continent::Europe,       CityID::Sofia,        "Sofia",              U16_TEXT("索非亚"),          42.6977f,   23.3219f, 550.0f, 120 },
            { CountryID::HUN, Continent::Europe,       CityID::Budapest,     "Budapest",           U16_TEXT("布达佩斯"),        47.4979f,   19.0402f, 96.0f, 60 },
            { CountryID::SRB, Continent::Europe,       CityID::Belgrade,     "Belgrade",           U16_TEXT("贝尔格莱德"),      44.7866f,   20.4489f, 117.0f, 60 },
            { CountryID::HRV, Continent::Europe,       CityID::Zagreb,       "Zagreb",             U16_TEXT("萨格勒布"),        45.8150f,   15.9819f, 158.0f, 60 },
            { CountryID::SVN, Continent::Europe,       CityID::Ljubljana,    "Ljubljana",          U16_TEXT("卢布尔雅那"),      46.0569f,   14.5058f, 295.0f, 60 },
            { CountryID::SVK, Continent::Europe,       CityID::Bratislava,   "Bratislava",         U16_TEXT("布拉迪斯拉发"),    48.1486f,   17.1077f, 134.0f, 60 },
            { CountryID::EST, Continent::Europe,       CityID::Tallinn,      "Tallinn",            U16_TEXT("塔林"),            59.4370f,   24.7536f, 9.0f, 120 },
            { CountryID::LVA, Continent::Europe,       CityID::Riga,         "Riga",               U16_TEXT("里加"),            56.9496f,   24.1052f, 10.0f, 120 },
            { CountryID::LTU, Continent::Europe,       CityID::Vilnius,      "Vilnius",            U16_TEXT("维尔纽斯"),        54.6872f,   25.2797f, 112.0f, 120 },
            { CountryID::MLT, Continent::Europe,       CityID::Valletta,     "Valletta",           U16_TEXT("瓦莱塔"),          35.8989f,   14.5146f, 56.0f, 60 },
            { CountryID::CYP, Continent::Europe,       CityID::Nicosia,      "Nicosia",            U16_TEXT("尼科西亚"),        35.1856f,   33.3823f, 220.0f, 120 },
            { CountryID::GEO, Continent::Asia,         CityID::Tbilisi,      "Tbilisi",            U16_TEXT("第比利斯"),        41.7151f,   44.8271f, 380.0f, 240 },
            { CountryID::KAZ, Continent::Asia,         CityID::Astana,       "Astana",             U16_TEXT("阿斯塔纳"),        51.1605f,   71.4704f, 347.0f, 360 },
            { CountryID::UZB, Continent::Asia,         CityID::Tashkent,     "Tashkent",           U16_TEXT("塔什干"),          41.2995f,   69.2401f, 455.0f, 300 },
            { CountryID::AZE, Continent::Asia,         CityID::Baku,         "Baku",               U16_TEXT("巴库"),            40.4093f,   49.8671f, 28.0f, 240 },
            { CountryID::ARM, Continent::Asia,         CityID::Yerevan,      "Yerevan",            U16_TEXT("埃里温"),          40.1792f,   44.4991f, 990.0f, 240 },
            { CountryID::MNG, Continent::Asia,         CityID::Ulaanbaatar,  "Ulaanbaatar",        U16_TEXT("乌兰巴托"),        47.8864f,  106.9057f, 1350.0f, 480 },
            { CountryID::BHR, Continent::Asia,         CityID::Manama,       "Manama",             U16_TEXT("麦纳麦"),          26.2285f,   50.5860f, 10.0f, 180 },

            // Additional capitals in Africa
            { CountryID::NGA, Continent::Africa,       CityID::Abuja,        "Abuja",              U16_TEXT("阿布贾"),           9.0765f,    7.3986f, 840.0f, 60 },
            { CountryID::KEN, Continent::Africa,       CityID::Nairobi,      "Nairobi",            U16_TEXT("内罗毕"),          -1.2921f,   36.8219f, 1795.0f, 180 },
            { CountryID::MAR, Continent::Africa,       CityID::Rabat,        "Rabat",              U16_TEXT("拉巴特"),          34.0209f,   -6.8416f, 75.0f, 0 },
            { CountryID::GHA, Continent::Africa,       CityID::Accra,        "Accra",              U16_TEXT("阿克拉"),           5.6037f,   -0.1870f, 61.0f, 0 },
            { CountryID::ETH, Continent::Africa,       CityID::AddisAbaba,   "Addis Ababa",        U16_TEXT("亚的斯亚贝巴"),     8.9806f,   38.7578f, 2355.0f, 180 },
            { CountryID::SDN, Continent::Africa,       CityID::Khartoum,     "Khartoum",           U16_TEXT("喀土穆"),           15.5007f,  32.5599f, 382.0f, 120 },

            // Famous non-capital cities (selection)
            { CountryID::USA, Continent::NorthAmerica, CityID::NewYork,      "New York",           U16_TEXT("纽约"),            40.7128f,  -74.0060f, 10.0f, -300 },
            { CountryID::USA, Continent::NorthAmerica, CityID::LosAngeles,   "Los Angeles",        U16_TEXT("洛杉矶"),          34.0522f, -118.2437f, 71.0f, -480 },
        };

        static int next_normalized_ascii_letter(const char **p)
        {
            const char *s = (const char *)*p;

            while (*s)
            {
                unsigned char c = *s;
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                {
                    unsigned char lower = (c >= 'A' && c <= 'Z') ? (c | 0x20) : c;
                    s++;
                    *p = (const char *)s;
                    return (int)lower;
                }
                s++;
            }

            *p = (const char *)s;
            return 0; /* end */
        }

        static int compare_names(const char *a, const char *b)
        {
            const char *pa = a;
            const char *pb = b;
            int ca, cb;

            for (;;)
            {
                ca = next_normalized_ascii_letter(&pa);
                cb = next_normalized_ascii_letter(&pb);

                if (ca == 0 && cb == 0) return 0;
                if (ca == 0) return -1;
                if (cb == 0) return 1;
                if (ca < cb) return -1;
                if (ca > cb) return 1;
            }
        }
    } // namespace

    const CountryInfo *GetCountryInfo(CountryID id)
    {
        for(const auto &ci:kCountries)
            if (ci.country_id==id)
                return &ci;

        return nullptr;
    }

    const CityInfo *GetCityInfo(CityID id)
    {
        for(const auto &ci:kCities)
        {
            if(ci.city_id==id)
                return &ci;
        }

        return nullptr;
    }

    const CountryInfo *GetCountryInfo(const AnsiString &eng_name)
    {
        for(const auto &ci:kCountries)
            if (!compare_names(eng_name.c_str(),ci.eng_name))
                return &ci;

        return nullptr;
    }

    const CountryInfo *GetCountryInfo(const U16String &chs_name)
    {
        for(const auto &ci:kCountries)
            if (!chs_name.Comp(ci.chs_name))
                return &ci;
        return nullptr;
    }

    const CityInfo *GetCityInfo(const AnsiString &eng_name)
    {
        for(const auto &ci:kCities)
            if(!compare_names(eng_name.c_str(),ci.eng_name))
                return &ci;
        return nullptr;
    }

    const CityInfo *GetCityInfo(const U16String &chs_name)
    {
        for(const auto &ci:kCities)
            if (!chs_name.Comp(ci.chs_name))
                return &ci;
        return nullptr;
    }

    static constexpr double PI_CONST = 3.14159265358979323846;
    static inline double deg2rad(double d){ return d * PI_CONST / 180.0; }
    static inline double rad2deg(double r){ return r * 180.0 / PI_CONST; }

    // Based on NOAA Solar Calculator (https://gml.noaa.gov/grad/solcalc/)
    const bool GetSunTime(float *sunrise,float *sunset,const float latitude,const float longitude,const Date &date)
    {
        if(!sunrise || !sunset) return false;

        // day of year
        int N = date.DayOfYear();

        // longitude hour value
        double lngHour = static_cast<double>(longitude) / 15.0;

        auto calc_time_utc = [&](double targetHour, double &outUT)->bool
        {
            // t for rise/set
            double t = static_cast<double>(N) + ((targetHour - lngHour) / 24.0);

            // Sun's mean anomaly
            double M = (0.9856 * t) - 3.289;

            // Sun's true longitude
            double L = M + (1.916 * sin(deg2rad(M))) + (0.020 * sin(deg2rad(2.0*M))) + 282.634;
            // normalize L to [0,360)
            L = fmod(L,360.0);
            if(L < 0) L += 360.0;

            // Sun's right ascension
            double RA = rad2deg(atan(0.91764 * tan(deg2rad(L))));
            // normalize RA to [0,360)
            RA = fmod(RA,360.0);
            if(RA < 0) RA += 360.0;

            // RA needs to be in the same quadrant as L
            double Lquadrant  = floor(L/90.0) * 90.0;
            double RAquadrant = floor(RA/90.0) * 90.0;
            RA = RA + (Lquadrant - RAquadrant);

            // RA into hours
            RA = RA / 15.0;

            // Sun's declination
            double sinDec = 0.39782 * sin(deg2rad(L));
            double cosDec = cos(asin(sinDec));

            // Sun's local hour angle
            double zenith = 90.833; // official zenith for sunrise/sunset
            double cosH = (cos(deg2rad(zenith)) - (sinDec * sin(deg2rad(latitude)))) / (cosDec * cos(deg2rad(latitude)));

            if(cosH > 1.0) return false; // sun never rises
            if(cosH < -1.0) return false; // sun never sets

            double H;
            if(targetHour <= 12.0)
            {
                // sunrise
                H = 360.0 - rad2deg(acos(cosH));
            }
            else
            {
                // sunset
                H = rad2deg(acos(cosH));
            }

            H = H / 15.0;

            // local mean time
            double T = H + RA - (0.06571 * t) - 6.622;

            // convert to UTC
            double UT = T - lngHour;
            // normalize to [0,24)
            UT = fmod(UT,24.0);
            if(UT < 0) UT += 24.0;

            outUT = UT;
            return true;
        };

        double riseUTC, setUTC;
        bool okRise = calc_time_utc(6.0, riseUTC);
        bool okSet  = calc_time_utc(18.0, setUTC);

        if(!okRise || !okSet)
        {
            // polar day/night or other issue: signal failure
            *sunrise = -1.0f;
            *sunset  = -1.0f;
            return false;
        }

        *sunrise = static_cast<float>(riseUTC);
        *sunset  = static_cast<float>(setUTC);

        return true;
    }

}
