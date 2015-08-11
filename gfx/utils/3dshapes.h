#include <memory>
#include <vector>
#include <tuple>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include "gfx/graphicscontext.h"

#ifndef GEOM_H_
#define GEOM_H_

namespace gfx {
namespace detail {

typedef std::tuple<glm::vec4, glm::vec3, glm::vec2> VertexData;

std::array<VertexData, 36> cubeData() {
	return std::array<VertexData, 36> {{
		std::make_tuple(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(0.0, 0.0)), // 0
		std::make_tuple(glm::vec4( 0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(1.0, 0.0)), // 1
		std::make_tuple(glm::vec4( 0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(1.0, 1.0)), // 2

		std::make_tuple(glm::vec4( 0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(1.0, 1.0)), // 2
		std::make_tuple(glm::vec4(-0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(0.0, 1.0)), // 3
		std::make_tuple(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0,  0.0,  1.0), glm::vec2(0.0, 0.0)), // 0

		std::make_tuple(glm::vec4(-0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(0.0, 1.0)), // 3
		std::make_tuple(glm::vec4( 0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(1.0, 1.0)), // 2
		std::make_tuple(glm::vec4( 0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(1.0, 0.0)), // 6

		std::make_tuple(glm::vec4( 0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(1.0, 0.0)), // 6
		std::make_tuple(glm::vec4(-0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(0.0, 0.0)), // 7
		std::make_tuple(glm::vec4(-0.5,  0.5,  0.5, 1.0), glm::vec3( 0.0,  1.0,  0.0), glm::vec2(0.0, 1.0)), // 3

		std::make_tuple(glm::vec4(-0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(0.0, 1.0)), // 7
		std::make_tuple(glm::vec4( 0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(1.0, 1.0)), // 6
		std::make_tuple(glm::vec4( 0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(1.0, 0.0)), // 5

		std::make_tuple(glm::vec4( 0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(1.0, 0.0)), // 5
		std::make_tuple(glm::vec4(-0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(0.0, 0.0)), // 4
		std::make_tuple(glm::vec4(-0.5,  0.5, -0.5, 1.0), glm::vec3( 0.0,  0.0, -1.0), glm::vec2(0.0, 1.0)), // 7

		std::make_tuple(glm::vec4(-0.5, -0.5, -0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 4
		std::make_tuple(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(0.0, 1.0)), // 0
		std::make_tuple(glm::vec4(-0.5,  0.5,  0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(1.0, 1.0)), // 3

		std::make_tuple(glm::vec4(-0.5,  0.5,  0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(1.0, 1.0)), // 3
		std::make_tuple(glm::vec4(-0.5,  0.5, -0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(1.0, 0.0)), // 7
		std::make_tuple(glm::vec4(-0.5, -0.5, -0.5, 1.0), glm::vec3(-1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 4

		std::make_tuple(glm::vec4( 0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 1
		std::make_tuple(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 0
		std::make_tuple(glm::vec4( 0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 5

		std::make_tuple(glm::vec4(-0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 4
		std::make_tuple(glm::vec4( 0.5, -0.5, -0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 5
		std::make_tuple(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec3( 0.0, -1.0,  0.0), glm::vec2(0.0, 0.0)), // 0

		std::make_tuple(glm::vec4( 0.5, -0.5,  0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 1
		std::make_tuple(glm::vec4( 0.5, -0.5, -0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 5
		std::make_tuple(glm::vec4( 0.5,  0.5, -0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 6

		std::make_tuple(glm::vec4( 0.5,  0.5, -0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 6
		std::make_tuple(glm::vec4( 0.5,  0.5,  0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 2
		std::make_tuple(glm::vec4( 0.5, -0.5,  0.5, 1.0), glm::vec3( 1.0,  0.0,  0.0), glm::vec2(0.0, 0.0)), // 1
	}};
}

void sphereData(double radius, size_t thetaSamples, size_t phiSamples, std::vector<VertexData>& vertices, std::vector<GLuint>& indices) {
	enum { POS_I = 0, NORM_I = 1, TEX_I = 2 };

	const size_t numVerts = thetaSamples * phiSamples;
	const size_t numInds = phiSamples * 6 + (thetaSamples - 2) * phiSamples * 6;

	// Map vertex and index buffer objects for the sphere
	vertices.resize(numVerts);
	indices.resize(numInds);

	// Variables hold the current vertex to write to
	unsigned vert_i = 0, ind_i = 0;

	// Angular distances between samples
	const double d_theta = glm::pi<double>() / thetaSamples;
	const double d_phi = glm::two_pi<double>() / phiSamples;

	// Angular representation of current theta sample
	double theta = -glm::half_pi<double>() + d_theta;

	// Radius of the circle for the current theta sample
	double xz_rad = radius * glm::cos(theta);

	// Cartesian y coordinate representation of current theta sample
	double y = radius * glm::sin(theta);

	// Offset of the first index for this theta sample
	unsigned index_base = 1;

	// Cache of cosine and sine of each phi sample for reuse in inner loop
	double* cos_sin_phi[2];
	cos_sin_phi[0] = new double[2*phiSamples];
	cos_sin_phi[1] = &(cos_sin_phi[0][phiSamples]);


	// Set the position of the top vertex
	std::get<POS_I>(vertices[vert_i]) = {0.0, -radius, 0.0, 1.0};
	std::get<NORM_I>(vertices[vert_i]) = glm::normalize(glm::vec3(std::get<POS_I>(vertices[vert_i])));
	vert_i += 1;

	// Construct the top triangle of vertices connected to the top vertex
	for (unsigned j = 0; j < phiSamples; j++) {
		double phi = j * d_phi;
		cos_sin_phi[0][j] = glm::cos(phi);
		cos_sin_phi[1][j] = glm::sin(phi);
		std::get<POS_I>(vertices[vert_i]) = {xz_rad * cos_sin_phi[0][j], y, xz_rad * cos_sin_phi[1][j], 1.0};
		std::get<NORM_I>(vertices[vert_i]) = glm::normalize(glm::vec3(std::get<POS_I>(vertices[vert_i])));
		vert_i += 1;

		indices[ind_i++] = 0;
		indices[ind_i++] = index_base + j;
		indices[ind_i++] = index_base + ((j + 1) % phiSamples);
	}

	// Construct all inner triangles not including the top and bottom vertex
	for (unsigned i = 0; i < (thetaSamples - 2); i++) {
		theta += d_theta;
		xz_rad = radius * glm::cos(theta);
		y = radius * glm::sin(theta);

		for (unsigned j = 0; j < phiSamples; j++) {
			std::get<POS_I>(vertices[vert_i]) = {xz_rad * cos_sin_phi[0][j], y, xz_rad * cos_sin_phi[1][j], 1.0};
			std::get<NORM_I>(vertices[vert_i])= glm::normalize(glm::vec3(std::get<POS_I>(vertices[vert_i])));
			vert_i += 1;

			indices[ind_i++] = index_base + j;
			indices[ind_i++] = index_base + j + phiSamples;
			indices[ind_i++] = index_base + ((j + 1) % phiSamples) + phiSamples;

			indices[ind_i++] = index_base + j;
			indices[ind_i++] = index_base + ((j + 1) % phiSamples) + phiSamples;
			indices[ind_i++] = index_base + ((j + 1) % phiSamples);
		}
		index_base += phiSamples;
	}

	// Construct the bottom triangles connecting to the last vertex
	const unsigned LAST_INDEX = index_base + phiSamples;
	for (unsigned j = 0; j < phiSamples; j++) {
		indices[ind_i++] = index_base + j;
		indices[ind_i++] = LAST_INDEX;
		indices[ind_i++] = index_base + ((j + 1) % phiSamples);
	}

	// Set the position of the bottom vertex
	std::get<POS_I>(vertices[vert_i]) = {0.0, radius, 0.0, 1.0};
	std::get<NORM_I>(vertices[vert_i]) = glm::normalize(glm::vec3(std::get<POS_I>(vertices[vert_i])));
	vert_i += 1;

	delete[] cos_sin_phi[0];
}

void planeData(size_t uSamples, size_t vSamples, std::vector<VertexData>& vertices, std::vector<GLuint>& indices) {
	enum { POS_I = 0, NORM_I = 1, TEX_I = 2 };

	size_t numVertices = (uSamples+1) * (vSamples+1);
    size_t numIndices = uSamples * vSamples * 6;

    vertices.resize(numVertices);
    indices.resize(numIndices);

    for(unsigned i = 0; i <= uSamples; i++) {
    	for(unsigned j = 0; j <= vSamples; j++) {
    		const glm::vec2 vPos = (glm::vec2(i, j) -
    				glm::vec2(static_cast<float>(uSamples)/2.0,
    						  static_cast<float>(vSamples)/2.0)) *
    						  glm::vec2(1.0/(uSamples+1), 1.0/(vSamples+1));
    		const size_t vOffset = i*(uSamples + 1) + j;

    		std::get<POS_I>(vertices[vOffset]) = glm::vec4(vPos, 0.0, 1.0);
    		std::get<TEX_I>(vertices[vOffset]) = vPos + glm::vec2(0.5);
    		std::get<NORM_I>(vertices[vOffset]) = glm::vec3(0.0, 0.0, -1.0);
    	}
    }

    for(unsigned i = 0; i < uSamples; i++) {
    	for(unsigned j = 0; j < vSamples; j++) {
    		const size_t iOffset = (i*uSamples + j) * 6;
    		const size_t iBase = i*(uSamples+1) + j;

    		indices[iOffset + 0] = iBase;
    		indices[iOffset + 1] = iBase + 1;
    		indices[iOffset + 2] = iBase + uSamples + 1;

    		indices[iOffset + 3] = iBase + 1;
    		indices[iOffset + 4] = iBase + uSamples + 2;
    		indices[iOffset + 5] = iBase + uSamples + 1;
    	}
    }
}

}

template <size_t PosIndex, size_t NormIndex, class Vertex>
void compute_normals(size_t numVertices, Vertex* data, bool invert = false) {
	glm::vec3 normScale = invert ? glm::vec3(-1.0) : glm::vec3(1.0);
	for(size_t i = 0; i < numVertices; i+=3) {
		const glm::vec3 v1 = glm::vec3(data[i+1]. template get<PosIndex>() - data[i]. template get<PosIndex>());
		const glm::vec3 v2 = glm::vec3(data[i+2]. template get<PosIndex>() - data[i]. template get<PosIndex>());

		for(size_t j = 0; j < 3; j++) {
			data[i+j]. template get<NormIndex>() =
					normScale * glm::normalize( glm::cross(v1, v2));
		}
	}
}

template <size_t POS_I, class Vertex>
gfx::GBufHandle<Vertex> makeCube(const gfx::GraphicsContext& ctx, const glm::vec3& sc = glm::vec3(1.0), bool invertNormals = false) {
	const size_t NUM_VERTS = 36;

	const glm::vec4 scale = glm::vec4(sc, 1.0);

	Vertex vertices[36];
	std::array<std::tuple<glm::vec4, glm::vec3, glm::vec2>, NUM_VERTS> data = detail::cubeData();
	for(size_t i = 0; i < 36; i++) {
		vertices[i].template get<POS_I>() = scale * std::get<0>(data[i]);
	}

	return ctx.makeGeometryBuffer<Vertex>(NUM_VERTS, &vertices[0]);
}

template <size_t POS_I, size_t NORM_I, class Vertex>
gfx::GBufHandle<Vertex> makeCube(const gfx::GraphicsContext& ctx, const glm::vec3& sc = glm::vec3(1.0), bool invertNormals = false) {
	const size_t NUM_VERTS = 36;

	const float normInvMul = invertNormals ? -1.0 : 1.0;
	const glm::vec4 scale = glm::vec4(sc, 1.0);

	Vertex vertices[36];
	std::array<std::tuple<glm::vec4, glm::vec3, glm::vec2>, NUM_VERTS> data = detail::cubeData();
	for(size_t i = 0; i < 36; i++) {
		vertices[i].template get<POS_I>() = scale * std::get<0>(data[i]);
		vertices[i].template get<NORM_I>() = normInvMul * std::get<1>(data[i]);
	}

	return ctx.makeGeometryBuffer<Vertex>(NUM_VERTS, &vertices[0]);
}

template <size_t POS_I, size_t NORM_I, size_t TEX_I, class Vertex>
gfx::GBufHandle<Vertex> makeCube(const gfx::GraphicsContext& ctx, const glm::vec3& sc = glm::vec3(1.0), bool invertNormals = false) {
	const size_t NUM_VERTS = 36;

	const float normInvMul = invertNormals ? -1.0 : 1.0;
	const glm::vec4 scale = glm::vec4(sc, 1.0);

	Vertex vertices[36];
	std::array<std::tuple<glm::vec4, glm::vec3, glm::vec2>, NUM_VERTS> data = detail::cubeData();
	for(size_t i = 0; i < 36; i++) {
		vertices[i].template get<POS_I>() = scale * std::get<0>(data[i]);
		vertices[i].template get<NORM_I>() = normInvMul * std::get<1>(data[i]);
		vertices[i].template get<TEX_I>() = std::get<2>(data[i]);
	}

	return ctx.makeGeometryBuffer<Vertex>(NUM_VERTS, &vertices[0]);
}

template <size_t POS_I, size_t NORM_I, size_t TEX_I, class Vertex>
gfx::GBufHandle<Vertex> makeSphere(const gfx::GraphicsContext& ctx, size_t thetaSamples, size_t phiSamples, float radius = 1.0, bool invertNormals = false) {
	std::vector<std::tuple<glm::vec4, glm::vec3, glm::vec2>> vertData;
	std::vector<GLuint> indData;

	detail::sphereData(radius, thetaSamples, phiSamples, vertData, indData);

	std::vector<Vertex> outVerts;
	outVerts.resize(vertData.size());

	for(size_t i = 0; i < vertData.size(); i++) {
		outVerts[i].template get<POS_I>() = std::get<0>(vertData[i]);
		outVerts[i].template get<NORM_I>() = std::get<1>(vertData[i]);
		outVerts[i].template get<TEX_I>() = std::get<2>(vertData[i]);
	}

	return ctx.makeIndexedGeometryBuffer(outVerts.size(), indData.size(), outVerts.data(), indData.data());
}

template <size_t POS_I, size_t NORM_I, class Vertex>
gfx::GBufHandle<Vertex> makeSphere(const gfx::GraphicsContext& ctx, size_t thetaSamples, size_t phiSamples, float radius = 1.0, bool invertNormals = false) {
	std::vector<std::tuple<glm::vec4, glm::vec3, glm::vec2>> vertData;
	std::vector<GLuint> indData;

	detail::sphereData(radius, thetaSamples, phiSamples, vertData, indData);

	std::vector<Vertex> outVerts;
	outVerts.reserve(vertData.size());

	for(size_t i = 0; i < vertData.size(); i++) {
		outVerts[i].template get<POS_I>() = std::get<0>(vertData[i]);
		outVerts[i].template get<NORM_I>() = std::get<1>(vertData[i]);
	}

	return ctx.makeIndexedGeometryBuffer(outVerts.size(), indData.size(), outVerts.data(), indData.data());
}

template <size_t POS_I, class Vertex>
gfx::GBufHandle<Vertex> makeSphere(const gfx::GraphicsContext& ctx, size_t thetaSamples, size_t phiSamples, float radius = 1.0, bool invertNormals = false) {
	std::vector<std::tuple<glm::vec4, glm::vec3, glm::vec2>> vertData;
	std::vector<GLuint> indData;

	detail::sphereData(radius, thetaSamples, phiSamples, vertData, indData);

	std::vector<Vertex> outVerts;
	outVerts.reserve(vertData.size());

	for(size_t i = 0; i < vertData.size(); i++) {
		outVerts[i].template get<POS_I>() = std::get<0>(vertData[i]);
	}

	return ctx.makeIndexedGeometryBuffer(outVerts.size(), indData.size(), outVerts.data(), indData.data());
}

template <size_t POS_I, size_t NORM_I, size_t TEX_I, class Vertex>
gfx::GBufHandle<Vertex> makePlane(const gfx::GraphicsContext& ctx, size_t uSamples, size_t vSamples, const glm::vec2 size=glm::vec2(1.0, 1.0), bool invertNormals = false) {
	const float invNormMul = invertNormals ? -1.0 : 1.0;

	std::vector<detail::VertexData> vertData;
	std::vector<GLuint> indData;

	detail::planeData(uSamples, vSamples, vertData, indData);

	std::vector<Vertex> verts;
	verts.resize(vertData.size());
	for(size_t i = 0; i < vertData.size(); i++) {
		verts[i].template get<POS_I>() = glm::vec4(size, 1.0, 1.0) * std::get<0>(vertData[i]);
		verts[i].template get<NORM_I>() = invNormMul * std::get<1>(vertData[i]);
		verts[i].template get<TEX_I>() = std::get<2>(vertData[i]);
	}

    return ctx.makeIndexedGeometryBuffer(verts.size(), indData.size(), verts.data(), indData.data());

}

template <size_t POS_I, size_t NORM_I, class Vertex>
gfx::GBufHandle<Vertex> makePlane(const gfx::GraphicsContext& ctx, size_t uSamples, size_t vSamples, const glm::vec2 size=glm::vec2(1.0, 1.0), bool invertNormals = false) {
	const float invNormMul = invertNormals ? -1.0 : 1.0;

	std::vector<detail::VertexData> vertData;
	std::vector<GLuint> indData;
	detail::planeData(uSamples, vSamples, vertData, indData);

	std::vector<Vertex> verts;
	verts.resize(vertData.size());
	for(size_t i = 0; i < vertData.size(); i++) {
		verts[i].template get<POS_I>() = glm::vec4(size, 1.0, 1.0) * std::get<0>(vertData[i]);
		verts[i].template get<NORM_I>() = invNormMul * std::get<1>(vertData[i]);
	}

    return ctx.makeIndexedGeometryBuffer(verts.size(), indData.size(), verts.data(), indData.data());

}

template <size_t POS_I, class Vertex>
gfx::GBufHandle<Vertex> makePlane(const gfx::GraphicsContext& ctx, size_t uSamples, size_t vSamples, const glm::vec2 size=glm::vec2(1.0, 1.0), bool invertNormals = false) {
	std::vector<detail::VertexData> vertData;
	std::vector<GLuint> indData;
	detail::planeData(uSamples, vSamples, vertData, indData);

	std::vector<Vertex> verts;
	verts.resize(vertData.size());
	for(size_t i = 0; i < vertData.size(); i++) {
		verts[i].template get<POS_I>() = glm::vec4(size, 1.0, 1.0) * std::get<0>(vertData[i]);
	}

    return ctx.makeIndexedGeometryBuffer(verts.size(), indData.size(), verts.data(), indData.data());

}

template <size_t POS_I, size_t NORM_I, size_t TEX_I, class Vertex>
gfx::GBufHandle<Vertex> makeTriangle(const gfx::GraphicsContext& ctx, const glm::vec2 size=glm::vec2(1.0, 1.0), bool invertNormals = false) {
	const float invNormMul = invertNormals ? -1.0 : 1.0;

	const size_t NUM_VERTICES = 3;

    Vertex vertices[NUM_VERTICES];

    vertices[0].template get<POS_I>() = glm::vec4{-0.5, -0.5, 0.0, 1.0 };
    vertices[1].template get<POS_I>() = glm::vec4{ 0.5, -0.5, 0.0, 1.0 };
    vertices[2].template get<POS_I>() = glm::vec4{ 0.0,  0.5, 0.0, 1.0 };
    vertices[0].template get<NORM_I>() = invNormMul * glm::vec3{ 0.0, 0.0, 1.0 };
    vertices[1].template get<NORM_I>() = invNormMul * glm::vec3{ 0.0, 0.0, 1.0 };
    vertices[2].template get<NORM_I>() = invNormMul * glm::vec3{ 0.0, 0.0, 1.0 };

    vertices[0].template get<TEX_I>() = glm::vec2{ 0.0, 0.0 };
    vertices[1].template get<TEX_I>() = glm::vec2{ 1.0, 0.0 };
    vertices[2].template get<TEX_I>() = glm::vec2{ 0.5, 1.0 };

    return ctx.makeGeometryBuffer(NUM_VERTICES, vertices);
}

}

#endif /* GEOMETRY_H_ */
