project(text_painter CXX)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    text_painter.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    database
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    .
)
