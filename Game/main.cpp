#include <SFML/Graphics.hpp>
#include <box2d.h>
#include "src/Engine.hpp" 
#include <Windows.h>
#include <thread>
using namespace sf;

int main()
{
	Engine engine(ScreenMode::Close, 0, 0);
	engine.Run();
	Sleep(2000);
	engine.Stop();


	system("pause");
	return 0;
}