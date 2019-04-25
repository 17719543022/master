#ifndef INCL_LOG_FORMAT_H
#define INCL_LOG_FORMAT_H

extern bool logSwitch;
int switchPrintf(const char* format, ...);

#define DBG_LOG ((logSwitch)?\
					(printf("DEBUG: %s(%d)-<%s>: ",__FILE__, __LINE__, __FUNCTION__), printf)\
					:\
					(switchPrintf))

#define ERR_LOG ((logSwitch)?\
					(printf("ERROR: %s(%d)-<%s>: ",__FILE__, __LINE__, __FUNCTION__), printf)\
					:\
					(switchPrintf))

#endif