/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.

#ifndef SAPI_HAL_RTC_HPP_
#define SAPI_HAL_RTC_HPP_

#include <sos/dev/rtc.h>
#include "Periph.hpp"


namespace hal {

class RtcFlags {
public:
	enum rtc_flags {
		flag_enable /*! Set the alarm */ = RTC_FLAG_ENABLE,
		flag_disable /*! Set the alarm */ = RTC_FLAG_DISABLE,
		flag_is_source_external_32768 /*! External 32.768KHz Crystal */ = RTC_FLAG_IS_SOURCE_EXTERNAL_32768,
		flag_is_source_internal_40000 /*! Internal 40KHz Oscillator */ = RTC_FLAG_IS_SOURCE_INTERNAL_40000,
		flag_enable_alarm /*! Enable the alarm */ = RTC_FLAG_ENABLE_ALARM,
		flag_disable_alarm /*! Enable the alarm */ = RTC_FLAG_DISABLE_ALARM,
		flag_is_alarm_once /*! One time alarm */ = RTC_FLAG_IS_ALARM_ONCE,
		flag_is_alarm_minute /*! Alarm every minute */ = RTC_FLAG_IS_ALARM_MINUTE,
		flag_is_alarm_hourly /*! Alarm every hour */ = RTC_FLAG_IS_ALARM_HOURLY,
		flag_is_alarm_daily /*! Daily alarm */ = RTC_FLAG_IS_ALARM_DAILY,
		flag_is_alarm_weekly /*! Weekly alarm */ = RTC_FLAG_IS_ALARM_WEEKLY,
		flag_is_alarm_monthly /*! Monthly alarm */ = RTC_FLAG_IS_ALARM_MONTHLY,
		flag_is_alarm_yearly /*! Yearly alarm */ = RTC_FLAG_IS_ALARM_YEARLY,
		flag_enable_count_event /*! Enable a count event */ = RTC_FLAG_ENABLE_COUNT_EVENT,
		flag_is_count_second /*! One time alarm */ = RTC_FLAG_IS_COUNT_SECOND,
		flag_is_count_minute /*! One time alarm */ = RTC_FLAG_IS_COUNT_MINUTE,
		flag_is_count_hour /*! One time alarm */ = RTC_FLAG_IS_COUNT_HOUR,
		flag_is_count_day_of_week /*! One time alarm */ = RTC_FLAG_IS_COUNT_DAY_OF_WEEK,
		flag_is_count_day_of_month /*! One time alarm */ = RTC_FLAG_IS_COUNT_DAY_OF_MONTH,
		flag_is_count_day_of_year /*! One time alarm */ = RTC_FLAG_IS_COUNT_DAY_OF_YEAR,
		flag_is_count_week /*! One time alarm */ = RTC_FLAG_IS_COUNT_WEEK,
		flag_is_count_month /*! One time alarm */ = RTC_FLAG_IS_COUNT_MONTH,
		flag_is_count_year /*! One time alarm */ = RTC_FLAG_IS_COUNT_YEAR,
		flag_disable_count_event /*! Enable a count event */ = RTC_FLAG_DISABLE_COUNT_EVENT,
	};
};

class RtcAttributes :
		public PeriphAttributes<rtc_attr_t>,
		public RtcFlags {
public:

private:

};

/*! \brief RTC Class
 * \details This class implements an RTC. (Not yet implemented)
 */
class Rtc :
		public Periph<rtc_info_t, rtc_attr_t, RtcAttributes, 'r'>,
		public RtcFlags {
public:
	Rtc(port_t port);

	/*! \details Set RTC time. */
	int set_time(const rtc_time_t & time) const;

	/*! \details Gets RTC time. */
	int get_time(rtc_time_t & time) const;

private:

};

}

#endif /* SAPI_HAL_RTC_HPP_ */
