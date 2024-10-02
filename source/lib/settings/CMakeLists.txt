project(settings CXX)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    settings_manager.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    database
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    .
)
