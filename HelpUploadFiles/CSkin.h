#pragma once
class CSkin
{
private:
	HMODULE hSkinMod;
public:
	CSkin();
	~CSkin();
protected:
	void FindSkinFile(char* skinPath);
};

