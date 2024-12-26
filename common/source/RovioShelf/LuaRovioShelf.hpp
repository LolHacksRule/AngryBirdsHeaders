#ifndef _COMMON_LUAROVIOSHELF_HPP
#define _COMMON_LUAROVIOSHELF_HPP

#include <RovioShelf.h>
#include "../../LuaManager.h"

class LuaRovioShelf
{
public:
	LuaRovioShelf(lang::Ptr<gr::Context> context, lang::Ptr<RovioCloudManager> cloudManager, LuaManager& luaManager, lua::LuaState& luaState);
	~LuaRovioShelf();
private:
	void lua_setAllowed(bool allowed);

	bool lua_isCapturingInput();
	void lua_setInputCapturing(bool activate);

	void lua_update(float dt);
	void lua_render();
	LuaObject m_interface;

	lang::Ptr<gr::Context> m_context;
	lang::Ptr<RovioCloudManager> m_cloudManager;

	lang::unique_ptr<rovioshelf::RovioShelf,lang::detail::default_delete<rovioshelf::RovioShelf> > m_rovioShelf;

	bool m_capturingInput;
	bool m_allowed;
};

#endif