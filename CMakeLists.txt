cmake_minimum_required(VERSION 3.23)

project(my_list LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib/book/
    ${CMAKE_CURRENT_LIST_DIR}/lib/list/
)

set(OPT -O0)
set(WARN -Wall)

set(MY_LIST_FLAGS ${OPT} ${WARN} -g)

add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:${MY_LIST_FLAGS}>"
)

target_sources(
    ${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/lib/list/my_list.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
