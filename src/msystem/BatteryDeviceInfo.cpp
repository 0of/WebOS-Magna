#include "BatteryDeviceInfo.h"

#include <cstring>

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 匀礀猀琀攀洀笀਀†
  †BatteryDeviceInfo::BatteryDeviceInfo( BatteryStatus a1, BatteryPowerStatus a2
  †  Ⰰ 甀椀渀琀㄀㘀 愀㌀Ⰰ 甀椀渀琀㠀 愀㐀Ⰰ 甀椀渀琀㠀 愀㔀Ⰰ 甀椀渀琀㌀㈀ 愀㘀Ⰰ 甀椀渀琀㌀㈀ 愀㜀⤀਀†  †:m_batteryStatus( a1 )
  †  Ⰰ洀开瀀漀眀攀爀匀琀愀琀甀猀⠀ 愀㈀ ⤀਀†  †,m_batteryPercentage( a3 )
  †  Ⰰ洀开椀猀䌀栀愀爀最椀渀最⠀ 愀㐀 ⤀਀†  †,m_hasBattery( a5 )
  †  Ⰰ洀开氀攀昀琀唀猀攀吀椀洀攀匀攀挀⠀ 愀㘀 ⤀਀†  †,m_fullUseTimeSec( a7 ){

  †}

  †BatteryDeviceInfo::BatteryDeviceInfo( BatteryDeviceInfo&& i){
  †  㨀㨀洀攀洀挀瀀礀⠀ 琀栀椀猀Ⰰ ☀椀Ⰰ 猀椀稀攀漀昀⠀䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀⤀ ⤀㬀਀†  紀਀਀†  䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀㨀㨀䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀⠀ 挀漀渀猀琀 䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀☀ 椀⤀笀਀†  †::memcpy( this, &i, sizeof(BatteryDeviceInfo) );
  †}

  †const String shared_battery_status_str_mapper[] = {
  †  䰀∀唀渀欀渀漀眀⁧⩷∀਀†  †,L"AC 交流电源"
  †  Ⰰ䰀∀䐀䌀⁶ꕵ㕟焀∀਀†  紀㬀਀਀†  挀漀渀猀琀 匀琀爀椀渀最 猀栀愀爀攀搀开戀愀琀琀攀爀礀开瀀漀眀攀爀开猀琀愀琀甀猀开猀琀爀开洀愀瀀瀀攀爀嬀崀 㴀 笀਀†  †L"Unknow 未知"
  †  Ⰰ䰀∀䰀漀眀⁏乵㖑케∀਀†  †,L"Medium 中等电量"
  †  Ⰰ䰀∀䠀椀最栀ₚ�㖑케∀਀†  紀㬀਀਀†  匀琀爀椀渀最 䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀㨀㨀琀漀䈀愀琀琀攀爀礀匀琀愀琀甀猀匀琀爀椀渀最⠀⤀ 挀漀渀猀琀笀਀†  †return shared_battery_status_str_mapper[ m_batteryStatus ];
  †}

  †String BatteryDeviceInfo::toBatteryPowerStatusString() const{
  †  爀攀琀甀爀渀 猀栀愀爀攀搀开戀愀琀琀攀爀礀开瀀漀眀攀爀开猀琀愀琀甀猀开猀琀爀开洀愀瀀瀀攀爀嬀 洀开瀀漀眀攀爀匀琀愀琀甀猀 崀㬀਀†  紀਀਀†  䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀㨀㨀縀䈀愀琀琀攀爀礀䐀攀瘀椀挀攀䤀渀昀漀⠀⤀笀਀਀†  紀਀਀†}
}
