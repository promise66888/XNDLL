#pragma once
#include"MachineBaseInfo.h"
#include"Fwlib32.h"

class XNLIBAPI FanucMachineTool
{
public:
	FanucMachineTool();
	~FanucMachineTool();
	void setConfig(string ip1, unsigned short port1, long timeout1, int nctype1, MachineInfo* info);		//��ʼ������
	short Connect(MachineInfo* info);//����
	short Disconnect(MachineInfo* info);//�Ͽ�����

	//���ắ��
	short getSpindleLoad(MachineInfo* info);//���Ḻ��
	short getSpindleSpeed(MachineInfo* info);//����ת��

	//�����ắ��
	short getAxisFeed(MachineInfo* info);//�����ٶ�
	short getAxisFeedrate(MachineInfo* info);//��������

	//���ߺ���
	short getToolNum(MachineInfo* info);//���ߺ�

	//NC����
	short getProgLineNum(MachineInfo* info);//�����к�(ÿ��ǰ�����O )

	MachineInfo m_info;
};

