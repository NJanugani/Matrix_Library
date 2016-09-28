#include "colsum.h"

GLuint texNum,vertices,texCoord,vao;
colSum::colSum(float *datum,int argc,char **argv,int size,int rows,int cols)
{

    initShaders();

    textureParameters.name = "Texture2D, RGBA32F,FLOAT";
    textureParameters.texTarget=GL_TEXTURE_2D;
    textureParameters.texInternalFormat= GL_RGBA32F_ARB;
    textureParameters.texFormat=GL_RGBA;

    textureNames[0]="Texture1";
    textureNames[1]="Texture2";
    textureNames[2]="Texture3";
    textureNames[3]="Texture4";
    NumberOfTextures=4;
    printf("Swag\n");
    StructureData(datum,rows,cols,size);

    initGLUT(argc,argv);

    initGLEW();

    initFBO();
    //createTextureSetter(rows,cols);
    createTextures();

    std::string shaderPathf = QDir::currentPath().toStdString() + "/../GPU_IO/shaders/Shader.frag";
    std::string shaderPathv = QDir::currentPath().toStdString() + "/../GPU_IO/shaders/Shader.vert";

    const GLchar* fragPath = shaderPathf.c_str();
    const GLchar* vertPath=shaderPathv.c_str();

    ourShader=new Shader(vertPath,fragPath);

    int temp = (cols*rows)/4; // if smaller than cols then stop
    float outputPos[temp];
    for(int i=0;i<temp;i++){
        outputPos[i]=1+(i%(rows/4));
        std::cout << outputPos[i] << std::endl;
    }

    float vertexAttr[24] = {
                       0.0,               0.0, 0.0, 1.0,                            0.0,0.0,
        InitialTextureSize,               0.0, 0.0, 1.0,                            1.0,0.0,
        InitialTextureSize,InitialTextureSize, 0.0, 1.0,                            1.0,1.0,
                       0.0,InitialTextureSize, 0.0, 1.0,                            0.0,1.0,
    };

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
/*
    glGenBuffers(1,&texNum);
    glBindBuffer(GL_ARRAY_BUFFER,texNum);
    glBufferData(GL_ARRAY_BUFFER,temp*sizeof(float),outputPos,GL_STATIC_DRAW);
    glVertexAttribPointer(0,1,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT),(GLvoid*) 0);
    glEnableVertexAttribArray(0);
*/
    glGenBuffers(1,&vertices);
    glBindBuffer(GL_ARRAY_BUFFER,vertices);
    glBufferData(GL_ARRAY_BUFFER,16*sizeof(float),vertexAttr,GL_STATIC_DRAW);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*) 0);
    glEnableVertexAttribArray(1);

/*
    glGenBuffers(1,&texCoord);
    glBindBuffer(GL_ARRAY_BUFFER,texCoord);
    glBufferData(GL_ARRAY_BUFFER,24*sizeof(float),outputPos,GL_STATIC_DRAW);
    glVertexAttribPointer(0,1,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*) (4*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);
*/
    glBindVertexArray(0);



    initGLSL();

}
void colSum::StructureData(float *datum,int rows,int cols,int size){
    InitialTextureSize=size/2;
    for(int i=0;i<4;i++)
        data[i] = (float*)malloc(size*size*sizeof(float));

    int counters[4];
    memset(counters,0,4*sizeof(int));
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            data[i%4][counters[i%4]++]= datum[i*rows + j];
        }
    }


    for(int i=0;i<4;i++){
        for(int j=0;j<size*size;j++)
                printf("%f ",data[i][j]);
        printf("\n\n");
    }
}

void colSum::CheckErrors (const char *label) {
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
void colSum::createTextures(){
    glGenTextures(4,TextureSet1);
    glGenTextures(4,TextureSet2);

    for(int i=0;i<4;i++){
        SetupTexture(TextureSet1[i]);
        SetupTexture(TextureSet2[i]);
        TransferToTexture(data[i],TextureSet1[i]);
        TransferToTexture(data[i],TextureSet2[i]);
    }
}

void colSum::createTextureSetter(int rows,int cols){



    glGenTextures(1,&textureSetter);
    glBindTexture(textureParameters.texTarget,textureSetter);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // define texture with integer format
    glTexImage2D(textureParameters.texTarget,0,textureParameters.texInternalFormat,InitialTextureSize,InitialTextureSize,0,textureParameters.texFormat,GL_INT,0);
    glBindTexture(textureParameters.texTarget, textureSetter);
    //glTexSubImage2D(textureParameters.texTarget,0,0,0,InitialTextureSize,InitialTextureSize,textureParameters.texFormat,GL_INT,textureSetterData);

}



void colSum::initShaders()
{
    Q_INIT_RESOURCE(assets);
}


void colSum::SetupTexture(const GLuint texID){
  glBindTexture(textureParameters.texTarget,texID);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // define texture with floating point format
  glTexImage2D(textureParameters.texTarget,0,textureParameters.texInternalFormat,InitialTextureSize,InitialTextureSize,0,textureParameters.texFormat,GL_FLOAT,0);
}

void colSum::initGLSL(){
    for(int i=0;i<NumberOfTextures;i++)
            TextureInputParamenters[i]=glGetUniformLocation(ourShader->Program,textureNames[i]);
}
void colSum::TransferToTexture(float*data,GLuint texID){
    glBindTexture(textureParameters.texTarget, texID);
    glTexSubImage2D(textureParameters.texTarget,0,0,0,InitialTextureSize,InitialTextureSize,textureParameters.texFormat,GL_FLOAT,data);
}

void colSum::initFBO(){
    glGenFramebuffers(1,&framebuffer);
    CheckErrors("generate()");
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    CheckErrors("bind");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0.0,0.0,InitialTextureSize,InitialTextureSize);
    CheckErrors("initFBO()");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,InitialTextureSize,0.0,InitialTextureSize);
    CheckErrors("projection()");
}

void colSum::initGLEW(){
    int err=glewInit();
    if(GLEW_OK !=err){
      printf((char*)glewGetErrorString(err));
      exit(0);
    }
}

void colSum::performComputation(){
    GLenum attachmentpoints[4]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT3,GL_COLOR_ATTACHMENT4};

  glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[0],textureParameters.texTarget,TextureSet2[0],0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[1],textureParameters.texTarget,TextureSet2[1],0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[2],textureParameters.texTarget,TextureSet2[2],0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[3],textureParameters.texTarget,TextureSet2[3],0);

  //glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentpoints[0],textureParameters.texTarget,output,0);

  ourShader->Use();

  glBindVertexArray(vao);

  for(int i=0;i<4;i++){
  glActiveTexture(GL_TEXTURE0+i);
  glBindTexture(textureParameters.texTarget,TextureSet1[i]);
  glUniform1i(TextureInputParamenters[i],i);
  }
  glFinish();

  glDrawBuffers(2,attachmentpoints);


  glPolygonMode(GL_FRONT,GL_FILL);


  //glBegin(GL_QUADS);
/*
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(InitialTextureSize, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(InitialTextureSize, InitialTextureSize);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, InitialTextureSize);
*/
  glDrawArrays(GL_QUADS,0,4);
     //   glEnd();
  CheckErrors("render()");
}
void colSum::initGLUT(int argc, char **argv){
    glutInit(&argc,argv);
    glutWindow=glutCreateWindow("WORK PLEASE!");
}
void colSum::Read(){
    float *data;
    data=(float*)malloc(4*InitialTextureSize*InitialTextureSize*sizeof(float));
  for(int i=0;i<4*InitialTextureSize*InitialTextureSize;i++)
        data[i]=0;

glReadBuffer(GL_COLOR_ATTACHMENT0);

glReadPixels(0,0,InitialTextureSize,InitialTextureSize,textureParameters.texFormat,GL_FLOAT,data);
for(int i=0;i<4*InitialTextureSize*InitialTextureSize;i++)
    printf("%f\n",data[i]);
}

void colSum::alterForNextPass(){

}
