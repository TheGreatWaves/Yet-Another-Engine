cmake_minimum_required(VERSION 3.21)
project(CMakeSFMLProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
    src/main.cpp
    inc/EngineLoop.hpp
     "inc/Utils.hpp" "inc/Common.hpp" "inc/Window.hpp" "inc/ResourceManager.hpp"  "inc/ECS/Entity.hpp" "inc/ECS/EntityManager.hpp" "inc/ECS/System.hpp" "inc/ECS/EntityManager.cpp" "inc/ECS/Component.hpp" "inc/ECS/Component.cpp" "inc/ECS/System.cpp" "inc/ECS/ECSUtils.hpp"   "inc/Core/States/Core/State.cpp"  "inc/ECS/Core/ECS.hpp" "inc/Core/States/Core/StateIdentifier.hpp" "inc/Core/States/Impl/TitleState.hpp")

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)


