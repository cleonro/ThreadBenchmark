cmake_minimum_required(VERSION 3.5)

project(ThreadBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(SourceFiles
#    main.cpp
#    controller.cpp
#    )

file(GLOB_RECURSE SourceFiles "Cpp/*.cpp")
file(GLOB_RECURSE HeaderFiles "Cpp/*.h")

message("Source files: " ${SourceFiles})
message("Header files: " ${HeaderFiles})

add_custom_target(Headers SOURCES ${HeaderFiles})
add_executable(ThreadBenchmark ${SourceFiles})
target_link_libraries(ThreadBenchmark pthread)


