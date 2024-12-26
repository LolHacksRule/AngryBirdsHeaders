#ifndef _ROVIOACCOUNT_H
#define _ROVIOACCOUNT_H

#include <GameLua.h>

class RovioAccount
{
public:
	RovioAccount(GameLua* gamelua, rcs::Identity* identity);
	~RovioAccount();
	
	void loginRovioId(bool, const std::string&, const std::string&, int, int);
	void cancelRovioIdLogin();
	void logoutRovioId();
	void showProfileViewTemp();
	void setAccountParameter(const std::string&, const std::string&);
	std::string getProfileParameter(const std::string&);
	
	bool isLoggedIn();
	bool isLoginInProgress();
	
	bool isViewActive();
	bool isInLoginViewFlow();
	
	void update();
	void setCloudSync(CloudSync*);
	bool shouldCloudOverwriteLocalSave();
	
	void loadLoginViewSuccessCallback();
	void loadLoginViewFailureCallback();
	void showLoginViewSuccessCallback();
	void showLoginViewFailureCallback();
	
	void showProfileView();
	void cancelProfileLoading();
	
	void loadProfileSuccessCallback();
	void loadProfileFailureCallback();
	void logoutProfileCallback();
	void closeProfileCallback();
	
	void handleSyncFailure();
	
	lang::Ptr<rcs::RovioIdentity> getRovioIdentity();
	struct WebViewInfo
	{
		int viewHeight;
		int viewWidth;
		bool promptLogin;
		std::string initialWebTarget;
		std::string locale;
		//~WebViewInfo();
	};
private:
	GameLua *m_gameLua;
	
	bool m_loadLoginView;
	bool m_showLoginView;
	bool m_isLoginSuccess;
	bool m_loginInProgress;
	bool m_loginCancelled;
	bool m_loginViewLoadFailed;
	bool m_isInLoginViewFlow;
	
	WebViewInfo m_webViewInfo;
	rcs::Identity *m_deviceIdentity;
	lang::Ptr<rcs::RovioIdentity> m_rovioIdentity;
	rcs::ProfileWebView *m_profileWebView;
	CloudSync *m_cloudSync;
};

#endif