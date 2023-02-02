#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <thread>
#include <vector>
#include "Entity.hpp"

#define WINDOW_NAME "SUPER GAME"

const b2Vec2 GRAVITY(0.f, 9.8f);


constexpr unsigned int RESERVE_ENTITIES = 50;


enum ScreenMode
{
    None = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
    Titlebar = 1 << 0, ///< Title bar + fixed border
    Resize = 1 << 1, ///< Title bar + resizable border + maximize button
    Close = 1 << 2, ///< Title bar + close button
    Fullscreen = 1 << 3,
};

class Engine
{
public:
	Engine(sf::RenderTarget*,ScreenMode, unsigned int, unsigned int);
    Engine() = delete;
    ~Engine();

    void Run();
	sf::RenderTarget* GetWindow();
    void SetScreenMode(ScreenMode);
    Entity* CreateObject(std::string name = std::string("Uknown"));
    b2World* GetMainWorld();
    uint32_t GetRenderTime();
    void Stop();
   
    void Update(sf::RenderTexture* window);
private:
    void Update(sf::RenderWindow* window);
   
    friend class Editor;
    friend class UI;
private:
	sf::RenderTarget* mWindow;
    unsigned int mScnWidht, mScnHeight;
    ScreenMode mWindowMode;
    bool mWorking;
    sf::Event mEvent;
    std::unique_ptr<std::thread> mMainThread;
    std::unique_ptr<b2World> mWorld;
    std::vector<Entity> mObjectList;
    uint32_t mLastRenderTime;
    sf::Clock mClock;
};

#endif // !ENGINE_H