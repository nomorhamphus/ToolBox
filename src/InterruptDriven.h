#pragma once

#include <Arduino.h>
#include <cstdint>

namespace ToolBox
{   
    /**
     * base class for interrupt driven objects
     */
    class InterruptDriven
    {
    public:        
        bool                    start(uint8_t);
        void                    stop();
        
        bool                    isStarted() const;
        
    protected:
                                InterruptDriven(uint8_t);
                                ~InterruptDriven();
                                
        virtual void            handleInterrupt() = 0;
                                            
        //! used pin
        uint8_t const           m_uiInterruptPin;
        
    private:
        //! flag "start has been called"
        bool                    m_bStarted = false;
        
        class InterruptHandler;
        friend class InterruptHandler;
    };
}
