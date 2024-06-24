#pragma once
#include"MachineBaseInfo.h"
#include"Fwlib32.h"

class XNLIBAPI FanucMachineTool
{
public:
	FanucMachineTool();
	~FanucMachineTool();
	void setConfig(string ip1, unsigned short port1, long timeout1, int nctype1, MachineInfo* info);		//初始化配置
	short Connect(MachineInfo* info);//连接
	short Disconnect(MachineInfo* info);//断开连接

	//主轴函数
	short getSpindleLoad(MachineInfo* info);//主轴负载
	short getSpindleSpeed(MachineInfo* info);//主轴转速

	//进给轴函数
	short getAxisFeed(MachineInfo* info);//进给速度
	short getAxisFeedrate(MachineInfo* info);//进给倍率

	//刀具函数
	short getToolNum(MachineInfo* info);//刀具号

	//NC函数
	short getProgLineNum(MachineInfo* info);//程序行号(每行前需添加O )

	MachineInfo m_info;
};

