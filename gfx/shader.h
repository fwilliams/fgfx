#include <memory>
#include <string>
#include <sstream>

#include <boost/assert.hpp>

#include "utils/gl_program_builder.h"
#include "utils/gl_traits.h"

#ifndef RENDERER_SHADER_H_
#define RENDERER_SHADER_H_

#define __SHADER_SS_MSG(msg) \
((std::stringstream&)(std::stringstream("") << msg)).str().c_str()

namespace gfx {

class GraphicsContext;

class ShaderProgram {
	friend class GraphicsContext;

	GLuint m_programId = 0;

	// TODO: handle double types
	template <class T>
	void getUniformForType(GLint loc, T* buf);

	ShaderProgram() = default;

public:
	virtual ~ShaderProgram() {
		glDeleteProgram(m_programId);
	}

	bool hasUniform(const std::string& name) {
		return glGetUniformLocation(m_programId, name.c_str()) != -1;
	}

	template <class T>
	void setUniform(const std::string& name, const T& value, size_t num, bool transpose) {
		static_assert(utils::is_glsl_type<T>(), "Error: invalid type for Shader::setUniform");
	}

	template <class T>
	void setUniform(const std::string& name, const T& value, bool transpose) {
		static_assert(utils::is_glsl_type<T>(), "Error: invalid type for Shader::setUniform");
		setUniform<T>(name, value, 1, transpose);
	}

	template <class T>
	void setUniform(const std::string& name, const T& value) {
		static_assert(utils::is_glsl_type<T>(), "Error: invalid type for Shader::setUniform");
		setUniform<T>(name, value, 1, false);
	}

	template <class T>
	T getUniform(const std::string& name) {
		static_assert(utils::is_glsl_type<T>(), "Error: invalid type for Shader::getUniform");
		T ret;
		const GLint loc = glGetUniformLocation(m_programId, name.c_str());
		getUniformForType<typename utils::container_type<T>::type>(loc, glm::value_ptr(ret));

		return ret;
	}

	// TODO: Program introspection functions
	//       https://www.opengl.org/wiki/Program_Introspection
	size_t numUniforms() const {
		return 0;
	}

	size_t numAttributes() const {
		return 0;
	}
};

typedef std::shared_ptr<ShaderProgram> ShaderProgramHandle;

template <>
void ShaderProgram::getUniformForType<GLfloat>(GLint loc, GLfloat* buf) {
	glGetUniformfv(m_programId, loc, buf);
}

template <>
void ShaderProgram::getUniformForType<GLint>(GLint loc, GLint* buf) {
	glGetUniformiv(m_programId, loc, buf);
}

template <>
void ShaderProgram::getUniformForType<GLuint>(GLint loc, GLuint* buf) {
	glGetUniformuiv(m_programId, loc, buf);
}

template <>
GLfloat ShaderProgram::getUniform<GLfloat>(const std::string& name) {
	GLfloat ret;
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	getUniformForType<GLfloat>(loc, &ret);
	return ret;
}

template <>
GLint ShaderProgram::getUniform<GLint>(const std::string& name) {
	GLint ret;
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	getUniformForType<GLint>(loc, &ret);
	return ret;
}

template <>
GLuint ShaderProgram::getUniform<GLuint>(const std::string& name) {
	GLuint ret;
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	getUniformForType<GLuint>(loc, &ret);
	return ret;
}

template <>
void ShaderProgram::setUniform<GLfloat>(const std::string& name, const GLfloat& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform1fv(m_programId, loc, num, &value);
}

template <>
void ShaderProgram::setUniform<glm::vec2>(const std::string& name, const glm::vec2& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform2fv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::vec3>(const std::string& name, const glm::vec3& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform3fv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::vec4>(const std::string& name, const glm::vec4& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform4fv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<GLint>(const std::string& name, const GLint& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform1iv(m_programId, loc, num, &value);
}

template <>
void ShaderProgram::setUniform<glm::ivec2>(const std::string& name, const glm::ivec2& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform2iv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::ivec3>(const std::string& name, const glm::ivec3& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform3iv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::ivec4>(const std::string& name, const glm::ivec4& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform4iv(m_programId, loc, num, glm::value_ptr(value));
}


template <>
void ShaderProgram::setUniform<GLuint>(const std::string& name, const GLuint& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform1uiv(m_programId, loc, num, &value);
}

template <>
void ShaderProgram::setUniform<glm::uvec2>(const std::string& name, const glm::uvec2& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform2uiv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::uvec3>(const std::string& name, const glm::uvec3& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform3uiv(m_programId, loc, num, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::uvec4>(const std::string& name, const glm::uvec4& value, size_t num, bool) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniform4uiv(m_programId, loc, num, glm::value_ptr(value));
}



template <>
void ShaderProgram::setUniform<glm::mat2>(const std::string& name, const glm::mat2& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix2fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat3>(const std::string& name, const glm::mat3& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix3fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat4>(const std::string& name, const glm::mat4& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix4fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat2x3>(const std::string& name, const glm::mat2x3& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix2x3fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat3x2>(const std::string& name, const glm::mat3x2& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix3x2fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat2x4>(const std::string& name, const glm::mat2x4& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix2x4fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat4x2>(const std::string& name, const glm::mat4x2& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix4x2fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat3x4>(const std::string& name, const glm::mat3x4& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix3x4fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}

template <>
void ShaderProgram::setUniform<glm::mat4x3>(const std::string& name, const glm::mat4x3& value, size_t num, bool transpose) {
	GLint loc = glGetUniformLocation(m_programId, name.c_str());
	BOOST_ASSERT_MSG(loc != -1, __SHADER_SS_MSG("Error: " << name << " is not a uniform for program."));
	glProgramUniformMatrix4x3fv(m_programId, loc, num, transpose, glm::value_ptr(value));
}


}
#undef __SHADER_SS_MSG

#endif /* RENDERER_SHADER_H_ */
