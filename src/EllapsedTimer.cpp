#include "EllapsedTimer.h"

#include <limits.h>

namespace ToolBox
{
	/**
	 * ctor 
	 * @param uiMillisToEllapse Milliseconds to ellapse
	 */
	EllapsedTimer::EllapsedTimer(uint32_t uiMillisToEllapse) :
		m_uiMillisToEllapse(uiMillisToEllapse)
	{
		restart();
	}

	/**
	 * set milliseconds to ellapse
	 */
	void
	EllapsedTimer::setMillisToEllapse(uint32_t uiMillisToEllapse)
	{
		m_uiMillisToEllapse = uiMillisToEllapse;
	}

	/**
	 * get milliseconds to ellapse
	 */
	uint32_t
	EllapsedTimer::getMillisToEllapse() const
	{
		return m_uiMillisToEllapse;
	}

	/**
	 * Restart Timer
	 */
	void
	EllapsedTimer::restart()
	{
		m_uiStartTime = millis();
	}
    
	/**
	 * Compute milliseconds ellapsed since last call of restart() or ctor
	 */
	uint32_t
	EllapsedTimer::getEllapsedMillis() const
	{
		uint32_t const uiNow = millis();
		return (uiNow >= m_uiStartTime)?
			   (uiNow - m_uiStartTime):
			   (ULONG_MAX - m_uiStartTime) + uiNow;
	}

	/**
	 * checks wether this timer has ellapsed or not
	 */
	bool
	EllapsedTimer::isEllapsed() const
	{
		return (getEllapsedMillis() >= m_uiMillisToEllapse);
	}
}
