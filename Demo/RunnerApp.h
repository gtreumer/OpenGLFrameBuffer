#include "AppNativeWindow.h"

namespace Runner
{
	struct Quad;
	class Program;
}

class RunnerApp : public AppNativeWindow
{
public:
	RunnerApp();
	~RunnerApp();

	virtual void Create(const int& /*uiWidth*/, const int& /*uiHeight*/);
	virtual void Destroy();
protected:
	void t_OnInit();                                                     

	void t_OnRender();
private:
	void m_BindVBO(int& vboID);
	void m_loadImage(const char* imagePath);
	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
private:
	Runner::Quad* m_quad;
	Runner::Program* m_program;
	unsigned int m_programID;
};