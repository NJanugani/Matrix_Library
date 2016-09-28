#version 110

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;

varying vec4 numtex;
void main(){
  vec4 inside1 = texture2D(Texture1,gl_TexCoord[0].st);
  vec4 inside2 = texture2D(Texture2,gl_TexCoord[1].st);
  vec4 inside3 = texture2D(Texture3,gl_TexCoord[2].st);
  vec4 inside4 = texture2D(Texture4,gl_TexCoord[3].st);

  //vec4 tex = vec4(numtex,0,1.1,1);

    gl_FragData[0]=inside2;//+inside2+inside3+inside4;

}
