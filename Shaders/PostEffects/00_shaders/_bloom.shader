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
#version 400

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool isbackbuffer;
uniform vec2 buffersize;
uniform float currenttime;
uniform mat4 cameramatrix;

out vec4 fragData0;
in vec4 fragData2;

void main(void)
{

vec2 icoord = vec2(gl_FragCoord.xy/buffersize);
if (isbackbuffer) icoord.y = 1.0 - icoord.y;
	
	vec4 scene = texture2D(texture1, icoord); // rendered scene
	vec4 blur = texture2D(texture2, icoord); // glowmap
	fragData0 = clamp(scene + (blur), 0.0, 1.0);
	
	//if (cameramatrix[3][1] <= -0.99) fragData0=texture(texture1, icoord);
}
