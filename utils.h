#ifndef _UTILS_H_
#define _UTILS_H_

///Macros

///Debuging
#define DEBUG 1
#ifdef DEBUG
#define DEBUG_LOG(msg) Serial.println(F(msg))
#define DEBUG_LOG_VAR(msg) Serial.println(msg)
#else
#define DEBUG_LOG(msg) nullptr
#define DEBUG_LOG_VAR(msg) nullptr
#endif


// Read pgmspace (Macro)
#define _RM(x) (void *)pgm_read_word(&x)


#endif // _UTILS_H_