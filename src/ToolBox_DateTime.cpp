#include "ToolBox_DateTime.h"

#include <limits.h>

namespace ToolBox
{
	static const uint32_t g_uiMilliSecondsPerSecond = 1000;
	static const uint32_t g_uiMilliSecondsPerMinute = 1000 * 60;
	static const uint32_t g_uiMilliSecondsPerHour = 1000 * 60 * 60;
	static const uint32_t g_uiMilliSecondsPerDay = 1000 * 60 * 60 * 24;	
	static const uint8_t g_arDaysPerMonthNonLeapYear[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	// ************************************************************************
	/**
	 * Helps creating strings
	 */
	static
	String
	makeString(uint32_t const uiValue,
			   uint8_t const uiDecimals)
	{
		String sResult(uiValue, DEC);
		while (sResult.length() < uiDecimals)
			sResult = "0" + sResult;
		return sResult;
	}
	
	// ************************************************************************
	/**
	 * ctor; creates an invalid time
	 */
	Time::Time()
	{
	}
	
	/**
	 * ctor
	 * @param uiHours Hour of day, may not be >= 24
	 * @param uiMinutes Minutes of day, may not be >= 60
	 * @param uiSeconds Seconds of day, may not be >= 60
	 * @param uiMilliSeconds Milliseconds of day, may not bet >= 1000
	 */
	Time::Time(uint8_t uiHours,
			   uint8_t uiMinutes,
			   uint8_t uiSeconds,
			   uint16_t uiMilliSeconds) :
		m_bValid(isValid(uiHours, uiMinutes, uiSeconds, uiMilliSeconds))		
	{
		if (m_bValid)
			m_uiMilliSeconds = static_cast<uint32_t>(uiMilliSeconds) +
							   static_cast<uint32_t>(uiSeconds) * g_uiMilliSecondsPerSecond +
							   static_cast<uint32_t>(uiMinutes) * g_uiMilliSecondsPerMinute +
							   static_cast<uint32_t>(uiHours) * g_uiMilliSecondsPerHour; 
							   
	}

	/**
	 * Validation
	 */
	bool
	Time::isValid(uint8_t uiHours,
				  uint8_t uiMinutes,
				  uint8_t uiSeconds,
				  uint16_t uiMilliSeconds)
	{
		return (uiHours < 24) &&
			   (uiMinutes < 60) &&
			   (uiSeconds < 60) &&
			   (uiMilliSeconds < 1000);
	}
	
	/**
	 * is time valid?
	 */
	bool
	Time::isValid() const
	{
		return m_bValid;
	}
	
	/**
	 * get Time-Of-Day hours
	 */
	uint8_t
	Time::getHours() const
	{
		if (m_bValid)
			return (m_uiMilliSeconds / g_uiMilliSecondsPerHour);
		return 0;
	}
	
	/**
	 * get Time-Of-Day minutes
	 */
	uint8_t
	Time::getMinutes() const
	{
		if (m_bValid)
			return ((m_uiMilliSeconds / g_uiMilliSecondsPerMinute) % 60);		
		return 0;
	}
	
	/**
	 * get Time-Of-Day seconds 
	 */
	uint8_t
	Time::getSeconds() const
	{
		if (m_bValid)
			return ((m_uiMilliSeconds / g_uiMilliSecondsPerSecond) % 60);
		return 0;
	}
	
	/**
	 * get Time-Of-Day milliseconds 
	 */
	uint8_t
	Time::getMilliSeconds() const
	{
		if (m_bValid)
			return (m_uiMilliSeconds % g_uiMilliSecondsPerSecond);
		return 0;
	}	

	/**
	 * Compare Time
	 */
	bool
	Time::operator < (Time const& rOther) const
	{
		if (!m_bValid)
			return rOther.m_bValid;		
		if (!rOther.m_bValid)
			return false;
		return (m_uiMilliSeconds < rOther.m_uiMilliSeconds);		
	}
	
	/**
	 * Compare Time
	 */
	bool
	Time::operator <= (Time const& rOther) const
	{
		return (operator < (rOther)) || (operator == (rOther));
	}
	
	/**
	 * Compare Time
	 */
	bool
	Time::operator == (Time const& rOther) const
	{
		if (!m_bValid)
			return !rOther.m_bValid;
		if (!rOther.m_bValid)
			return false;
		return (m_uiMilliSeconds == rOther.m_uiMilliSeconds);
	}
	
	/**
	 * Compare Time
	 */
	bool
	Time::operator != (Time const& rOther) const
	{
		return !operator == (rOther);
	}
	
	/**
	 * Compare Time
	 */
	bool
	Time::operator >= (Time const& rOther) const
	{
		return rOther.operator <= (*this);
	}
	
	/**
	 * Compare Time
	 */
	bool
	Time::operator > (Time const& rOther) const
	{
		return rOther.operator < (*this);
	}

	/**
	 * add hours, time may wrap around
	 */
	void
	Time::addHours(int8_t iHours)
	{
		addMilliSeconds(g_uiMilliSecondsPerHour * iHours);
	}
	
	/**
	 * add minutes, time may wrap around
	 */
	void
	Time::addMinutes(int8_t iMinutes)
	{
		addMilliSeconds(g_uiMilliSecondsPerMinute * iMinutes);
	}
	
	/**
	 * add seconds, time may wrap around
	 */
	void
	Time::addSeconds(int8_t iSeconds)
	{
		addMilliSeconds(g_uiMilliSecondsPerSecond * iSeconds);
	}
	
	/**
	 * add milliseconds, time may wrap around
	 */
	void
	Time::addMilliSeconds(int32_t iMilliSeconds)
	{
		if (m_bValid)
		{
			uint64_t uiTemp = m_uiMilliSeconds;
			uiTemp += iMilliSeconds;
			m_uiMilliSeconds = static_cast<uint32_t>(uiTemp % g_uiMilliSecondsPerDay);
		};
	}
    
	/**
	 * Berechnet die Anzahl Millisekunden von dieser Uhrzeit zur angegebenen
	 */
    int32_t
    Time::getMilliSecondsTo(Time const& rTo)  const
    {
		if ((!m_bValid) || (!rTo.m_bValid))
			return 0;
		
		return static_cast<int32_t>(rTo.m_uiMilliSeconds) - static_cast<int32_t>(m_uiMilliSeconds);
    }
    
	/**
	 * convert Time to String
	 * @param rsFormat Format of string to create; use "hh" for hours, "mm" for minutes, "ss" for seconds, "xxx" for milliseconds
	 *                 the format is case-sensitive
	 * @return time as string
	 */
	String
	Time::toString(String const& rsFormat) const
	{
		String sResult(rsFormat);
		if (m_bValid)
		{
			sResult.replace("hh", makeString(getHours(), 2));
			sResult.replace("mm", makeString(getMinutes(), 2));
			sResult.replace("ss", makeString(getSeconds(), 2));
			sResult.replace("xxx", makeString(getMilliSeconds(), 3));
		}
		else
		{
			sResult.replace("hh", "??");
			sResult.replace("mm", "??");
			sResult.replace("ss", "??");
			sResult.replace("xxx", "???");
		};
		return sResult;
	}

	// ************************************************************************
	/**
	 * ctor, creates an invalid date
	 */
	Date::Date()
	{
	}
	
	/**
	 * ctor
	 */
	Date::Date(uint8_t uiDayInMonth,
			   Month eMonthInYear,
			   uint16_t uiYear) :
		m_bValid(isValid(uiDayInMonth, eMonthInYear, uiYear))
	{
		if (m_bValid)
		{
			// compute number of days
			m_uiDays = 0;
			for (uint16_t uiLoopYear = 1970; uiLoopYear < uiYear; ++uiLoopYear)
				m_uiDays += isLeapYear(uiLoopYear) ? 366 : 365;
			bool const bLeapYear = isLeapYear(uiYear);
			for (uint8_t uiMonth = 0; uiMonth < static_cast<uint8_t>(eMonthInYear); ++uiMonth)
			{
				if ((uiMonth == static_cast<uint8_t>(Month::February)) && (bLeapYear))
					m_uiDays += 29;
				else
					m_uiDays += g_arDaysPerMonthNonLeapYear[uiMonth];
			};
			m_uiDays += uiDayInMonth - 1;
			
			// cache is clean...
			m_bCacheClean = false;
			m_uiYear = uiYear;
			m_eMonthInYear = eMonthInYear;
			m_uiDayInMonth = uiDayInMonth;
			m_eDayOfWeek = static_cast<DayOfWeek>((m_uiDays + 4) % 7);
		};
	}
	
	/**
	 * check wether the given date is valid or not
	 */
	bool
	Date::isValid(uint8_t uiDayInMonth,
			      Month eMonthInYear,
				  uint16_t uiYear)
	{
		// check year
		if (uiYear < 1970)
			return false;
		
		// check month
		uint8_t const uiMonthInYear = static_cast<uint8_t>(eMonthInYear) + 1;
		if (uiMonthInYear > 12)
			return false;
		
		// check days
		uint8_t const uiDaysPerMonth = getDaysPerMonth(eMonthInYear, uiYear);
		return ((uiDayInMonth > 0) && (uiDayInMonth <= uiDaysPerMonth));		
	}
	
	/**
	 * is date valid
	 */
	bool
	Date::isValid() const
	{
		return m_bValid;
	}
	
	/**
	 * get number of days in given month in given year
	 */
	uint8_t
	Date::getDaysPerMonth(Month eMonth,
						  uint16_t uiYear)
	{
		uint8_t const uiMonth = static_cast<uint8_t>(eMonth);
		if (uiMonth > static_cast<uint8_t>(Month::December))
			return 0;
		if ((eMonth == Month::February) && (isLeapYear(uiYear)))
			return 29;
		return g_arDaysPerMonthNonLeapYear[uiMonth];
	}
	
	/**
	 * check wether the given year is a leap year or not
	 */
	bool
	Date::isLeapYear(uint16_t uiYear)
	{
		if ((uiYear % 400) == 0)
			return true;
		if ((uiYear % 100) == 0)
			return false;
		return ((uiYear % 4) == 0);
	}
	
	/**
	 * get day in month
	 */
	uint8_t
	Date::getDayInMonth() const
	{
		if (!m_bValid)
			return 1;
		
		validateCache();
		return m_uiDayInMonth;
	}
	
	/**
	 * get month in year
	 */
	Month
	Date::getMonthInYear() const
	{
		if (!m_bValid)
			return Month::January;
		
		validateCache();
		return m_eMonthInYear;
	}
	
	/**
	 * get year
	 */
	uint16_t
	Date::getYear() const
	{
		if (!m_bValid)
			return 1970;
		
		validateCache();
		return m_uiYear;
	}
		
	/**
	 * get day of week
	 */
	DayOfWeek
	Date::getDayOfWeek() const
	{
		if (!m_bValid)
			return DayOfWeek::Sunday;
		
		validateCache();
		return m_eDayOfWeek;
	}

	/**
	 * add days
	 */
	void
	Date::addDays(int16_t iDays)
	{
		if (!m_bValid)
			return;
		
		m_uiDays += iDays;
		m_bCacheClean = false;
	}
	
	/**
	 * Berechnet die Anzahl Tage von diesem Datum zum angegebenen
	 */
	int32_t
	Date::getDaysTo(Date const& rTo) const	
	{
		if ((!m_bValid) || (!rTo.m_bValid))
			return 0;
		
		return static_cast<int32_t>(rTo.m_uiDays) - static_cast<int32_t>(m_uiDays);
	}
		
	/**
	 * Compare Date
	 */
	bool
	Date::operator < (Date const& rOther) const
	{
		if (!m_bValid)
			return rOther.m_bValid;		
		if (!rOther.m_bValid)
			return false;
		return (m_uiDays < rOther.m_uiDays);
	}
	
	/**
	 * Compare Date
	 */
	bool
	Date::operator <= (Date const& rOther) const
	{
		return (operator < (rOther)) || (operator == (rOther));
	}
	
	/**
	 * Compare Date
	 */
	bool
	Date::operator == (Date const& rOther) const
	{
		if (!m_bValid)
			return !rOther.m_bValid;
		if (!rOther.m_bValid)
			return false;
		return (m_uiDays == rOther.m_uiDays);
	}
	
	/**
	 * Compare Date
	 */
	bool
	Date::operator != (Date const& rOther) const
	{
		return !operator == (rOther);
	}

	/**
	 * Compare Date
	 */
	bool
	Date::operator >= (Date const& rOther) const
	{
		return rOther.operator <= (*this);
	}
	
	/**
	 * Compare Date
	 */
	bool
	Date::operator > (Date const& rOther) const
	{
		return rOther.operator < (*this);
	}
		
	/**
	 * convert Date to String
	 * @param rsFormat Format of string to create; use "DD" for day in month, "MM" for month in year, "YYYY" for year
	 *                 the format is case-sensitive
	 * @return date as string
	 */
	String
	Date::toString(String const& rsFormat) const
	{
		String sResult(rsFormat);
		if (m_bValid)
		{
			sResult.replace("DD", makeString(getDayInMonth(), 2));
			sResult.replace("MM", makeString(static_cast<uint32_t>(getMonthInYear()) + 1, 2));
			sResult.replace("YYYY", makeString(getYear(), 4));
		}
		else
		{
			sResult.replace("DD", "??");
			sResult.replace("MM", "??");
			sResult.replace("YYYY", "????");
		};
		return sResult;
	}
	
	/**
	 * ensure cached values are valid
	 */
	void
	Date::validateCache() const
	{
		if (m_bCacheClean)
			return;
		
		// compute day of week
		m_eDayOfWeek = static_cast<DayOfWeek>((m_uiDays + 4) % 7);
		
		// compute year
		uint32_t uiRemainingDays = m_uiDays;
		m_uiYear = 1970;
		bool bYearFound = false;
		while (!bYearFound)
		{
			uint32_t const uiDaysInYear = isLeapYear(m_uiYear) ? 366 : 365;
			if (uiRemainingDays < uiDaysInYear)
				bYearFound = true;
			else
			{
				uiRemainingDays -= uiDaysInYear;
				m_uiYear++;
			};
		};
		
		// compute month
		bool bMonthFound = false;
		uint8_t uiMonth = 0;
		while (!bMonthFound)
		{
			m_eMonthInYear = static_cast<Month>(uiMonth);
			uint32_t const uiDaysInMonth = getDaysPerMonth(m_eMonthInYear, m_uiYear);
			if (uiRemainingDays < uiDaysInMonth)
				bMonthFound = true;
			else
			{
				uiRemainingDays -= uiDaysInMonth;
				uiMonth++;
			};
		};
		
		// compute day
		m_uiDayInMonth = static_cast<uint8_t>(uiRemainingDays + 1);
		
		// cache is clean
		m_bCacheClean = true;
	}
	
	// ************************************************************************
	/**
	 * ctor; creates an invalid date time
	 */
	DateTime::DateTime()
	{
	}
										 
	/**
	 * ctor
	 */
	DateTime::DateTime(Date const& rDate,
					   Time const& rTime) :
		m_bValid(rDate.m_bValid && rTime.m_bValid)
	{
		if (m_bValid)
		{
			m_uiMilliSeconds = rDate.m_uiDays;
			m_uiMilliSeconds *= g_uiMilliSecondsPerDay;
			m_uiMilliSeconds += rTime.m_uiMilliSeconds;
		};
	}
	
	/**
	 * ctor
	 */
	DateTime::DateTime(bool bValid,
					   uint64_t uiMilliSeconds) :
		m_bValid(bValid),
		m_uiMilliSeconds(uiMilliSeconds)
	{
	}

	/**
	 * get date
	 */
	Date
	DateTime::getDate() const
	{
		if (!m_bValid)
			return Date();
		
		uint64_t const uiTemp = m_uiMilliSeconds / g_uiMilliSecondsPerDay;
		Date result;
		result.m_bValid = true;
		result.m_uiDays = static_cast<uint32_t>(uiTemp % ULONG_MAX);
		return result;
	}
	
	/**
	 * get time
	 */
	Time
	DateTime::getTime() const
	{
		if (!m_bValid)
			return Time();
		
		Time result;
		result.m_bValid = true;
		result.m_uiMilliSeconds = static_cast<uint32_t>(m_uiMilliSeconds % g_uiMilliSecondsPerDay);
		return result;
	}
		
	/**
	 * is date time valid?
	 */
	bool
	DateTime::isValid() const
	{
		return m_bValid;
	}
	
	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator < (DateTime const& rOther) const
	{
		if (!m_bValid)
			return rOther.m_bValid;		
		if (!rOther.m_bValid)
			return false;
		return (m_uiMilliSeconds < rOther.m_uiMilliSeconds);
	}
	
	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator <= (DateTime const& rOther) const
	{
		return (operator <(rOther)) || (operator == (rOther));
	}
	
	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator == (DateTime const& rOther) const
	{
		if (!m_bValid)
			return !rOther.m_bValid;
		if (!rOther.m_bValid)
			return false;
		return (m_uiMilliSeconds == rOther.m_uiMilliSeconds);
	}
	
	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator != (DateTime const& rOther) const
	{
		return !operator == (rOther);
	}
	
	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator >= (DateTime const& rOther) const
	{
		return rOther.operator <= (*this);
	}

	/**
	 * Compare DateTime
	 */
	bool
	DateTime::operator > (DateTime const& rOther) const
	{
		return rOther.operator < (*this);
	}
		
	/**
	 * convert DateTime to String
	 * @param rsFormat @see Time::toString() @see Date::toString()
	 * @return DateTime as string
	 */
	String
	DateTime::toString(String const& rsFormat) const
	{
		return getDate().toString(getTime().toString(rsFormat));
	}		
}	
