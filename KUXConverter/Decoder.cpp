#include "stdafx.h"
#include "Decoder.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "resource.h"
#include <errno.h>
using namespace std;


Decoder::Decoder()
{
	paths[0] = "./kuxdecoder/aliplayerVS.dll";
	paths[1] = "./kuxdecoder/ffmpeg.exe";
	paths[2] = "./kuxdecoder/libcurl.dll";
	paths[3] = "./kuxdecoder/libeay32.dll";
	paths[4] = "./kuxdecoder/libexpat.dll";
	paths[5] = "./kuxdecoder/msvcp100.dll";
	paths[6] = "./kuxdecoder/msvcp120.dll";
	paths[7] = "./kuxdecoder/msvcr100.dll";
	paths[8] = "./kuxdecoder/msvcr120.dll";
	paths[9] = "./kuxdecoder/pthreadVC2.dll";
	paths[10] = "./kuxdecoder/ssleay32.dll";
}


Decoder::~Decoder()
{
}

bool Decoder::TestFile(const char * path)
{
	FILE *file = fopen(path, "rb+");
	if (file == NULL) {
		return false;
	}
	else {
		fclose(file);
		return true;
	}
}

void Decoder::WriteDecoder()
{
	CreateDirectory(L"kuxdecoder", NULL);
	LPWSTR resources[11] = {
		MAKEINTRESOURCE(IDF_ALIPLAYERVS_DLL),MAKEINTRESOURCE(IDF_FFMPEG_EXE),MAKEINTRESOURCE(IDF_LIBCURL_DLL),
		MAKEINTRESOURCE(IDF_LIBEAY32_DLL),MAKEINTRESOURCE(IDF_LIBEXPAT_DLL),MAKEINTRESOURCE(IDF_MSVCP100_DLL),
		MAKEINTRESOURCE(IDF_MSVCP120_DLL),MAKEINTRESOURCE(IDF_MSVCR100_DLL),MAKEINTRESOURCE(IDF_MSVCR120_DLL),
		MAKEINTRESOURCE(IDF_PTHREADVC2_DLL),MAKEINTRESOURCE(IDF_SSLEAY32_DLL)
	};
	for (int i = 0; i < 11; ++i) {
		if (!TestFile(paths[i].c_str())) {
			HRSRC src = FindResourceW(NULL, resources[i], L"TRANSCODE");
			HGLOBAL global = LoadResource(NULL, src);
			void* pointer = LockResource(global);
			DWORD Size = SizeofResource(NULL, src);
			HANDLE File = CreateFileA(paths[i].c_str(), GENERIC_ALL, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD Write = 0;
			WriteFile(File, global, Size, &Write, NULL);
			CloseHandle(File);
			FreeResource(src);
		}
	}
}

void Decoder::DeleteDecoder()
{
	for (int i = 0; i < 11; ++i) {
		if (TestFile(paths[i].c_str())) {
			DeleteFileA(paths[i].c_str());
		}
	}
	RemoveDirectoryA("kuxdecoder");
}
