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

uniform sampler2D texture1; //Color
uniform sampler2D texture2; //SSAO
uniform bool isbackbuffer;
uniform vec2 buffersize;

out vec4 fragData0;

void main(void)
{
	vec2 texcoord = gl_FragCoord.xy/buffersize + 0.5/(buffersize*0.5);
	if (isbackbuffer) texcoord.y = 1.0 - texcoord.y;
	vec2 pixelsize = 1.0/buffersize;
	
	vec4 outputcolor = texture(texture1, texcoord);
	
	float ao=0.0;
	for(int dx = -2 ; dx < 2 ; dx ++ ) {
		for(int dy = -2 ; dy < 2 ; dy ++ ) {
			ao +=  texture(texture2,texcoord+vec2(pixelsize.x*float(dx),pixelsize.y*float(dy))).a;
		}
	}
	ao /= 16.0;
	
	outputcolor*=ao;	
    fragData0=outputcolor;
}
