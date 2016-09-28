#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <iostream>

using UInt		= GLuint;
using Literal	= const char*;

class Exemplar
{
public:
	Exemplar();
	bool
	initBuffer(UInt& hBuffer);
	bool
	initShaders(UInt& hFragShader, UInt& hVertShader, UInt& hProgram);
	bool
	validate(Literal source);

};
