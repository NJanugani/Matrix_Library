#version 110
//attribute vec2 texCoord;
attribute vec4 vertices;
//attribute float texNum;

varying vec4 numtex;

void main(void){
    numtex = vertices;
    gl_Position = vertices;
}
