// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PROCESSLOG_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PROCESSLOG_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

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
����:Roger
����:2017-07-17
ģ���������������log���ֽڽӿ�
����˵����File->��ǰ�������ڵ��ļ�
Line->��ǰ������к�
Action->��������ַ���
Flag->�����ַ�������
����ֵ���ɹ�TRUE��ʧ��FALSE
***********************************************************/
PROCESSLOG_API bool ProcessLogW(wchar_t* File, int Line, wchar_t* Action, INFOTYPE Flag);


/************************************************************
����:Roger
����:2017-07-17
ģ���������������log���ֽڽӿ�
����˵����File->��ǰ�������ڵ��ļ�
Line->��ǰ������к�
Action->��������ַ���
Flag->�����ַ�������
����ֵ���ɹ�TRUE��ʧ��FALSE
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
//ProcessLog(_T("DEBUG��¼"), LOGDEBUG);
