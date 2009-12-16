#include "stdafx.h"
#include "wlm.h"

//#define FORMAT_STR_SEND L"PSI\\0Music\\01\\0{0} - {1}\\0LocalTime\\0%s\\0\\0"
//#define FORMAT_STR_END L"PSI\\0Music\\00\\0{0} - {1}\\0\LocalTime\0\\0\\0\\0"
#define FORMAT_STR_SEND L"PSI\\0Music\\01\\0{0}\\0%s\\0\\0"
#define FORMAT_STR_END L"PSI\\0Music\\00\\0{0}\\0\\0\\0\\0"

bool WLM_sendMessage(wchar_t* str){
	HWND msnui = NULL;
	COPYDATASTRUCT mlm_data;

	size_t size = wcslen(FORMAT_STR_SEND)*2 + wcslen(str)*2 + 256;
	wchar_t* buff = new wchar_t[size];
	swprintf_s(buff,size,FORMAT_STR_SEND,str);

	mlm_data.dwData = 0x547;
	mlm_data.lpData = (void*)buff;
	mlm_data.cbData = (wcslen(buff)*2)+2;

	while (msnui = FindWindowEx(NULL, msnui, L"MsnMsgrUIManager", NULL))
	{
		SendMessage(msnui, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&mlm_data);
	}

	delete [] buff;

	return true;
}
bool WLM_clearMessage(){
	HWND msnui = NULL;
	COPYDATASTRUCT mlm_data;

	mlm_data.dwData = 0x547;
	mlm_data.lpData = (void*)(FORMAT_STR_END);
	mlm_data.cbData = (wcslen(FORMAT_STR_END)*2)+2;

	while (msnui = FindWindowEx(NULL, msnui, L"MsnMsgrUIManager", NULL))
	{
		SendMessage(msnui, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&mlm_data);
	}
	return true;
}

