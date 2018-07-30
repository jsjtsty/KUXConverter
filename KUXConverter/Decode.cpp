#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "Decoder.h"
#include <ShellAPI.h>
#include <conio.h>
#include <vector>
using namespace std;

void DecodeSingleFile() {
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
	//wstring s;
	//getline(wcin, s);
}

void DecodeAllFilesInFolder() {
	string path, path2;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hListFile;
	//char szFilePath[MAX_PATH];
	vector<string> paths;
	while (true) {
		cin.clear();
		wcout << L"Input Directory Path: ";
		getline(cin, path);
		
		if (path[0] == '\"') {
			path.erase(0, 1);
		}
		if (path[path.length() - 1] == '\"') {
			path.erase(path.length() - 1, 1);
		}
		if ((hListFile = FindFirstFileA(path.c_str(), &FindFileData)) == INVALID_HANDLE_VALUE) {
			wcout << L"Directory is not exist. Please try again." << endl;
			continue;
		}
		break;
	}
	path2 = path;
	if (path2.find('\\') != string::npos) {
		if (path2[path.length() - 1] != '\\')
			path2 += '\\';
	}
	else if (path2.find('/') != string::npos) {
		if (path2[path.length() - 1] != '/')
			path2 += '/';
	}
	path2 += "*.kux";
	hListFile = FindFirstFileA(path2.c_str(), &FindFileData);
	do
	{
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			paths.push_back(FindFileData.cFileName);
			cout << FindFileData.cFileName << endl;
		}
	} while (FindNextFileA(hListFile, &FindFileData));

	/*
	vector<string> usefulPaths;
	vector<string> usefulFileTitles;
	for (vector<string>::iterator it = paths.begin(); it != paths.end(); ++it) {
		string& str = *it;
		if (str.substr(str.length() - 4, 3) == "kux") {
			usefulPaths.push_back(path + *it);
			usefulFileTitles.push_back(path + it->substr(0, it->length() - 5));
		}
	}
	*/
	Decoder decoder;
	decoder.WriteDecoder();
	if (path.find('\\') != string::npos) {
		if (path[path.length() - 1] != '\\')
			path += '\\';
	}
	else if (path.find('/') != string::npos) {
		if (path[path.length() - 1] != '/')
			path += '/';
	}
	for (vector<string>::iterator pathIt = paths.begin(); pathIt != paths.end(); ++pathIt) {
		system((".\\kuxdecoder\\ffmpeg.exe -y -i \"" + path + *pathIt + "\" -c:v copy -c:a copy -threads 2 \""
			+ path + pathIt->substr(0, pathIt->length() - 4) + ".mp4\"").c_str());
	}
	decoder.DeleteDecoder();
	wcout << endl << L"Success. File has been saved to ";
	cout << path;
	wcout << endl << L"Press any key to continue." << endl;
	_getch();
	wcout << endl;
	//wstring s;
	//getline(wcin, s);
}