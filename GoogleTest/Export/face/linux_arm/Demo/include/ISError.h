#ifndef ISError_H
#define ISError_H


#define SUCC 				          0	      //成功
#define UNKNOWN_ERROR  			      9999    //未知错误
#define PARAM_BUFFER_TOO_SMALL	      1001    //函数返回值缓冲区太小
	

//图片相关
#define IMG_DATA_ERROR				  1100    //图片数据错误
#define IMG_SIZE_TOO_LARGE		      1101    //图片太大
#define IMG_SIZE_TOO_SMALL		      1102    //图片太小


//算法相关
#define DETECTION_ERROR               1200    //检测错误
#define DETECT_NO_FACE 		          1201    //没有检测到人脸
#define GET_KEY_POINT_ERROR		      1202    //获取关键点错误
#define GET_FEATURE_ERROR		      1203    //提取特征错误
#define FEATURE_SIZE_ERROR	          1204    //特征长度错误
#define COMPARE_ERROR			      1205    //1:1比对错误
#define COMPARE_MN_ERROR              1206    //M:N比对错误


//授权相关
#define UKEY_CHECK_ERROR              1300    //ukey检测错误
#define NO_DET_TRACK_AUTHORIZE        1301    //未授权检测功能
#define NO_FEATURE_AUTHORIZE          1302    //未授权特征提取功能
#define NO_COMPARE_AUTHORIZE          1303    //未授权比对功能
#define DET_CHANNEL_NUM_EXCEED        1304    //超出最大授权检测通道数
#define FEA_CHANNEL_NUM_EXCEED        1305    //超出最大授权特征通道数
#define COMPARE_CHANNEL_NUM_EXCEED    1306    //超出最大授权比对通道数



#endif


