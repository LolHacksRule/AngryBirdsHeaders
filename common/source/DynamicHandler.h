#ifndef _COMMON_DYNAMICHANDLER_H
#define _COMMON_DYNAMICHANDLER_H

#include <lua/LuaObject.h>
#include <game/Resources.h>

class DynamicHandler :
	public lua::LuaObject
{
public:
	struct Asset
	{
		explicit Asset(int);
		
		int ref;
		int type;
		
		lang::optional<unsigned long> memory;
	};
	
	DynamicHandler(lua::LuaTable& table, game::Resources& res, const gr::Context& ctx, const std::string& imagePath);
	
	virtual ~DynamicHandler();
	
	int load(lua::LuaState* L);
	
	int queueLoad(lua::LuaState* L);
	
	int release(lua::LuaState* L);
	
	int delayRelease(lua::LuaState* L);
	
	void clear();
	
	void delayClear();
	
	void reloadAssets();
	
	void printLoaded();
	
	size_t totalMemory();
	size_t maxMemory();
	
	bool validID(const std::string& reqId) const;
	
	int addRequirements(lua::LuaState* L);
private:
	void loadImpl(const std::vector<std::string>& reqIds, bool queued = false);
	void releaseImpl(const std::vector<std::string>& reqIds, bool delayed = false);
	void clearImpl(bool delayRelease = false);
	
	void addToCurrent(const std::string& reqId);
	void removeFromCurrent(const std::string& reqId, bool delayRelease = false);
	void releaseUnused();
	
	void queueLoadGroup(const std::string& group);
	void releaseGroup(const std::string& group, bool delayRelease = false);
	
	void addRequirement(const std::string& id, const lua::LuaTable& entry);
	
	void loadSheet(const std::string& path);
	void queueLoadSheet(const std::string& path);
	void releaseSheet(const std::string& path);
	void loadAllQueued();
	
	DynamicHandler(const DynamicHandler&);
	DynamicHandler& operator=(const DynamicHandler&)
	
	const gr::Context& m_context;
	
	game::Resources& m_resources;
	
	std::string m_imagePath;
	
	std::map<std::string,std::vector<std::string>> m_requirements;
	
	std::map<std::string,DynamicHandler::Asset> m_currentAssets;
	size_t m_totalMemory, m_maxMemory;
	
	std::set<std::string> m_loaded;
	
	std::vector<std::string> m_loadQueue;
};

#endif