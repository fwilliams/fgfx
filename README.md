# FGFX
A lightweight typesafe 3D graphics abstraction based on OpenGL. The goal of this project is to automate a lot of the tedium that comes with writing OpenGL code. This library depends on [glm](http://glm.g-truc.net/0.9.7/index.html) for vector and matrix types and operations.

## Type safety
By using type information, the interface between GPU and CPU code is vastly simplified. In addition the abstractions provided by this framework are typesafe, preventing many errors which would normally only be caught at runtime. In addition an OpenGL traits library is provided, allowing static conversion from types to OpenGL constants. 

## Shader compiler
FGFX automates many OpenGL tasks such as shader compilation and linking. In addition, the FGFX shader compiler supports external defines, as well as includes for modular shader development. 

## Context and window creation
FGFX provides a simple API for OpenGL context and Window creation based on GLEW and SDL 2. The API allows fast prototyping of interactive 3D applications.
