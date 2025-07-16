#ifndef _CLOUDPAYMENT_HPP
#define _CLOUDPAYMENT_HPP

#include "../../GameLua.h"
#include <lang/Ptr.h>
#include <cloud/Payment/LuaCloudPayment.hpp>
#include <functional> 
#include <cloud/core/IdentityLevel2.h> 

class CloudPayment
{
public:
	typedef std::tr1::function<void ()> CloudPayment::InitSuccessCallback InitSuccessCallback; //?
	typedef std::tr1::function<void (int, const std::string&)> CloudPayment::InitFailureCallback InitFailureCallback; //?
	typedef std::tr1::function<void (bool)> CloudPayment::RestoreCallback RestoreCallback; //?
	typedef std::tr1::function<void (rcs::payment::CodeStatus)> CloudPayment::RedeemCallback RedeemCallback; //?
	struct InitCallback
	{
		InitSuccessCallback onSuccess;
		InitFailureCallback onError;
	};
	enum PurchaseError
	{
		ERROR_UNKOWN,
		ERROR_NOT_ALLOWED
	};
	class Director
	{
		virtual void onInitialized(const std::string& paymentProvider) = 0;
		virtual void onProductPurchased(const std::string& productId) = 0;
		virtual void onPurchaseLimitExceeded() = 0;
		virtual void onPurchaseCanceled(const std::string& productId) = 0;
		virtual void onPurchaseFailed(const std::string& productId, PurchaseError err) = 0;
		virtual bool userHasNonConsumable(const std::string& productId) = 0;
	};
	CloudPayment(RovioCloudManager* cloudManager, GameLua* gamelua);

	void setClientProductPrice(const std::string& productId, float referencePrice);

	void initialize(InitSuccessCallback *onSuccess, InitFailureCallback *onFailure, rcs::IdentityLevel2& skynestIdentity);

	void buyProduct(const std::string& productId);

	void restorePurchases(CompletionCallback* onComplete);

	bool hasAutomaticRestore();

	bool isInitialized() const;

	void getLocalizedPrices();

	void getAvailableProducts();

	bool isProductAvailable(std::string& productId);

	void redeemCode(const std::string& code, RedeemCallback onRedeemResult);

	void setDirector(Director* director);

	std::string serviceName();
private:
	GameLua* m_gameLua;
	bool m_initialized;
	InitCallback m_onInitComplete;

	LuaCloudPayment* m_luaCloudPayment;

	lang::unique_ptr<rcs::payment::Payment,lang::detail::default_delete<rcs::payment::Payment> > m_payment;

	std::map<std::string,float> m_productReferencePrice;

	std::map<std::string,rcs::wallet::Voucher> m_purchasedProductsBuffer;

	Director* m_purchaseDirector;
	lang::Ptr<rcs::Identity> m_identity;

	void onPurchaseProgress(const rcs::payment::PurchaseInfo& info);
	void onPurchaseSuccess(const std::string& paymentProvider);
	void onError(int status, const std::string& msg);
};

#endif