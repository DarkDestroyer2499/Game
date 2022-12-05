#ifndef ENGINE
#define ENGINE

#include <SFML/Graphics.hpp>
#include <box2d.h>
#include <thread>

#define WINDOW_NAME "SUPER GAME"

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
	Engine(ScreenMode, unsigned int, unsigned int);
    Engine() = delete;
    ~Engine();
    void Run();

	sf::RenderWindow& GetWindow();

    void SetScreenMode(ScreenMode);

    void Stop();


private:
    



private:
	sf::RenderWindow mWindow;
    unsigned int mScnWidht, mScnHeight;
    ScreenMode mWindowMode;
    bool mWorking;
    sf::Event mEvent;
    std::unique_ptr<std::thread> mMainThread;
};

#endif // !ENGINE