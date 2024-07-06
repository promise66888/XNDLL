#pragma once
#include"open62541.h"
#include"MachineBaseInfo.h"

class XNLIBAPI SiemensMachineTool
{
public:
	SiemensMachineTool();
	~SiemensMachineTool();
	void setConfig(string url1, string user1, string password1, string cer_der1, string key_der1, int nctype1, MachineInfo* info);//初始化
	short Connect(MachineInfo* info);//连接

private:
	UA_ByteString loadFile(const char * path);
};

