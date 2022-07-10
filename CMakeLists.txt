cmake_minimum_required(VERSION 3.5)

project(BNB2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        Image.qrc

        gamewindow.cpp gamewindow.h gamewindow.ui
        instructionwindow.cpp instructionwindow.h instructionwindow.ui

        framework/gamescene.h framework/gamescene.cpp
        framework/gameobject.h framework/gameobject.cpp
        framework/component.h framework/component.cpp
        framework/transform.h framework/transform.cpp
        framework/imagetransform.h framework/imagetransform.cpp
        framework/transformbuilder.h framework/transformbuilder.cpp

        core.h core.cpp
        health.h health.cpp
        hitable.h hitable.cpp
        bomb.h bomb.cpp
        light.h light.cpp
        player.h player.cpp
        floor.h floor.cpp
        wall.h wall.cpp
        pausebutton.h pausebutton.cpp
        numbomb.h numbomb.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BNB2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BNB2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BNB2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BNB2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(BNB2 PRIVATE framework/)
target_include_directories(BNB2 PRIVATE image/)
target_link_libraries(BNB2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(BNB2 PRIVATE Qt6::Multimedia)

set_target_properties(BNB2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BNB2)
endif()
