// ************************************************************************
// *
// * Debug-Macros
// *
// ************************************************************************
#pragma once

//#define TOOLBOX_DEBUGGING_ACTIVE

#ifdef TOOLBOX_DEBUGGING_ACTIVE
#   define TOOLBOX_DEBUG_BEGIN(o) Serial.begin(o); while (!Serial);
#   define TOOLBOX_DEBUG_PRINT(o) Serial.print(o)
#   define TOOLBOX_DEBUG_PRINTLN(o) Serial.println(o)
#else
#   define TOOLBOX_DEBUG_BEGIN(o)
#   define TOOLBOX_DEBUG_PRINT(o)
#   define TOOLBOX_DEBUG_PRINTLN(o)
#endif

