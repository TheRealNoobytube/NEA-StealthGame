# CMakeList.txt : CMake project for NEA Stealth Game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("NEA Stealth Game")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Libraries/SDL2/cmake/)
set(SDL2_Image_DIR ${CMAKE_CURRENT_LIST_DIR}/Libraries/SDL2_image/cmake/)
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (CMakeTarget "Source/NEA Stealth Game.cpp" "Source/NEA Stealth Game.h" "Source/Application/Application.cpp" "Source/Application/Application.h" "Source/Application/Timer.cpp" "Source/Application/Timer.h" "Source/SceneTree/SceneTree.h" "Source/SceneTree/SceneTree.cpp" "Source/Nodes/Node.h" "Source/Nodes/Node.cpp"  "Source/Application/Data Structures/List.h" "Source/Nodes/Sprite/Sprite.h" "Source/Nodes/Sprite/Sprite.cpp" "Source/Nodes/Node2D/Node2D.cpp" "Source/Nodes/Node2D/Node2D.h" "Source/Application/Texture.cpp" "Source/Application/Texture.h")


target_link_libraries(CMakeTarget SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)




# TODO: Add tests and install targets if needed.
