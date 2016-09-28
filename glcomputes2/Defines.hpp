#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <vector>
#include <QString>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES/gl.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace zero
{
	using String	= QString;
	using Strings	= std::vector<QString>;


    using GLInt		= GLint;
    using GLUInt	= GLuint;
    using GLInts	= GLint*;

	using GLChar	= GLchar;
    using GLString	= GLchar*;
    using GLStrings = GLchar**;

}

#endif // DEFINES_HPP
