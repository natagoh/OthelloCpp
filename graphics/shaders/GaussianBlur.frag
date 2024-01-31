uniform sampler2D 	texture;
uniform vec2 		blurOffset;

void main()
{
	// lookup the pixel in the texture
	vec2 textureCoordinates = gl_TexCoord[0].xy;
	vec4 color = vec4(0.0);
	color += texture2D(texture, textureCoordinates - 4.0 * blurOffset) * 0.0162162162;
	color += texture2D(texture, textureCoordinates - 3.0 * blurOffset) * 0.0540540541;
	color += texture2D(texture, textureCoordinates - 2.0 * blurOffset) * 0.1216216216;
	color += texture2D(texture, textureCoordinates - blurOffset) * 0.1945945946;
	color += texture2D(texture, textureCoordinates) * 0.2270270270;
	color += texture2D(texture, textureCoordinates + blurOffset) * 0.1945945946;
	color += texture2D(texture, textureCoordinates + 2.0 * blurOffset) * 0.1216216216;
	color += texture2D(texture, textureCoordinates + 3.0 * blurOffset) * 0.0540540541;
	color += texture2D(texture, textureCoordinates + 4.0 * blurOffset) * 0.0162162162;

	gl_FragColor = color;

	 gl_FragColor = vec4(0, 0, 0.0, 1.0);
}