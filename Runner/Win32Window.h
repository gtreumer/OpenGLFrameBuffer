#ifndef WIN32_WINDOW_H__
#define WIN32_WINDOW_H__

#include "windows.h"
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "common.h"

#include "Scene.h"
#include <memory>

namespace Runner
{
	class Win32Window
	{
	public:
		Win32Window() {}
		virtual ~Win32Window() {}

		virtual void Create(const int& /*uiWidth*/, const int& /*uiHeight*/);
		void Run();
		virtual void Destroy();

        void addScene(ScenePtr scene);
	protected:
		virtual void t_OnRender() {}
        virtual void t_OnInit() {}
	private:
		EGLDisplay	sEGLDisplay;
		EGLContext	sEGLContext;
		EGLSurface	sEGLSurface;
        ScenePtr mScene;
	};

    typedef std::shared_ptr<Win32Window> Win32WindowPtr;
}

#endif
