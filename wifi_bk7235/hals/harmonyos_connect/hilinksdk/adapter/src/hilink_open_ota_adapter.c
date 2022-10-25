/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2021. All rights reserved.
 * Description: OTA����ʵ�� (���豸����ʵ��)
 */
#include "hilink_open_ota_adapter.h"
#include <stdio.h>
#include <unistd.h>
#include "securec.h"


#define DOWNLOAD_PATITION_ADDR 0x253000   //68+2048+300KB
#define DOWNLOAD_PATITION_LEN 0x187000	  //1536KB
static unsigned int write_length = 0;
#define HILINK_OK 0
#define HILINK_ERROR -1

/*
 * Flash��ʼ��
 * ����ֵ��trueʱ����ʾ��ʼ������
 * ����ֵ��falseʱ����ʾ��ʼ���쳣
 */
bool HILINK_OtaAdapterFlashInit(void)
{
	printf("HILINK_OtaAdapterFlashInit start\r\n");
	IoTFlashInit();
	write_length = 0;
	return true;
}


/*
 * �ж���Ҫ�����ķ���
 * ����ֵ��UPGRADE_FW_BIN1ʱ����ʾ�����̼�������1
 * ����ֵ��UPGRADE_FW_BIN2ʱ����ʾ�����̼�������2
 */
unsigned int HILINK_OtaAdapterGetUpdateIndex(void)
{
	printf("HILINK_OtaAdapterGetUpdateIndex start\r\n");
    return UPGRADE_FW_BIN1;
}

/*
 * ������Ҫ�����ķ���
 * size��ʾ��Ҫ�����ķ�����С
 * ����ֵ��ILINK_OKʱ����ʾ�����ɹ�
 * ����ֵ��HILINK_ERRORʱ����ʾ����ʧ��
 */
int HILINK_OtaAdapterFlashErase(unsigned int size)
{
	printf("HILINK_OtaAdapterFlashErase start size=%d\r\n",size);
	return IoTFlashErase(DOWNLOAD_PATITION_ADDR,DOWNLOAD_PATITION_LEN);
}

/*
 * ��������д�������ķ���
 * buf��ʾ��д������
 * bufLen��ʾ��д�����ݵĳ���
 * ����ֵ��HILINK_OKʱ����ʾд��ɹ�
 * ����ֵ��HILINK_ERRORʱ����ʾд��ʧ��
 */
int HILINK_OtaAdapterFlashWrite(const unsigned char *buf, unsigned int bufLen)
{
	//printf("HILINK_OtaAdapterFlashWrite start\r\n");
	#if 1
	int ret;
	if (bufLen == 0) 
	{
		return HILINK_OK;
	}
	if (buf == NULL)
	{
		return HILINK_ERROR;
	}
	
	ret = IoTFlashWrite(DOWNLOAD_PATITION_ADDR + write_length, bufLen, buf, 0);

	write_length += bufLen;
	if(ret == 0)
		return HILINK_OK;
	else
		return HILINK_ERROR;
	#else
	return HILINK_OK;
	#endif
}


/*
 * ��ȡ������������
 * offset��ʾ��дƫ��
 * buf��ʾ������ݵ��ڴ��ַ
 * bufLen��ʾ������ݵ��ڴ泤��
 * ����ֵ��HILINK_OKʱ����ʾ��ȡ�ɹ�
 * ����ֵ��HILINK_ERRORʱ����ʾ��ȡʧ��
 */
int HILINK_OtaAdapterFlashRead(unsigned int offset, unsigned char *buf, unsigned int bufLen)
{
	//printf("HILINK_OtaAdapterFlashRead start\r\n");
	#if 1
    int ret;
	if ( (buf == NULL) || (bufLen == 0)) 
	{
		return HILINK_ERROR;
	}
  ret = IoTFlashRead(DOWNLOAD_PATITION_ADDR + offset, bufLen, buf);

	if(ret == 0)
		return HILINK_OK;
	else
		return HILINK_ERROR;
	#else
	return HILINK_OK;
	#endif
}

/*
 * ������������
 * ����ֵ��trueʱ����ʾ��������
 * ����ֵ��falseʱ����ʾ�����쳣
 */
bool HILINK_OtaAdapterFlashFinish(void)
{
	printf("HILINK_OtaAdapterFlashFinish start\r\n");
	IoTFlashDeinit();
    return true;
}

/* ��ȡ����������󳤶� */
unsigned int HILINK_OtaAdapterFlashMaxSize(void)
{
	printf("HILINK_OtaAdapterFlashMaxSize start\r\n");
	
	return DOWNLOAD_PATITION_LEN;
}

/*
 * ���ݱ�־����ģ��
 * flag��ʾ������־
 * ��flag��RESTART_FLAG_NOWʱ����ʾֻ��MCU����ʱ��������
 * ��flag��RESTART_FLAG_LATERʱ����ʾ��ģ��ʱ�л�������������
 */
void HILINK_OtaAdapterRestart(int flag)
{
	printf("HILINK_OtaAdapterRestart start\r\n");
 reboot();
    return;
}

/*
 * ��ʼģ������
 * type��ʾ��������
 * ��type��UPDATE_TYPE_MANUALʱ����ʾ�����������������û�����������ֶ�����
 * ��type��UPDATE_TYPE_AUTOʱ����ʾ�������������Ǿ����û�ͬ����Զ�����
 * ����ֵ��RETURN_OKʱ����ʾ����ɹ���HiLink SDK����ʼ������������
 * ����ֵ��RETURN_ERRORʱ����ʾ�����ɹ���HiLink SDK����ֹ������������
 * ע�⣺���ֶ����������£�HiLink SDK�ڽ��յ��û�����������ָ��󣬽�ֱ�ӵ��ô˽ӿڣ�
 * ���Զ����������£���HiLink SDK�ڵ���HilinkGetRebootFlag�ӿڷ���ֵ��MODULE_CAN_REBOOTʱ��HiLink SDK�����ô˽ӿڡ�
 * ���̿��ڴ˽ӿ�����ɺ�����������صĴ���
 * ������10���ӵ�1Сʱ�����ʱ����һ���Ƿ����°汾��֮���Ե�ǰʱ��Ϊ��㣬23Сʱ��1Сʱ�����ֵ�����Լ���°汾��
 * ����û������Զ��������أ���⵽���°汾�����ǿ�������������£��ͽ����°汾�����أ�������ɺ��Զ�������
 * �Զ��������̿������賿���У���˳�����ʵ������������ع���ʱ��ȷ�������������ذ�װ�̼��������豸ʱ������û�����
 * Ӱ�죬���緢�������������ȡ�
 */
int HILINK_OtaStartProcess(int type)
{
	printf("HILINK_OtaStartProcess start type =%d\r\n",type);
    return RETURN_OK;
}

/*
 * ģ����������
 * status��ʾ�������
 * ��status��100ʱ����ʾ�����ɹ�
 * ��status����100ʱ����ʾ����ʧ��
 * ����ֵ��RETURN_OKʱ����ʾ����ɹ���HiLink SDK����������־���л���������־
 * ����ֵ����RETURN_OKʱ����ʾ�����ɹ���HiLink SDK����ֹ������������
 * ע�⣺HiLink SDK�ڽ��̼�д�뵽OTA����������������У��ͨ���󣬽����ó�������Ĵ˽ӿڣ�
 * ���̿��ڴ˽ӿ�����ɺ�����������صĴ���
 * ������10���ӵ�1Сʱ�����ʱ����һ���Ƿ����°汾��֮���Ե�ǰʱ��Ϊ��㣬23Сʱ��1Сʱ�����ֵ�����Լ���°汾��
 * ����û������Զ��������أ���⵽���°汾�����ǿ�������������£��ͽ����°汾�����أ�������ɺ��Զ�������
 * �Զ��������̿������賿���У���˳�����ʵ������������ع���ʱ��ȷ�������������ذ�װ�̼��������豸ʱ������û�����
 * Ӱ�죬���緢�������������ȣ����������Ƿ�Ϊ�Զ������ɲο��ӿ�HilinkOtaStartProcess�Ĳ���type��������
 */
int HILINK_OtaEndProcess(int status)
{
	printf("HILINK_OtaEndProcess start status=%d\r\n",status);
    return RETURN_OK;
}

/*
 * �ж�ģ���Ƿ�����������������
 * ����ֵ��MODULE_CAN_REBOOTʱ����ʾģ���������������������HiLink SDK����ʼ�Զ��������̡�
 * ����ֵ��MODULE_CANNOT_REBOOTʱ����ʾģ�鲻������������������HiLink SDK�������б����Զ��������̡�
 * ע�⣺���û�ͬ���豸�����Զ�����������£�HiLink SDK���ô˽ӿڻ�ȡ�豸��ǰҵ��״̬�£�ģ���Ƿ�������������������ı�־��
 * ֻ�е��豸����ҵ�����״̬ʱ���ӿڲſ��Է���MODULE_CAN_REBOOT��
 * ���豸����ҵ��ǿ���״̬ʱ���ӿڷ���MODULE_CANNOT_REBOOT��
 */
int HILINK_GetRebootFlag(void)
{
	printf("HILINK_GetRebootFlag start\r\n");
	return MODULE_CAN_REBOOT;
}

/*
 * �����豸��ota�°汾����
 * ��⵽�İ汾��sdk��ͨ��cb�ص�������������
 */
void HILINK_TrigOtaSelfUpdate(TrigSelfUpdateCb cb)
{
    return;
}