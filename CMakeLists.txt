cmake_minimum_required(VERSION 3.20)
project(SwarmSimulation)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# so it doesnt take 100 bajillion years for the cmake's first-time configure
# if finding bug maybe try comment these out temporarily
set(FETCHCONTENT_QUIET ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "")
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)


# since we do not use find_package we need this for imgui-sfml to work well with sfml and imgui
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)

# Setting the options on how to populate the "content" with their git repositories
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.2)
FetchContent_Declare(box2d GIT_REPOSITORY https://github.com/erincatto/box2d.git GIT_TAG main)
FetchContent_Declare(box2cpp GIT_REPOSITORY https://github.com/HolyBlackCat/box2cpp.git GIT_TAG master)
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG master)
FetchContent_Declare(imgui-sfml GIT_REPOSITORY https://github.com/SFML/imgui-sfml GIT_TAG master)


# Populating the content based on how we declared it
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(box2d)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(box2cpp)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
FetchContent_MakeAvailable(imgui-sfml)

# Since header only (they are not actual libraries) we must add them as libraries so we can include them later on
# we must also link against them

add_library(imgui ${imgui_SOURCE_DIR}/imgui.cpp ${imgui_SOURCE_DIR}/imgui_draw.cpp ${imgui_SOURCE_DIR}/imgui_tables.cpp ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

add_library(box2cpp INTERFACE)
target_include_directories(box2cpp INTERFACE ${box2cpp_SOURCE_DIR}/include)

add_library(imgui-sfml INTERFACE)
target_include_directories(imgui-sfml INTERFACE ${imgui-sfml_SOURCE_DIR})



add_executable(SwarmSimulation main.cpp)


target_link_libraries(SwarmSimulation PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network

        box2d
        box2cpp
        imgui
        ImGui-SFML::ImGui-SFML
)

