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
/*
//---------------------------------------------------------------------------
-- SSLR (Screen-Space Local Reflections) by Igor Katrich and Shadmar 26/03/2015
-- Email: igorbgz@outlook.com
//---------------------------------------------------------------------------*/
#version 400

uniform sampler2DMS texture0;
uniform sampler2D texture1;
uniform sampler2DMS texture2;

uniform bool isbackbuffer;
uniform vec2 buffersize;

uniform mat4 projectioncameramatrix;
uniform vec3 cameraposition;
uniform mat3 cameranormalmatrix;

//User variable's
#define reflectionfalloff 1.0f
#define raylength 1.1f
#define maxstep 10
#define edgefadefactor 0.5f

out vec4 fragData0;

vec4 getPosition(in vec2 texCoord)
{
	float x = texCoord.s * 2.0f - 1.0f;
	float y = texCoord.t * 2.0f - 1.0f;
	float z = texelFetch(texture0, ivec2(texCoord*buffersize),0).r;
	vec4 posProj = vec4(x,y,z,1.0f);
	vec4 posView = inverse(projectioncameramatrix) * posProj;
	posView /= posView.w;
	return posView;
}

void main(void)
{
	vec2 icoord = vec2(gl_FragCoord.xy/buffersize);
	if (isbackbuffer) icoord.y = 1.0f - icoord.y;
	
	vec4 color = texture(texture1,icoord);
	vec3 normalView = normalize(texelFetch(texture2, ivec2(icoord*buffersize),0).xyz * 2.0f - 1.0f);
	normalView = cameranormalmatrix*normalView;
	
	vec3 posView = getPosition(icoord).xyz;
	
	vec4 reflectedColor = vec4(0.0f);
	vec3 reflected = normalize(reflect(normalize(posView-cameraposition), normalView));
	
	float rayLength = raylength;
	vec4 T = vec4(0.0f);
	vec3 newPos;
	
	float cdepth = texelFetch(texture0, ivec2(icoord.xy*buffersize),0).r;
	
	for (int i = 0; i < maxstep; i++)
	{
		newPos = posView + reflected * rayLength;
		T = projectioncameramatrix * vec4(newPos, 1.0f);
		T.xy = vec2(0.5f) + 0.5f * T.xy / T.w;
		T.z /= T.w;
		if (T.x <= 1.0f && T.x >= 0.0f && T.y <= 1.0f && T.y >= 0.0f)
		{
			float depth = texelFetch(texture0, ivec2(T.xy*buffersize),0).r;
			float delta = abs(cdepth - depth);
			newPos = getPosition(T.xy).xyz;
			rayLength = length(posView - newPos);
			if(abs(depth - T.z) < 1.0f && delta < 0.25f)
			{
				reflectedColor = texture(texture1,T.xy);
			} 
		} 
		else 
		{
			reflectedColor=color;
		}
	}	
	
	//Fading to screen edges
	vec2 fadeToScreenEdge = vec2(1.0f);
	fadeToScreenEdge.x = distance(icoord.x , 1.0f);
	fadeToScreenEdge.x *= distance(icoord.x, 0.0f) * 4.0f;
	fadeToScreenEdge.y = distance(icoord.y, 1.0f);
	fadeToScreenEdge.y *= distance(icoord.y, 0.0f) * 4.0f;
	
	float fresnel =  reflectionfalloff*(1.0f-(pow(dot(normalize(posView-cameraposition), normalize(normalView)), 2.0f)));
	if(color.a < 1.0f) color = mix(color, reflectedColor,clamp(fresnel*pow(fadeToScreenEdge.x * fadeToScreenEdge.y,edgefadefactor)*(1.0f-color.a),0.0f,1.0f));
	
	fragData0 = color;
}
