SHADER version 1
@OpenGL2.Vertex
/*
---------------------------------------------------------------------------
-- Film Grain (Scanline) by Igor Katrich 26/02/20015
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
-- Film Grain (Scanline) by Igor Katrich 26/02/20015
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
-- Film Grain (Scanline) by Igor Katrich 26/02/20015
-- Email: igorbgz@outlook.com
//---------------------------------------------------------------------------*/
#version 400

uniform sampler2D texture1;
uniform bool isbackbuffer;
uniform vec2 buffersize;
uniform float currenttime;

//User variables
//Noise
#define nsamount 10.0
#define nssize 3.0

//Scanline
#define slenabled 1
#define slindent 5.0
#define slsize 70.0
#define slopacity 0.03

out vec4 fragData0;

vec2 pixelation(vec2 coord, vec2 size)
{
	vec3 tc = vec3(1.0, 0.0, 0.0);
	float dx = size.x*(1./buffersize);
	float dy = size.y*(1./buffersize);
	return vec2(dx*floor(coord.x/dx), dy*floor(coord.y/dy));
}

highp float rand(vec2 co)
{
    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b)+currenttime);
    highp float sn= mod(dt,12.1);
    return fract(sin(sn) * c);
}  

void main(void)
{
	vec2 tcoord = vec2(gl_FragCoord.xy/buffersize);
	if (isbackbuffer) tcoord.y = 1.0 - tcoord.y;
	
	vec4 color = texture(texture1, tcoord);
	
	//Noise
	float noise = rand(pixelation(tcoord,vec2(nssize)));
	color+=(noise/nsamount);
	
	//Wave
	float wave = tcoord.y;
	wave+=cos(currenttime*0.003+wave/0.1)*0.01; 
	wave = clamp(wave,0.0,1.0);

#if slenabled==1
	//Type 1 (RGB)
    float global_pos = ((wave-currenttime*.0001) + buffersize.y) * 70.0;
    float wave_pos = cos((fract( global_pos ) - 0.5)*3.14);
	color *= mix(vec4(1.0,0.8,0.9,1.0), vec4(1.0), wave_pos);
	
	//Type 2 (Grayscale)
    if (mod(floor((wave-currenttime*.0002) * buffersize.y / slsize), slindent) == 0.0)
        //fragData0 = color - vec4(slopacity); //Black
		fragData0 = color + vec4(slopacity); //White 
    else
		fragData0 = color;
#else
	fragData0 = color;
#endif

}
