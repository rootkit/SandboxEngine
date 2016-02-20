SHADER version 1
@OpenGL2.Vertex
#version 400

uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;
uniform vec2 position[4];

in vec3 vertex_position;

void main(void)
{
	gl_Position = projectionmatrix * (drawmatrix * vec4(position[gl_VertexID]+offset, 0.0, 1.0));
}
@OpenGLES2.Vertex

@OpenGLES2.Fragment

@OpenGL4.Vertex
#version 400

uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;
uniform vec2 position[4];

in vec3 vertex_position;

void main(void)
{
	gl_Position = projectionmatrix * (drawmatrix * vec4(position[gl_VertexID]+offset, 0.0, 1.0));
}
@OpenGL4.Fragment
//--------------------------------------
// Godray shader by Shadmar
//--------------------------------------

#version 400

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec2 buffersize;
uniform float currenttime;
uniform bool isbackbuffer;
uniform vec2 camerarange;
uniform vec2 screenLightPos=vec2(0.5,0.5);
uniform mat4 cameramatrix;

out vec4 fragData0;

uniform bool fWhiteOnly=true;
uniform float fExposure=0.3;
uniform float fDecay=0.97;
uniform float fDensity=0.6;
uniform float fWeight=0.24;
uniform float fClamp=1.0;
uniform vec3 sunDir;
uniform vec3 camDir;
const int iSamples = 20;

void main()
{
	vec2 icoord = vec2(gl_FragCoord.xy/buffersize);
	if (isbackbuffer) icoord.y = 1.0 - icoord.y;

	vec4 color=texture(texture1, icoord);
	
	vec2 deltaTextCoord = vec2(icoord - vec2(screenLightPos));
	deltaTextCoord *= 1.0 / float(iSamples) * fDensity;
	vec2 coord = icoord;
	float illuminationDecay = 1.0;
	vec4 fragColor = vec4(0.0);

	vec2 screenPosNormalized=screenLightPos-0.5;

	for(int i=0; i < iSamples ; i++)
	{
		coord -= deltaTextCoord;
		vec4 texel = texture(texture1, coord);
		texel *= illuminationDecay * fWeight;

		fragColor += texel;

		illuminationDecay *= fDecay;
	}
	fragColor *= fExposure;
	fragColor = clamp(fragColor, 0.0, fClamp);

	float cc=dot(sunDir,camDir);

	if (fWhiteOnly)
		fragData0 = mix(color,.5*vec4(fragColor.r+fragColor.b+fragColor.g),max(0.0,cc*(1-abs(pow(screenPosNormalized.x,2)))*(1-abs(pow(screenPosNormalized.y,2)))));
	else
		fragData0 = mix(color,fragColor,max(0.0,cc*(1-abs(pow(screenPosNormalized.x,2)))*(1-abs(pow(screenPosNormalized.y,2)))));
	if (screenPosNormalized.x < -1.0 || screenPosNormalized.x > 1.0 || screenPosNormalized.y < -1.0 || screenPosNormalized.y > 1.0) fragData0=color;
	
	if (cameramatrix[3][1] <= -0.99) fragData0=texture(texture1, icoord);
}
