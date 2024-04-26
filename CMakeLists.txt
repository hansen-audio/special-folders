cmake_minimum_required(VERSION 3.19.0)

project("Special Folders")

add_subdirectory(external)

# library
add_library(special-folders STATIC
    include/hao/special_folders/special_folders.h
)

target_include_directories(special-folders
    PUBLIC
        include
    PRIVATE
        source
)

target_compile_features(special-folders 
    PRIVATE 
        cxx_std_17
)

# executable
add_executable(special-folders-app
    app/main.cpp
)

target_link_libraries(special-folders-app
    PRIVATE
        special-folders
)

target_compile_features(special-folders-app
    PRIVATE 
        cxx_std_17
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(special-folders
        PRIVATE
            source/special_folders_win32.cpp
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_sources(special-folders
        PRIVATE
            source/special_folders_mac.mm
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(special-folders
        PRIVATE
            source/special_folders_linux.cpp
    )
endif()
