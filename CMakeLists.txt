cmake_minimum_required(VERSION 2.9)
project(wzq-p2p)

aux_source_directory(./src SRC)
include_directories(./include)

add_executable(wzq-p2p ${SRC})
target_link_libraries(wzq-p2p pthread)
