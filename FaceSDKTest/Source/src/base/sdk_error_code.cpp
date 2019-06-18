#include "sdk_error_code.h"

static char out[50] = {0};

char * toCode(int x)
{
	if(x == 0) strcpy(out, "SUCC");
	else if(x == 1001) strcpy(out, "PARAM_BUFFER_TOO_SMALL");
	else if(x == 1100) strcpy(out, "IMG_DATA_ERROR");
	else if(x == 1101) strcpy(out, "IMG_SIZE_TOO_LARGE");
	else if(x == 1102) strcpy(out, "IMG_SIZE_TOO_SMALL");
	else if(x == 1200) strcpy(out, "DETECTION_ERROR");
	else if(x == 1201) strcpy(out, "DETECT_NO_FACE");
	else if(x == 1202) strcpy(out, "GET_KEY_POINT_ERROR");
	else if(x == 1203) strcpy(out, "GET_FEATURE_ERROR");
	else if(x == 1205) strcpy(out, "COMPARE_ERROR");
	else if(x == 1206) strcpy(out, "COMPARE_MN_ERROR");
	else if(x == 1300) strcpy(out, "UKEY_CHECK_ERROR");
	else if(x == 1301) strcpy(out, "NO_DET_TRACK_AUTHORIZE");
	else if(x == 1302) strcpy(out, "NO_FEATURE_AUTHORIZE");
	else if(x == 1303) strcpy(out, "NO_COMPARE_AUTHORIZE");
	else if(x == 1304) strcpy(out, "DET_CHANNEL_NUM_EXCEED");
	else if(x == 1305) strcpy(out, "FEA_CHANNEL_NUM_EXCEED");
	else if(x == 1306) strcpy(out, "COMPARE_CHANNEL_NUM_EXCEED");
	else if(x == 9999) strcpy(out, "UNKNOWN_ERROR");
	else strcpy(out, "UNDEFINED_ERROR");
	
	return out;
}
