#pragma once
#include <string>
#include "CContext.h"

class CIgnoreFileManager
{
private:
	CContext* context;
	static CIgnoreFileManager* singleton;
public:
	static CIgnoreFileManager* getSingleton();
public:
	CIgnoreFileManager();
	void addIgnoreFile(std::wstring fileName);
	void removeIgnoreFile(std::wstring fileName);
};

