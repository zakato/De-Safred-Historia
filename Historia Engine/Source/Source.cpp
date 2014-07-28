#include <Application.hpp>





using namespace zkt;

int main()
{
	Application* app;
	app = new Application();
	app->Start();
	app->Run();
	return 0;
}