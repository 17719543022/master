#include "stdafx.h"
#include "sdk_error_code.h"

static char out[50] = {0};

char * toCode(int x)
{
	if(x == 0) strcpy_s(out, "SUCC");
	else if(x == 1001) strcpy_s(out, "PARAM_BUFFER_TOO_SMALL");
	else if(x == 1100) strcpy_s(out, "IMG_DATA_ERROR");
	else if(x == 1101) strcpy_s(out, "IMG_SIZE_TOO_LARGE");
	else if(x == 1102) strcpy_s(out, "IMG_SIZE_TOO_SMALL");
	else if(x == 1200) strcpy_s(out, "DETECTION_ERROR");
	else if(x == 1201) strcpy_s(out, "DETECT_NO_FACE");
	else if(x == 1202) strcpy_s(out, "GET_KEY_POINT_ERROR");
	else if(x == 1203) strcpy_s(out, "GET_FEATURE_ERROR");
	else if(x == 1205) strcpy_s(out, "COMPARE_ERROR");
	else if(x == 1206) strcpy_s(out, "COMPARE_MN_ERROR");
	else if(x == 1300) strcpy_s(out, "UKEY_CHECK_ERROR");
	else if(x == 1301) strcpy_s(out, "NO_DET_TRACK_AUTHORIZE");
	else if(x == 1302) strcpy_s(out, "NO_FEATURE_AUTHORIZE");
	else if(x == 1303) strcpy_s(out, "NO_COMPARE_AUTHORIZE");
	else if(x == 1304) strcpy_s(out, "DET_CHANNEL_NUM_EXCEED");
	else if(x == 1305) strcpy_s(out, "FEA_CHANNEL_NUM_EXCEED");
	else if(x == 1306) strcpy_s(out, "COMPARE_CHANNEL_NUM_EXCEED");
	else if(x == 9999) strcpy_s(out, "UNKNOWN_ERROR");
	else strcpy_s(out, "UNDEFINED_ERROR");
	
	return out;
}
