file(GLOB_RECURSE renderer_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(gfx SHARED ${renderer_srcs})
target_link_libraries(gfx GL)
target_link_libraries(gfx GLEW)
