/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: MCU OTA�����ӿ�(���豸����ʵ��)
 */
#ifndef HILINK_OPEN_OTA_MCU_ADAPTER_H
#define HILINK_OPEN_OTA_MCU_ADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* �������� */
#ifndef RETURN_OK
#define RETURN_OK               0
#endif

/* û��MCU */
#ifndef RETURN_ERROR_NO_MCU
#define RETURN_ERROR_NO_MCU     (-1)
#endif

/* MCU������������ */
#ifndef RETURN_ERROR
#define RETURN_ERROR            (-2)
#endif

/* MCU����Ҫ���� */
#ifndef RETURN_MCU_NO_NEED_OTA
#define RETURN_MCU_NO_NEED_OTA  (-3)
#endif

/* �ֶ����� */
#ifndef UPDATE_TYPE_MANUAL
#define UPDATE_TYPE_MANUAL      0x00
#endif

/* �Զ����� */
#ifndef UPDATE_TYPE_AUTO
#define UPDATE_TYPE_AUTO        0x01
#endif

/* ��ʼ����MCU���� */
#ifndef START_SEND_DATA
#define START_SEND_DATA         0
#endif

/* ����MCU���ݽ��� */
#ifndef STOP_SEND_DATA
#define STOP_SEND_DATA          1
#endif

/* �쳣��ֹ */
#ifndef SEND_DATA_ERROR
#define SEND_DATA_ERROR         2
#endif

typedef int (*RptUpgProgressFlagCb)(void);

/*
 * ��ȡMCU��ǰ�汾
 * version��ʾ�汾�ַ���
 * inLen��ʾ�����ַ�������
 * outLen��ʾ����ַ�������
 * ����ֵ��RETURN_OKʱ����ʾ��ȡ�ɹ�
 * ����ֵ��RETURN_ERROR_NO_MCUʱ����ʾû��MCU
 * ����ֵ��RETURN_ERRORʱ����ʾ��ȡʧ��
 * ע�⣺�����ȡ����MCU�İ汾���򲻶�MCU����������
 * ���鳧����MCU���������󣬻����������󣬾ͽ�MCU�İ汾�Ŵ��ݸ�ģ�飬ȷ��ģ����Ի�ȡ��MCU�İ汾��
 */
int HILINK_GetMcuVersion(char *version, unsigned int inLen, unsigned int *outLen);

/*
 * HiLink SDK���ó�������Ĵ˽ӿ�֪ͨMCU�̼������״̬
 * flag��ʾ�������̱�־
 * ��flag��START_SEND_DATAʱ����ʾ֪ͨģ�鼴����ʼ����MCU�̼����ݰ�
 * ��flag��STOP_SEND_DATAʱ����ʾ֪ͨģ��������MCU�̼����ѷ������
 * ��flag��SEND_DATA_ERRORʱ����ʾ֪ͨģ�鱾��MCU�̼������쳣��ֹ
 * len��ʾMCU�̼����Ĵ�С
 * type��ʾ��������
 * ��type��UPDATE_TYPE_MANUALʱ����ʾ�����������������û�����������ֶ�����
 * ��type��UPDATE_TYPE_AUTOʱ����ʾ�������������Ǿ����û�ͬ����Զ�����
 * ����ֵ��RETURN_OKʱ����ʾ����ɹ���HiLink SDK�������������������
 * ����ֵ��RETURN_ERRORʱ����ʾ����ʧ�ܣ�HiLink SDK����ֹ����MCU��������
 * ע�⣺��flag��STOP_SEND_DATAʱ���˽ӿ��践��MCU��̼������Ľ������flag������ֵʱ���践�ؽӿڽ��յ�����Ϣ��Ĵ�������
 * ������10���ӵ�1Сʱ�����ʱ����һ���Ƿ����°汾��֮���Ե�ǰʱ��Ϊ��㣬23Сʱ��1Сʱ�����ֵ�����Լ���°汾��
 * ����û������Զ��������أ���⵽���°汾�����ǿ�������������£��ͽ����°汾�����أ�������ɺ��Զ�������
 * �Զ��������̿������賿���У���˳�����ʵ������������ع���ʱ��ȷ�������������ذ�װ�̼��������豸ʱ������û�����
 * Ӱ�죬���緢�������������ȡ�
 */
int HILINK_NotifyOtaStatus(int flag, unsigned int len, unsigned int type);

/*
 * HiLink SDK���ó�������Ĵ˽ӿ�֪ͨ���̷���MCU�̼��ļ�����
 * data��ʾ���͵�����
 * len��ʾ���͵����ݵĳ���
 * offset��ʾ���͵�������ʼλ������������̼�����ƫ����
 * �˽ӿ���Ҫ����MCU�����ⲿ�����ݵĴ�����
 * ����ֵ��RETURN_OKʱ��ģ�齫֪ͨ��������ȷ���͸�MCU����MCU��ȷ�����͵����ݣ�HiLink SDK���������������������
 * ����ֵ��RETURN_ERRORʱ��ģ���MCUδ����������֪ͨ��MCU�Ĺ̼��ļ����ݣ�HiLink SDK����ֹ����MCU�̼���������
 */
int HILINK_NotifyOtaData(const unsigned char *data, unsigned int len, unsigned int offset);

/*
 * ��ƷOTA����ʱ��������������Ϊ100%�������, APP����ʾ�豸������
 * Ȼ����豸�������ϱ�����0, APP�ϲŻ���ʾ�����ɹ�
 * ͨ���ص�����cb������Hilink Sdk��������Ƿ�������APP�ϱ�����0
 * cb����1ʱhilink sdk������󲻻������ϱ�����0��
 * �ϱ�ʱ���ɲ�Ʒ�Լ�����,����hilink_ota_rpt_prg�����ϱ�
 * cb����0ʱhilink sdk�������������ϱ�����0
 * ��Ʒ����������������ж��Ƿ���Ҫע��cb���粻ע����Ĭ��hilink sdk�������������ϱ�����0
 */
void HILINK_PowerOnRptUpgProgress(RptUpgProgressFlagCb cb);

#ifdef __cplusplus
}
#endif
#endif /* HILINK_OPEN_OTA_BRIDGE_ADAPTER_H */