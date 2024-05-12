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

void main()
{
	//FragAlbedo = vec4(Color.rgb * texture(ColorTexture, TexCoord).rgb, 1);
	//FragAlbedo = vec4(Color.rgb * vec4(0,1,0,0).rgb, 1);

	vec3 viewNormal = SampleNormalMap(NormalTexture, TexCoord, normalize(ViewNormal), normalize(ViewTangent), normalize(ViewBitangent));
	FragNormal = viewNormal.xy;

	FragOthers = texture(SpecularTexture, TexCoord);

	float maxHeight = 1.0;

	float gradient = FragPosition.y / maxHeight; // Calculate gradient based on y position
    vec3 finalColor = mix(vec3(1,0,0), vec3(0,1,0), gradient); // Interpolate between colors based on gradient
    FragAlbedo = vec4(finalColor, 1.0);
}
