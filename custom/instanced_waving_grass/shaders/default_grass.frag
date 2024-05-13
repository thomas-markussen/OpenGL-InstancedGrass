//Inputs
in vec3 ViewNormal;
in vec3 ViewTangent;
in vec3 ViewBitangent;
in vec2 TexCoord;
in vec3 FragPosition;

//Outputs
out vec4 FragAlbedo;
out vec2 FragNormal;
out vec4 FragOthers;

//Uniforms
uniform vec3 Color;
uniform sampler2D ColorTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;

// Grass gradient
uniform vec3 BottomColor;
uniform vec3 TopColor;
uniform float GradientBias;

void main()
{
	float gradient = FragPosition.y / GradientBias; // Calculate gradient based on y position
    vec3 finalColor = mix(BottomColor, TopColor, gradient); // Interpolate between colors based on gradient
    FragAlbedo = vec4(finalColor, 1);

	vec3 viewNormal = SampleNormalMap(NormalTexture, TexCoord, normalize(ViewNormal), normalize(ViewTangent), normalize(ViewBitangent));
	FragNormal = viewNormal.xy;

	FragOthers = texture(SpecularTexture, TexCoord);
}
