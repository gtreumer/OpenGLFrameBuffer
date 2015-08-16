#ifndef COMMON_H__
#define COMMON_H__

namespace
{
	#define NULL 0

	#define SAFE_DELETE_PTR(ptr)\
	{\
		if (ptr)\
		{\
			delete ptr;\
			ptr = NULL;\
		}\
	}\

	#define SAFE_DELETE_ARR_PTR(ptr)\
	{\
		if (ptr)\
		{\
			delete[] ptr;\
			ptr = NULL;\
		}\
	}\

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
	}

} /*anonymous namespace*/

#endif