cmake_minimum_required(VERSION 3.15)
project(Chapaev)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "SFML-2.5.1/lib")
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

include_directories("Headers")
file(GLOB CPPS "Sources/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS} Sources/Physics.cpp Headers/Physics.h Headers/CGame.h Sources/CVector.cpp Headers/CVector.h)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)