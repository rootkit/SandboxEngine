SHADER version 1
@OpenGL2.Vertex
#version 400

uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;
uniform float resolution;
uniform vec2 position[4];
uniform vec2 texcoords[4];

in vec3 vertex_position;
in vec2 vertex_texcoords0;

out vec2 ex_texcoords0;
out vec4 vertexposition;

void main(void)
{
	vertexposition = (drawmatrix * vec4(position[gl_VertexID], 0.0, 1.0));
	gl_Position = projectionmatrix * vertexposition;
	ex_texcoords0 = texcoords[gl_VertexID];
}
@OpenGLES2.Vertex

@OpenGLES2.Fragment

@OpenGL4.Vertex
#version 400

uniform mat4 projectionmatrix;
uniform mat4 drawmatrix;
uniform vec2 offset;
uniform float resolution;
uniform vec2 position[4];
uniform vec2 texcoords[4];

in vec3 vertex_position;
in vec2 vertex_texcoords0;

out vec2 ex_texcoords0;
out vec4 vertexposition;

void main(void)
{
	vertexposition = (drawmatrix * vec4(position[gl_VertexID], 0.0, 1.0));
	gl_Position = projectionmatrix * vertexposition;
	ex_texcoords0 = texcoords[gl_VertexID];
}
@OpenGL4.Fragment
#version 400

uniform vec4 drawcolor;
uniform vec2 toolradius;
uniform float strength;
uniform sampler2D texture0;
uniform sampler2D texture1;//brush shape
uniform vec2 toolposition;

in vec2 ex_texcoords0;
in vec4 vertexposition;

out vec4 fragData0;

void main(void)
{
	float current = texture(texture0,ex_texcoords0).a;
	float d = length(vertexposition.xy-toolposition);
	if (toolradius[1]-toolradius[0]>0.0)
	{
		d = 1.0 - (d - toolradius[0]) /(toolradius[1]-toolradius[0]);
	}
	else
	{
		d = 1.0 - (d - toolradius[0]);
	}
	d = clamp(d,0.0,1.0);
	
	d *= 0.05 * strength;
	d = clamp(current+d,0.0,1.0);
	fragData0 = vec4(d);
}
