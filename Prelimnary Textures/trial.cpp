#include<iostream>
#include<math.h>
#include<GL/glew.h>
#include<GLUT/glut.h>
#include<GLES2/gl2.h>
#include"Shader.hpp"
#include<stdio.h>
void FramebufferStatus(void);
void CheckErrors(const char *label);
void createTextures(void);
void initGLSL(Shader ourShader);
void initFBO(void);
void initGLEW(void);
void initGLUT(int argc,char **argv);
void performComputation(Shader ourShader);
void printProgramLog(GLuint obj);
void printShaderLog(GLuint obj);
void setupTexture(const GLuint texID);
void transferFromTexture(float *data);
void transferToTexture(float *data);

//Textures
GLuint input,output;
//Attachment Points
GLenum attachmentpoints[]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1};
//FramebufferStatus
GLuint framebuffer;
//window
GLuint glutWindow;

//Texture Parameters
struct parameterTextureStruct{
  char *name;
  GLenum texTarget;
  GLenum texInternalFormat;
  GLenum texFormat;
}textureParameters;
//Extra Parameters
GLuint inParam,outParam;
//Data
int size; //actual size will be 4*size*size
float *DataIn;
float *DataOut;

//Main
int main(int argc,char **argv){
  size=2;
  //Setting texture Parameters
  textureParameters.name = "Texture2D, RGBA,FLOAT";
  textureParameters.texTarget=GL_TEXTURE_2D;
  textureParameters.texInternalFormat= GL_RGBA;
  textureParameters.texFormat=GL_RGBA;
  //Initializing Data
  DataIn=(float*)malloc(size*size*4*sizeof(float));
  DataOut=(float*)malloc(size*size*4*sizeof(float));
  for(int i=0;i<4*size*size;i++)
    DataIn[i]=i+1.0;
  initGLUT(argc,argv);
  CheckErrors("GLUT()");

  initGLEW();
  CheckErrors("GLEW()");
  initFBO();
  createTextures();
  Shader ourShader("Shader.vert","Shader.frag");

  initGLSL(ourShader);

  performComputation(ourShader);
  transferFromTexture(DataOut);
  for(int i=0;i<4*size*size;i++)
    printf("%f ",DataOut[i]);
  return 0;
}

void transferFromTexture(float *data){
  glReadBuffer(attachmentpoints[0]);
  glReadPixels(0,0,size,size,GL_RGBA,GL_FLOAT,data);
}

void setupTexture(const GLuint texID){
  glBindTexture(textureParameters.texTarget,texID);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // define texture with floating point format
  glTexImage2D(textureParameters.texTarget,0,textureParameters.texInternalFormat,size,size,0,textureParameters.texFormat,GL_FLOAT,0);
}

void transferToTexture(float *data,GLuint texID){
  glBindTexture(textureParameters.texTarget, texID);

  glTexSubImage2D(textureParameters.texTarget,0,0,0,size,size,textureParameters.texFormat,GL_FLOAT,data);
}

void initGLUT(int argc,char **argv){
  glutInit(&argc,argv);
  glutWindow=glutCreateWindow("WORK PLEASE!");
}

void initGLEW(void){
  int err=glewInit();
  if(GLEW_OK !=err){
    printf((char*)glewGetErrorString(err));
    exit(0);
  }
}

void initFBO(void){
  glGenFramebuffers(1,&framebuffer);
  CheckErrors("generate()");

  glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
  CheckErrors("bind");



  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0.0,0.0,size,size);

  CheckErrors("initFBO()");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0.0,size,0.0,size);
  CheckErrors("projection()");

}

void CheckErrors (const char *label) {
    GLenum errCode;
    const GLubyte *errStr;

    if ((errCode = glGetError()) != GL_NO_ERROR) {
	errStr = gluErrorString(errCode);
	printf("OpenGL ERROR: ");
	printf((char*)errStr);
	printf("(Label: ");
	printf(label);
	printf(")\n.");
    }
}

void createTextures(void){
  glGenTextures(1,&input);

  glGenTextures(1,&output);

  setupTexture(input);

  transferToTexture(DataIn,input);

  setupTexture(output);
  transferToTexture(DataIn,output);

  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  CheckErrors("createFBOandTextures()");

}

void initGLSL(Shader ourShader){
  inParam=glGetUniformLocation(ourShader.Program,"textureIn");
  outParam=glGetUniformLocation(ourShader.Program,"textureOut");
}

void performComputation(Shader ourShader){
  glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[0],textureParameters.texTarget,output,0);
  ourShader.Use();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(textureParameters.texTarget,input);
  glUniform1i(inParam,0);
  glFinish();

  glDrawBuffer(attachmentpoints[0]);
  glPolygonMode(GL_FRONT,GL_FILL);
  glBegin(GL_QUADS);
	    glTexCoord2f(0.0, 0.0);
	    glVertex2f(0.0, 0.0);
	    glTexCoord2f(1.0, 0.0);
	    glVertex2f(size, 0.0);
	    glTexCoord2f(1.0, 1.0);
	    glVertex2f(size, size);
	    glTexCoord2f(0.0, 1.0);
	    glVertex2f(0.0, size);
	    glEnd();
  CheckErrors("render()");
}
