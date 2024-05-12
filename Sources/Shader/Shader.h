#pragma once

#include <string>

struct ShaderInfo
{
	unsigned int type;
	const char* filename;
	unsigned int shaderID;
};

struct Shader
{
	static unsigned int loadShaders(ShaderInfo* shaderInfo);

private:

};