// Clock.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "wlm.h"

bool Running = true;

bool signal_handler(DWORD dwCtrlType){
	switch(dwCtrlType){
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			WLM_clearMessage();
			wprintf(L"Get Exit Event.\n");
			Running = false;
			return true;
		case CTRL_CLOSE_EVENT:
			WLM_clearMessage();
			wprintf(L"Get Exit Event.\n");
			return true;
		default:
			return false;
	}
}

wchar_t* getTime(wchar_t* buff,size_t size){
	_SYSTEMTIME st;
	GetLocalTime(&st);
	//swprintf_s(buff,size,L"%04d/%02d/%02d %02d:%02d:%02d", st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	//return buff;
	/* センター */
	struct tm center;
	center.tm_sec = 0;
	center.tm_min = 40;
	center.tm_hour = 8;
	center.tm_mday = 25;
	center.tm_wday = 0;
	center.tm_mon = 1;
	center.tm_year = 110;
	center.tm_isdst = -1;
	time_t center_day = mktime(&center);
	time_t now;
	time(&now);
	int diff = (int)difftime(center_day,now);
	int day = diff / (24*3600);
	int hour = (diff % (24*3600)) / 3600;
	int min = (diff % 3600) / 60;
	int sec = diff % 60;
	swprintf_s(buff,size,L"国立二次まで%02d日%02d:%02d:%02d %04d/%02d/%02d %02d:%02d:%02d",
		day,hour,min,sec,
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond
	);
	return buff;
}

int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t* time = new wchar_t[2048];
	_tsetlocale(LC_ALL, _T(""));
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)signal_handler,true);
	while(Running){
		WLM_sendMessage(getTime(time,2048));
		wprintf(L"Sending: %s\n",time);
		Sleep(1000*30);
	}
	delete[] time;
	//念のため
	WLM_clearMessage();
	return 0;
}

