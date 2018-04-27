#include <vld.h>
#include <ECS/Engine.h>
#include <Context/Window.h>


using namespace Context;

ECS::ECSEngine* ECS::ECS_Engine;

int main()
{
	Window context;
	context.Init();
	context.Run();
	context.Close();
}