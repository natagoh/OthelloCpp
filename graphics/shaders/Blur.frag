
uniform sampler2D texture; // Texture which will be modified
uniform int blurSize; // Size of the blur

void main() {
    vec4 color = vec4( 0 );
    vec4 tmpColor;
    float sumColors = 0;
    float sumAlphas = 0;
    float textureSize = 640 * 0.6;

   vec2 textureCoordinates = gl_TexCoord[0].xy;


    for( int i = -blurSize; i <= blurSize; ++i ){
     for( int j = -blurSize; j <= blurSize; ++j ){
        tmpColor = texture2D( texture, textureCoordinates + vec2(i * blurSize, j * blurSize));

        color.rgb += tmpColor.rgb * tmpColor.a;
        color.a += tmpColor.a;

        sumColors += tmpColor.a;
        sumAlphas += 1;
    }
    }
    color.rgb /= sumColors;
    color.a /= sumAlphas;
     gl_FragColor = vec4( color.r, color.g, color.b, color.a );
}