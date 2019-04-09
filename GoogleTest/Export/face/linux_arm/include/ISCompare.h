#ifndef ISCompare_H
#define ISCompare_H


#include "ISConfig.h"


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///ŽŽœšÏàËÆ¶È±ÈœÏÍšµÀ£¬ÒÔºóÏà¹Ø²Ù×÷×÷Îª²ÎÊýŽ«Èë
	///@return
	///-1 Ê§°Ü£¬0...N ³É¹Š
IS_API int ISCreateCompareChannel(char *modelpath);

	///@brief
	///Ïú»Ù
	///@param
	///channel-ISCreateCompareChannel·µ»ØÖµ
IS_API int ISDestroyCompareChannel(int channel);

	///@brief
	///·µ»ØÁœžöÌØÕ÷ÖµµÄÏàËÆ¶È
IS_API int ISCompare(int channel,char *feature1,char *feature2,float *outScore);

	///@brief
	///·µ»ØMºÍNžöÌØÕ÷ÖµµÄÏàËÆ¶ÈŸØÕó
IS_API int ISCompareMN(int channel, char **featureM, int numM, char **featureN, int numN, float **outScore);

	///@brief
	///½«N¸öÌØÕ÷ÖµÔ¤ÏÈÔØÈë£¬¿ÉÒÔ½ÚÊ¡±È¶ÔÊ±¼ä
IS_API int ISCompareMNfasterprep(int channel, char **featureN, int numN);

	///@brief
	///·µ»ØMºÍN¸öÌØÕ÷ÖµµÄÏàËÆ¶È¾ØÕó£¬ÐèÒªÏÈÊ¹ÓÃISCompareMNfasterprepÔØÈëN¸öÌØÕ÷Öµ
IS_API int ISCompareMNfaster(int channel, char **featureM, int numM, float **outScore);

	///@brief
	///·µ»Øµ±Ç°SDK  ÄÜ¹»ŽŽœšµÄÌØÕ÷ÌáÈ¡Æ÷×îŽóÍšµÀÊý
IS_API int ISGetMaxCompareChannel();

	///@brief
	///·µ»Øµ±Ç°SDK  ÌØÕ÷ÌáÈ¡Æ÷ÐÅÏ¢
IS_API const char* ISGetCompareVersionInfo();
	

#if defined (__cplusplus)
}
#endif


#endif


