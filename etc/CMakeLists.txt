file(GLOB_RECURSE utils_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(etc SHARED ${utils_srcs})
target_link_libraries(etc GL)
target_link_libraries(etc GLEW)
target_link_libraries(etc SDL2)