#include "Shader.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <QtCore>
#include <QFile>

inline
void
initShaders()
{
	Q_INIT_RESOURCE(assets);
}

namespace zero
{
	String
	normalize(const String& locus)
	{
		QString retVal = locus;
		if (!locus.startsWith(":/shaders"))
			retVal.prepend(":/shaders");
		if(!locus.endsWith(".glsl"))
			retVal.append(".glsl");

		return retVal;
	}

	Strings
	normalize(const Strings& locii)
	{
		Strings retVal;
		for(auto& locus : locii)
			retVal.push_back(normalize(locus));
		return retVal;
	}

	Shader
	::Shader(const String& vertexSource, const String& fragmentSource)
	: vtxSize(1), frgSize(1)
	{
		vtxSourceLocii.push_back(normalize(vertexSource));
		frgSourceLocii.push_back(normalize(fragmentSource));

		init();
	}

	Shader
	::Shader(const Strings& vertexSources, const String& fragmentSources)
	:
	  vtxSourceLocii(normalize(vertexSources)),
	  vtxSize(vertexSources.size()),
	  frgSize(1)
	{
		frgSourceLocii.push_back(normalize(fragmentSources));
		init();
	}

	Shader
	::Shader(const Strings& vertexSources, const Strings& fragmentSources)
	:
	  vtxSourceLocii(normalize(vertexSources)),
	  frgSourceLocii(normalize(fragmentSources)) ,
	  vtxSize(vertexSources.size()),
	  frgSize(fragmentSources.size())
	{
		init();
	}

	Shader
	::~Shader()
	{
		for (size_t i = 0; i < vtxSize; i++)
			delete[] vtxCode[i];

		delete[] vtxCode;
		delete nVertexStrings;

		delete[] frgCode;
		delete nFragmentStrings;

	}

	void
	Shader
	::Use()
	{
		glUseProgram(this->hProgram);
	}

	void
	Shader
	::SetUniform(const String& name, glm::vec4 value)

	{
		GLInt uniform =  glGetUniformLocation(hProgram, name.toStdString().c_str());
		glUniform4fv(uniform, 1, glm::value_ptr(value));
	}

	void
	Shader
	::SetUniform(const String& name, glm::mat4 value)
	{
		GLInt uniform =  glGetUniformLocation(hProgram, name.toStdString().c_str());
		glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	void
	Shader
	::SetUniform(const String& name, float value)
	{
		GLInt uniform =  glGetUniformLocation(hProgram, name.toStdString().c_str());
		glUniform1f(uniform, value);
	}

	void
	Shader
	::init()
	{
		initShaders();
		initPointers();
		loadVertex();
		loadFragment();
		compile();
		link();
	}

	void
	Shader
	::loadVertex()
	{
		for (size_t i = 0; i < vtxSize; i++)
			load(vtxSourceLocii[i],   vtxCode[i], nVertexStrings[i]);

	}

	void
	Shader
	::loadFragment()
	{
		for (size_t i = 0; i < frgSize; i++)
			load(frgSourceLocii[i], frgCode[i],nFragmentStrings[i]);


	}



	void
	Shader
	::compile()
	{

		GLInt success;
		GLInt logSize = 0;
		GLString infoLog;


		vtxShader = glCreateShader(GL_VERTEX_SHADER);
		frgShader = glCreateShader(GL_FRAGMENT_SHADER);


		glShaderSource(vtxShader, vtxSize, vtxCode , nVertexStrings);
		glCompileShader(vtxShader);

		glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &success);
		if(success != 1)
		{
			glGetShaderiv(vtxShader, GL_INFO_LOG_LENGTH, &logSize);
			infoLog = new GLChar[logSize];

			glGetShaderInfoLog(vtxShader, logSize, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<  std::endl;

			delete infoLog;
		}



		glShaderSource(frgShader, frgSize, frgCode, nFragmentStrings);
		glCompileShader(frgShader);
		glGetShaderiv(frgShader, GL_INFO_LOG_LENGTH, &success);
		if(success != 1)
		{
			glGetShaderiv(frgShader, GL_INFO_LOG_LENGTH, &logSize);

			infoLog = new GLchar[logSize];

			glGetShaderInfoLog(frgShader, logSize, nullptr, infoLog);

            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog <<  std::endl;

			delete infoLog;
		}



		this->hProgram = glCreateProgram();
		glAttachShader(this->hProgram, vtxShader);
		glAttachShader(this->hProgram, frgShader);
	}

	void
	Shader
	::link()
	{
		GLInt success;
		GLString infoLog;

		glLinkProgram(this->hProgram);

		glGetProgramiv(this->hProgram, GL_LINK_STATUS, &success);

		if(!success)
		{
			GLint logSize = 0;
			glGetProgramiv(this->hProgram, GL_INFO_LOG_LENGTH, &logSize);
			infoLog = new GLchar[logSize];
			glGetProgramInfoLog(this->hProgram, logSize, nullptr, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
			std::cout << "File names: \n";
			for (auto vertex : vtxSourceLocii)
				std::cout << vertex.toStdString() << std::endl;


			for (auto fragment : frgSourceLocii)
				std::cout << fragment.toStdString() << std::endl;


			std::cout  << infoLog <<  std::endl;
			delete infoLog;

		}

		glDeleteShader(vtxShader);
		glDeleteShader(frgShader);
	}

	void
	Shader
	::initPointers()
	{
		vtxCode				= new GLString[vtxSize];
		nVertexStrings		= new GLInt[vtxSize];

		frgCode				= new GLString[frgSize];
		nFragmentStrings	= new GLInt[frgSize];

	}

	void
	Shader
	::load(const String& sourcePath, GLString& output, GLInt& count)
	{

		String returnCode;
		try
		{
			// Open files
			QFile vShaderFile(sourcePath);
			if (!vShaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
					throw std::runtime_error("Could not open Shader.");

			QTextStream vShaderStream(&vShaderFile);
			returnCode = vShaderStream.readAll();
			// close file handlers
			vShaderFile.close();
		}

        catch(std::exception e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << sourcePath.toStdString() << std::endl;
		}

		count	= returnCode.length() ;
		output	= new GLChar[count + 1];
		auto
		length	= returnCode.toStdString().copy(output,count,0);
		output[length]= '\0';
	}

	void
	Shader
	::SetUniform(const String& name, glm::vec3 value)
	{
		GLInt uniform =  glGetUniformLocation(hProgram, name.toStdString().c_str());
		glUniform3fv(uniform, 1, glm::value_ptr(value));
	}


	void
	Shader
	::SetUniform(const String& name, bool value)
	{
		GLInt uniform =  glGetUniformLocation(hProgram, name.toStdString().c_str());
		glUniform1i(uniform, value);
	}

} //namespace zero
