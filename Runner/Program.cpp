#include "Program.h"
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "common.h"

namespace Runner
{

	void Program::Init(const std::string& vertShaderSrc,  const std::string& fragShaderSrc)
	{
		m_vertShader = vertShaderSrc;
		m_fragShader = fragShaderSrc;

		isCreated = false;
	}

	unsigned int Program::GetProgramID()
	{
		if (isCreated)
		{
			return m_progID;
		}

		m_create_shader(GL_VERTEX_SHADER, m_vertShader, &m_vertID);
		m_create_shader(GL_FRAGMENT_SHADER, m_fragShader, &m_fragID);
		m_create_program(m_vertID, m_fragID, &m_progID);

		isCreated = true;

		return m_progID;
	}

	void Program::m_create_shader(int shaderType, std::string& shaderSrc, unsigned int* shaderID)
	{
		int iStatus = -1;

		*shaderID = GL_CHECK(glCreateShader(shaderType));

		const char *c_str = shaderSrc.c_str();
		GL_CHECK(glShaderSource(*shaderID, 1, &c_str, NULL));
		GL_CHECK(glCompileShader(*shaderID));
		GL_CHECK(glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &iStatus));

		if(iStatus != GL_TRUE) {
			GLint iLen;
			char *sDebugSource = NULL;
			char *sErrorLog = NULL;

			//* Get shader source. */
				GL_CHECK(glGetShaderiv(*shaderID, GL_SHADER_SOURCE_LENGTH, &iLen));

			sDebugSource = (char*)malloc(iLen);

			GL_CHECK(glGetShaderSource(*shaderID, iLen, NULL, sDebugSource));

			printf("Debug source START:\n%s\nDebug source END\n\n", sDebugSource);
			free(sDebugSource);

			//* Now get the info log. */
				GL_CHECK(glGetShaderiv(*shaderID, GL_INFO_LOG_LENGTH, &iLen));

			sErrorLog = (char*)malloc(iLen);

			GL_CHECK(glGetShaderInfoLog(*shaderID, iLen, NULL, sErrorLog));

			printf("Log START:\n%s\nLog END\n\n", sErrorLog);
			free(sErrorLog);
		}
	}

	void Program::m_create_program(const unsigned int& vertShaderID, const unsigned int& fragShaderID, unsigned int* programID)
	{
		*programID = GL_CHECK(glCreateProgram());

		///* Attach shaders and link uiProgram */
		GL_CHECK(glAttachShader(*programID, vertShaderID));
		GL_CHECK(glAttachShader(*programID, fragShaderID));
		GL_CHECK(glLinkProgram(*programID));
	}
}