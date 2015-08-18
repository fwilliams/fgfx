#include <GL/glew.h>

#include <memory>
#include <boost/assert.hpp>

#include "utils/tuple.h"
#include "utils/gl_traits.h"

#ifndef RENDERER_GEOMETRY_H_
#define RENDERER_GEOMETRY_H_

namespace gfx {

enum PrimitiveType { TRIANGLES = GL_TRIANGLES, LINES = GL_LINES, POINTS = GL_POINTS };

class GraphicsContext;

namespace detail {

/*
 * Named Vertex buffer
 * Type Name, Type, Name, ...
 * TODO:
 *  * NamedType constructor:
 *    1) Function using variadic templates with a type constructor
 *       Vertex<vec4, name("position"), vec3, name("normal"), vec2("texcoords")>
 *    2) Macro:
 *       Vertex(vec4, position, vec3 normal, vec2 texcoords) expands to vertex type
 *  * CreateVAO function which uses attribute names
 *
 *  Another solution:
 *  struct Vertex {
 *    ATTRIB(vec4, "position") position;
 *    ATTRIB(vec3, "normal") normal;
 *    ATTRIB(vec2, "texcoord") texcoord;
 *  };
 */
template <size_t I, class... Types>
struct NamedVertexConsCell;

template <size_t I, class T, class NameT, class... Types>
struct NamedVertexConsCell<I, T, NameT, Types...> {
	using HeadType = T;
	using TailType = NamedVertexConsCell<I+1, Types...>;
	using NameType = NameT;

	HeadType head;
	TailType tail;
};

template <size_t I, class T, class NameT>
struct NamedVertexConsCell<I, T, NameT> {
	using HeadType = T;
	using TailType = detail::EmptyListType;
	using NameType = NameT;

	HeadType head;
};

/*
 * Setup vertex attribute pointers for a cons-list of types
 */
template <size_t I, class ConsCell>
struct EnableAttribArrayAOS;

template <size_t I>
struct EnableAttribArrayAOS<I, EmptyListType> {
	inline static void enable(size_t stride) {
		return;
	}
};

template <size_t I, class ConsCell>
struct EnableAttribArrayAOS {
	inline static void enable(size_t stride) {
		typedef typename ConsCell::HeadType HT;
		typedef typename ConsCell::TailType TT;
		typedef ListElement<0, ConsCell> LE;

		glEnableVertexAttribArray(I);
		glVertexAttribPointer(I, utils::dim<HT>(), utils::gl_value_type_id<HT>(), GL_FALSE, stride, (void*)LE::offset());

		EnableAttribArrayAOS<I+1, TT>::enable(stride);
	}
};



/*
 * Generate a VAO for an array of vertices of type Vertex
 * Vertex must be have the trait IsTypeTuple
 * TODO: Test with program which doesn't use middle attributes
 */
template <class Vertex>
inline static GLuint generateVAO() {
	static_assert(IsGfxTuple<Vertex>::value,
			"Error Vertex type is not a TupleN or TypeList.");
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	const size_t sizeofVertex = sizeof(Vertex);
	EnableAttribArrayAOS<0, typename Vertex::ListType>::enable(sizeofVertex);
	return vao;
}

class Geometry {
protected:
	friend class GraphicsContext;

	PrimitiveType m_primType = PrimitiveType::TRIANGLES;
	size_t m_numVerts = 0, m_numInds = 0;
	GLuint m_vboId = 0, m_iboId = 0, m_vaoId = 0;

public:
	PrimitiveType primitiveType() const {
		return m_primType;
	}

	size_t numVertices() const {
		return m_numVerts;
	}

	size_t numIndices() const {
		return m_numInds;
	}

	bool isIndexed() const {
		return m_iboId != 0;
	}

	void setPrimiveType(const PrimitiveType& primType) {
		m_primType = primType;
	}
};


}

template <size_t I, class... Types>
struct IsGfxTuple<detail::NamedVertexConsCell<I, Types...>> {
	static const constexpr bool value = true;
};

template <class Vertex>
class GeometryBuffer: public detail::Geometry {
	friend class GraphicsContext;

	GeometryBuffer(bool isIndexed, PrimitiveType pType = TRIANGLES) {
		m_primType = pType;

		glGenBuffers(1, &m_iboId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);

		m_vaoId = detail::generateVAO<Vertex>();

		if(isIndexed) {
			glGenBuffers(1, &m_vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GeometryBuffer(size_t numVerts, PrimitiveType pType = TRIANGLES) {
		m_primType = pType;
		m_numVerts = numVerts;

		glGenBuffers(1, &m_vboId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), nullptr, GL_STATIC_DRAW);

		m_vaoId = detail::generateVAO<Vertex>();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GeometryBuffer(size_t numVerts, const Vertex* verts, PrimitiveType pType = TRIANGLES) {
		m_primType = pType;
		m_numVerts = numVerts;

		glGenBuffers(1, &m_vboId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), verts, GL_STATIC_DRAW);

		m_vaoId = detail::generateVAO<Vertex>();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GeometryBuffer(size_t numVerts, size_t numInds, PrimitiveType pType = TRIANGLES) {
		m_primType = pType;
		m_numVerts = numVerts;
		m_numInds = numInds;

		glGenBuffers(1, &m_vboId);
		glGenBuffers(1, &m_iboId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), nullptr, GL_STATIC_DRAW);

		m_vaoId = detail::generateVAO<Vertex>();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInds*sizeof(GLuint), nullptr, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GeometryBuffer(size_t numVerts, size_t numInds, const Vertex* verts, const GLuint* inds, PrimitiveType pType=TRIANGLES) {
		m_primType = pType;
		m_numVerts = numVerts;
		m_numInds = numInds;

		glGenBuffers(1, &m_vboId);
		glGenBuffers(1, &m_iboId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), verts, GL_STATIC_DRAW);

		m_vaoId = detail::generateVAO<Vertex>();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInds*sizeof(GLuint), inds, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

public:
	virtual ~GeometryBuffer() {
		glDeleteBuffers(1, &m_vboId);
		glDeleteVertexArrays(1, &m_vaoId);
		if(isIndexed()) {
			glDeleteBuffers(1, &m_iboId);
		}
	}

	void setVertexData(Vertex* data, size_t numVertices) {
		m_numVerts = numVertices;
		glNamedBufferData(m_vboId, m_numVerts*sizeof(Vertex), data, GL_STATIC_DRAW);
	}

	void setIndexData(GLuint* data, size_t numIndices) {
		BOOST_ASSERT_MSG(m_iboId != 0, "Error attempting to set index data of non indexed geometry buffer");
		m_numInds = numIndices;
		glNamedBufferData(m_iboId, m_numInds*sizeof(GLuint), data, GL_STATIC_DRAW);
	}

	void setVertexSubData(Vertex* data, size_t vertexOffset, size_t numVertices) {
		glNamedBufferSubData(m_vboId, vertexOffset*sizeof(Vertex), numVertices*sizeof(Vertex), data);
	}

	void setIndexSubData(GLuint* data, size_t indexOffset, size_t numIndices) {
		BOOST_ASSERT_MSG(m_iboId != 0, "Error attempting to set index data of non indexed geometry buffer");
		glNamedBufferSubData(m_vboId, indexOffset*sizeof(GLuint), numIndices*sizeof(GLuint), data);
	}
};


template <class Vertex>
using GBufHandle = std::shared_ptr<GeometryBuffer<Vertex>>;

}

#endif /* RENDERER_GEOMETRY_H_ */
