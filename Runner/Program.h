#ifndef PROGRAM_H__
#define PROGRAM_H__

#include <string>
#include <memory>

namespace Runner
{
	class Program
	{
	public:
		Program() : isCreated(false) {}
		~Program() {}
		void Init(const std::string& /*vertShaderSrc*/,  const std::string& /*fragShaderSrc*/);
		unsigned int GetProgramID();
	private:
		void m_create_shader(int shaderType, std::string& shaderSrc, unsigned int* shaderID);
		void m_create_program(const unsigned int& vertShaderID, const unsigned int& fragShaderID, unsigned int* programID);
	private:
		std::string m_vertShader;
		std::string m_fragShader;
		unsigned int m_fragID;
		unsigned int m_vertID;
		unsigned int m_progID;
		bool isCreated;
	};

    typedef std::shared_ptr<Program> ProgramPtr;
}

#endif