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

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool isbackbuffer;
uniform vec2 buffersize;
uniform float currenttime;

out vec4 fragData0;

float Gaussian (float x, float deviation)
{
    return (1.0 / sqrt(2.0 * 3.141592 * deviation)) * exp(-((x * x) / (2.0 * deviation)));  
}

void main(void)
{

vec2 icoord = vec2(gl_FragCoord.xy/buffersize);
if (isbackbuffer) icoord.y = 1.0 - icoord.y;

	vec2 orientation=vec2(1,0);
	float BlurStrength=0.2;
	float halfBlur = 12.0 * 0.5;
	vec4 colour = vec4(0.0);
	vec4 texColour = vec4(0.0);

   fragData0 = vec4(0);
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.028))*0.0044299121055113265;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.024))*0.00895781211794;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.020))*0.0215963866053;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.016))*0.0443683338718;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.012))*0.0776744219933;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.008))*0.115876621105;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, -0.004))*0.147308056121;
   fragData0 += texture2D(texture1, icoord)*0.159576912161;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.004))*0.147308056121;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.008))*0.115876621105;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.012))*0.0776744219933;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.016))*0.0443683338718;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.020))*0.0215963866053;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.024))*0.00895781211794;
   fragData0 += texture2D(texture1, icoord+ vec2(0.0, 0.028))*0.0044299121055113265;
}
