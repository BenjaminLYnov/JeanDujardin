#ifndef SHADER_H
#define SHADER_H

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
};

#endif // SHADER_H