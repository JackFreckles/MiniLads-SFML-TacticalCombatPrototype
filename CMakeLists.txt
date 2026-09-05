cmake_minimum_required(VERSION 3.16)

project(MiniLads-SFML-TacticalCombatPrototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(MiniLads src/main.cpp)

target_include_directories(MiniLads PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(MiniLads PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)