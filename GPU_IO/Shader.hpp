
/*
 *
 *
 * SPAGHETTI CODE AHEAD, TREAD WITH CAUTION
 *
 *
 *
 */





#ifndef SHADER_H
#define SHADER_H
#include <QString>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include<iostream>
#include <QtCore>
#include <QFile>
#include<math.h>
#include<GL/glut.h>
#include<GLES2/gl2.h>
#include"Shader.hpp"
#include<stdio.h>
class Shader
{
public:
    GLuint Program;
    // Constructor generates the shader on the fly
    Shader(){

    };
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
    {


        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::badbit);
        try
        {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar * fShaderCode = fragmentCode.c_str();

        QString returnCode;
        try
        {
            // Open files
            QFile ShaderFile(fragmentPath);
            if (!ShaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
                    throw std::runtime_error("Could not open Shader.");

            QTextStream ShaderStream(&ShaderFile);
            returnCode = ShaderStream.readAll();
            // close file handlers
            ShaderFile.close();
        }

        catch(std::exception e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << fragmentPath << std::endl;
        }

        GLint count	= returnCode.length() ;
        GLchar* output	= new GLchar[count + 1];
        GLint length	= returnCode.toStdString().copy(output,count,0);
        output[length]= '\0';


        // 2. Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // Print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &output, NULL);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        // Print linking errors if any
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Bind the attribute passed to vertex shader
        glBindAttribLocation(this->Program,0,"texNum");
        glBindAttribLocation(this->Program,1,"vertices");
        glBindAttribLocation(this->Program,2,"texCoord");


        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        int vert;
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,& vert);

        std::cout << "nadksjnkjdnask " << vert << std::endl;

    }
    // Uses the current shader
    void Use()
    {
        glUseProgram(this->Program);
    }
};

#endif
