#include "ToolBox_InterruptLock.h"

namespace ToolBox
{
	/**
	 * ctor 
	 */
	InterruptLock::InterruptLock()
	{
        lock();
	}

	/**
	 * dtor
	 */
	InterruptLock::~InterruptLock()
	{	
        unlock();
	}
    
	/**
	 * lock
	 */
    void
	InterruptLock::lock()
	{
        if (m_bLocked)
            return;
#ifdef ESP32
        // disable interrupts
        m_Mutex = portMUX_INITIALIZER_UNLOCKED;
        portENTER_CRITICAL(&m_Mutex);
#else
        // disable interrupts
        cli();
#endif
        m_bLocked = true;
	}

	/**
	 * unlock
	 */
    void
	InterruptLock::unlock()
	{	
        if (!m_bLocked)
            return;
#ifdef ESP32
        // enable interrupts
        portEXIT_CRITICAL(&m_Mutex);
#else
        // enable interrupts
        sei();
#endif
        m_bLocked = false;
	}
}
