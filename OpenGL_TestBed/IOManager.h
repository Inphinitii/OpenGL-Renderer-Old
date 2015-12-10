#pragma once
#include <stdlib.h>
#include <stdio.h>

class IOManager
{
private:
	static IOManager* m_IOManagerSingleton;
	IOManager();
	~IOManager();

public:
	static IOManager* GetInstance();
	char* FileToBuffer(char* _filename);
};

