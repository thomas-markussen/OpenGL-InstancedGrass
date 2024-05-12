//Inputs
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexTangent;
layout (location = 3) in vec3 VertexBitangent;
layout (location = 4) in vec2 VertexTexCoord;
layout (location = 5) in mat4 InstanceMatrix; // INSTANCING

//Outputs
out vec3 ViewNormal;
out vec3 ViewTangent;
out vec3 ViewBitangent;
out vec2 TexCoord;
out vec3 FragPosition; // Need this for color blending

//Uniforms
uniform mat4 WorldViewMatrix;
uniform mat4 WorldViewProjMatrix;
uniform float Time;

void main()
{
	// normal in view space (for lighting computation)
	ViewNormal = (WorldViewMatrix * vec4(VertexNormal, 0.0)).xyz;

	// tangent in view space (for lighting computation)
	ViewTangent = (WorldViewMatrix * vec4(VertexTangent, 0.0)).xyz;

	// bitangent in view space (for lighting computation)
	ViewBitangent = (WorldViewMatrix * vec4(VertexBitangent, 0.0)).xyz;

	// texture coordinates
	TexCoord = VertexTexCoord;

	vec3 pos = VertexPosition;

	// Calculate wind sway effect
    float windStrength = 1.4; // Adjust this value to control wind intensity
    float swayFrequency = 0.3; // Adjust this value to control wind sway speed
    float swayAmount = sin(VertexPosition.z * swayFrequency + Time) * windStrength;

    // Adjust swayAmount based on height of grass
    float heightFactor = 1.0 - (1.0 - VertexPosition.y);
    swayAmount *= heightFactor;

    pos.z += swayAmount;

	// final vertex position (for opengl rendering, not for lighting)
	gl_Position = WorldViewProjMatrix * InstanceMatrix * vec4(pos, 1.0);
	FragPosition = VertexPosition;
}
