#version 330 core

in vec2 TexCoord;

uniform sampler2D myTexture;

uniform vec3 color;
uniform float alpha;
uniform bool useTexture;

void main()
{
	if (useTexture)
	{
		vec4 tex = texture(myTexture, TexCoord);

		if (tex.a < 0.1f)
			discard;

		tex.a *= alpha;
		gl_FragColor = tex;
	}
	else
		gl_FragColor = vec4(color, alpha);
}