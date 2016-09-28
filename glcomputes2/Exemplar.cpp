#include "Exemplar.hpp"
#include <vector>

#include <cstdio>
#include <iostream>


#define VERTEX_ARRAY	0

bool
Exemplar
::initBuffer(UInt& hBuffer)
{
	GLfloat vertexData[] =
	{
	   -0.4f, -0.4f, 0.0f,	// Bottom Left
		0.4f, -0.4f, 0.0f,	// Bottom Right
		0.0f, 0.4f, 0.0f	// Top Middle
	};

   // Generate a buffer object
   glGenBuffers(1, &hBuffer);

   // Bind buffer as an vertex buffer so we can fill it with data
   glBindBuffer(GL_ARRAY_BUFFER, hBuffer);

   //	Set the buffer's size, data and usage
   //	Note the last argument - GL_STATIC_DRAW. This tells the driver that we intend to read from the buffer on the GPU, and don't intend
   //	to modify the data until we're done with it.
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
   if (!validate("glBufferData"))
   {return false;}
   return true;
}

bool
Exemplar
::initShaders(UInt& hFragShader, UInt& hVertShader, UInt& hProgram)
{
	Literal const
	fragShaderSource =
	"\
	 void main (void)\
	 {\
	  gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
	 }\
	";

	// Create a fragment shader object
	hFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(hFragShader, 1, (Literal*)&fragShaderSource, NULL);

	// Compile the source code
	glCompileShader(hFragShader);

	// Check that the shader compiled
	GLint isShaderCompiled;
	glGetShaderiv(hFragShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(hFragShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		std::vector<char> infoLog;
		infoLog.resize(infoLogLength);
		glGetShaderInfoLog(hFragShader, infoLogLength, &charactersWritten, infoLog.data());

		// Display the error in a dialog box
		infoLogLength > 1 ? printf("%s", infoLog.data()) : printf("Failed to compile fragment shader.");

		return false;
	}


	Literal const vertexShaderSource =
	"\
	   attribute highp vec4	myVertex;\
	   uniform mediump mat4	transformationMatrix;\
	   void main(void)\
	   {\
		gl_Position = transformationMatrix * myVertex;\
	   }\
	";

	// Create a vertex shader object
	hVertShader = glCreateShader(GL_VERTEX_SHADER);

	// Load the source code into the shader
	glShaderSource(hVertShader, 1, (const char**)&vertexShaderSource, NULL);

	// Compile the shader
	glCompileShader(hVertShader);

	// Check the shader has compiled
	glGetShaderiv(hVertShader, GL_COMPILE_STATUS, &isShaderCompiled);
	if (!isShaderCompiled)
	{
		// If an error happened, first retrieve the length of the log message
		int infoLogLength, charactersWritten;
		glGetShaderiv(hVertShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Allocate enough space for the message and retrieve it
		std::vector<char> infoLog; infoLog.resize(infoLogLength);
		glGetShaderInfoLog(hVertShader, infoLogLength, &charactersWritten, infoLog.data());

		// Display the error in a dialog box
		infoLogLength > 1 ? printf("%s", infoLog.data()) : printf("Failed to compile vertex shader.");

		return false;
	}

		// Create the shader program
		hProgram = glCreateProgram();

		// Attach the fragment and vertex shaders to it
		glAttachShader(hProgram, hFragShader);
		glAttachShader(hProgram, hVertShader);

		// Bind the vertex attribute "myVertex" to location VERTEX_ARRAY (0)
		glBindAttribLocation(hProgram, VERTEX_ARRAY, "myVertex");

		// Link the program
		glLinkProgram(hProgram);

		// Check if linking succeeded in the same way we checked for compilation success
		GLint isLinked;
		glGetProgramiv(hProgram, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
		{
			// If an error happened, first retrieve the length of the log message
			int infoLogLength, charactersWritten;
			glGetProgramiv(hProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

			// Allocate enough space for the message and retrieve it
			std::vector<char> infoLog; infoLog.resize(infoLogLength);
			glGetProgramInfoLog(hProgram, infoLogLength, &charactersWritten, infoLog.data());

			// Display the error in a dialog box
			infoLogLength > 1 ? printf("%s", infoLog.data()) : printf("Failed to link shader program.");

			return false;
		}

		//	Use the Program
		//	Calling glUseProgram tells OpenGL ES that the application intends to use this program for rendering. Now that it's installed into
		//	the current state, any further glDraw* calls will use the shaders contained within it to process scene data. Only one program can
		//	be active at once, so in a multi-program application this function would be called in the render loop. Since this application only
		//	uses one program it can be installed in the current state and left there.
		glUseProgram(hProgram);

		if (!validate("glUseProgram")){	return false; }
		return true;
}

bool
Exemplar
::validate(Literal source)
{
	GLenum lastError = glGetError();
	if (lastError != GL_NO_ERROR)
	{
		printf("%s failed (%x).\n", source, lastError);
		return false;
	}
	return true;
}


