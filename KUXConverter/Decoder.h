#pragma once
#include <string>
class Decoder
{
public:
	Decoder();
	~Decoder();
	static bool TestFile(const char* path);
	void WriteDecoder();
	void DeleteDecoder();
private:
	std::string paths[11];
};

