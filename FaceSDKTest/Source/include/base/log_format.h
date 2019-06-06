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

#define EXPECT_TRUE_EX(x) {\
							int result2019 = x;\
							if(SUCC != result2019 && logSwitch)\
							{\
								DBG_LOG("result2019: %d.\n", result2019);\
							}\
						}

#endif