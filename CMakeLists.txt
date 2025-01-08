# CMakeList.txt : CMake project for NEA Stealth Game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 17)

project ("NEA Stealth Game")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Libraries/SDL2/cmake/)
set(SDL2_Image_DIR ${CMAKE_CURRENT_LIST_DIR}/Libraries/SDL2_image/cmake/)
set(SDL2_ttf_DIR ${CMAKE_CURRENT_LIST_DIR}/Libraries/SDL2_ttf/cmake/)
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (CMakeTarget WIN32 "Source/NEA Stealth Game.cpp" "Source/NEA Stealth Game.h" "Source/Application/Application.cpp" "Source/Application/Application.h" "Source/Application/Timer.cpp" "Source/Application/Timer.h" "Source/SceneTree/SceneTree.h" "Source/SceneTree/SceneTree.cpp" "Source/Nodes/Node.h" "Source/Nodes/Node.cpp"  "Source/Application/Data Structures/List.h" "Source/Nodes/Sprite/Sprite.h" "Source/Nodes/Sprite/Sprite.cpp" "Source/Nodes/Node2D/Node2D.cpp" "Source/Nodes/Node2D/Node2D.h" "Source/Application/Texture.cpp" "Source/Application/Texture.h" "Source/UI/Label/Label.h" "Source/UI/Label/Label.cpp" "Source/UI/Button/Button.h" "Source/UI/Button/Button.cpp" "Source/Application/Color.h" "Source/Scenes/Menus/MainMenu/MainMenu.cpp" "Source/Scenes/Menus/MainMenu/MainMenu.h" "Source/Application/Vector2D.h" "Source/Application/Signal.h"  "Source/Scenes/Menus/AboutMenu/AboutMenu.cpp" "Source/Scenes/Menus/SettingsMenu/SettingsMenu.cpp" "Source/Scenes/Menus/SettingsMenu/SettingsMenu.h" "Source/UI/Slider/Slider.cpp" "Source/UI/Slider/Slider.h" "Source/Scenes/TestScene.cpp" "Source/Scenes/TestScene.h" "Source/Entities/Player/Player.cpp" "Source/Entities/Player/Player.h"      "Source/Nodes/TimerNode/TimerNode.cpp" "Source/Nodes/TimerNode/TimerNode.h" "Source/Nodes/AnimatedSprite/AnimatedSprite.cpp" "Source/Nodes/AnimatedSprite/AnimatedSprite.h" "Source/Collision/CollisionBody.h" "Source/Collision/CollisionBody.cpp" "Source/Collision/CollisionShapes/CollisionShape.h" "Source/Collision/CollisionShapes/CollisionShape.cpp"   "Source/Collision/CollisionShapes/CollisionRect.h" "Source/Collision/CollisionShapes/CollisionRect.cpp"    "Source/Components/Movement/MovementComponent.cpp" "Source/Components/Movement/MovementComponent.h" "Source/Entities/Entity.cpp" "Source/Entities/Entity.h"   "Source/Entities/Enemy/Enemy.cpp" "Source/Entities/Enemy/Enemy.h")

target_link_libraries(CMakeTarget 
SDL2::SDL2main 
SDL2::SDL2 
SDL2_image::SDL2_image
SDL2_ttf::SDL2_ttf)





# TODO: Add tests and install targets if needed.
