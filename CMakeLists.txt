cmake_minimum_required(VERSION 3.18)
set(CMAKE_USE_DIRECTORIES ON)
project(RasterProject)
file(GLOB SOURCES
    "include/*.h"
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME} 
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)
install(TARGETS ${PROJECT_NAME} 
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)