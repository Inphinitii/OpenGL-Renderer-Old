#version 330

in	vec4 inputColor;
out vec4 outputColor;

void main()
{
	outputColor = inputColor;
	//gl_FragColor[0] = gl_FragCoord.x/640.0;
	//gl_FragColor[1] = gl_FragCoord.y/480.0;
	//gl_FragColor[2] = 1.0;
}