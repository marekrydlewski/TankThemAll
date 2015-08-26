#pragma once

class ShaderLoader
{
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:
	ShaderLoader();
	virtual ~ShaderLoader();
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename);
};

