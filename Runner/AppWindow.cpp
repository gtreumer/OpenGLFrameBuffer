#include "AppWindow.h"
#include "stdio.h"
#include <stdlib.h>

#ifdef _WIN32
	#include <windows.h>
#endif


#define GL_CHECK(x) \
	x; \
		{ \
		GLenum glError = glGetError(); \
		if(glError != GL_NO_ERROR) { \
		fprintf(stderr, "glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
		exit(1); \
		} \
		}

#define EGL_CHECK(x) \
	x; \
	{ \
	EGLint eglError = eglGetError(); \
	if(eglError != EGL_SUCCESS) { \
	fprintf(stderr, "eglGetError() = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
	exit(1); \
	} \
	} \

namespace Runner
{
#ifdef _WIN32
		/*
	* process_win32_window(): This function handles Windows callbacks.
	*/
	LRESULT CALLBACK process_win32_window(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
		switch(uiMsg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		case WM_ACTIVATE:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SIZE:
			return 0;
		}

		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	HWND create_win32_window(unsigned uiWidth, unsigned uiHeight) {
		WNDCLASS wc;
		RECT wRect;
		HWND sWindow;
		HINSTANCE hInstance;

		wRect.left = 0L;
		wRect.right = (long)uiWidth;
		wRect.top = 0L;
		wRect.bottom = (long)uiHeight;

		hInstance = GetModuleHandle(NULL);

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = (WNDPROC)process_win32_window;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = L"OGLES";

		RegisterClass(&wc);

		AdjustWindowRectEx(&wRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		sWindow = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, L"OGLES", L"main", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, uiWidth, uiHeight, NULL, NULL, hInstance, NULL);

		ShowWindow(sWindow, SW_SHOW);
		SetForegroundWindow(sWindow);
		SetFocus(sWindow);

		return sWindow;
	}
#endif

	void AppWindow::Create(unsigned width, unsigned height)
	{
#ifdef _WIN32
		HWND hWindow;
		HDC  hDisplay;
#endif

		/* EGL Configuration */

		EGLint aEGLAttributes[] = {
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE
		};

		EGLint aEGLContextAttributes[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLConfig	aEGLConfigs[1];
		EGLint		cEGLConfigs;

		const unsigned int uiWidth  = 640;
		const unsigned int uiHeight = 480;

		hDisplay = EGL_DEFAULT_DISPLAY;

		sEGLDisplay = EGL_CHECK(eglGetDisplay(hDisplay));

		EGL_CHECK(eglInitialize(sEGLDisplay, NULL, NULL));
		EGL_CHECK(eglChooseConfig(sEGLDisplay, aEGLAttributes, aEGLConfigs, 1, &cEGLConfigs));

		if (cEGLConfigs == 0) {
			printf("No EGL configurations were returned.\n");
			exit(-1);
		}

#ifdef _WIN32
		hWindow = create_win32_window(uiWidth, uiHeight);
#endif

		sEGLSurface = EGL_CHECK(eglCreateWindowSurface(sEGLDisplay, aEGLConfigs[0], (EGLNativeWindowType)hWindow, NULL));

		if (sEGLSurface == EGL_NO_SURFACE) {
			printf("Failed to create EGL surface.\n");
			exit(-1);
		}

		sEGLContext = EGL_CHECK(eglCreateContext(sEGLDisplay, aEGLConfigs[0], EGL_NO_CONTEXT, aEGLContextAttributes));

		if (sEGLContext == EGL_NO_CONTEXT) {
			printf("Failed to create EGL context.\n");
			exit(-1);
		}

		EGL_CHECK(eglMakeCurrent(sEGLDisplay, sEGLSurface, sEGLSurface, sEGLContext));
	}	

	void AppWindow::ProccesMessage()
	{
		int bDone = 0;
		MSG sMessage;

		while (!bDone) 
		{
			if(PeekMessage(&sMessage, NULL, 0, 0, PM_REMOVE)) {
				if(sMessage.message == WM_QUIT) {
					bDone = 1;
				} else {
					TranslateMessage(&sMessage);
					DispatchMessage(&sMessage);
				}
			}

			// graphic render functionality
			if (m_renderCallback)
			{
				m_renderCallback();
			}

			if (!eglSwapBuffers(sEGLDisplay, sEGLSurface)) {
				printf("Failed to swap buffers.\n");
			}

			Sleep(20);

		}

		// here there will be release graphic functions
		if (m_releaseCallback)
			m_releaseCallback();

	}

	void AppWindow::SetOnRenderCallback(AppCallback callback)
	{
		m_renderCallback = callback;
	}
	
	void AppWindow::SetOnReleaseCallback(AppCallback callback)
	{
		m_releaseCallback = callback;
	}

} // namespace Runner