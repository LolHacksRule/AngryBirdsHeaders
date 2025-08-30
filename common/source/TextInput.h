#ifndef _COMMON_TEXTINPUT_H
#define _COMMON_TEXTINPUT_H

//Classic and Seasons

#include <pf/TextInput.h>

class GameLua;

class TextInput :
	public pf::TextInputObserver
{
public:
	void TextInput(std::string name, GameLua* gamelua);
	~TextInput();
    
	void activate(const std::string& string);
	void deactivate();
    
	virtual bool acceptInput(const std::string&, unsigned short) { return true; };
	virtual void inputChanged(const std::string& newString);
private:
	void updateLuaInput(const std::string& newString);
	lang::Ptr<pf::TextInput> m_textInput;
	std::string n_name;
	GameLua* m_gameLua;
};

#endif