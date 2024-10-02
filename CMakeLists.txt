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
cmake_minimum_required(VERSION 3.23)
project(TIP_PROJECT CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build) # path/to/build_directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if (NOT DEFINED QT5_DIR)
    message(FATAL_ERROR "QT5_DIR is not defined")
endif ()
if (NOT DEFINED OPEN_XLSX_DIR)
    message(FATAL_ERROR "OPEN_XLSX_DIR is not defined")
endif ()
list(APPEND CMAKE_PREFIX_PATH "${QT5_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${OPEN_XLSX_DIR}")

add_subdirectory(source/client)
add_subdirectory(source/lib)

set(QT_COMPONENTS Core Gui Widgets Sql PrintSupport Network)
