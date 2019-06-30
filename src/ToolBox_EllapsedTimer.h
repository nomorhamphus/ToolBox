#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace ToolBox
{
	/**
	 * computes ellapsed time
	 */
	class EllapsedTimer final
	{
	public:
		explicit				EllapsedTimer(uint32_t = 0);
									
		void					setMillisToEllapse(uint32_t);
		uint32_t				getMillisToEllapse() const;
		
		void					restart();
		
		uint32_t				getEllapsedMillis() const;
		
		bool					isEllapsed() const;
									
	private:
		/**
		 * milliseconds to ellapse
		 */
		uint32_t				m_uiMillisToEllapse = 0;
		
		/**
		 * value of millis() in last call of restart() or ctor.
		 * This is the starting time
		 */
		uint32_t				m_uiStartTime = 0;
	};
}
