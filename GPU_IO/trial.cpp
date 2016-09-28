#include<iostream>
#include <QtCore>
#include <QFile>

#include<math.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GLES2/gl2.h>
#include"Shader.hpp"
#include<stdio.h>
#include"colsum.h"


int main(int argc,char **argv){
    int size=4;
   float *data = (float*)malloc(4*size*size*sizeof(float));

   for(int i=0;i<4*size*size;i++)
       data[i]=(float)i+1.0f;

    colSum p1(data,argc,argv,size,8,8);
    p1.performComputation();
    p1.Read();

  return 0;
}
