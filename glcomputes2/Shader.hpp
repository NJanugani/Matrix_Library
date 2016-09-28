#ifndef SHADER_HPP
#define SHADER_HPP


#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Defines.hpp"
#include <glm/fwd.hpp>

namespace zero
{

	class Shader
	{


	public:
		// Our program ID
		GLUInt			hProgram;

	private:
		Strings			vtxSourceLocii;
		Strings			frgSourceLocii;

		GLStrings		vtxCode;
		GLStrings		frgCode;

		GLInts			nVertexStrings;
		GLInts			nFragmentStrings;


		const size_t	vtxSize;
		const size_t	frgSize;


		GLInt			vtxShader;
		GLInt			frgShader;


	public:
		// Constructor reads and builds our shader
		Shader(const String& vertexSources, const String& fragmentSources);
		Shader(const Strings& vertexSources, const String& fragmentSources);
		Shader(const Strings& vertexSources, const Strings& fragmentSources);

		~Shader();


		// Use our program
		void Use();


		void SetUniform(const String& name, glm::vec3 value);
		void SetUniform(const String& name, glm::vec4 value);
		void SetUniform(const String& name, glm::mat4 value);
		void SetUniform(const String& name, float value);
		void SetUniform(const String& name, bool value);

	private:

		void init();

		void loadVertex();
		void loadFragment();

		static
		void
		load(const String& sourcePath,  GLString& output, GLInt& count );

		void compile();

		void link();

		void initPointers();

	};
} //namespace zero

#endif // SHADER_HPP
