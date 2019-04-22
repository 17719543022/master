#ifndef INCL_LOG_FORMAT_H
#define INCL_LOG_FORMAT_H

#define ERR_LOG (printf("ERROR: %s(%d)-<%s>: ",__FILE__, __LINE__, __FUNCTION__), printf)
#define DBG_LOG (printf("DEBUG: %s(%d)-<%s>: ",__FILE__, __LINE__, __FUNCTION__), printf)

#endif