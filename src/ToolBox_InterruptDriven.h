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
    protected:
                                InterruptDriven(uint8_t);
                                ~InterruptDriven();
                                
        bool                    attach(uint8_t);
        void                    detach();
        
        bool                    isAttached() const;        
    
        virtual void            handleInterrupt() = 0;
                                            
        //! used pin
        uint8_t const           m_uiInterruptPin;
        
    private:
        //! flag "object is attached to interrupt"
        bool                    m_bAttached = false;
        
        class InterruptHandler;
        friend class InterruptHandler;
    };
}
