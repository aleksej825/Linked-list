cmake_minimum_required(VERSION 3.23)

project(my_list LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_sources(
    ${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/my_list.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
