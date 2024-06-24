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

struct ConnectInfo  //������Ϣ
{
	int nc_type = 0;            //����ϵͳ����
	short state;             //����״̬
	string ip;
	unsigned short port;
	long timeout = 10;
	unsigned short FlibHndl;
	long mySleep = -1;
	bool flag = 0;           //��ȡ��־
};

struct AxisInfo  //��������Ϣ
{
	short state;
	double axis_actfeed = -99;//�������ٶ�
	double axis_feedrate = -99;//��������
	double absolute_position[6] = { -99,-99,-99,-99,-99,-99 };//��������
	double relative_position[6] = { -99,-99,-99,-99,-99,-99 };//�������
	string lastTime = "-1";
};

struct SpindleInfo //������Ϣ
{
	short state;
	double sp_speed = -99;//����ת�٣�ʵ�ʣ�
	int sp_rate = -1;//����ת�ٱ���
	double sp_load = -99;//���Ḻ��
	string lastTime = "-1";
	bool isSuccess = false;
};

struct NCInfo   //ϵͳ��Ϣ
{
	short state;
	bool isSuccess = false;
	int ProLineNum = -99;//����ִ���к�
	int ProNum = -99;//�������
};

struct ToolInfo   //ϵͳ��Ϣ
{
	short state;
	int toolnum = -99;//���ߺ�
	int group = -99;//�������
	bool isSuccess = false;
};

struct MachineInfo //������Ϣ
{
	ConnectInfo connectinfo;
	AxisInfo axisinfo;
	SpindleInfo spindleinfo;
	NCInfo ncinfo;
	ToolInfo toolinfo;
};