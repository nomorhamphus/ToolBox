#include "ToolBox_InterruptDriven.h"

// ****************************************************************************
#ifdef ESP32
#   define ISR_PROC_ATTRIBUTE       IRAM_ATTR
#else
#   define ISR_PROC_ATTRIBUTE
#endif

namespace ToolBox
{
    // ***********************************************************************
	// @private
    typedef void (*ISR_FUNCTION)();
    
    /**
     * interrupt handler
     */
    class InterruptDriven::InterruptHandler
    {
    public:
        static void             attach(InterruptDriven*,
                                       uint8_t);
        static void             detach(InterruptDriven*);                                     
        static void             interruptProc(uint8_t);
    
    private:
        static void ISR_PROC_ATTRIBUTE interruptProc0();
        static void ISR_PROC_ATTRIBUTE interruptProc1();
        static void ISR_PROC_ATTRIBUTE interruptProc2();
        static void ISR_PROC_ATTRIBUTE interruptProc3();
        static void ISR_PROC_ATTRIBUTE interruptProc4();
        static void ISR_PROC_ATTRIBUTE interruptProc5();
        static void ISR_PROC_ATTRIBUTE interruptProc6();
        static void ISR_PROC_ATTRIBUTE interruptProc7();
        static void ISR_PROC_ATTRIBUTE interruptProc8();
        static void ISR_PROC_ATTRIBUTE interruptProc9();
        static void ISR_PROC_ATTRIBUTE interruptProc10();
        static void ISR_PROC_ATTRIBUTE interruptProc11();
        static void ISR_PROC_ATTRIBUTE interruptProc12();
        static void ISR_PROC_ATTRIBUTE interruptProc13();
        static void ISR_PROC_ATTRIBUTE interruptProc14();
        static void ISR_PROC_ATTRIBUTE interruptProc15();
        static void ISR_PROC_ATTRIBUTE interruptProc16();
        static void ISR_PROC_ATTRIBUTE interruptProc17();
        static void ISR_PROC_ATTRIBUTE interruptProc18();
        static void ISR_PROC_ATTRIBUTE interruptProc19();
        static void ISR_PROC_ATTRIBUTE interruptProc20();
        static void ISR_PROC_ATTRIBUTE interruptProc21();
        static void ISR_PROC_ATTRIBUTE interruptProc22();
        static void ISR_PROC_ATTRIBUTE interruptProc23();
        static void ISR_PROC_ATTRIBUTE interruptProc24();
        static void ISR_PROC_ATTRIBUTE interruptProc25();
        static void ISR_PROC_ATTRIBUTE interruptProc26();
        static void ISR_PROC_ATTRIBUTE interruptProc27();
        static void ISR_PROC_ATTRIBUTE interruptProc28();
        static void ISR_PROC_ATTRIBUTE interruptProc29();
        static void ISR_PROC_ATTRIBUTE interruptProc30();
        static void ISR_PROC_ATTRIBUTE interruptProc31();
    
        static ISR_FUNCTION const   cm_ISRFunctions[32];
        static InterruptDriven*     cm_InterruptDriven[32];
    };
    
    /**
     * one interrupt handling function for each interrupt (0 - 31)
     */
    ISR_FUNCTION const 
    InterruptDriven::InterruptHandler::cm_ISRFunctions[32] = 
        {
            interruptProc0 , interruptProc1 , interruptProc2 , interruptProc3 , interruptProc4 , interruptProc5 , interruptProc6 , interruptProc7 ,
            interruptProc8 , interruptProc9 , interruptProc10, interruptProc11, interruptProc12, interruptProc13, interruptProc14, interruptProc15, 
            interruptProc16, interruptProc17, interruptProc18, interruptProc19, interruptProc20, interruptProc21, interruptProc22, interruptProc23,
            interruptProc24, interruptProc25, interruptProc26, interruptProc27, interruptProc28, interruptProc29, interruptProc30, interruptProc31
        };
     
    /**
     * current object for each interrupt (0 - 31)
     */
    InterruptDriven*
    InterruptDriven::InterruptHandler::cm_InterruptDriven[32] = 
        {
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
        };
     
    /**
     * attach object to interrupt
     * @param pObject Object to attach to interruptProc
     * @param uiMode mode; could be LOW, CHANGE, RISING, FALLING or HIGH
     */
    void
    InterruptDriven::InterruptHandler::attach(InterruptDriven* pObject,
                                              uint8_t uiMode)
    {
        if ((!pObject) || (pObject->m_bAttached))
            return;
        
        uint8_t const uiInterrupt = digitalPinToInterrupt(pObject->m_uiInterruptPin);
        if ((uiInterrupt >= 32) || (cm_InterruptDriven[uiInterrupt] != nullptr))
            return;
        
        attachInterrupt(uiInterrupt, cm_ISRFunctions[uiInterrupt], uiMode);
        cm_InterruptDriven[uiInterrupt] = pObject;
        pObject->m_bAttached = true;
    }                                         

    /**
     * detach object from interrupt
     */
    void
    InterruptDriven::InterruptHandler::detach(InterruptDriven* pObject)
    {
        if ((!pObject) || (!pObject->m_bAttached))
            return;
        
        uint8_t const uiInterrupt = digitalPinToInterrupt(pObject->m_uiInterruptPin);
        if ((uiInterrupt >= 32) || (cm_InterruptDriven[uiInterrupt] != pObject))
            return;
        
        detachInterrupt(uiInterrupt);
        cm_InterruptDriven[uiInterrupt] = nullptr;
        pObject->m_bAttached = false;
    }

    /**
     * call interrupt handler function of object assigned to the given pin number
     */
    void
    InterruptDriven::InterruptHandler::interruptProc(uint8_t uiPin)
    {
        uint8_t const uiInterrupt = digitalPinToInterrupt(uiPin);
        if (uiInterrupt >= 32)
            return;
        
        InterruptDriven* const pObject = cm_InterruptDriven[uiInterrupt];
        if (!pObject)
            return;
        pObject->handleInterrupt();
    }
    
    // generate an interrupt routine for each possible IRQ pin
    // since there is no way to pass an argument via an interrupt
    #define CREATE_ISR_FUNCTION(O)\
        void\
        ISR_PROC_ATTRIBUTE\
        InterruptDriven::InterruptHandler::interruptProc##O()\
        {\
            interruptProc(O);\
        }
        
    CREATE_ISR_FUNCTION(0)
    CREATE_ISR_FUNCTION(1)
    CREATE_ISR_FUNCTION(2)
    CREATE_ISR_FUNCTION(3)
    CREATE_ISR_FUNCTION(4)
    CREATE_ISR_FUNCTION(5)
    CREATE_ISR_FUNCTION(6)
    CREATE_ISR_FUNCTION(7)
    CREATE_ISR_FUNCTION(8)
    CREATE_ISR_FUNCTION(9)
    CREATE_ISR_FUNCTION(10)
    CREATE_ISR_FUNCTION(11)
    CREATE_ISR_FUNCTION(12)
    CREATE_ISR_FUNCTION(13)
    CREATE_ISR_FUNCTION(14)
    CREATE_ISR_FUNCTION(15)
    CREATE_ISR_FUNCTION(16)
    CREATE_ISR_FUNCTION(17)
    CREATE_ISR_FUNCTION(18)
    CREATE_ISR_FUNCTION(19)
    CREATE_ISR_FUNCTION(20)
    CREATE_ISR_FUNCTION(21)
    CREATE_ISR_FUNCTION(22)
    CREATE_ISR_FUNCTION(23)
    CREATE_ISR_FUNCTION(24)
    CREATE_ISR_FUNCTION(25)
    CREATE_ISR_FUNCTION(26)
    CREATE_ISR_FUNCTION(27)
    CREATE_ISR_FUNCTION(28)
    CREATE_ISR_FUNCTION(29)
    CREATE_ISR_FUNCTION(30)
    CREATE_ISR_FUNCTION(31)    
    
    // ************************************************************************
    /**
     * ctor
     * @param uiInterruptPin pin to assign to Object
     */
    InterruptDriven::InterruptDriven(uint8_t uiInterruptPin) :
        m_uiInterruptPin(uiInterruptPin)
    {
    }
    
    /**
     * dtor
     * detaches object from interrupt if required
     */
    InterruptDriven::~InterruptDriven()
    {
        detach();
    }
                                    
    /**
     * attach object to interrupt; derived classes need to set pin mode 
     * @param uiMode mode; could be LOW, CHANGE, RISING, FALLING or HIGH
     * @return true, on success; false, otherwise
     */
    bool
    InterruptDriven::attach(uint8_t uiMode)
    {
        InterruptHandler::attach(this, uiMode);        
        return m_bAttached;
    }

    /**
     * detach object from interrupt
     */
    void
    InterruptDriven::detach()
    {
        InterruptHandler::detach(this);
    }
    
    /**
     * @return true, when object is attached to interrupt; false, otherwise
     */
    bool
    InterruptDriven::isAttached() const
    {
        return m_bAttached;
    }
        
    /**
     * called from interrupt handler
     */
    void
    InterruptDriven::handleInterrupt()
    {
    }
}
