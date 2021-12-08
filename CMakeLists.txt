cmake_minimum_required(VERSION 3.19)

set(NAME helloworld)

project(${NAME})

if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/workspace/tmpinstall")
endif ()

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)
if (WIN32)
    find_package(Qt6 COMPONENTS Gui/Qt6QWindowsIntegrationPlugin)
endif ()

qt_add_executable(${NAME}
        main.cpp
        )

set_target_properties(${NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )

target_link_libraries(${NAME} PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

qt6_add_resources(${NAME} "mainwindow"
        PREFIX
        "/res"
        FILES
        "c1.png"
        "c2.png"
        )

install(TARGETS ${NAME}
        EXPORT ${NAME}
        RUNTIME_DEPENDENCY_SET rds
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}/__TODO_bundle__
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

if (WIN32)
    target_compile_options(${NAME} PRIVATE -mwindows)
    install(RUNTIME_DEPENDENCY_SET rds
            PRE_EXCLUDE_REGEXES "^api-ms-.*\\.dll$|^ext-ms-.*\\.dll$|^emclient\\.dll$|^hvsifiletrust\\.dll$"
            POST_EXCLUDE_REGEXES "^.*[\\\\/]system32/.*\\.dll$"
            DIRECTORIES c:/tools/msys64/mingw64/bin)

    install(
            FILES "$<TARGET_FILE:Qt6::QWindowsIntegrationPlugin>"
            DESTINATION ${CMAKE_INSTALL_BINDIR}/platforms
    )

    if (DEACTIVATED_WIN32)
        install(CODE [[
file(GET_RUNTIME_DEPENDENCIES
        RESOLVED_DEPENDENCIES_VAR rdv
        UNRESOLVED_DEPENDENCIES_VAR udv
        EXECUTABLES $<TARGET_FILE:clion_qt_test>
        PRE_EXCLUDE_REGEXES "^api-ms-.*\\.dll$|^ext-ms-.*\\.dll$|^emclient\\.dll$|^hvsifiletrust\\.dll$"
        POST_EXCLUDE_REGEXES "^.*[\\\\/]system32/.*\\.dll$"
        DIRECTORIES c:/tools/msys64/mingw64/bin)
list(JOIN udv "\n" udv_r)
message("UNRESOLVED_DEPENDENCIES_VAR:\n" ${udv_r})
list(JOIN rdv "\n" rdv_r)
message("RESOLVED_DEPENDENCIES_VAR:\n" ${rdv_r})
file(INSTALL DESTINATION ${CMAKE_INSTALL_BINDIR}_deps TYPE EXECUTABLE FILES ${rdv})
]])
        #        EXECUTABLES C:/workspace/tmpinstall/bin/helloworld.exe
    endif ()
endif ()

#add_library(ttt main.cpp)
#include(GenerateExportHeader)
#generate_export_header(ttt)
