#ifndef _LUACLOUDPAYMENT_HPP
#define _LUACLOUDPAYMENT_HPP

#include <GameLua.h>
#include "CloudPayment.hpp"

class LuaCloudPayment :
	CloudPayment::Director, lua::LuaObject
{
public:
	LuaCloudPayment(RovioCloudManager& cloudManager, GameLua* gameLua);
	virtual ~LuaCloudPayment();
	
	virtual void onInitialized(const std::string&);
	virtual void onProductPurchased(const std::string& productId);
	virtual void onPurchaseLimitExceeded();
	virtual void onPurchaseCanceled(const std::string& productId);
	virtual void onPurchaseFailed(const std::string& productId, PurchaseError err);
	virtual bool userHasNonConsumable(const std::string& productId);
	
private:
	void lua_buyProduct(std::string productId);
	void lua_restorePurchases(lua::LuaFunction onSuccess, lua::LuaFunction onError);
	bool lua_hasAutomaticRestore();
	bool lua_isInitialized();
	int lua_getLocalizedPrices(lua::LuaState* lua);
	int lua_getAvailableProducts(lua::LuaState* lua);
	bool lua_isProductAvailableForPurchase(std::string productId);
	
	void lua_requireLogin(lua::LuaFunction onSuccess, lua::LuaFunction onError);
	
	void lua_registerProductReferencePrice(std::string productId, float price);
	
	int lua_redeemCode(LuaState* lua);
	
	void lua_ready();
	
	GameLua* m_gameLua;
	RovioCloudManager& m_cloudManager;
};

#endif