#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <string>

class ShaderManager
{
public:

	ShaderManager();
	~ShaderManager();
	void CreateProgram(const std::string& shaderName,
		const std::string& VertexShaderFilename,
		const std::string& FragmentShaderFilename);

	static const GLuint GetShader(const std::string&);

private:

	std::string ReadShader(const std::string& filename);

	GLuint CreateShader(GLenum shaderType,
		const std::string& source,
		const std::string& shaderName);


	static std::map<std::string, GLuint> programs;
};