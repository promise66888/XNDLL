#include "pch.h"
#include "SiemensMachineTool.h"
#include<string>
#include<iostream>

using namespace std;

SiemensMachineTool::SiemensMachineTool()
{
}

SiemensMachineTool::~SiemensMachineTool()
{
}

void SiemensMachineTool::setConfig(string url1, string user1, string password1, string cer_der1, string key_der1, int nctype1, MachineInfo* info)
{
	info->connectinfo.ip = url1;
	info->connectinfo.nc_type = nctype1;
	info->connectinfo.username = user1;
	info->connectinfo.password = password1;
	info->connectinfo.ua_cerder = cer_der1;
	info->connectinfo.ua_keyder = key_der1;

	//初始化客户端
	info->connectinfo.ua_client = UA_Client_new();
	UA_ClientConfig* config = UA_Client_getConfig(info->connectinfo.ua_client);
	UA_ByteString certificate = loadFile(info->connectinfo.ua_cerder.c_str());  // 修改为实际的客户端证书路径
	UA_ByteString privateKey = loadFile(info->connectinfo.ua_keyder.c_str());    // 修改为实际的客户端私钥路径
	config->clientDescription.applicationUri = UA_STRING_ALLOC("urn:open62541.client.application");
	config->securityMode = UA_MESSAGESECURITYMODE_NONE;//设置安全模式
	config->securityPolicyUri = UA_STRING_ALLOC("http://opcfoundation.org/UA/SecurityPolicy#None");//设置安全策略
	UA_ClientConfig_setDefaultEncryption(config, certificate, privateKey,
		nullptr, 0,
		nullptr, 0);
	config->clientDescription.applicationUri = UA_STRING_ALLOC("urn:open62541.client.application");
}

short SiemensMachineTool::Connect(MachineInfo * info)
{
	//连接
	UA_StatusCode retval = UA_Client_connectUsername(info->connectinfo.ua_client, info->connectinfo.ip.c_str(), info->connectinfo.username.c_str(), info->connectinfo.password.c_str());
	if (retval != UA_STATUSCODE_GOOD) {
		UA_Client_delete(info->connectinfo.ua_client);
		cout << "Failed to connect，error code:" << retval;
		info->connectinfo.state = retval;
		return (short)info->connectinfo.state;
	}
	info->connectinfo.state = retval;
	info->connectinfo.flag = true;
	return info->connectinfo.state;
}

UA_ByteString SiemensMachineTool::loadFile(const char * path)
{
	UA_ByteString fileContents = UA_STRING_NULL;
	FILE* fp;
	errno_t err = fopen_s(&fp, path, "rb");
	if (err != 0 || !fp) {
		cerr << "Failed to open file: " << path << endl;
		return fileContents;
	}
	fseek(fp, 0, SEEK_END);
	size_t fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fileContents.length = fileSize;
	fileContents.data = (UA_Byte*)UA_malloc(fileSize * sizeof(UA_Byte));
	if (fileContents.data) {
		fread(fileContents.data, sizeof(UA_Byte), fileSize, fp);
	}
	fclose(fp);
	return fileContents;
}
