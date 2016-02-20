SHADER version 1
@OpenGL2.Vertex
/*
---------------------------------------------------------------------------
-- SSAO (Screen-Space Ambient Occlusion) by Igor Katrich 26/02/20015
-- Email: igorbgz@outlook.com
//---------------------------------------------------------------------------*/
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
/*
---------------------------------------------------------------------------
-- SSAO (Screen-Space Ambient Occlusion) by Igor Katrich 26/02/20015
-- Email: igorbgz@outlook.com
//---------------------------------------------------------------------------*/
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
---------------------------------------------------------------------------
-- SSAO (Screen-Space Ambient Occlusion) by Igor Katrich 26/02/20015
-- Email: igorbgz@outlook.com
--
-- Update script file by Josh Klint and Shadmar 08/03/2015
//---------------------------------------------------------------------------*/

#version 400

uniform sampler2DMS texture1; //Depth
uniform sampler2DMS texture2; //Normal
uniform sampler2D texture10; //Noise
uniform bool isbackbuffer;
uniform vec2 buffersize;
uniform vec2 camerarange;

#define raycasts 2.0
#define aoscale 0.015
#define samples 16.0

out vec4 fragData0;

float DepthToZPosition(in float depth) {
	return camerarange.x / (camerarange.y - depth * (camerarange.y - camerarange.x)) * camerarange.y;
}

mat3 vec3tomat3( in vec3 z ) {
	mat3 mat;
	mat[2]=z;
	vec3 v=vec3(z.z,z.x,-z.y);
	mat[0]=cross(z,v);
	mat[1]=cross(mat[0],z);
	return mat;
}

vec2 GetTexCoord()
{
	vec2 texcoord = vec2(gl_FragCoord.xy / buffersize);
	if (isbackbuffer) texcoord.y = 1.0 - texcoord.y;
	return texcoord;
}

void main(void)
{
	float depth;
	float lineardepth;
	vec2 pixelsize = 1.0 / buffersize;
	vec2 texcoord = GetTexCoord();
	
	depth = texelFetch(texture1, ivec2(texcoord * buffersize), 0).x;
	
	if(depth < 1.0) {
		lineardepth = DepthToZPosition(depth);

		vec2 rotationTC=(texcoord*buffersize)/4.0;
		vec3 vRotation=normalize((texture(texture10, rotationTC).xyz * 2.0) - 1.0);
		mat3 rotMat=vec3tomat3(vRotation);	
		
		float fSceneDepthP = DepthToZPosition(depth);

		float offsetScale = aoscale;
		float offsetScaleStep = 1.0 + 1.5 / samples;
		
		float ao = 0.0;	
		
		for(int i = 0; i < (samples / 8); i++)
			for(int x = -1; x <= 1; x += 2)
			for(int y = -1; y <= 1; y += 2)
			for(int z = -1; z <= 1; z += 2)
			{
				vec3 vOffset = normalize (vec3(x, y, z)) * (offsetScale *= offsetScaleStep);
				vec3 vRotatedOffset = rotMat * vOffset;
				vec3 vSamplePos = vec3(texcoord, fSceneDepthP);
				vSamplePos += vec3(vRotatedOffset.xy, vRotatedOffset.z * fSceneDepthP*raycasts);
				
				float fSceneDepthS = DepthToZPosition(texelFetch(texture1, ivec2(vSamplePos.xy * buffersize), 0).x);
				float fRangeIsInvalid = clamp(((fSceneDepthP - fSceneDepthS) / fSceneDepthS), 0.0, 1.0);
				
				ao += mix(clamp(ceil(fSceneDepthS - vSamplePos.z), 0.0, 1.0), 0.5, fRangeIsInvalid);
			}
			
		ao /= samples * 1.5;
		fragData0 = vec4(clamp(ao + ao + ao * 1.22, 0.0, 1.0));
	}
	else {
		fragData0 = vec4(1.0);
	}	
}
