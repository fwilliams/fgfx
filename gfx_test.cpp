#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <boost/assert.hpp>

#include "etc/sdl_gl_window.h"
#include "gfx/graphicscontext.h"
#include "gfx/utils/3dshapes.h"
#include "gfx/utils/camera.h"
#include "gfx/utils/vertex.h"

using namespace glm;
using namespace std;
using namespace gfx;

typedef Vertex4P3N2T Vertex;
typedef gfx::GBufHandle<Vertex> GBufHdl;
typedef gfx::ShaderProgramHandle ProgHdl;

struct Material {
	vec4 diffuse;
	vec4 specular;
	float shininess;
	float reflectance;
};

struct Light {
	vec4 position;
	vec4 intensity;
	float attenuation;
	float enabled;
};


struct App : public SDLGLWindow {
	static const size_t NUM_LIGHTS = 10;

	Light lights[NUM_LIGHTS];
	vec4 globalAmbient;

	Material cubeMaterial;

	FirstPersonCamera camera;

	GBufHdl cubeGeometry;
	GBufHdl sphereGeometry;
	GBufHdl planeGeometry;

	ProgHdl program;

	gfx::GraphicsContext* ctx = nullptr;

	App(size_t w, size_t h) :
		SDLGLWindow(w, h) {
		ctx = new gfx::GraphicsContext();
	}

	void setupLights() {
	    globalAmbient = vec4(0.0001f);
	    const vec4 center(0.0, 15.0, -5.0, 1.0);
	    const vec2 squareSize(42.5);
	    for(int i = 0; i < 3; i++) {
	      for(int j = 0; j < 3; j++) {
	        const size_t light_index = 3 * i + j;
	        const vec4 offset((i-1)*squareSize.x/2.0, 0.0, (j-1)*squareSize.y/2.0, 0.0);
	        lights[light_index].intensity = vec4(0.5, 0.5, 0.5, 1.0);
	        lights[light_index].position = center + offset;
	        lights[light_index].attenuation = 1.0 / pow(25.0, 2.0);
	      }
	    }

	    lights[9].position = vec4(0.0, 2.0, -5.0, 1.0);
	    lights[9].intensity = vec4(0.3525, 0.3525, 0.3525, 1.0);
	    lights[9].attenuation = 1.0 / pow(20.0, 2.0);
	}

	void setupStdUniforms(ProgHdl hdl, const mat4& model = mat4(1.0)) {
		if(hdl->hasUniform("std_Modelview"))
			hdl->setUniform("std_Modelview", camera.getViewMatrix() * model);
		if(hdl->hasUniform("std_Projection"))
			hdl->setUniform("std_Projection", camera.getProjectionMatrix());
		if(hdl->hasUniform("std_Normal"))
			hdl->setUniform("std_Normal", mat4(transpose(inverse(mat3(camera.getViewMatrix() * model)))));
		if(hdl->hasUniform("std_View"))
			hdl->setUniform("std_View", camera.getViewMatrix());
		if(hdl->hasUniform("std_GlobalAmbient"))
			hdl->setUniform("std_GlobalAmbient", globalAmbient);

		#define __APP_LIGHT_UNAME(i, name) (string("std_Lights[") + to_string(i) + string("].") + string(name))
	    for(size_t i = 0; i < NUM_LIGHTS; i++) {
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "position")))
	    		hdl->setUniform(__APP_LIGHT_UNAME(i, "position"), lights[i].position);
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "color")))
	    		hdl->setUniform(__APP_LIGHT_UNAME(i, "color"), lights[i].intensity);
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "attenuation")))
	    		hdl->setUniform(__APP_LIGHT_UNAME(i, "attenuation"), lights[i].attenuation);

	    }
		#undef __APP_LIGHT_UNAME
	}

	void printStdUniforms(ProgHdl hdl) {
		if(hdl->hasUniform("std_Modelview"))
			cout << "std_Modelview: " << to_string(hdl->getUniform<mat4>("std_Modelview")) << endl;
		if(hdl->hasUniform("std_Projection"))
			cout << "std_Projection: " << to_string(hdl->getUniform<mat4>("std_Projection")) << endl;
		if(hdl->hasUniform("std_Normal"))
			cout << "std_Normal: " << to_string(hdl->getUniform<mat4>("std_Normal")) << endl;
		if(hdl->hasUniform("std_View"))
			cout << "std_View: " << to_string(hdl->getUniform<mat4>("std_View")) << endl;
		if(hdl->hasUniform("std_GlobalAmbient"))
			cout << "std_GlobalAmbient: " << to_string(hdl->getUniform<vec4>("std_GlobalAmbient")) << endl;

		#define __APP_LIGHT_UNAME(i, name) (string("std_Lights[") + to_string(i) + string("].") + string(name))
	    for(size_t i = 0; i < NUM_LIGHTS; i++) {
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "position")))
	    		cout << __APP_LIGHT_UNAME(i, "position") << ": " << to_string(hdl->getUniform<vec4>(__APP_LIGHT_UNAME(i, "position"))) << endl;
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "color")))
	    		cout << __APP_LIGHT_UNAME(i, "color") << ": " << to_string(hdl->getUniform<vec4>(__APP_LIGHT_UNAME(i, "color"))) << endl;
	    	if(hdl->hasUniform(__APP_LIGHT_UNAME(i, "attenuation")))
	    		cout << __APP_LIGHT_UNAME(i, "attenuation") << ": " << to_string(hdl->getUniform<float>(__APP_LIGHT_UNAME(i, "attenuation"))) << endl;

	    }
		#undef __APP_LIGHT_UNAME
	}

	void printShaderUtniforms(ProgHdl hdl) {
	    if(hdl->hasUniform("mat.diffuse"))
	    	cout << "mat.diffuse: " << to_string(program->getUniform<vec4>("mat.diffuse")) << endl;
	    if(hdl->hasUniform("mat.specular"))
	    	cout << "mat.specular: " << to_string(program->getUniform<vec4>("mat.specular")) << endl;
	    if(hdl->hasUniform("mat.roughness"))
	    	cout << "mat.roughness: " << to_string(program->getUniform<float>("mat.roughness")) << endl;
	    if(hdl->hasUniform("mat.reflectance"))
	    	cout << "mat.reflectance: " << to_string(program->getUniform<float>("mat.reflectance")) << endl;
	}

	void setup(SDLGLWindow& w) {
		ctx->enableDepthBuffer();
		ctx->enableFaceCulling();

		cubeGeometry = makeCube<0, 1, 2, Vertex>(*ctx, vec3(3.0));
		sphereGeometry = makeSphere<0, 1, 2, Vertex>(*ctx, 100, 100, 1.5);
		planeGeometry = makePlane<0, 1, 2, Vertex>(*ctx, 1, 1, vec2(1000.0));

		ctx->addShaderProgramIncludeDir("gfx/shaders/glsl330");
		program = ctx->makeShaderProgramFromFiles("gfx/shaders/phong_vertex.glsl",
				                                  "gfx/shaders/physical_frag.glsl");


		// Setup a first person camera
	    camera.setPosition(vec3(0.0, 1.0, -7.5));
	    camera.setPerspectiveProjection(45.0f, w.aspectRatio(), 0.5, 1000.0);
	    camera.setCameraVelocity(vec2(0.1));


		// Create a grid of lights and one light close to the object
	    setupLights();

	    // Create a material for the cube
	    vec4 goldColor(1.0, 0.71, 0.29, 0.0);
	    cubeMaterial.diffuse = goldColor;
	    cubeMaterial.specular = goldColor * 0.5f;
	    cubeMaterial.shininess = 2.0 + (2.0 / pow(0.2, 2.0));
	    cubeMaterial.reflectance = 0.8f;


		// Move mouse cursor to the middle of the screen and hide it
		setMousePosition(w.width()/2, w.height()/2);
		showCursor(false);
	}

	void handle_event(SDLGLWindow& w, const SDL_Event& event) {
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_w) {
				camera.setForwardDirection(FirstPersonCamera::CameraDirection::POSITIVE);
			}
			if(event.key.keysym.sym == SDLK_s) {
				camera.setForwardDirection(FirstPersonCamera::CameraDirection::NEGATIVE);
			}
			if(event.key.keysym.sym == SDLK_d) {
				camera.setHorizontalDirection(FirstPersonCamera::CameraDirection::POSITIVE);
			}
			if(event.key.keysym.sym == SDLK_a) {
				camera.setHorizontalDirection(FirstPersonCamera::CameraDirection::NEGATIVE);
			}
		}

		if(event.type == SDL_KEYUP) {
			if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) {
				camera.setForwardDirection(FirstPersonCamera::CameraDirection::STOPPED);
			}
			if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
				camera.setHorizontalDirection(FirstPersonCamera::CameraDirection::STOPPED);
			}
			if(event.key.keysym.sym == SDLK_f) {
				setFullScreen(true);
			}
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				setFullScreen(false);
			}
		}

	    if(event.type == SDL_MOUSEBUTTONDOWN) {
	      if(event.button.button == SDL_BUTTON_LEFT) {
	    	  printStdUniforms(program);
	    	  printShaderUtniforms(program);
	      }
	    }
	}

	void update(SDLGLWindow& w) {
	    vec2 mp;
	    getNormalizedMousePos(value_ptr(mp));
	    setMousePosition(width()/2, height()/2);
	    camera.updateLookat(mp);
	    camera.updatePosition();
	}

	void draw(SDLGLWindow& w) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    setupStdUniforms(program);
	    if(program->hasUniform("mat.diffuse"))
	    	program->setUniform("mat.diffuse", cubeMaterial.diffuse);
	    if(program->hasUniform("mat.specular"))
	    	program->setUniform("mat.specular", cubeMaterial.diffuse);
	    if(program->hasUniform("mat.roughness"))
	    	program->setUniform("mat.roughness", cubeMaterial.shininess);
	    if(program->hasUniform("mat.reflectance"))
	    	program->setUniform("mat.reflectance", cubeMaterial.reflectance);

		ctx->setShaderProgram(program);

		ctx->setGeometryBuffer(cubeGeometry);
		ctx->draw();

		setupStdUniforms(program, translate(mat4(1.0), vec3(10.0, 0.0, 1.0)));

		ctx->setGeometryBuffer(sphereGeometry);
		ctx->draw();

		setupStdUniforms(program, translate(mat4(1.0), vec3(0.0, -1.5, 0.0)) * rotate(mat4(1.0), glm::half_pi<float>(), vec3(1.0, 0.0, 0.0)));

		ctx->setGeometryBuffer(planeGeometry);
		ctx->draw();
	}

	void teardown(SDLGLWindow& w) {
		delete ctx;
	}
};

int main(int argc, char** argv) {
	App w(800, 600);
//	BOOST_ASSERT_MSG(GLEW_EXT_direct_state_access, "DSA extension not found!");
	w.mainLoop();
}


