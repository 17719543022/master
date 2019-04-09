#ifndef ISConfig_H
#define ISConfig_H


#ifdef IS_EXPORTS
	#define IS_API  __declspec(dllexport)
#else
	#define IS_API
#endif

#define MAX_DETECT_NUM 50


#endif


