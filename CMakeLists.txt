cmake_minimum_required(VERSION 3.7)
project(CGEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

file(GLOB_RECURSE RESOURCES    CG184/Resources/textures/*.jpg          CG184/Resources/textures/*.png)

file(GLOB_RECURSE CAMERA        CG184/src/Camera/*.cpp          CG184/src/Camera/*.h)
file(GLOB_RECURSE INPUT         CG184/src/EventSystem/*.cpp     CG184/src/EventSystem/*.h)
file(GLOB_RECURSE GRAPHICS      CG184/src/Graphics/*.cpp        CG184/src/Graphics/*.h)
file(GLOB_RECURSE MATHS         CG184/src/Maths/*.cpp           CG184/src/Maths/*.h)
file(GLOB_RECURSE GEOMETRYS     CG184/src/Geometry/*.cpp        CG184/src/Geometry/*.h)
file(GLOB_RECURSE SCENE         CG184/src/Scene/*.cpp           CG184/src/Scene/*.h)
file(GLOB_RECURSE LIGHTS        CG184/src/Lights/*.cpp          CG184/src/Lights/*.h)



include_directories(${PROJECT_SOURCE_DIR}/external-dependencies/Extras)

include_directories(${PROJECT_SOURCE_DIR}/external-dependencies/GLFW/GLFW/include)
link_directories(${PROJECT_SOURCE_DIR}/external-dependencies/GLFW/GLFW/lib-mingw)

include_directories(${PROJECT_SOURCE_DIR}/external-dependencies/GLEW/GLEW/include)
link_directories(${PROJECT_SOURCE_DIR}/external-dependencies/GLEW/GLEW/lib)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/external-dependencies/GLFW/GLFW/")
    list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/external-dependencies/GLEW/GLEW/")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    find_package(glfw3 3.2 REQUIRED)
#    include_directories(${GLFW_INCLUDE_DIRS})
endif()


# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")


find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR})
find_package(GLEW REQUIRED)

configure_file (${PROJECT_SOURCE_DIR}/CG184/Resources/objects/rock/rock.obj       Resources/objects/rock/rock.obj     COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/Resources/objects/cyborg/cyborg.obj   Resources/objects/cyborg/cyborg.obj COPYONLY)

configure_file (${PROJECT_SOURCE_DIR}/CG184/Resources/textures/container.jpg  Resources/textures/container.jpg COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/Resources/textures/container2.png Resources/textures/container2.png COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/Resources/textures/container2_specular.png Resources/textures/container2_specular.png COPYONLY)

configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/BoxSolid.vs         TestShaders/BoxSolid.vs         COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/BoxSolid.fs         TestShaders/BoxSolid.fs         COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/LightCube.vs        TestShaders/LightCube.vs        COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/LightCube.fs        TestShaders/LightCube.fs        COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/PhongShader.fs      TestShaders/PhongShader.fs      COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/PhongShader.vs      TestShaders/PhongShader.vs      COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/multipleLights.vs   TestShaders/multipleLights.vs   COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/multipleLights.fs   TestShaders/multipleLights.fs   COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/texture.vs          TestShaders/texture.vs          COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/texture.fs          TestShaders/texture.fs          COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/TextureSetup.vs     TestShaders/TextureSetup.vs     COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/TextureSetup.fs     TestShaders/TextureSetup.fs     COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/picker.vs           TestShaders/picker.vs           COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/picker.fs           TestShaders/picker.fs           COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/anchor.vs           TestShaders/anchor.vs           COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/anchor.fs           TestShaders/anchor.fs           COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/solidWireframe.vs   TestShaders/solidWireframe.vs   COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/solidWireframe.fs   TestShaders/solidWireframe.fs   COPYONLY)
configure_file (${PROJECT_SOURCE_DIR}/CG184/TestShaders/solidWireframe.gs   TestShaders/solidWireframe.gs   COPYONLY)

#configure_file (${PROJECT_SOURCE_DIR}/src/Shaders/basic.fs basic.fs COPYONLY)
#configure_file (${PROJECT_SOURCE_DIR}/src/Shaders/myText.txt myText.txt COPYONLY)


message(STATUS ${PROJECT_SOURCE_DIR})
#message(STATUS ${GLEW_LIBRARY})

#message(STATUS ${CMAKE_SYSTEM_NAME} )

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SOURCE_FILES CG184/main.cpp ${GRAPHICS} ${MATHS} ${INPUT} ${CAMERA} ${RESOURCES} ${GEOMETRYS} ${SCENE} ${LIGHTS})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SOURCE_FILES CG184/main.cpp ${GRAPHICS} ${MATHS} ${INPUT} ${CAMERA} ${RESOURCES} ${GEOMETRYS} ${SCENE} ${LIGHTS})
endif()

add_executable(CGEngine ${SOURCE_FILES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(CGEngine glfw3 glew32 ${OPENGL_LIBRARY} assimp)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(CGEngine ${OPENGL_LIBRARY} ${GLEW_LIBRARY} glfw assimp)
endif()
