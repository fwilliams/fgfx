#include "graphicscontext.h"


namespace gfx {

utils::GLProgramBuilder GraphicsContext::programBuilder;

ShaderProgramHandle GraphicsContext::makeShaderProgramFromFiles(const std::string& vert, const std::string& frag) const {
	std::shared_ptr<ShaderProgram> ret = std::shared_ptr<ShaderProgram>(new ShaderProgram());
	ret->m_programId = programBuilder.buildFromFiles(vert, frag);
	return ret;
}

ShaderProgramHandle GraphicsContext::makeShaderProgramFromStrings(const std::string& vert, const std::string& frag) const {
	std::shared_ptr<ShaderProgram> ret = std::shared_ptr<ShaderProgram>(new ShaderProgram());
	ret->m_programId = programBuilder.buildFromFiles(vert, frag);
	return ret;
}

void GraphicsContext::addShaderProgramIncludeDir(const std::string& dirname) {
	programBuilder.addIncludeDir(dirname);
}

void GraphicsContext::enableAlphaBlending() {
	glEnable(GL_BLEND);
}

void GraphicsContext::enableFaceCulling() {
	glEnable(GL_CULL_FACE);
}

void GraphicsContext::disableFaceCulling() {
	glDisable(GL_CULL_FACE);
}

void GraphicsContext::setFaceCullMode(FaceCullMode mode) {
	glCullFace(mode);
}

void GraphicsContext::setClearColor(const glm::vec4& clearColor) {
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void GraphicsContext::enableDepthBuffer() {
	glEnable(GL_DEPTH_TEST);
}

void GraphicsContext::disableDepthBuffer() {
	glDisable(GL_DEPTH_TEST);
}
}
