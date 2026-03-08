cmake_minimum_required(VERSION 3.10)
project(PrimitiveShowcase)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

add_subdirectory(lib/glfw)

add_executable(PrimitiveShowcase
    src/main.cpp
    src/Application.cpp
    src/Camera.cpp
    src/Entity.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Scene.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Lighting.cpp
    src/InputManager.cpp
    src/TextureManager.cpp
    src/Menu.cpp
    src/std_image.cpp
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/glad/src/glad.c
)

target_include_directories(PrimitiveShowcase PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends
)



if (WIN32)
    target_link_libraries(PrimitiveShowcase PRIVATE glfw opengl32)
elseif(APPLE)
    target_link_libraries(PrimitiveShowcase PRIVATE glfw "-framework OpenGL")
else()
    target_link_libraries(PrimitiveShowcase PRIVATE glfw GL)
endif()
set_target_properties(PrimitiveShowcase PROPERTIES OUTPUT_NAME "build")



add_custom_command(TARGET PrimitiveShowcase POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:PrimitiveShowcase>/shaders)

add_custom_command(TARGET PrimitiveShowcase POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:PrimitiveShowcase>/assets)