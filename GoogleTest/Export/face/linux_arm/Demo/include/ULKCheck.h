/*UKey operation function definitions.
**Add the .h file and the corresponding .cpp file to project.
**Author:
**			LuoDaijian
**Date: 20161103
*//*
#ifndef _ULKCHECK_H_
#define _ULKCHECK_H_

#ifdef ULKCHECK_EXPORTS
#define ULK_API  __declspec(dllexport)
#else
#define ULK_API
#endif

/*����UK������������*/
/*typedef  enum
{
	LOCK_TYPE_FACE = 1,
	LOCK_TYPE_DIRECTALARM,
	LOCK_TYPE_XRAY,
	LOCK_TYPE_OCR,
	LOCK_TYPE_FIRE,
	LOCK_TYPE_CROWD,
	LOCK_TYPE_VEHICLE
}LockType;*/

/*�����UK �л�ȡ����Ϣ*/
/*typedef struct
{*/
	/*ǰ����ͺ��룬������֤UK�ĺϷ��ԡ�*/
/*	unsigned int preCode[2];
	unsigned int postCode[2];*/

	/*ģ��Ŀ����ԣ�ÿ��ģ��ռ1bit��1Ϊ���ã�0Ϊ������*/
	//unsigned short modEnable;
	
	/*֧�ֵ���󲢷�����*/
//	unsigned short concurNum;

	/*Uk ���ͣ�0��ӲKey;1����Key*/
/*	unsigned short ukType;

	unsigned short reserved;

}LockInfo;*/

/*���巵��ֵ����*/
/*typedef enum
{ 
	/*ӲKey�ɹ�*/
//	LOCK_STATUS_OK,
	/*Ukey ������*/
//	LOCK_STATUS_NOT_EXIST,
	/*Ukey ��Ϣ��ȡ����*/
//	LOCK_STATUS_INFO_ERR,
	/*UKey ��Ч����֤��Ϣ��ƥ��*/
//	LOCK_STATUS_INVALID,
	/*UKey ����������Ͳ�ƥ��*/
//	LOCK_STATUS_UNMATCH,
	/*UKey ����*/
//	LOCK_STATUS_EXPIRE,
	/*UKey �����Ч*/
//	LOCK_STATUS_HND_INV
//}LockStatus;
/*
#if defined (__cplusplus)
extern "C" {
#endif*/

/*UK��¼
**������type�� ����������������
**			   pInfo��UK�洢����Ϣ�����
**		       lockId�����صĵ�¼���������������ʹ�ã����
**����ֵ��
**				LockSattus��LOCK_STATUS_OK��ʾ�ɹ���������ʾʧ�ܡ�
**˵�������жϵ�¼�Ƿ�ɹ�ʱ���˼�麯������ֵ�⣬��������UK��ǰ���������Ƿ���ȷ��
*//*
ULK_API LockStatus LockLogin(LockType type, LockInfo* pInfo, unsigned long* lockId);

/*UK ��飬���ڵ�¼����UK�Ƿ���ڻ���Ϣ�Ƿ���ȷ���������Ե���
**������
**			lockId����¼���ص�UK���������
**			pInfo��UK�洢����Ϣ�����
**����ֵ��
**				LockSattus��LOCK_STATUS_OK��ʾ�ɹ���������ʾʧ�ܡ�
**˵�����ڵ���ʱ���˼�麯������ֵ�⣬��������UK��ǰ���������Ƿ���ȷ��
*//*
ULK_API LockStatus LockCheck(unsigned long lockId, LockInfo* pInfo);

/*UK �˳���¼��ʹ����Ϻ��˳�UK
**������
**			lockId����¼���ص�UK���������
**����ֵ��
**				LockSattus��LOCK_STATUS_OK��ʾ�ɹ���������ʾʧ�ܡ�
*//*
ULK_API LockStatus LockLogout(unsigned long lockId);

#if defined (__cplusplus)
}
#endif

#endif*/