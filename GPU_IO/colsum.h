#ifndef COLSUM_H
#define COLSUM_H
#include"Shader.hpp"

class colSum
{

private:

    struct parameterTextureStruct{
      char *name;
      GLenum texTarget;
      GLenum texInternalFormat;
      GLenum texFormat;
    }textureParameters;

    Shader *ourShader;
    GLchar *textureNames[4];
    GLuint glutWindow;

    float  *data[4];
    int    *textureSetterData;
    GLuint NumberOfTextures;
    GLuint TextureInputParamenters[4];
    GLuint framebuffer;
    //Textures
    GLuint TextureSet1[4];
    GLuint TextureSet2[4];
    GLuint textureSetter;


    void initGLSL(void);
    void initFBO(void);
    void initGLEW(void);
    void initGLUT(int argc,char **argv);
    void initShaders();
    int InitialTextureSize;
    int textureSetterSize;


    void createTextures();
    void createTextureSetter(int rows,int cols);
    void SetupTexture(GLuint textureID);
    void TransferToTexture(float *data,GLuint textureID);
    void StructureData(float *data,int rows,int cols,int size);
    void CheckErrors(const char *label);


public:
    colSum(float *datum,int argc,char **argv,int size,int rows,int cols);
    void performComputation();
    void alterForNextPass();
    void Read();
};

#endif // COLSUM_H
