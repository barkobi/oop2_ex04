cmake_minimum_required (VERSION 3.20)

project (oop2_ex04)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline /analyze)

endif ()


if(APPLE)

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/oop1_Project.app/Contents/MacOS)

    add_executable (${CMAKE_PROJECT_NAME} MACOSX_BUNDLE "" src/ColorBtn.cpp include/ColorBtn.h)

    add_subdirectory (include)
    add_subdirectory (src)
    add_subdirectory (resources)


    set (SFML_STATIC_LIBRARIES FALSE)
    set (SFML_DIR "/usr/local/Cellar/sfml/2.5.1")

    find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)

    set_target_properties ( PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)

endif()



if(WIN32)

    add_executable (${CMAKE_PROJECT_NAME} src/Controller.cpp include/Controller.h src/Board.cpp include/Board.h src/Pad.cpp include/Pad.h src/Mosaic.cpp include/Mosaic.h src/ColorBtn.cpp include/ColorBtn.h src/Player/Player.cpp include/Player/Player.h src/ResourceManager.cpp include/ResourceManager.h src/Player/RandomPlayer.cpp include/Player/RandomPlayer.h src/Player/GreedyPlayerSmallDistance.cpp include/Player/GreedyPlayerSmallDistance.h src/Player/GreedyPlayerLongDistance.cpp include/Player/GreedyPlayerLongDistance.h src/Player/UserPlayer.cpp include/Player/UserPlayer.h src/mainMenu.cpp include/mainMenu.h include/MosaicNode.cpp include/MosaicNode.h include/Shapes.cpp include/Shapes.h)

    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

    add_subdirectory (include)
    add_subdirectory (src)
    add_subdirectory (resources)

    set (SFML_STATIC_LIBRARIES TRUE)
    set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

    find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-main sfml-audio)

    configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)


endif()