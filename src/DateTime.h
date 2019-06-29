#pragma once

#include <Arduino.h>

namespace ToolBox
{
	class Date;
	class Time;
	class DateTime;
	class EEPROMStorage;
	
	/**
	 * moth names enumeration
	 */
	enum class Month
	{	
		January = 0,
		February = 1,
		March = 2,
		April = 3,
		May = 4,
		June = 5,
		July = 6,
		August = 7,
		September = 8,
		October = 9,
		November = 10,
		December = 11
	};
	
	/**
	 * day of week
	 */
	enum class DayOfWeek
	{
		Sunday = 0,
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6
	};
	
	/**
	 * Simple Time-Off-Day class
	 */
	class Time final
	{
	public:
								Time();
		explicit				Time(uint8_t,
									 uint8_t,
									 uint8_t,
									 uint16_t = 0);
									 
		static bool				isValid(uint8_t,
										uint8_t,
										uint8_t,
										uint16_t);
										
		bool					isValid() const;
		
		uint8_t					getHours() const;
		uint8_t					getMinutes() const;
		uint8_t					getSeconds() const;
		uint8_t					getMilliSeconds() const;
		
		void					addHours(int8_t);
		void					addMinutes(int8_t);
		void					addSeconds(int8_t);
		void					addMilliSeconds(int32_t);
        int32_t                 getMilliSecondsTo(Time const&)  const;
		
		bool					operator < (Time const&) const;
		bool					operator <= (Time const&) const;
		bool					operator == (Time const&) const;
		bool					operator != (Time const&) const;
		bool					operator >= (Time const&) const;
		bool					operator > (Time const&) const;
		
		String					toString(String const&) const;
		
	private:
		friend class DateTime;
		friend class EEPROMStorage;		
		
		//! flag "time is valid"
		bool					m_bValid = false;
		
		//! Milliseconds since beginning of day
		uint32_t				m_uiMilliSeconds = 0;
	};
		
	/**
	 * Simple Date class
	 */
	class Date final
	{
	public:
								Date();								
		explicit				Date(uint8_t,
									 Month,
									 uint16_t);
									 
		static bool				isValid(uint8_t,
										Month,
										uint16_t);
										
		bool					isValid() const;
										
		static uint8_t			getDaysPerMonth(Month,
												uint16_t);
									 
		static bool				isLeapYear(uint16_t);
		
		uint8_t					getDayInMonth() const;
		Month					getMonthInYear() const;
		uint16_t				getYear() const;
		DayOfWeek				getDayOfWeek() const;
									 
		void					addDays(int16_t);
		int32_t					getDaysTo(Date const&) const;
		
		bool					operator < (Date const&) const;
		bool					operator <= (Date const&) const;
		bool					operator == (Date const&) const;
		bool					operator != (Date const&) const;
		bool					operator >= (Date const&) const;
		bool					operator > (Date const&) const;
		
		String					toString(String const&) const;
		
	private:
		friend class DateTime;
		friend class EEPROMStorage;
		
		void					validateCache() const;
		
		//! flag "date is valid"
		bool					m_bValid = false;
		
		//! Number of days since 1.1.1970
		uint32_t				m_uiDays = 0;
		
		//! flag "cache is clean"
		mutable bool			m_bCacheClean = false;
		
		//! cached year
		mutable uint16_t		m_uiYear = 1970;
		
		//! cached month
		mutable Month			m_eMonthInYear = Month::January;
		
		//! cached day
		mutable uint8_t			m_uiDayInMonth = 1;
		
		//! cached day of week
		mutable DayOfWeek		m_eDayOfWeek = DayOfWeek::Monday;
	};
	
	/**
	 * Simple DateTime class
	 */
	class DateTime
	{
	public:
								DateTime();
								DateTime(Date const&,
										 Time const&);
										 
		Date					getDate() const;
		Time					getTime() const;
		
		bool					isValid() const;
		
		bool					operator < (DateTime const&) const;
		bool					operator <= (DateTime const&) const;
		bool					operator == (DateTime const&) const;
		bool					operator != (DateTime const&) const;
		bool					operator >= (DateTime const&) const;
		bool					operator > (DateTime const&) const;
		
		String					toString(String const&) const;
		
	protected:
		friend class EEPROMStorage;

		explicit				DateTime(bool,
										 uint64_t);
								
		//! flag "datetime is valid"
		bool					m_bValid = false;

		//! milliseconds since 01.01.1970 00:00:00.000
		uint64_t				m_uiMilliSeconds = 0;
	};
}
