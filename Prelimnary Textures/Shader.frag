#version 120
uniform sampler2D textureIn;
void main(){
  vec4 inside = texture2D(textureIn,gl_TexCoord[0].st);
  gl_FragData[0] = inside+vec4(1.0,1.0,1.0,1.0);
}
