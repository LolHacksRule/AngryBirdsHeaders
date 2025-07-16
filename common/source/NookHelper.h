#ifndef _COMMON_PLATFORM_NOOKHELPER_H
#define _COMMON_PLATFORM_NOOKHELPER_H

#include <lang/Object.h>

//Also in root of "common".

class NookStoreStatusListener
{
public:
	virtual void storeStatusChanged(bool isInsideStore) = 0; //Recover var from GameLua
};

class NookHelper :
	public lang::Object
{
public:
	NookHelper();
	virtual ~NookHelper();
	
	void setListener(NookStoreStatusListener* listener); //?
	void notifyListener();
private:
	NookStoreStatusListener* m_listener;
};

#endif