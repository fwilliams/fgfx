#include <GL/glew.h>

#include <array>
#include <memory>
#include <utility>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/gl_program_builder.h"
#include "geometrybuffer.h"
#include "shader.h"

#ifndef RENDERER_H_
#define RENDERER_H_

namespace gfx {

enum FaceCullMode { BACK = GL_BACK, FRONT = GL_FRONT, FRONT_AND_BACK = GL_FRONT_AND_BACK };
enum WindingMode { CW, CCW };

class GraphicsContext {
	std::shared_ptr<detail::Geometry> m_currentBuf;

	static utils::GLProgramBuilder programBuilder;

public:
	ShaderProgramHandle makeShaderProgramFromFiles(const std::string& vert, const std::string& frag) const;
	ShaderProgramHandle makeShaderProgramFromStrings(const std::string& vert, const std::string& frag) const;
	void addShaderProgramIncludeDir(const std::string& dirname);

	template <class Vertex>
	GBufHandle<Vertex> makeGeometryBuffer() const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(new GeometryBuffer<Vertex>(false));
	}

	template <class Vertex>
	GBufHandle<Vertex> makeGeometryBuffer(size_t numVerts) const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(new GeometryBuffer<Vertex>(numVerts));
	}

	template <class Vertex>
	GBufHandle<Vertex> makeGeometryBuffer(size_t numVerts, const Vertex* verts) const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(new GeometryBuffer<Vertex>(numVerts, verts));
	}

	template <class Vertex>
	GBufHandle<Vertex> makeIndexedGeometryBuffer() const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(new GeometryBuffer<Vertex>(true));
	}

	template <class Vertex>
	GBufHandle<Vertex> makeIndexedGeometryBuffer(size_t numVerts, size_t numInds) const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(
				new GeometryBuffer<Vertex>(numVerts, numInds));
	}

	template <class Vertex>
	GBufHandle<Vertex> makeIndexedGeometryBuffer(size_t numVerts, size_t numInds, const Vertex* verts, const GLuint* inds) const {
		return std::shared_ptr<GeometryBuffer<Vertex>>(
				new GeometryBuffer<Vertex>(numVerts, numInds, verts, inds));
	}

	template <class Vertex>
	void setGeometryBuffer(const GBufHandle<Vertex>& hdl) {
		m_currentBuf = std::static_pointer_cast<detail::Geometry>(hdl);
		glBindVertexArray(hdl->m_vaoId);
	}

	void setShaderProgram(const ShaderProgramHandle& hdl) {
		glUseProgram(hdl->m_programId);
	}

	void draw() {
		if(m_currentBuf->isIndexed()) {
			glDrawElements(m_currentBuf->primitiveType(), m_currentBuf->numIndices(), GL_UNSIGNED_INT, nullptr);
		} else {
			glDrawArrays(GL_TRIANGLES, 0, m_currentBuf->numVertices());
		}
	}

	// TODO: Wireframe drawing
	void drawWireFrame();

	// TODO: Instanced rendering
	void drawInstanced();

	void enableAlphaBlending();

	void enableFaceCulling();

	void disableFaceCulling();

	void setFaceCullMode(FaceCullMode mode);

	void setClearColor(const glm::vec4& clearColor);

	void enableDepthBuffer();

	void disableDepthBuffer();
};

}

#endif /* RENDERER_H_ */
