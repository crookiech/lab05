cmake_minimum_required(VERSION 3.7.2)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(physics VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пытаемся найти предустановленный SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # Если SFML не найден - выкачиваем и собираем из исходников
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # Обход потенциальных проблем при сборке sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

# define ниже нужен для включения M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp Dust.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp)
target_link_libraries(physics PRIVATE sfml-graphics)

# Укажите директорию, где находятся ваши DLL-файлы
set(DLL_DIR "${CMAKE_SOURCE_DIR}/sources")

# Список необходимых DLL-файлов
set(DLL_FILES
    "${DLL_DIR}/sfml-audio-2.dll"
    "${DLL_DIR}/sfml-audio-d-2.dll"
    "${DLL_DIR}/sfml-graphics-2.dll"
    "${DLL_DIR}/sfml-graphics-d-2.dll"
    "${DLL_DIR}/sfml-network-2.dll"
    "${DLL_DIR}/sfml-network-d-2.dll"
    "${DLL_DIR}/sfml-system-2.dll"
    "${DLL_DIR}/sfml-system-d-2.dll"
    "${DLL_DIR}/sfml-window-2.dll"
    "${DLL_DIR}/sfml-window-d-2.dll"
)

# Копирование DLL-файлов в выходной каталог после сборки
foreach(DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET physics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL_FILE}" $<TARGET_FILE_DIR:physics>)
endforeach()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")    # Флаг для компилятора MSVC (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    else()
    # Флаг для g++ и clang++ (Linux, MacOS)    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )


install(TARGETS physics DESTINATION bin)
set(CPACK_GENERATOR "ZIP;DEB")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME "physics")
set(CPACK_PACKAGE_DESCRIPTION "Описание вашего проекта")
set(CPACK_PACKAGE_VENDOR "Ваше имя или компания")
set(CPACK_PACKAGE_CONTACT "Ваш контактный email")
include(CPack)
