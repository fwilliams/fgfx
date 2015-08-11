#include "tuple.h"

#ifndef GFX_UTILS_VERTEX_H_
#define GFX_UTILS_VERTEX_H_

namespace gfx {

struct Vertex4P3N2T : public Tuple<glm::vec4, glm::vec3, glm::vec2> {
	enum { POS_I = 0, NORM_I = 1, TEX_I = 2};

	inline glm::vec4& position() {
		return get<POS_I>();
	}

	inline glm::vec3& normal() {
		return get<NORM_I>();
	}

	inline glm::vec2& texcoord() {
		return get<TEX_I>();
	}

	inline const glm::vec4& position() const {
		return get<POS_I>();
	}

	inline const glm::vec3& normal() const {
		return get<NORM_I>();
	}

	inline const glm::vec2& texcoord() const {
		return get<TEX_I>();
	}
};

struct Vertex4P3N : public Tuple<glm::vec4, glm::vec3> {
	enum { POS_I = 0, NORM_I = 1};

	inline glm::vec4& position() {
		return get<POS_I>();
	}

	inline glm::vec3& normal() {
		return get<NORM_I>();
	}

	inline const glm::vec4& position() const {
		return get<POS_I>();
	}

	inline const glm::vec3& normal() const {
		return get<NORM_I>();
	}
};

struct Vertex4P2T : public Tuple<glm::vec4, glm::vec2> {
	enum { POS_I = 0, TEX_I = 1};

	inline glm::vec4& position() {
		return get<POS_I>();
	}

	inline glm::vec2& texcoord() {
		return get<TEX_I>();
	}

	inline const glm::vec4& position() const {
		return get<POS_I>();
	}

	inline const glm::vec2& texcoord() const {
		return get<TEX_I>();
	}
};

struct Vertex4P : public Tuple<glm::vec4> {
	enum { POS_I = 0 };

	inline glm::vec4& position() {
		return get<POS_I>();
	}

	inline const glm::vec4& position() const {
		return get<POS_I>();
	}
};

template <>
struct IsGfxTuple<Vertex4P3N2T> {
	static const constexpr bool value = true;
};

template <>
struct IsGfxTuple<Vertex4P2T> {
	static const constexpr bool value = true;
};

template <>
struct IsGfxTuple<Vertex4P3N> {
	static const constexpr bool value = true;
};

template <>
struct IsGfxTuple<Vertex4P> {
	static const constexpr bool value = true;
};
}

#endif /* GFX_UTILS_VERTEX_H_ */
