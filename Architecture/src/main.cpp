#include <vld.h>
#include <ECS/Engine.h>
#include <Graphics/Window.h>


using namespace Graphics;

ECS::ECSEngine* ECS::ECS_Engine;

int main()
{
	Window context;
	context.Init();
	context.Run();
	context.Close();
}