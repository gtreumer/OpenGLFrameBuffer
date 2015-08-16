#include "stdio.h"
#include "RunnerApp.h"
#include "common.h"
#include "Scene.h"

const int wndWidth   = 512;
const int wndHeight  = 512;

int main(int argc, char** argv)
{
    Runner::Win32WindowPtr newWindow = Runner::Win32WindowPtr(new Runner::Win32Window());
    Runner::ScenePtr newScene = Runner::ScenePtr(new Runner::Scene(600, 600));
    newWindow->Create(600, 600);
    newWindow->addScene(newScene);
    newWindow->Run();

	//RunnerApp* app = new RunnerApp();
	//app->Create(wndWidth, wndHeight);
	//app->Run();

	//SAFE_DELETE_PTR(app);

	return 0;
}