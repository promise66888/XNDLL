#pragma once
#include "FanucMachineTool.h"
#include "pch.h"
#include<iostream>
#include<cmath>

using namespace std;

FanucMachineTool::FanucMachineTool()
{
}

FanucMachineTool::~FanucMachineTool()
{
}

void FanucMachineTool::setConfig(string ip1, unsigned short port1, long timeout1, int nctype1, MachineInfo * info)
{
	info->connectinfo.ip = ip1;
	info->connectinfo.port = port1;
	info->connectinfo.timeout = timeout1;
	info->connectinfo.nc_type = nctype1;
}

short FanucMachineTool::Connect(MachineInfo * info)
{
	info->connectinfo.state = cnc_allclibhndl3(info->connectinfo.ip.c_str(), info->connectinfo.port, info->connectinfo.timeout, &info->connectinfo.FlibHndl);
	if (info->connectinfo.state == EW_OK)
	{
		info->connectinfo.flag = true;
		return info->connectinfo.state;
	}
	else
	{
		info->connectinfo.flag = false;
		cout << "Failed to connect，error code：" << info->connectinfo.state;
		return info->connectinfo.state;
	}
}

short FanucMachineTool::Disconnect(MachineInfo * info)
{
	cout << "DLL中handle:" << info->connectinfo.FlibHndl;
	info->connectinfo.flag = 0;
	short ret = cnc_freelibhndl(info->connectinfo.FlibHndl);
	if (info->connectinfo.state == 0) {
		return ret;
	}
	else {
		cout << "Connection not established correctly, error code:" << ret;
		return ret;
	}
}

short FanucMachineTool::getSpindleLoad(MachineInfo * info)
{
	ODBSPLOAD sp[MAX_SPINDLE];
	short num = MAX_SPINDLE;
	short ret = cnc_rdspmeter(info->connectinfo.FlibHndl, 0, &num, sp);
	if (ret == EW_OK)
	{
		int dec = sp[num - 1].spload.dec;
		int data = sp[num - 1].spload.data;

		if (0 == dec)
		{
			info->spindleinfo.sp_load = data * 1.0;
		}
		else {
			info->spindleinfo.sp_load = data * pow(10, -dec);
		}
	}
	else {
		cout << "fail to read SpindleLoad with code:" << ret;
	}
	return ret;
}

short FanucMachineTool::getSpindleSpeed(MachineInfo * info)
{
	ODBACT buf;
	short ret = cnc_acts(info->connectinfo.FlibHndl, &buf);
	if (ret == EW_OK)
	{
		info->spindleinfo.sp_speed = buf.data;
	}
	else {
		cout << "fail to read SpindleSpeed with code:" << ret;
	}
	return ret;
}

short FanucMachineTool::getAxisFeed(MachineInfo * info)
{
	ODBACT buf;
	short ret = cnc_actf(info->connectinfo.FlibHndl, &buf);
	if (ret == EW_OK)
	{
		info->axisinfo.axis_actfeed = buf.data;
	}
	else {
		cout << "fail to read AxisFeed with code:" << ret;
	}
	return ret;
}

short FanucMachineTool::getAxisFeedrate(MachineInfo * info)
{
	IODBPMC buf;
	short ret;
	short adr_type = 0, data_type = 0;
	unsigned short length = 10, s_number = 12, e_number = 13;
	ret = pmc_rdpmcrng(info->connectinfo.FlibHndl, adr_type, data_type, s_number, e_number, length, &buf);
	if (ret == EW_OK)
	{
		int rate;
		rate = -(int)buf.u.idata[0] - 1;
		info->axisinfo.axis_feedrate = rate;
	}
	else {
		cout << "fail to read AxisFeedRate with code:" << ret << endl;
	}
	return ret;
}

short FanucMachineTool::getPosition(MachineInfo * info)
{
	ODBPOS position[MAX_AXIS];
	short num = MAX_AXIS;
	short ret = cnc_rdposition(info->connectinfo.FlibHndl, -1, &num, position);
	if (ret == EW_OK)
	{
		for (int i = 0; i < num; i++) {
			info->axisinfo.absolute_position[i] = position[i].abs.data * pow(10, -position[i].abs.dec);
			info->axisinfo.relative_position[i] = position[i].rel.data * pow(10, -position[i].rel.dec);
		}
	}
	else {
		cout << "fail to read Position with code:" << ret << endl;
	}
	return ret;
}

short FanucMachineTool::getToolNum(MachineInfo * info)
{
	ODBM macro;
	short ret = cnc_rdmacro(info->connectinfo.FlibHndl,4012,10,&macro);
	if (ret == EW_OK)
	{
		info->toolinfo.toolnum = macro.mcr_val;
		return ret;
	}
	else
	{
		cout << "fail to read ToolNum with code:" << ret << endl;
		return ret;
	}
}

short FanucMachineTool::getProgLineNum(MachineInfo * info)
{
	ODBPRO dbpro;
	ODBSEQ buf;
	short ret = cnc_rdprgnum(info->connectinfo.FlibHndl, &dbpro);
	short ret2 = cnc_rdseqnum(info->connectinfo.FlibHndl, &buf);
	if (ret == EW_OK && ret2 == EW_OK)
	{
		info->ncinfo.ProNum = dbpro.mdata;//主程序号
		info->ncinfo.ProLineNum = buf.data;//当前运行程序号（子程序号）
		return ret;
	}
	else
	{
		if (ret != 0)
		{
			cout << "fail to read ProNum with code:" << ret << endl;
			return ret;
		}
		if (ret2 != 0)
		{
			cout << "fail to read ProLineNum with code:" << ret2 << endl;
			return ret2;
		}
	}
}
