#include "Serial.h"
#include <iostream>
//#include <getopt.h>
#include "parsingargs.h"
#include <string.h>


using namespace std;
CSerial AtCom;
std::map<std::string, std::vector<std::string> > result;
map<std::string, std::vector<std::string> >::iterator it;
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
	if (result.find("p") == result.end() && result.find("b") == result.end() && result.find("t") == result.end() && result.find("s") == result.end())
	{
		cout << "Param Error!!!" << endl;
		return FALSE;
	}

	if (AtCom.IsOpened())
	{
		AtCom.Close();
	}
	if (!AtCom.Open(atoi(result["p"].front().c_str()), atoi(result["b"].front().c_str()))){ return FALSE; }

	SendAtCmd(result["s"].front().c_str());
	time_t Endtime;
	Endtime = time(NULL) + atoi(result["t"].front().c_str());
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
		}
	} while (time(NULL) <= Endtime);
	cout << szStrGet << endl;
	AtCom.Close();
	return TRUE;
}

int main(int argc, char * argv[])
{
	string tmpPara = "";
	ParsingArgs pa;
	pa.AddArgType('p', "port", ParsingArgs::MUST_VALUE);
	pa.AddArgType('b', "baudrate", ParsingArgs::MUST_VALUE);
	pa.AddArgType('t', "intervaltime", ParsingArgs::MUST_VALUE);
	pa.AddArgType('s', "sendstr", ParsingArgs::MUST_VALUE);
	pa.AddArgType('h', "help", ParsingArgs::MUST_VALUE);

	for (int i = 1; i <argc; i++)
	{
		if (strlen(argv[i]) == 0) //处理空字符串
		{
			cout << "Param Error!!!" << endl;
			tmpPara += char(31);
		}
		else
		{
			tmpPara += argv[i];
		}
		tmpPara += " ";
	}
	
	result.clear();
	std::string errPos;
	int iRet = pa.Parse(tmpPara, result, errPos);
	if (0>iRet)
	{
		cout << "Param Error!!!" << iRet << errPos << endl;
		return -1;
	}

	for (it = result.begin(); it != result.end(); ++it)
	{
		if (it->first.compare("h") == 0)
		{
			cout << "Usage: " << endl;
			cout << "-p port:               set com port." << endl;
			cout << "-b baudrate:           set baudrate." << endl;
			cout << "-t intervaltime:       delay time after sendstr." << endl;
			cout << "-s sendstr:            send str." << endl;
			cout << "-h help:               show help message." << endl;
			cout << "example: " << endl;
			cout << "xxx.exe -p 3 -b 115200 -t 2 -s AT" << endl;
			return TRUE;
		}
	}

	return Exefunction();
}

