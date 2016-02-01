#ifndef BATTERYDEVICEINFO_H
#define BATTERYDEVICEINFO_H

#include "system_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace System{

    class SYSTEM_LIB_EXPORT BatteryDeviceInfo{
      public:
        enum BatteryStatus{
          BatteryStatus_Unknow,
          BatteryStatus_AC,
          BatteryStatus_DC
        };

        enum BatteryPowerStatus{
          BatteryPowerStatus_Unknow,
          BatteryPowerStatus_Low,
          BatteryPowerStatus_Medium,
          BatteryPowerStatus_High
        };

      public:
        explicit BatteryDeviceInfo( BatteryStatus , BatteryPowerStatus, uint16, uint8, uint8, uint32, uint32 );
        BatteryDeviceInfo( const BatteryDeviceInfo& );
        BatteryDeviceInfo( BatteryDeviceInfo&& );
        ~BatteryDeviceInfo();

      public:
        inline BatteryStatus getBatteryStatus() const{
          return m_batteryStatus;
        }

        inline BatteryPowerStatus getBatteryPowerStatus() const{
          return m_powerStatus;
        }

        inline uint32 getBatteryPercentage() const{
          return m_batteryPercentage;
        }

        inline bool isCharging() const{
          return static_cast<bool>(m_isCharging);
        }

        inline bool hasBattery() const{
          return static_cast<bool>(m_hasBattery);
        }

        inline uint32 getLeftUseTimeSec() const{
          return m_leftUseTimeSec;
        }

        inline uint32 getFullUseTimeSec() const{
          return m_fullUseTimeSec;
        }

        String toBatteryStatusString() const;
        String toBatteryPowerStatusString() const;
        
      private:
        BatteryStatus m_batteryStatus;
        BatteryPowerStatus m_powerStatus;
        uint32 m_batteryPercentage: 16;
        uint32 m_isCharging : 8;
        uint32 m_hasBattery : 8;

        uint32 m_leftUseTimeSec;
        uint32 m_fullUseTimeSec;

        
    };

  }
}

#endif  /*  BATTERYDEVICEINFO_H  */