cmake_minimum_required(VERSION 3.10)

project(torodofi VERSION 0.9 LANGUAGES CXX)

set(SOURCE_MAIN torodofi.cpp)
set(SOURCE_ALL torodofi/App.cpp torodofi/types.cpp torodofi/logic.cpp torodofi/Config/Config.cpp torodofi/Tasks/Task.cpp torodofi/Tasks/TaskContainer.cpp)

add_executable(torodofi ${SOURCE_MAIN} ${SOURCE_ALL})
include_directories(torodofi PRIVATE torodofi)

install(TARGETS torodofi)
