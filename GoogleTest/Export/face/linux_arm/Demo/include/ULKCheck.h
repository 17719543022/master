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

/*定义UK保护的软件类别*/
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

/*定义从UK 中获取的信息*/
/*typedef struct
{*/
	/*前导码和后导码，用于验证UK的合法性。*/
/*	unsigned int preCode[2];
	unsigned int postCode[2];*/

	/*模块的可用性，每个模块占1bit：1为可用，0为不可用*/
	//unsigned short modEnable;
	
	/*支持的最大并发数量*/
//	unsigned short concurNum;

	/*Uk 类型：0，硬Key;1：软Key*/
/*	unsigned short ukType;

	unsigned short reserved;

}LockInfo;*/

/*定义返回值类型*/
/*typedef enum
{ 
	/*硬Key成功*/
//	LOCK_STATUS_OK,
	/*Ukey 不存在*/
//	LOCK_STATUS_NOT_EXIST,
	/*Ukey 信息读取错误*/
//	LOCK_STATUS_INFO_ERR,
	/*UKey 无效，验证信息不匹配*/
//	LOCK_STATUS_INVALID,
	/*UKey 软件保护类型不匹配*/
//	LOCK_STATUS_UNMATCH,
	/*UKey 过期*/
//	LOCK_STATUS_EXPIRE,
	/*UKey 句柄无效*/
//	LOCK_STATUS_HND_INV
//}LockStatus;
/*
#if defined (__cplusplus)
extern "C" {
#endif*/

/*UK登录
**参数：type， 保护的软件类别，输入
**			   pInfo，UK存储的信息，输出
**		       lockId，返回的登录句柄，后续操作均使用，输出
**返回值：
**				LockSattus，LOCK_STATUS_OK表示成功，其他表示失败。
**说明：在判断登录是否成功时除了检查函数返回值外，还必需检查UK的前导、后导码是否正确。
*//*
ULK_API LockStatus LockLogin(LockType type, LockInfo* pInfo, unsigned long* lockId);

/*UK 检查，用于登录后检查UK是否存在或信息是否正确，可周期性调用
**参数：
**			lockId，登录返回的UK句柄，输入
**			pInfo，UK存储的信息，输出
**返回值：
**				LockSattus，LOCK_STATUS_OK表示成功，其他表示失败。
**说明：在调用时除了检查函数返回值外，还必需检查UK的前导、后导码是否正确。
*//*
ULK_API LockStatus LockCheck(unsigned long lockId, LockInfo* pInfo);

/*UK 退出登录，使用完毕后退出UK
**参数：
**			lockId，登录返回的UK句柄，输入
**返回值：
**				LockSattus，LOCK_STATUS_OK表示成功，其他表示失败。
*//*
ULK_API LockStatus LockLogout(unsigned long lockId);

#if defined (__cplusplus)
}
#endif

#endif*/