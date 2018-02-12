
include_directories(${PROJECT_SOURCE_DIR}/include/)

# Application source
set(CG184_SOURCE
        "main.cpp"

        ## Camera
        "src/Camera/Camera.cpp"

        ## Input
        "src/EventSystem/Input.cpp"

        ## Geometry
        "src/Geometry/Box.cpp"
        "src/Geometry/Circle.cpp"
        "src/Geometry/Mesh.cpp"
        "src/Geometry/MeshFilter.cpp"
        "src/Geometry/HalfEdgeElement.cpp"
        "src/Geometry/Plane.cpp"
        "src/Geometry/Sphere.cpp"
        "src/Geometry/Torus.cpp"

        ## Graphics
        "src/Graphics/IndexBuffer.cpp"
        "src/Graphics/Material.cpp"
        "src/Graphics/Renderer.cpp"
        "src/Graphics/Shader.cpp"
        "src/Graphics/Texture.cpp"
        "src/Graphics/Window.cpp"

        ## Scene
        "src/Scene/Node.cpp"
        "src/Scene/Scene.cpp"
        "src/Scene/Transform.cpp"

        ## Maths
        "src/Maths/Matrix4D.cpp"
        "src/Maths/Quaternions.cpp"
        "src/Maths/Vector2D.cpp"
        "src/Maths/Vector3D.cpp"
        "src/Maths/Vector4D.cpp"

        ## Lights
        "src/Lights/Light.cpp"
        "src/Lights/DirectionalLight.cpp"
        "src/Lights/PointLight.cpp"
        "src/Lights/SpotLight.cpp"
   )

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${CG184_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
		${ASSIMP_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Add executable
#-------------------------------------------------------------------------------
add_executable(CG184 ${CG184_SOURCE})

if (WIN32)
    target_link_libraries( CG184 glew32 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} assimp)
elseif(LINUX)
    target_link_libraries( CG184 GLEW glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} assimp)
endif ()

message(STATUS "RESOURCE_FILE : " ${RESOURCE_FILE})

set_target_properties(CG184 PROPERTIES
        RESOURCE "${RESOURCE_FILE}"
        )

# Install to project root
install(TARGETS CG184 DESTINATION ${CG184_SOURCE_DIR})
