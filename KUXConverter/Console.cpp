#include "stdafx.h"
#include "Version.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "resource.h"
#include <algorithm>
#include <exception>
using namespace std;

void init();
int MainPageSelector(bool error);
void PrintApplicationInformation();
void DecodeSingleFile();
void DecodeAllFilesInFolder();

void RunConsole() {
	init();
	int MainSelect = 0;
	bool MainSelectError = false;
	while (true) {
		MainSelect = MainPageSelector(MainSelectError);
		if (MainSelect == 1) {
			DecodeSingleFile();
			MainSelectError = false;
		}
		else if (MainSelect == 2) {
			DecodeAllFilesInFolder();
			MainSelectError = false;
		}
		else if (MainSelect == 3) {
			MainSelectError = true;
			PrintApplicationInformation();
		}
		else if (MainSelect == 4) {
			return;
		}
		else {
			MainSelectError = true;
			wcout << L"Input Error. Please try again." << endl;
		}
	}
	wcin.get();
}

void init() {
	SetConsoleTitleW(L"Youku Video File Converter");
	wcout << GetApplicationName() << L" " << GetApplicationVersion() << endl;
	wcout << L"Copyright (C) " << GetDeveloperInformation() << L". Licenced on GNU Public Licence v3." << endl << endl;
}

int MainPageSelector(bool error) {
	if (!error) {
		wcout << L"* Select transform mode:" << endl << L"1. Input File Path" << endl << L"2. Tranform All kux Files in a Certain Folder"
			<< endl << L"3. Application Information" << endl << L"4. Exit" << endl << endl;
	}
	wcout << L"Select the mode you need (1-4): ";
	wstring s;
	getline(wcin, s);
	if (s == L"1") {
		return 1;
	}
	else if (s == L"2") {
		return 2;
	}
	else if (s == L"3") {
		return 3;
	}
	else if (s == L"4") {
		return 4;
	}
	return 0;
}

void PrintApplicationInformation() {
	wcout << L"Youku Video File Converter " << GetApplicationVersion() << endl << L"Copyright (C) " << GetDeveloperInformation() << L"."
		<< endl << L"Youku FFmpeg Version: 3.4" << endl << L"Youku Version: 7.5.9.7101" << endl << L"Released on 2018/7/27"
		<< endl << L"Built with Visual C++ 2017, with Windows XP Support." << endl << L"Licenced on GNU Public Licence v3. View Licence? (y/n)";
	wstring s;
	wcin >> s;
	if (s == L"y") {
		wstring text;
		HGLOBAL hResource = NULL;
		HWND hWnd = GetConsoleWindow();
		HINSTANCE hInstance = GetModuleHandleW(NULL);
		hResource = LoadResource(hInstance, FindResourceW(hInstance, MAKEINTRESOURCE(IDF_GPL), L"LICENCE"));
		const wchar_t* fileText = (const wchar_t*)LockResource(hResource);
		text = fileText;
		text.erase(remove(text.begin(), text.end(), L'\r'), text.end());
		wprintf(L"%s\n\n", text.c_str());
		FreeResource(hResource);
	}
	else {
		wcout << endl;
	}
}