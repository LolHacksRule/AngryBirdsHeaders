#ifndef _COMMON_GAMELUA_H
#define _COMMON_GAMELUA_H

#include <game/Anchor.h>
#include <game/LuaResources.h>
#include "GameObject.hpp"
#include "Vignette.h"
#include <lua/LuaState.h>
#include <b2Joint.h>
#include <b2Body.h>
#include <lang/FastDelegate.h>
#include "DebugConsole.h"
#include "pf/AppSettings.h"
#include "cloud/RovioCloudManager.h"
//#include "ObjectTeleporter.h"

class ObjectTeleporter;
class NookStoreStatusListener;

#if !defined(ABC) && ABC_VERSION < 163 //Does not exist in those two platforms
struct GameLuaConfig
{
	std::string imagePath;
	std::string fontPath;
	std::string audioPath;
	std::string localizationPath;
	std::string levelPath;
	std::string scriptPath;
	std::string commonScriptPath;
	std::string deviceModel;
	bool isHDVersion;
};
#endif

class GameLua :
	public lua::LuaObject, b2ContactListener, b2ContactFilter, pf::VideoPlayerListener, 
	#if !defined(ABC) && ABC_VERSION < 163
	pf::LocalNotificationsListener, NookStoreStatusListener
	#else
	pf::VideoPlayerObserver
	#endif
{
public:
	GameLua(framework::App* app, lang::Ptr<game::LuaResources> resources, lua::LuaState *lua, gr::Context *context, const GameLuaConfig& config);
	~GameLua();
	
	struct jointData //97, 37 in ABFM 1.1.5 Meego, Why is this lowercase
	{
		FUSION_CUSTOM_STRING name;
		FUSION_CUSTOM_STRING end1;
		FUSION_CUSTOM_STRING end2;
		b2Joint *joint;
		int type;
	};
	
	#if !defined(ABC) && ABC_VERSION < 163

	enum BlockMaterial { NONE, WOOD, ROCK, LIGHT, IMMOVABLE, IMMOVABLE_FRAGILE, CLOUDS, SNOW };
	enum BlockParameters {P_LEVEL_GOAL, P_MASS, P_UNDEFINED	};
	
	struct TransformData //46, moved to GameObject in new
	{
		float x;
		float y;
		float angle;
	};
	struct RenderObjectData //52
	{
		TransformData positions[2];
		BlockMaterial material;
		lua::LuaTable objectTable;
		math::float2 afterCollisionVelocity;
		lang::String objectName;
		lang::String spriteName;
		b2Body *body;
		game::Sprite *sprite;
		gr::Image *texture;
		float radius;
		float x;
		float y;
		float angle;
		float z_order;
		bool updateAfterCollision;
		bool oldSleep;
		bool collision;
		bool controlled;
		bool sphere;
		bool piglette;
		bool mightyEagle;
	};
	
	class LevelLoadData //89
	{
		LevelLoadData();
		void reset();
		io::ByteArrayInputStream m_data;
		lang::String m_url;
		lang::String m_today;
		lang::String m_errorMsg;
		lang::String m_uid;
		int m_status;
		int m_error;
		int m_timeToNext;
	};
	
	struct ThemeSpriteData
	{
		Sprite* sprite;
		float x;
		float y;
		float scaleX;
		float scaleY;
		float angle;
		lang::String name;
	};
	
	struct ThemeLayerData //326
	{
		std::string sheet;
		std::string sprite;

		float height;
		float width;

		float pivotX;
		float pivotY;
		float parallaxSpeed;
		float scale;
		float offset;
		bool looping;
		float startX;
		lang::Array<ThemeSpriteData> sprites;
	};
	
	void setLeaderboardScoresForRange(lang::Array<ScoreData> lData, lang::String category, int start, int length, int maxRange, int localScore);
	void setMaterial(FUSION_CUSTOM_STRING objectName, FUSION_CUSTOM_STRING materialName);
	
	void clearParticles();
	void clearVertices();
	void addVertex(float x, float y);
	void avoidCrystalBackgroundActivity(bool unk); //Exists in 1.6.3.
	
	b2Body* createCircle(RenderObjectData* rod, lang::String name, lang::String sprite, float x, float y, float w, float h, float density, float friction, float restitution);
	b2Body* createBox(RenderObjectData* rod, lang::String name, lang::String sprite, float x, float y, float w, float h, float density, float friction, float restitution);
	b2Body* createPolygon(RenderObjectData* rod, lang::String name, lang::String sprite, float x, float y, float w, float h, float density, float friction, float restitution);
	
	void fullScreenAdDisappeared(bool banner); //Unimplemented in Meego. ABC <2.3.0, ABR <1.4.2, ABS <3.0.1, Space <1.3.2, ABSW <1.0.2
	void hideAdvertisement(); //ABC <2.3.0, ABR <1.4.2, ABS <3.0.1, Meego [unimplemented]
	
#if defined(PLATFORM_IOS) || defined(ABFM) //These functions only appear on iOS ABC <1.4.0, ABR <1.8.0, ABS <2.4.1, Space <1.5.2, SW <1.3.0 / SW Console and Trilogy but they do appear empty in ABFM, maybe ABFM was based off iOS-era source?
	void enableiAds();
	void disableiAds();
	void hidingFinished();
	void prepareiAd(iAdDelegate* iAd); //Not in ABC, ABR <1.8.0, ABS <2.4.1, Space <1.5.2, SW <1.3.0, Trilogy
	void requestAd();
	void requestAdCallback();
	void requestAndShowVideo();
	void requestVideoAd();
#endif
	
	void prepareAdMob(Admob* admob);
	
	void drawBackground();
	void drawParticles();
	void drawSome(lang::String spriteName);
	float getAngle(lang::String name);
	
#ifdef ABFM //Functions exclusive to ABFM.
	void foundNFC(lang::String macAddress);
	void toggleNFC(bool enable);
#endif
	
	void showAdvertisement();
	void showVideoAdvertisement();
	void startAdTimer();
	
	void showAlertBox(lang::String title, lang::String text);
	
	void setTopLeft(float x, float y);
	void setVideoReady(bool ready);
	bool videoPlayEnded();
	
	void setWorldScale(float worldScale);
	
	int getLoadStatus(LuaState* lua);
	void loadLevel(lang::String name);
	void loadLevelFile(lang::String name, lang::String dateString);
	void loadLevelFileOnline(lang::String url, lang::String filename);
	void loadLuaFile(const lang::String& fileName, const lang::String& tableName);
	
	void setGameOn(bool mode);
	
	bool userEnabledCrystal();
	
	//Crystal, these two do not exist in Meego but are defined in the header.
	void activateCrystalUI();
	void activateCrystalUIAtProfile();
	void deactivateCrystalUI();
	bool isCrystalSplashShowing();
	bool isCrystalUIShowing();
	bool showCrystalSplash();
	
	//Flurry
	void logFlurryEvent(lang::String eventName);
	void logFlurryEventWithParam(lang::String eventName, lang::String paramName, lang::String paramValue);
	void logFlurryEventWithParams(lang::String eventName, lang::String paramTable);
	
#endif
	
	struct ScoreData //221, 158 in ABFM 1.15 Meego
	{
		FUSION_CUSTOM_STRING playerID;
		FUSION_CUSTOM_STRING alias;
		int rank;
		int score;
		FUSION_CUSTOM_STRING formattedValue;
		FUSION_CUSTOM_STRING category;
	};
	
	struct AchievementData //231, 168 in ABFM 1.15 Meego
	{
		FUSION_CUSTOM_STRING identifier;
		FUSION_CUSTOM_STRING title;
		FUSION_CUSTOM_STRING achievedText;
		bool completed;
		bool hidden;
		bool percentComplete;
	};

	struct LevelAvailabilityCheckData
	{
	public:
		void reset();
		std::string m_today;
		int m_timeToNext;
		int m_status;
	};
	
	LevelAvailabilityCheckData m_levelAvailabilityCheckData;
	
	struct CollisionData
	{
		bool doesCollide;
		lang::FastDelegate1<b2Contact* beginContact; //FD is used here, old versions probably use just b2Contact
		lang::FastDelegate1<b2Contact* endContact;
		lang::FastDelegate1<b2Contact* preSolve;
	};
	struct URLCallbackStatus
	{
		lang::Mutex m_mutex;
		std::map<std::string, std::string> m_responses;
	};
	std::vector<std::pair<b2Body*, b2Body*>> m_newGlueJoints;
	
	gr::Context* m_context;
	framework::App* m_app;
	lang::Ptr<game::LuaResources> m_luaResources;
	game::Resources* m_resources;
	hgr::DefaultResourceManager* m_resourceManager; //Why like literally why is this still here
	
	particle::Manager* m_particles;
	
	lua::LuaTable m_keyPressed;
	lua::LuaTable m_keyReleased;
	lua::LuaTable m_keyHold;
	lua::LuaTable m_cursor;
	lua::LuaTable m_multitouchSweep;
	lua::LuaTable m_multitouchZoom;
	
	bool m_captureScreen;
	std::string m_captureScreenFileName;
	
	unsigned int m_bgcolor;
	
	int m_positionIndex;
	
	std::vector<math::float2> m_vertices;
	
	CollisionData m_collisionTable[16][16];
	
	b2World* m_world;
	
	float m_gameTime;
	
	std::map<std::string, float> m_rollingSoundVolumes;
	std::map<std::string, GameObject*> m_renderObjects;
	
	std::map<int, std::vector<std::string>> m_zObjects;
	std::map<std::string, ObjectTeleporter*> m_activeObjectTeleportations;
	std::vector<GameObject*> m_birdsList;
	
	std::vector<jointData> m_joints;
	std::vector<jointData> m_destroyJoints;
	lua::LuaTable m_objectTable;
	lua::LuaTable m_worldTable;
	lua::LuaTable m_deadBlocksTable;
	lua::LuaTable m_blockTable;
	lua::LuaTable m_clippedText;
	float m_physicsScale;
	bool m_physicsEnabled;
	bool m_loading;
	bool m_editing;
	bool m_compiled;
	float m_left;
	float m_top;
	float m_physicsLeftoverTime;
	float m_gameScale;
	float m_minWorldScale;
	
	bool m_screenParticlesDrawn;
	
	std::vector<math::float2> m_trajectories[6];
	std::vector<math::float2> m_trajectoryPuffs[6];
	int m_trajectoryStartIndex;
	std::vector<std::string> m_trajectorySprites[2];
	
	MaskTexturizer m_maskTexturizer;
	lang::Ptr<Vignette> m_vignette;
	lang::Ptr<Spotlight> m_spotlight;
	int m_levelLeftEdge;
	int m_levelRightEdge;
	
	std::vector<unsigned char> m_variableKeyOld;
	std::vector<unsigned char> m_variableKeyNew;

	GameCenter* m_gc; //Appears in ABFM
	
	std::string m_purchaseCallbackName;
	
	lang::Ptr<pf::VideoPlayer> m_videoPlayer;
	
	lang::Ptr<pf::AppSettings> m_appSettings;
	
	lang::Ptr<pf::LocalNotifications> m_notifications;
	std::string m_notificationCallbackName;
	WebViewLuaInterface m_webViewLuaInterface;
	
	lang::Ptr<lang::Thread> m_checkForURLThread;
	URLCallbackStatus m_urlCallbackStatus;
	
	bool m_safeToQuit;
	
	lang::unique_ptr<ThemeData, detail::default_delete<ThemeData> > m_theme;
	
	lang::Ptr<NookHelper> m_nookHelper;
	lang::Ptr<DynamicHandler> m_assetHandler;
	
	bool m_latestVersionRequestReady;
	bool m_updateCheckDone;
	bool m_updateAvailable;
	lang::Ptr<lang::Thread> m_updateCheckThread;
	
	std::string m_latestVersionName;
	std::string m_latestVersionURL;
	
	lang::Ptr<pf::Accelerometer> m_accelerometer;
	bool m_isAccelerometerActive;
	float m_acceleroMeterFilteredX;
	
	pf::DrmV2* m_DRM;
	bool m_keyValid;
	bool m_registerCallbackFinished;
	std::string m_keyType;
	
	bool m_active;
	bool m_updating;
	lang::Ptr<RovioCloudManager> m_rovioCloudManager;
	
	//lang::Event<void(float, float, float, float)> CAMERA_VIEWPORT_CHANGED;
	
	//lang::Event<void(int, int)> RESOLUTION_CHANGED;
private:
	int64_t m_timerStart;
	int64_t m_pauseStart;
	int64_t m_timeInPause;
	
	DebugConsole* m_debugConsole;
	std::map<std::string, TextInput*> m_textInputFields;
	bool m_particleEditorActive;
	
	lang::Mutex m_levelCheckMutex;
	lang::Ptr<DrawUtils> m_drawUtils;
public:
	void resetTimer();
	void startTimerPause();
	void stopTimerPause();
	int getGameTimer(lua::LuaState* lua);
	
	void compile(const FUSION_CUSTOM_STRING& file);
	
	void setChannelCountLimit(int channel, int cap);
	
	void createAssets();
	
	void setupCollisionTable();
	void setBeginContactHandler(ColliderType type1, ColliderType type2, lang::FastDelegate1<b2Contact*, void> handler);
	void setEndContactHandler(ColliderType type1, ColliderType type2, lang::FastDelegate1<b2Contact*, void> handler);
	void setPreSolveHandler(ColliderType type1, ColliderType type2, lang::FastDelegate2<b2Contact*, const b2Manifold*, void> handler);
	void setDoesCollide(ColliderType type1, ColliderType type2, bool collide);
	
	void createDynamicHandler(std::string name);
	
	void update(float dt);
	void updateWater(float dt);
	void updateFriction(GameObject& rod, float dt);
	void updateForceAdder(GameObject& rod, float dt);
	
	#if defined(ABC) && ABC_VERSION > 163
	void loadLuaFile(std::string fileName, std::string tableName);
	#endif
	void saveLuaFile(std::string fileName, std::string tableName, bool appData);
	void saveLuaTable(const std::string& fileName, lua::LuaTable& table, bool appData = false);
	int loadLuaFileToObjectFromLua(lua::LuaState* lua);
	int loadLuaFileToObject(const std::string& fileName, lua::LuaTable& table, const std::string& name, bool expectFileToBeFound = true, bool checkFileName = false);
	lua::LuaTable loadPersistentFile(const FUSION_CUSTOM_STRING& name);
	
	void notify(const std::string& event, lua::LuaTable params);
	
	uint32_t getBGColor() const;
	void setBGColor(float R, float G, float B);
	
	void resolutionChanged(); //Computer only
	void requestExit();
	
	void toggleZoomSteps(float steps, float minZoom, short maxZoom);
	
	bool safeToQuit() const { return m_safeToQuit; }
	void print(FUSION_CUSTOM_STRING str);
	void printWarning(FUSION_CUSTOM_STRING str);
	void printError(FUSION_CUSTOM_STRING str);
	
	int setRenderState(lua::LuaState* lua);
	void setAlpha(float alpha);
	void drawRect(float r, float g, float b, float a, float x1, float y1, float x2, float y2, bool inWorld);
	void drawTexturedRect(FUSION_CUSTOM_STRING spriteName, float x1, float y1, float x2, float y2, bool inWorld);
	
	void drawGame();
	void drawBackgroundNative();
	void drawForegroundNative();
	void drawPigDaysVignette(); //Seasons
	void drawLayer(float layer);
	void setSprite(FUSION_CUSTOM_STRING objectName, FUSION_CUSTOM_STRING spriteName);
	void setRollingSound(std::string objectName, std::string rollingSound);
	void setTexture(FUSION_CUSTOM_STRING objectName, FUSION_CUSTOM_STRING sheetName);
	void setObjectParameter(FUSION_CUSTOM_STRING name, float index, float value);
	void setScale(std::string name, float scaleX, float scaleY);
	int getScale(lua::LuaState* lua);
	void setGravityEnabled(std::string name, bool enabled);
	bool isGravityEnabled(std::string name);
	
	void setTheme(FUSION_CUSTOM_STRING theme);
	void setSleeping(FUSION_CUSTOM_STRING name, bool sleeping);
	void clipText(FUSION_CUSTOM_STRING textGroup, FUSION_CUSTOM_STRING text, float maxAllowedWidth);
	void drawLine2D(float x0, float y0, float x1, float y1, float w, float r, float g, float b, float a);
	void drawRectLines(float x0, float y0, float x1, float y1, float w, float r, float g, float b, float a);
	void drawRubberband(float x1, float y1, float x2, float y2, float w, float r, float g, float b, float a);
	void addToTrajectory(float index, float x, float y);
	void addPuffToTrajectory(float index, float x, float y);
	void startNewTrajectory();
	void setLevelLimits(float minx, float miny, float maxx, float maxy); //Is this the right order? Recovered from ABFM 1.1.5 DWARF
	bool isStringOnScreen(const std::string& str, float y, float scale_x, float scale_y, float x, game::Anchor anchor) const;
	int drawBox(lua::LuaState *lua);
	int drawUIText(lua::LuaState *lua);
	void drawUITextInternal(const lua::LuaTable& self, float x, float y, float scale_x, float scale_y, float angle, float hover_scale, float x_coord, float y_coord, std::string group, std::string text, game::Anchor* anchor);
	
	void multiplyGlyphRenderer(gr::Context*, Sprite*, float, float); //Only in Seasons?
	int getTrajectory(lua::Lua::LuaState* lua);
	void drawSlingScope(float vx0, float vy0, float verticalForce);
	void createThemeSprite(FUSION_CUSTOM_STRING name, FUSION_CUSTOM_STRING sprite, float x, float y, float speedX, float scaleX, float speedX, float speedY);
	void removeThemeSprite(FUSION_CUSTOM_STRING name, float layer);
	void modifyThemeSprite(FUSION_CUSTOM_STRING name, float x, float y, float scaleX, float scaleY, float angle, float layer);
	void setThemeRectColour(int index, uchar r, uchar g, uchar b, uchar a);
	void setThemeForegroundOffsetY(int index, float offset);
	void setThemeLayerTintColour(int index, uchar r, uchar g, uchar b, uchar a);
	void setThemeTintColour(uchar r, uchar g, uchar b);
	void enablePigDaysVignette(bool enable);
	void enableSpotlight(int x, int y);
	void disableSpotlight(); //Seasons
	
	lua::LuaTable getCurrentTime();
	int getTimeDifference(lua::LuaState* lua);
	int getTimeDifferenceInSeconds(lua::LuaState* lua);
	int toNewTimeFormat(lua::LuaState* lua);
	
	void postHighscore(FUSION_CUSTOM_STRING leaderBoardId, float score, bool levelScore);
	void unlockAchievement(FUSION_CUSTOM_STRING achievementId, FUSION_CUSTOM_STRING description);
	
	std::string exportLuaTableAsJSON(const std::string tableName);
	std::string importJSONToLuaTable(const std::string json, const std::string tableName);
	
	void initGameCenter();
	void prepareGameCenter(GameCenter* gc, FUSION_CUSTOM_STRING playerID, FUSION_CUSTOM_STRING alias);
	void removeGameCenter();
	void removeSupport();
	void getLeaderboardCategories();
	void setLeaderboardCategories(FUSION_CUSTOM_VECTOR<FUSION_CUSTOM_STRING> lb);
	void getFriends(); //Implemented on iOS only.
	void setFriends(FUSION_CUSTOM_MAP<FUSION_CUSTOM_STRING, FUSION_CUSTOM_STRING> fr); //Implemented on iOS only.
	void getLeaderboardScoresForRange(FUSION_CUSTOM_STRING category, float start, float length);
	void getLeaderboardScoresForFriends(FUSION_CUSTOM_STRING category); //Implemented on iOS only.
	void getLeaderboardScoreForLocalPlayer(FUSION_CUSTOM_STRING category); //Implemented on iOS only.
	void setLeaderboardScores(FUSION_CUSTOM_VECTOR<ScoreData> lData, FUSION_CUSTOM_STRING category, int range, int localRank, int localScore);
	void getAchievements();
	void captureScreen(std::string fileName);
	void setAchievements(FUSION_CUSTOM_VECTOR<AchievementData> aData);
	void setAchievementMetaData(FUSION_CUSTOM_VECTOR<AchievementData> aData);
	void getLeaderboardScoresForPlayers();
	void showAchievementPopUp(FUSION_CUSTOM_STRING identifier);
	void showLeaderboards();
	void showAchievements();
	void highScoresPosted(FUSION_CUSTOM_STRING leaderBoardId);
	void stopMainMenuAnimation(FUSION_CUSTOM_STRING icon);
	void hideLoadingInitGameCenter();
	void setAchievementsLoading(bool loading);
	void setGCPopupAllowed(bool value);
	
	void checkForUpdates(); //PC only?
	void updateCheckProc(); //PC only?
	void callVersionUpdater(); //PC only?
	
	void captureMouse(bool capture);
	void drawWindowResizer();
	bool isMouseCaptured();
	void setFullScreenMode(bool fullScreen);
	bool isInFullScreenMode();
	void setResolution(float width, float height);
	std::string getClipboardText();
	bool setMousePosition(int x, int y);
	
	void enableMotion(bool enable); //Dummied?
	bool isMotionEnabled(); //Always false?
	
	bool registerKey(FUSION_CUSTOM_STRING key, FUSION_CUSTOM_STRING type, FUSION_CUSTOM_STRING url); //Mangled symbol says it's not const.
	bool verifyDeviceID(std::string id);
	std::string getDeviceID();
	int checkRegistrationResult(lua::LuaState* lua);
	
	bool hasSpriteImage(const std::string& , const std::string& ) const;
	bool createSpriteImage(const void *, int, io::FileFormat, const std::string&, const std::string&, float, float);
	bool createSpriteFromData(const void *, unsigned int, unsigned int, const std::string&, const std::string&, float, float);
	
	void startURLThread(std::string url);
	void checkForURLProc(const std::string& url);
	
	void checkURLCallbacks();
	
	int unlockRequestChecksum(lua::LuaState* state);
	
	std::string sumLuaIntegerTableToString(lua::LuaTable* integersToSum);
	
	void setOffsetedViewport(float offsetX, float offsetY);
	
	void getCurrentLocale();
	
	virtual void storeStatusChanged(bool isInsideStore);
	void registerStoreStatusListener();
	
	void playVideo(std::string filename);
	void videoPlayEnded();
	
	void setNotificationsEnabled(bool value);
	
	void refreshRovioCloudManager();
	
	bool addNotificationAfter(std::string eventName, std::string seconds, std::string text);
	bool removeNotification(std::string eventName) { return m_notifications->removeNotification(eventName); } 
	void removeAllNotifications() { return m_notifications->removeAllNotifications(); }
	void setNotificationCallback(std::string callbackName) { m_notificationCallbackName = callBackname; }
	virtual void notificationReceived(const std::string& eventName);
	
	void setRemoteNotificationsEnabled(bool);
	
	//Open program
	bool openProgram(std::string target);
	bool canOpenProgram(std::string);
	
	//Device info
	std::string getOSName();
	std::string getOSVersion();
	std::string getModel();
	std::string getManufacturer();
	int getFullScreenWidth();
	int getFullScreenHeight();
	
	//Debug console
	void activateDebugConsole(std::string defaultText);
	void deactivateDebugConsole();
	
	void setMaxTranslation(float translation);
	
	bool drawScreenParticles();
	void createBoxLua(FUSION_CUSTOM_STRING name, FUSION_CUSTOM_STRING sprite, float x, float y, float w, float h, float density, float friction, float restitution, bool collision, bool controllable, float z_order); //Vars recovered from 1.1.5 ABFM Meego.
	void createCircleLua(std::string name, std::string sprite, float x, float y, float r, float density, float friction, float restitution, float z_order, bool collision, float controllable);
	void resizeCircle(std::string name, float radius);
	float getRadius(std::string name);
	void createPolygonLua(std::string name, std::string sprite, float x, float y, lua::LuaTable verts, float density, float friction, float restitution, float z_order, bool collision, bool, float);
	void setColliderType(std::string name, int type);
	void setVisible(std::string name, bool visible);
	void setFilterCategory(std::string name, int category);
	void setFilterMask(std::string name, int mask);
	void setSensor(std::string name, bool isSensor);
	int createJointLua(lua::LuaState *lua);
	void checkJointLimits(FUSION_CUSTOM_STRING jointName);
	int setJointParameters(lua::LuaState* lua);
	int getJointListLua(lua::LuaState* lua);
	void destroyJointLua(FUSION_CUSTOM_STRING jointName); //Unimplemented on ABS410.
	void destroyJoint(b2Joint* joint);
	void applyImpulse(FUSION_CUSTOM_STRING name, float xForce, float yForce, float x, float y); //Unimplemented in ABS410.
	int applyImpulse(lua::LuaState* lua); //Does not exist in ABC < 1.6.3.
	void applyForce(FUSION_CUSTOM_STRING name, float xForce, float yForce, float x, float y);
	void setPosition(FUSION_CUSTOM_STRING name, float x, float y);
	void setRotation(FUSION_CUSTOM_STRING name, float angle);
	void setVelocity(FUSION_CUSTOM_STRING name, float velocityX, float velocityY);
	void setAngularVelocity(FUSION_CUSTOM_STRING name, float velocity);
	void setLinearDamping(std::string name, float linearDamping);
	void setAngularDamping(std::string name, float angularDamping);
	void setFriction(float friction);
	void setRestitution(float restitution);
	void setDensity(float density);
	void setPhysicsSimulationScale(float scale);
	void setPhysicsEnabled(bool enabled);
	bool isPhysicsEnabled();
	void setWorldGravity(float gravityX, float gravityY);
	void setAccelerometerActive(bool state);
	void setCameraViewport(float left, float top, float right, float bottom);
	int getCameraTopleft(lua::LuaState *l);
	void saveLevel(FUSION_CUSTOM_STRING name);
	#if defined(ABC) && ABC_VERSION > 163
	void loadLevel(std::string name, std::string key);
	#endif
	void removeTemporaryLevel(std::string name);
	void saveParticleFile(std::string particleName);
	void setParticleEditorActive(bool active);
	b2Body* getBody(const std::string& name);
	FUSION_CUSTOM_STRING getBodyName(b2Body* body);
	void removeObject(FUSION_CUSTOM_STRING name);
	void setEditing(bool editing);
	bool isEditing();
	void createDirectory(FUSION_CUSTOM_STRING path);
	bool checkDirectory(FUSION_CUSTOM_STRING path);
	lua::LuaTable getDirectoryFileList(std::string path);
	void removeParticleFile(std::string filename);
	bool checkForLuaFile(FUSION_CUSTOM_STRING filename);
	void verifyLuaTableFileName(const lua::LuaTable& table, const std::string& filename);
	void goToTaskSwitcherLua();
	void activate(bool active);
	int getIntersectingObjects(lua::LuaState* lua);
	int getWorldPoint(lua::LuaState* lua);
	int getLocalPoint(lua::LuaState* lua);
	float getAngularVelocity(std::string name);
	float getSpeed(std::string name);
	void printGlobals();
	void setUpdating(bool update);
	
	//Text input
	void createTextInputField(std::string name);
	void removeTextInputField(std::string name);
	void activateTextInputField(std::string name, std::string initialText);
	void deactivateTextInputField(std::string name);
	
	void getGameObject(const std::string& objectName);
	
	//Contact
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(const b2Manifold* manifold);
	
	//Collide
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
	virtual bool RayCollide(void*, b2Fixture*) { return true; }
	
	void basicBeginContact(b2Contact* contact);
	
	float countCollisionForce(const b2Body* bodyA, const b2Body* bodyB, const float forceDivider);
	void destroyBreakableJoints(std::string blockName, float impactForce);
	
	//Hoop
	void hoopBeginContact(b2Contact* contact);
	void hoopEndContact(b2Contact* contact);
	
	//Portal
	void portalBeginContact(b2Contact* contact);
	void portalEndContact(b2Contact* contact);
	void inheritTeleportation(std::string blockName, lua::LuaTable children);
	
	void createGlueJoints();
	
	void bubbleBeginContact(b2Contact* contact);
	
	void addTrajectoryPositionsForBirds(lang::FastDelegate1<GameObject*, b2Vec2> positionFunction);
	b2Vec2 getBodyPosition(GameObject *object);
	b2Vec2 getLastPositionFromTransformData(GameObject *object);
	b2Vec2 getCurrentInterpolatedPosition(GameObject* object);
	
	void reloadInGameSprites();
	
	bool additionalViewsActive();
	
	void loadTableFromFile(std::string fileName, std::string targetTable);
	
	lang::Ptr<RovioCloudManager> getRovioCloudManager();
	//RESOLUTION_CHANGED
private:
	void drawTrajectories();
};

#endif