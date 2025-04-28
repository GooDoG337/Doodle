cmake_minimum_required(VERSION 3.5)

project(Doodle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 OPTIONAL_COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Multimedia)
set(PROJECT_SOURCES
    include/score/jumpscore.cpp
    include/platform/platform.cpp
    include/doodle/doodle.cpp
    include/background/background.cpp
    include/volume/volume.h
    include/volume/volume.cpp
        main.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Doodle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()
if(Qt${QT_VERSION_MAJOR}_Multimedia_FOUND)
    add_executable(Doodle
    ${PROJECT_SOURCES}
       include/gameplay/gameplay.cpp
        include/music/musicplayer.cpp)
    target_link_libraries(Doodle PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
else()
    add_executable(Doodle
        ${PROJECT_SOURCES}
        include/gameplayNOMUSIC/gameplay.cpp)
endif()
target_link_libraries(Doodle PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Doodle)
endif()
set_target_properties(Doodle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Doodle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Doodle)
endif()
