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
// flare shader conversion by Shadmar
// Shadetoy : ...
//--------------------------------------

#version 400

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2DMS texture3;
uniform vec2 buffersize;
uniform float currenttime;
uniform bool isbackbuffer;
uniform vec2 camerarange;
uniform vec2 screenLightPos=vec2(0.5,0.5);
uniform mat4 cameramatrix;

out vec4 fragData0;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float noise(float t)
{
	return rand(vec2(t,t));//gl_FragCoord.x;//texture(texture2,vec2(t, 0.0) / buffersize.xy*.5).x;
}
float noise(vec2 t)
{
	return rand(t);//gl_FragCoord.y;//texture(texture2,(t + vec2(currenttime)) / buffersize.xy*.5).x;
}

vec3 lensflare(vec2 uv,vec2 pos)
{
	vec2 main = uv-pos;
	vec2 uvd = uv*(length(uv));
	
	float ang = atan(main.y, main.x);
	float dist=length(main); dist = pow(dist,.1);
	float n = noise(vec2((ang-currenttime/9999.0)*16.0,dist*32.0));
	
	float f0 = 1.0/(length(uv-pos)*32.0+1.0);
	
	f0 = 0;//f0+f0*(sin((ang+currenttime/18000.0 + noise(abs(ang)+n/2.0)*2.0)*1.0)*.05+dist*.1+.8);

	float f2 = max(1.0/(1.0+32.0*pow(length(uvd+0.8*pos),2.0)),.0)*00.25;
	float f22 = max(1.0/(1.0+32.0*pow(length(uvd+0.85*pos),2.0)),.0)*00.23;
	float f23 = max(1.0/(1.0+32.0*pow(length(uvd+0.9*pos),2.0)),.0)*00.21;
	
	vec2 uvx = mix(uv,uvd,-0.5);
	
	float f4 = max(0.01-pow(length(uvx+0.4*pos),2.4),.0)*6.0;
	float f42 = max(0.01-pow(length(uvx+0.45*pos),2.4),.0)*5.0;
	float f43 = max(0.01-pow(length(uvx+0.5*pos),2.4),.0)*3.0;
	
	uvx = mix(uv,uvd,-.4);
	
	float f5 = max(0.01-pow(length(uvx+0.2*pos),5.5),.0)*2.0;
	float f52 = max(0.01-pow(length(uvx+0.4*pos),5.5),.0)*2.0;
	float f53 = max(0.01-pow(length(uvx+0.6*pos),5.5),.0)*2.0;
	
	uvx = mix(uv,uvd,-0.5);
	
	float f6 = max(0.01-pow(length(uvx-0.3*pos),1.6),.0)*6.0;
	float f62 = max(0.01-pow(length(uvx-0.325*pos),1.6),.0)*3.0;
	float f63 = max(0.01-pow(length(uvx-0.35*pos),1.6),.0)*5.0;
	
	vec3 c = vec3(.0);
	
	c.r+=f2+f4+f5+f6; c.g+=f22+f42+f52+f62; c.b+=f23+f43+f53+f63;
	c+=vec3(f0);
	
	return c;
}

vec3 cc(vec3 color, float factor,float factor2) // color modifier
{
	float w = color.x+color.y+color.z;
	return mix(color,vec3(w)*factor,w*factor2);
}

float DepthToZPosition(in float depth) {
	return camerarange.x / (camerarange.y - depth * (camerarange.y - camerarange.x)) * camerarange.y;
}

void main()
{
	vec2 icoord = vec2(gl_FragCoord.xy/buffersize);
	if (isbackbuffer) icoord.y = 1.0 - icoord.y;

	vec4 color=texture(texture1, icoord); 
	
	//flare
	vec2 uv = gl_FragCoord.xy / buffersize.xy - 0.5;
	if (isbackbuffer) uv.y = - uv.y;
	uv.x *= buffersize.x/buffersize.y; //fix aspect ratio
	vec2 pos=screenLightPos-0.5;
	pos.x *= buffersize.x/buffersize.y;
	vec3 fcolor = vec3(1.4,1.2,1.0)*lensflare(uv,pos.xy);
	fcolor = cc(fcolor,.5,.1);

	//occluder
	float posZ = DepthToZPosition(texelFetch(texture3, ivec2((screenLightPos*buffersize)),0).r);

	fragData0=vec4(color.rgb,1);

	if (posZ>camerarange.y*.25) fragData0.rgb+=fcolor;
	if (cameramatrix[3][1] <= -0.99) fragData0=texture(texture1, icoord);
}
