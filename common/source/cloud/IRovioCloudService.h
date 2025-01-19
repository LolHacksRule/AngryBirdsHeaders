#ifndef _CLOUD_IROVIOCLOUDSERVICE_H
#define _CLOUD_IROVIOCLOUDSERVICE_H

#include <string>

class IRovioCloudService
{
public:
	virtual ~IRovioCloudService();
	virtual void initialize() = 0;
	virtual void onGameActivated(bool active) = 0;
	virtual bool isAdditionalViewActive() const = 0;
	virtual std::string getServiceName() const = "";
};

#endif