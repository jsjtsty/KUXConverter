#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "Decoder.h"
#include <ShellAPI.h>
#include <conio.h>
#include <vector>
using namespace std;

void EncodeSingleFile() {
	string path;
	while (true) {
		wcin.clear();
		wcout << L"Input File Path: ";
		getline(cin, path);
		if (path[0] == '\"') {
			path.erase(0, 1);
		}
		if (path[path.length() - 1] == '\"') {
			path.erase(path.length() - 1, 1);
		}
		if (!Decoder::TestFile(path.c_str())) {
			wcout << L"File is not exist. Please try again." << endl;
			continue;
		}
		break;
	}
	string target;
	wcout << L"Input Output Path: ";
	getline(cin, target);
	if (target[0] == '\"') {
		target.erase(0, 1);
	}
	if (target[target.length() - 1] == '\"') {
		target.erase(target.length() - 1, 1);
	}
	Decoder decoder;
	decoder.WriteDecoder();
	system((".\\kuxdecoder\\ffmpeg.exe -y -i \"" + path + "\" -c:v copy -c:a copy -threads 2 \"" + target + "\"").c_str());
	decoder.DeleteDecoder();
	wcout << endl << L"Success. File has been saved to ";
	cout << target;
	wcout << L"." << endl << L"Press any key to continue." << endl;
	_getch();
	wcout << endl;
}