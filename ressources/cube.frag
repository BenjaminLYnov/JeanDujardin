#version 430 core

in vec4 materialColor;
in vec3 normalWorld;
in vec3 positionWorld;

struct Material
{
	float ambiant;
	float diffuse;
	float specular;
	float shinyness;
};

struct DirectonalLight
{
	vec3 dir;
	vec3 color;
};

uniform Material material;
uniform DirectonalLight light;
uniform vec4 cameraPosWorld;

void main()
{
	vec4 ambiant = material.ambiant * materialColor;

	vec4 diffuse = material.diffuse * max(0, -dot(light.dir, normalWorld.xyz)) * materialColor;
	
	vec3 dc = normalize(positionWorld - cameraPosWorld.xyz);
	vec3 dcprime = 2.0 * dot(dc, normalWorld) * normalWorld - dc;

	float specularCoef = pow(max(0, dot(light.dir, -dcprime)), material.shinyness);

	gl_FragColor = (1. - specularCoef) * ( ambiant + diffuse ) + specularCoef * vec4(light.color, 1);










	//float specularCoef = clamp(material.specular * pow(max(0, dot(light.dir, -dcprime)), material.shinyness), 0.0, 1.0);

	//gl_FragColor = (1.0 - specularCoef) * ( ambiant + diffuse ) + specularCoef * vec4(light.color, 1);
}
