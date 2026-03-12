cmake_minimum_required(VERSION 3.14)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 17)

# --- 1. BAIXAR GLFW AUTOMATICAMENTE ---
include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# --- 2. CONFIGURAR SEUS ARQUIVOS ---
include_directories(include)

# Procuramos por TODOS os arquivos de uma vez (incluindo o glad.c)
#file(GLOB SOURCES "src/*.cpp" "src/*.c")
set(SOURCES 
    src/main.cpp
    src/Vector.cpp
    src/CelestialBody.cpp
    src/glad.c
)

# Criamos o executável UMA ÚNICA VEZ com todos os arquivos
add_executable(SolarSystem ${SOURCES})
target_include_directories(SolarSystem PRIVATE ${glfw_SOURCE_DIR}/include)

# --- 3. CONECTAR AS BIBLIOTECAS ---
find_package(OpenGL REQUIRED)
target_link_libraries(SolarSystem PRIVATE glfw OpenGL::GL)