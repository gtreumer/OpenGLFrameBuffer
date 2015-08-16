#ifndef RUNNER_H__
#define RUNNER_H__

#include "GLES2/gl2.h"
#include "EGL/egl.h"

namespace Runner
{
	typedef void (*AppCallback)();

	class AppWindow
	{
	public:
		AppWindow() : 
			  m_renderCallback(0), 
			  m_releaseCallback(0) {}

		~AppWindow() {}

		void Create(unsigned width, unsigned height);
		
		void Initialize();
		void Render();
		void Rezize(unsigned int width, unsigned int height);

		void ProccesMessage();
		void SetOnRenderCallback(AppCallback callback);
		void SetOnReleaseCallback(AppCallback callback);
	private:
		AppCallback m_renderCallback;
		AppCallback m_initCallback;
		AppCallback m_releaseCallback;

		EGLDisplay	sEGLDisplay;
		EGLContext	sEGLContext;
		EGLSurface	sEGLSurface;
	};
}

#endif /*RUNNER_H__*/