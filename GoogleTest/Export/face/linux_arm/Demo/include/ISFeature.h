#ifndef ISFeature_H
#define ISFeature_H


#include "ISConfig.h"


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///ŽŽœšÌØÕ÷ÌáÈ¡ÍšµÀ£¬ÒÔºóÏà¹Ø²Ù×÷×÷Îª²ÎÊýŽ«Èë
	///@return
	///-1 Ê§°Ü£¬0...N ³É¹Š
IS_API int ISCreateFeatureChannel(char *modelpath);

	///@brief
	///Ïú»Ù
	///@param
	///channel-ISCreateFeatureChannel·µ»ØÖµ
IS_API int ISDestroyFeatureChannel(int channel);

	///@brief
	///·µ»Øµ¥žöÄ£°å×ÖœÚ³€¶È
IS_API int ISGetFeatureLength();

	///@brief
	///ÌáÈ¡ÌØÕ÷£¬·µ»ØŽ«ÈëÍŒÆ¬×îÖÐŒäÈËÁ³µÄÌØÕ÷
	///@param
	///channel-»á»°Ÿä±ú
	///imgData-ÍŒÆ¬ÊýŸÝ
	///imgLen-ÍŒÆ¬³€¶È
	///outFeature-ÓÃÓÚ±£Žæ·µ»ØµÄÌØÕ÷ÊýŸÝ(ISGetFeatureLengthº¯Êý·µ»Ø³€¶ÈµÄ»º³åÇø)
IS_API int ISGetFeature(int channel,char *imgData,int imgLen,char *outFeature);

    ///@brief
	///ÌáÈ¡ÌØÕ÷£¬·µ»ØŽ«ÈëÍŒÆ¬×îÖÐŒäÈËÁ³µÄÌØÕ÷
	///@param
	///channel-»á»°Ÿä±ú
	///imgPath-ÍŒÆ¬Â·Ÿ¶
	///outFeature-ÓÃÓÚ±£Žæ·µ»ØµÄÌØÕ÷ÊýŸÝ(ISGetFeatureLengthº¯Êý·µ»Ø³€¶ÈµÄ»º³åÇø)
IS_API int ISGetFeaturePath(int channel,char *imgPath,char *outFeature);

	///@brief
	///ÌáÈ¡ÌØÕ÷£¬·µ»ØŽ«ÈëÍŒÆ¬×îÖÐŒäÈËÁ³µÄÌØÕ÷
	///@param
	///channel-»á»°Ÿä±ú
	///imgData-ÍŒÆ¬ÊýŸÝ
	///imgLen-ÍŒÆ¬³€¶È
	///outFeature-ÓÃÓÚ±£Žæ·µ»ØµÄÌØÕ÷ÊýŸÝ(swGetFeatureLengthº¯Êý·µ»Ø³€¶ÈµÄ»º³åÇø)
IS_API int ISGetFeatureRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, char *outFeature);

	///@brief
	///ÌáÈ¡ÌØÕ÷£¬ÓŠÓÃœ«ÍŒÆ¬ÖÐ¶ÔÓŠÈËÁ³µÄÎ»ÖÃ×÷Îª²ÎÊýŽ«žøÏµÍ³ÌáÈ¡Ã¿žö
	///ÈËÁ³ÌØÕ÷²¢·µ»Ø
	///@param
	///param-ÍŒÆ¬ÖÐËùÓÐÈËÁ³Î»ÖÃ¶þÎ¬Êý×é(left,top,right,bottom)
    ///facenum-ÍŒÆ¬ÖÐÈËÁ³žöÊý
	///outFeature-ÈËÁ³žöÊý³ËÒÔ  µ¥žöÌØÕ÷Ä£°å×ÖœÚ³€¶ÈµÄ»º³åÇø
IS_API int ISGetFeatureWithFacePos(int channel,char *imgData,int imgLen,int param[][4],int facenum,char *outFeature);

    ///@brief
	///ÌáÈ¡ÌØÕ÷£¬ÓŠÓÃœ«ÍŒÆ¬ÖÐ¶ÔÓŠÈËÁ³µÄÎ»ÖÃ×÷Îª²ÎÊýŽ«žøÏµÍ³ÌáÈ¡Ã¿žö
	///ÈËÁ³ÌØÕ÷²¢·µ»Ø
	///@param
	///param-ÍŒÆ¬ÖÐËùÓÐÈËÁ³Î»ÖÃ¶þÎ¬Êý×é(left,top,right,bottom)
    ///facenum-ÍŒÆ¬ÖÐÈËÁ³žöÊý
	///outFeature-ÈËÁ³žöÊý³ËÒÔ  µ¥žöÌØÕ÷Ä£°å×ÖœÚ³€¶ÈµÄ»º³åÇø
IS_API int ISGetFeatureWithFacePosPath(int channel,char *imgPath,int param[][4],int facenum,char *outFeature);

	///@brief
	///ÌáÈ¡ÌØÕ÷£¬ÓŠÓÃœ«ÍŒÆ¬ÖÐ¶ÔÓŠÈËÁ³µÄÎ»ÖÃ×÷Îª²ÎÊýŽ«žøÏµÍ³ÌáÈ¡Ã¿žö
	///ÈËÁ³ÌØÕ÷²¢·µ»Ø
	///@param
	///param-ÍŒÆ¬ÖÐËùÓÐÈËÁ³Î»ÖÃ¶þÎ¬Êý×é(left,top,right,bottom)
    ///facenum-ÍŒÆ¬ÖÐÈËÁ³žöÊý
	///outFeature-ÈËÁ³žöÊý³ËÒÔ  µ¥žöÌØÕ÷Ä£°å×ÖœÚ³€¶ÈµÄ»º³åÇø
IS_API int ISGetFeatureWithFacePosRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int param[][4],int facenum, char *outFeature);

	///@brief
	///ÌØÕ÷ÈÚºÏ£¬×î¶àŽ«ÈëÊ®žöÌØÕ÷
	///@param
	///feature-ÐèÒªÈÚºÏµÄÌØÕ÷Œ¯
	///weight-ÌØÕ÷Œ¯µÄÈšÖØ
	///count-ÊµŒÊŽ«ÈëÌØÕ÷žöÊý
	///outFeature-ÈÚºÏºóµÄÌØÕ÷
IS_API int ISMergeFeature(char *feature[10], float weight[10], int count, char *outFeature);

    ///@brief
    ///·µ»Ø¶ÔÊäÈëµÄ2048Î¬ÌØÕ÷½øÐÐPca
IS_API int ISGetPcaFea(int channel,char* fea_Org,char* fea_Pca);

	///@brief
	///·µ»Øµ±Ç°SDK  ÄÜ¹»ŽŽœšµÄÌØÕ÷ÌáÈ¡Æ÷×îŽóÍšµÀÊý
IS_API int ISGetMaxFeatureChannel();

	///@brief
	///·µ»Øµ±Ç°SDK  ÌØÕ÷ÌáÈ¡Æ÷ÐÅÏ¢
IS_API const char* ISGetFeatureVersionInfo();
	

#if defined (__cplusplus)
}
#endif


#endif


