#pragma once

#include <Arduino.h>

namespace ToolBox
{
	/**
	 * interrupt lock sentry
	 */
	class InterruptLock final
	{
	public:
                                InterruptLock();  
                                ~InterruptLock();

        void                    lock();
        void                    unlock();
        
	private:
        //! flag "is locked"
        bool                    m_bLocked = false;
        
#ifdef ESP32
        //! mutex
        portMUX_TYPE            m_Mutex;
#endif    
	};
}
