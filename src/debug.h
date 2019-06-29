// ************************************************************************
// *
// * Debug-Macros
// *
// ************************************************************************
#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define DEBUGGING_ACTIVE

#ifdef DEBUGGING_ACTIVE
#   define DEBUG_BEGIN(o) Serial.begin(o); while (!Serial);
#   define DEBUG_PRINT(o) Serial.print(o)
#   define DEBUG_PRINTLN(o) Serial.println(o)
#else
#   define DEBUG_BEGIN(o)
#   define DEBUG_PRINT(o)
#   define DEBUG_PRINTLN(o)
#endif


#endif
