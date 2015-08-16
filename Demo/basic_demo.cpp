//#include "AppWindow.h"
#include "RunnerApp.h"
#include "common.h"
#include "stdio.h"

#include "GLES2/gl2.h"

//void render()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
//};

int basic_demo_main()
{
	RunnerApp* app = new RunnerApp();
	int mWidth  = 512;
	int mHeight = 512;
	
	app->Create(mWidth, mHeight);
	app->Run();
	//window->Destroy();

	SAFE_DELETE_PTR(app);
	return 0;
}
