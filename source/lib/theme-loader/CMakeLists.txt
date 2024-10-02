project(theme_loader CXX)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    theme_loader.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    .
)
