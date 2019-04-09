#ifndef ISError_H
#define ISError_H


#define SUCC 				          0	      //�ɹ�
#define UNKNOWN_ERROR  			      9999    //δ֪����
#define PARAM_BUFFER_TOO_SMALL	      1001    //��������ֵ������̫С
	

//ͼƬ���
#define IMG_DATA_ERROR				  1100    //ͼƬ���ݴ���
#define IMG_SIZE_TOO_LARGE		      1101    //ͼƬ̫��
#define IMG_SIZE_TOO_SMALL		      1102    //ͼƬ̫С


//�㷨���
#define DETECTION_ERROR               1200    //������
#define DETECT_NO_FACE 		          1201    //û�м�⵽����
#define GET_KEY_POINT_ERROR		      1202    //��ȡ�ؼ������
#define GET_FEATURE_ERROR		      1203    //��ȡ��������
#define FEATURE_SIZE_ERROR	          1204    //�������ȴ���
#define COMPARE_ERROR			      1205    //1:1�ȶԴ���
#define COMPARE_MN_ERROR              1206    //M:N�ȶԴ���


//��Ȩ���
#define UKEY_CHECK_ERROR              1300    //ukey������
#define NO_DET_TRACK_AUTHORIZE        1301    //δ��Ȩ��⹦��
#define NO_FEATURE_AUTHORIZE          1302    //δ��Ȩ������ȡ����
#define NO_COMPARE_AUTHORIZE          1303    //δ��Ȩ�ȶԹ���
#define DET_CHANNEL_NUM_EXCEED        1304    //���������Ȩ���ͨ����
#define FEA_CHANNEL_NUM_EXCEED        1305    //���������Ȩ����ͨ����
#define COMPARE_CHANNEL_NUM_EXCEED    1306    //���������Ȩ�ȶ�ͨ����



#endif


