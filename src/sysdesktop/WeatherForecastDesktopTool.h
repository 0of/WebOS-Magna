#ifndef WEATHERFORECASTDESKTOPTOOL_H
#define WEATHERFORECASTDESKTOPTOOL_H

#include "glue_img/Image.h"
using namespace Magna::Glue;

#include "basegui/Controller.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/ButtonGroup.h"
using namespace Magna::GUI;

#include "WeatherforecastService.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class WeatherForecastDesktopToolController : public Controller{
        friend class WeatherForecastDesktopToolImplmentor;

        enum Weather{
          Sun, Cloudy, PartlyCloudy, Sprinkle, ModerateRain
          ,HeavyRain,Thundershower
        };
    
        public:
          WeatherForecastDesktopToolController();
          virtual ~WeatherForecastDesktopToolController();

        public:
          void updateLocationInfomation();
          void updateWeatherInfos();

        private:
          Weather m_weather;
          String m_locationName;
          String m_weatherDetails;
          String m_celciusDegrees;

          WeatherForecastService m_service;
      };

    }
  }//namespace System
}//namespace Magna
#endif  /*  WEATHERFORECASTDESKTOPTOOL_H  */