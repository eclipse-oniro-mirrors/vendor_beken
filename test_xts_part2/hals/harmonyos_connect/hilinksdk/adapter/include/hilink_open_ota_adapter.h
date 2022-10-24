/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2021. All rights reserved.
 * Description: OTA�����ӿ�(���豸����ʵ��)
 */
#ifndef HILINK_OPEN_OTA_ADAPTER_H
#define HILINK_OPEN_OTA_ADAPTER_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* OTA��������1 */
#ifndef UPGRADE_FW_BIN1
#define UPGRADE_FW_BIN1         0x00
#endif

/* OTA��������2 */
#ifndef UPGRADE_FW_BIN2
#define UPGRADE_FW_BIN2         0x01
#endif

/* ֻ��MCU����ʱ�������� */
#ifndef RESTART_FLAG_NOW
#define RESTART_FLAG_NOW        0x01
#endif

/* ��ģ��ʱ�л������������� */
#ifndef RESTART_FLAG_LATER
#define RESTART_FLAG_LATER      0x02
#endif

/* ģ��������� */
#ifndef MODULE_CAN_REBOOT
#define MODULE_CAN_REBOOT       0x01
#endif

/* ģ�鲻������ */
#ifndef MODULE_CANNOT_REBOOT
#define MODULE_CANNOT_REBOOT    0x00
#endif

/* �ֶ����� */
#ifndef UPDATE_TYPE_MANUAL
#define UPDATE_TYPE_MANUAL      0x00
#endif

/* �Զ����� */
#ifndef UPDATE_TYPE_AUTO
#define UPDATE_TYPE_AUTO        0x01
#endif

/* �������� */
#ifndef RETURN_OK
#define RETURN_OK               0
#endif
/* û��MCU */
#ifndef RETURN_ERROR_NO_MCU
#define RETURN_ERROR_NO_MCU     (-1)
#endif
/* ������������ */
#ifndef RETURN_ERROR
#define RETURN_ERROR            (-2)
#endif
/* MCU����Ҫ���� */
#ifndef RETURN_MCU_NO_NEED_OTA
#define RETURN_MCU_NO_NEED_OTA  (-3)
#endif

typedef void (*GetOtaVerCb)(const char *version);
typedef void (*TrigSelfUpdateCb)(const char *url, const unsigned int size);

/*
 * Flash��ʼ��
 * ����ֵ��trueʱ����ʾ��ʼ������
 * ����ֵ��falseʱ����ʾ��ʼ���쳣
 */
bool HILINK_OtaAdapterFlashInit(void);

/*
 * �ж���Ҫ�����ķ���
 * ����ֵ��UPGRADE_FW_BIN1ʱ����ʾ�����̼�������1
 * ����ֵ��UPGRADE_FW_BIN2ʱ����ʾ�����̼�������2
 */
unsigned int HILINK_OtaAdapterGetUpdateIndex(void);

/*
 * ������Ҫ�����ķ���
 * size��ʾ��Ҫ�����ķ�����С
 * ����ֵ��0ʱ����ʾ�����ɹ�
 * ����ֵ��-1ʱ����ʾ����ʧ��
 */
int HILINK_OtaAdapterFlashErase(unsigned int size);

/*
 * ��������д�������ķ���
 * buf��ʾ��д������
 * bufLen��ʾ��д�����ݵĳ���
 * ����ֵ��0ʱ����ʾд��ɹ�
 * ����ֵ��-1ʱ����ʾд��ʧ��
 */
int HILINK_OtaAdapterFlashWrite(const unsigned char *buf, unsigned int bufLen);

/*
 * ��ȡ������������
 * offset��ʾ��дƫ��
 * buf��ʾ������ݵ��ڴ��ַ
 * bufLen��ʾ������ݵ��ڴ泤��
 * ����ֵ��0ʱ����ʾ��ȡ�ɹ�
 * ����ֵ��-1ʱ����ʾ��ȡʧ��
 */
int HILINK_OtaAdapterFlashRead(unsigned int offset, unsigned char *buf, unsigned int bufLen);

/*
 * ������������
 * ����ֵ��trueʱ����ʾ��������
 * ����ֵ��falseʱ����ʾ�����쳣
 */
bool HILINK_OtaAdapterFlashFinish(void);

/* ��ȡ����������󳤶� */
unsigned int HILINK_OtaAdapterFlashMaxSize(void);

/*
 * ���ݱ�־����ģ��
 * flag��ʾ������־
 * ��flag��RESTART_FLAG_NOWʱ����ʾֻ��MCU����ʱ��������
 * ��flag��RESTART_FLAG_LATERʱ����ʾ��ģ��ʱ�л�������������
 */
void HILINK_OtaAdapterRestart(int flag);

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
int HILINK_OtaStartProcess(int type);

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
int HILINK_OtaEndProcess(int status);

/*
 * �ж�ģ���Ƿ�����������������
 * ����ֵ��MODULE_CAN_REBOOTʱ����ʾģ���������������������HiLink SDK����ʼ�Զ��������̡�
 * ����ֵ��MODULE_CANNOT_REBOOTʱ����ʾģ�鲻������������������HiLink SDK�������б����Զ��������̡�
 * ע�⣺���û�ͬ���豸�����Զ�����������£�HiLink SDK���ô˽ӿڻ�ȡ�豸��ǰҵ��״̬�£�ģ���Ƿ�������������������ı�־��
 * ֻ�е��豸����ҵ�����״̬ʱ���ӿڲſ��Է���MODULE_CAN_REBOOT��
 * ���豸����ҵ��ǿ���״̬ʱ���ӿڷ���MODULE_CANNOT_REBOOT��
 */
int HILINK_GetRebootFlag(void);

/*
 * �����豸��ota�°汾���
 * ��⵽�İ汾��sdk��ͨ��cb�ص������ϱ����������Ҫ��ȡ�汾�ţ���ɽ�cb�ÿա�
 * �ϱ���version���Ϊ�գ���δ�ɹ���ȡ���°汾��
 * ע��:1���������Ƶ�����һ��һ��
 * 2���״�ͨ���ֻ������ɹ����ܵ��ã��������Ƴɹ�������5s�����
 */
void HILINK_TrigOtaVersionCheck(GetOtaVerCb cb);

/*
 * �����豸��ota�°汾����
 * ��⵽�İ汾��sdk��ͨ��cb�ص�������������
 */
void HILINK_TrigOtaSelfUpdate(TrigSelfUpdateCb cb);

#ifdef __cplusplus
}
#endif

#endif