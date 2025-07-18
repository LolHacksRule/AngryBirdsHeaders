#ifndef _COMMON_DEBUGCONSOLE_H
#define _COMMON_DEBUGCONSOLE_H

//Classic, Friends and Seasons

#include "TextInput.h"

class DebugConsole :
	public pf::TextInputObserver
{
public:
	DebugConsole(GameLua* gameLua);
	~DebugConsole();
	
	void activate(const std::string& defaultText);
	void deactivate();
	
	virtual bool acceptInput(const std::string&, unsigned short);
	virtual void inputChanged(const std::string& newString);
	
private:
	pf::TextInput* m_textInput;
	GameLua* m_gameLua;
	void updateLuaInput(const std::string& newString);
	std::string getInput() //inline.
	{
		return m_textInput->isActive() ? m_textInput->input() : "";
	}
};

#endif