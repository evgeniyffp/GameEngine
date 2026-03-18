cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GameEngine)

find_package(OpenGL          REQUIRED)
find_package(glfw3           REQUIRED)
find_package(glm     CONFIG  REQUIRED)
find_package(spdlog          REQUIRED)

add_executable(${PROJECT_NAME} 
 src/main.cpp
 src/Game/Game.cpp
 
 src/utils/displayInfo.cpp
 src/utils/File.cpp 
 
 src/Time/Time.cpp
 src/Time/TimeFromLastFrame.cpp
 
 src/Engine/Core/Window.cpp   
 src/Engine/Core/Engine.cpp

 src/Engine/Events/Events.cpp 
 src/Engine/Events/Keyboard.cpp 
 
 src/Engine/Wordl/Wordl.cpp
 
 src/Engine/Utilities/ObjLoader/ObjLoader.cpp                
 src/Engine/Utilities/ProjectionMatrix/ProjectionMatrix.cpp  
 
 src/Engine/Graphics/Camera/Camera.cpp                         
 src/Engine/Graphics/Mesh/Mesh.cpp                            
 src/Engine/Graphics/Shader/Shader.cpp
 src/Engine/Graphics/Model/Model.cpp                          
 src/Engine/Graphics/Texture/Texture.cpp
 src/Engine/Graphics/Light/Light.cpp                           
 src/Engine/Graphics/Material/Material.cpp                     
)

include_directories(glad/include)
add_library(glad STATIC glad/src/glad.c)

include_directories(src)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL::GL glfw glad glm::glm soil2
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

