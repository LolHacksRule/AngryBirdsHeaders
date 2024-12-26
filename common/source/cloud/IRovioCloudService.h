#ifndef _CLOUD_IROVIOCLOUDSERVICE_H
#define _CLOUD_IROVIOCLOUDSERVICE_H

class IRovioCloudService
{
public:
	virtual ~IRovioCloudService();
	virtual void initialize();
	virtual void onGameActivated(bool active) = 0;
	virtual bool isAdditionalViewActive() = 0;
	virtual std:string getServiceName() const = "";
	IRovioCloudService();
};

#endif