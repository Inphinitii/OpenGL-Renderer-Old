#include "IOManager.h"

IOManager* IOManager::m_IOManagerSingleton;

IOManager* IOManager::GetInstance()
{
	if (m_IOManagerSingleton == nullptr)
		m_IOManagerSingleton = new IOManager();

	return m_IOManagerSingleton;
}
IOManager::IOManager()
{
}


IOManager::~IOManager()
{
}

char* IOManager::FileToBuffer(char* _filename)
{
	FILE*	_filePtr;
	long	_fileLength;
	char*	_buffer;

	fopen_s(&_filePtr, _filename, "rb");

	if (!_filePtr)
		return NULL;

	fseek(_filePtr, 0, SEEK_END);
	_fileLength = ftell(_filePtr);
	_buffer = (char*)malloc(_fileLength + 1);

	fseek(_filePtr, 0, SEEK_SET);
	fread(_buffer, _fileLength, 1, _filePtr);
	fclose(_filePtr);

	_buffer[_fileLength] = 0;

	return _buffer;
}
