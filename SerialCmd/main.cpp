#include "Serial.h"
#include <iostream>
#include <string.h>
#include "cmdlineparser.h"



using namespace std;
CSerial AtCom;
ccutils::cmdline::CmdLineParser parser;

void SendAtCmd(const char *sAtSend)
{
	char strSendbuf[300];
	int nLen;
	strcpy_s(strSendbuf, sAtSend);
	nLen = strlen(strSendbuf);
	strSendbuf[nLen] = 0x0D;
	strSendbuf[nLen + 1] = 0x0A;
	strSendbuf[nLen + 2] = 0;
	AtCom.SendData(strSendbuf, nLen + 2);
}



bool Exefunction()
{
	//命令完整性检查
	if (parser.hasKey("p") == 0 || parser.hasKey("b") == 0 || parser.hasKey("t") == 0 || parser.hasKey("s") == 0 ||
		parser.getValStr("p", 0) == "" || parser.getValStr("b", 0) == "" || parser.getValStr("t", 0) == "" || parser.getValStr("s", 0) == "")
	{
		cout << "Param error,Please check." << endl;
		ProcessLog(_T("Param error,Please check."), LOGDEBUG);
		return FALSE;
	}

	if (AtCom.IsOpened())
	{
		ProcessLog(_T("AtCom.Close()"), LOGDEBUG);
		AtCom.Close();
	}
	if (!AtCom.Open(atoi(parser.getValStr("p", 0).c_str()), atoi(parser.getValStr("b", 0).c_str())))
	{
		ProcessLog(_T("open com fail"), LOGDEBUG);
		return FALSE; 
	}

	SendAtCmd(parser.getValStr("s", 0).c_str());
	time_t Endtime;
	Endtime = time(NULL) + atoi(parser.getValStr("t", 0).c_str());
	char strRcbuf[1024];
	int nLen;
	string szStrGet;
	do
	{
		nLen = AtCom.ReadData(strRcbuf, 1024);
		if (nLen> 0)
		{
			strRcbuf[nLen] = 0;
			szStrGet += strRcbuf;
			ProcessLog(strRcbuf, LOGDEBUG);
		}
	} while (time(NULL) <= Endtime);
	cout << szStrGet << endl;
	AtCom.Close();
	return TRUE;
}

void help()
{
	cout << "Usage: " << endl;
	cout << "-p port:               set com port." << endl;
	cout << "-b baudrate:           set baudrate." << endl;
	cout << "-t intervaltime:       delay time after sendstr." << endl;
	cout << "-s sendstr:            send str." << endl;
	cout << "-h help:               show help message." << endl;
	cout << "example: " << endl;
	cout << "xxx.exe -p 3 -b 115200 -t 2 -s AT" << endl;
}

int main(int argc, char* argcv[])
{

	if (argc > 1)
	{
		parser.parse(argc, argcv);
		for (unsigned int i = 0; i < parser.getParamsCount(); i++)
		{
			if (parser.getKeyName(i) == "h" || parser.getKeyName(i) == "help")
			{
				help();
				return TRUE;
			}
		}
	}
	else
	{
		help();
		return TRUE;
	}
	
	//Exec function
	return Exefunction();
}