/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: ���MCU��������ʵ�� (���豸����ʵ��)
 */

#include "hilink_open_ota_mcu_adapter.h"

/*
 * ��ȡMCU��ǰ�汾
 * version��ʾ�汾�ַ���
 * inLen��ʾ�����ַ�������
 * outLen��ʾ����ַ�������
 * ����ֵ��RETURN_OKʱ����ʾ��ȡ�ɹ�
 * ����ֵ��RETURN_ERROR_NO_MCUʱ����ʾû��MCU
 * ����ֵ��RETURN_ERRORʱ����ʾ��ȡʧ��
 * ����ֵ��RETURN_MCU_NO_NEED_OTAʱ����ʾ����ҪMCU����
 * ע�⣺�����ȡ����MCU�İ汾���򲻶�MCU����������
 * ���鳧����MCU���������󣬻����������󣬾ͽ�MCU�İ汾�Ŵ��ݸ�ģ�飬ȷ��ģ����Ի�ȡ��MCU�İ汾��
 */
int HILINK_GetMcuVersion(char *version, unsigned int inLen, unsigned int *outLen)
{
    /* ����ʵ�ִ˽ӿ� */
    return RETURN_OK;
}

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
int HILINK_NotifyOtaStatus(int flag, unsigned int len, unsigned int type)
{
    /* ����ʵ�ִ˽ӿ� */
    return RETURN_OK;
}

/*
 * HiLink SDK���ó�������Ĵ˽ӿ�֪ͨ���̷���MCU�̼��ļ�����
 * data��ʾ���͵�����
 * len��ʾ���͵����ݵĳ���
 * offset��ʾ���͵�������ʼλ������������̼�����ƫ����
 * �˽ӿ���Ҫ����MCU�����ⲿ�����ݵĴ�����
 * ����ֵ��RETURN_OKʱ��ģ�齫֪ͨ��������ȷ���͸�MCU����MCU��ȷ�����͵����ݣ�HiLink SDK���������������������
 * ����ֵ��RETURN_ERRORʱ��ģ���MCUδ����������֪ͨ��MCU�Ĺ̼��ļ����ݣ�HiLink SDK����ֹ����MCU�̼���������
 */
int HILINK_NotifyOtaData(const unsigned char *data, unsigned int len, unsigned int offset)
{
    /* ����ʵ�ִ˽ӿ� */
    return RETURN_OK;
}