project(image_printer CXX)

find_package(Qt5 COMPONENTS Core Gui PrintSupport REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    image_printer.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::PrintSupport
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    .
)
