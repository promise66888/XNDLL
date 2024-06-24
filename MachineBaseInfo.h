#pragma once

#ifdef FANUC_MACHINE_TOOL_EXPORTS
#define XNLIBAPI __declspec(dllexport)
#else
#define XNLIBAPI __declspec(dllimport)
#endif

#define no_init_all deprecated
#define TYPE_FANUC 0
#include<string>

using namespace std;

struct ConnectInfo  //连接信息
{
	int nc_type = 0;            //数控系统种类
	short state;             //连接状态
	string ip;
	unsigned short port;
	long timeout = 10;
	unsigned short FlibHndl;
	long mySleep = -1;
	bool flag = 0;           //读取标志
};

struct AxisInfo  //进给轴信息
{
	short state;
	double axis_actfeed = -99;//进给轴速度
	double axis_feedrate = -99;//进给倍率
	double absolute_position[6] = { -99,-99,-99,-99,-99,-99 };//绝对坐标
	double relative_position[6] = { -99,-99,-99,-99,-99,-99 };//相对坐标
	string lastTime = "-1";
};

struct SpindleInfo //主轴信息
{
	short state;
	double sp_speed = -99;//主轴转速（实际）
	int sp_rate = -1;//主轴转速倍率
	double sp_load = -99;//主轴负载
	string lastTime = "-1";
	bool isSuccess = false;
};

struct NCInfo   //系统信息
{
	short state;
	bool isSuccess = false;
	int ProLineNum = -99;//程序执行行号
	int ProNum = -99;//主程序号
};

struct ToolInfo   //系统信息
{
	short state;
	int toolnum = -99;//刀具号
	int group = -99;//刀具组号
	bool isSuccess = false;
};

struct MachineInfo //机床信息
{
	ConnectInfo connectinfo;
	AxisInfo axisinfo;
	SpindleInfo spindleinfo;
	NCInfo ncinfo;
	ToolInfo toolinfo;
};