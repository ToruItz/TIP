#[[
"Text Insertion Program (TIP)" is a software
for client management and generating unique images for each client.
Copyright (C) 2024  Pavel Remdenok

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
]]

########################################################################
#                                               .:^7^                  #
#                                         :^!?Y5PGGBG~77               #
#                                 .:~7JJ B#GGBBBGPYJ&#G#^              #
#                          .^. 5GGBBBB#&.!@GPB?   ?JPB5:               #
#                   .^!JPG##&#.#&#&#G#Y.  B&PPPGBBBBBG^                #
#              .5G#&&&&&&&#BP? .. ?@GB5   :@BPGBJ7~:.                  #
#              ^@@&&B#@#&P         #&GB!   Y&PG5                       #
#               ^^.  .&&##:        ^@BGB.   &#PG~                      #
#                     ?@##G         P&GBY   ~@PPG                      #
#                      #&#&!         &#GB~:~ G&PGJ                     #
#                      ^@###       .!G#GGBB#J.&#B?                     #
#                       P@##Y      Y@####BPY: ..                       #
#                       .&&#&:     .J7^.                               #
#                        7&B5.                                         #
#                                                                      #
#                                                                      #
########################################################################
project(TIP CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/forms")

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_CXX_LINKER_FLAGS "-static-libgcc -static-libstdc++ ${CMAKE_CXX_LINKER_FLAGS}")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
    QT_DEPLOY_COMPONENTS
    "Core"
    "Gui"
    "Widgets"
    "Sql"
    "PrintSupport"
    "Network"
)

find_package(
    Qt5
    COMPONENTS
    Core
    Gui
    Widgets
    Sql
    PrintSupport
    Network
    REQUIRED
)

find_package(
    OpenXLSX
    REQUIRED
)

set(CONSOLE_FLAG)
if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(CONSOLE_FLAG WIN32)
endif ()

add_executable(
    ${PROJECT_NAME}
    ${CONSOLE_FLAG}
    main.cpp
    interfaces/font-editor/font_editor.cpp
    interfaces/font-editor/font_editor.h
    interfaces/options/options.cpp
    interfaces/options/options.h
    interfaces/mainwindow/mainwindow.cpp
    interfaces/mainwindow/mainwindow.h
    interfaces/text-position-selector/text_position_selector.cpp
    interfaces/text-position-selector/text_position_selector.h
    interfaces/database-settings/database_settings.cpp
    interfaces/database-settings/database_settings.h
    interfaces/password-form/password_form.cpp
    interfaces/password-form/password_form.h
    interfaces/records-amount-form/records_amount_form.cpp
    interfaces/records-amount-form/records_amount_form.h

    forms/database_settings.ui
    forms/font_editor.ui
    forms/mainwindow.ui
    forms/options.ui
    forms/password_form.ui
    forms/records_amount_form.ui
    forms/text_position_selector.ui


    resources/icon.rc
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    .
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
    Qt5::PrintSupport
    Qt5::Network

    OpenXLSX::OpenXLSX

    database
    image_printer
    settings
    text_painter
    theme_loader
    logger
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)

# Копирование содержимого папки reference в build
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/build_folder_reference/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${OPEN_XLSX_DIR}/bin/libOpenXLSX.dll"

    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Qt autoDLL
if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH ${QT5_DIR})
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlpsql${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlpsql${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/sqldrivers/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${QT_INSTALL_PATH}/plugins/printsupport"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/printsupport")
    endif ()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${QT_INSTALL_PATH}/plugins/imageformats/qjpeg.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/qjpeg.dll"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${QT_INSTALL_PATH}/plugins/imageformats/qwbmp.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/qwbmp.dll"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${QT_INSTALL_PATH}/plugins/imageformats/qwebp.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/qwebp.dll"
    )
    foreach (QT_LIB ${QT_DEPLOY_COMPONENTS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    if (DEFINED DEPLOY_DEPENDENCY)
        set(DEPLOY_COMMAND deployment/deploy_windows.bat ${DEPLOY_DEPENDENCY})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${DEPLOY_COMMAND}
            COMMENT "Running Inno Setup Compiler"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()
endif ()