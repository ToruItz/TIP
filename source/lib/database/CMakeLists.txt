project(database CXX)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    database.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Sql
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    .
)
