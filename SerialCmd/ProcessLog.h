// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 PROCESSLOG_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// PROCESSLOG_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#ifdef PROCESSLOG_EXPORTS
#define PROCESSLOG_API __declspec(dllexport)
#else
#define PROCESSLOG_API __declspec(dllimport)
#endif


typedef enum
{
	LOGDEBUG = 0,
	LOGERR
}INFOTYPE;

/************************************************************
作者:Roger
日期:2017-07-17
模块描述：程序过程log宽字节接口
参数说明：File->当前代码所在的文件
Line->当前代码的行号
Action->传入调试字符串
Flag->调试字符串类型
返回值：成功TRUE，失败FALSE
***********************************************************/
PROCESSLOG_API bool ProcessLogW(wchar_t* File, int Line, wchar_t* Action, INFOTYPE Flag);


/************************************************************
作者:Roger
日期:2017-07-17
模块描述：程序过程log多字节接口
参数说明：File->当前代码所在的文件
Line->当前代码的行号
Action->传入调试字符串
Flag->调试字符串类型
返回值：成功TRUE，失败FALSE
***********************************************************/
PROCESSLOG_API bool ProcessLogA(char* File, int Line, char* Action, INFOTYPE Flag);

#ifdef _UNICODE
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define ProcessLog(x,y) ProcessLogW(__WFILE__,__LINE__,x,y)
#else
#define ProcessLog(x,y) ProcessLogA(__FILE__,__LINE__,x,y)
#endif
//ProcessLog(_T("DEBUG记录"), LOGDEBUG);
