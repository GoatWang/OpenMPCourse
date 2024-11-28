# export CC=/opt/homebrew/bin/gcc-14
# export CXX=/opt/homebrew/bin/g++-14
# export CC=/opt/homebrew/opt/llvm/bin/clang
# export CXX=/opt/homebrew/opt/llvm/bin/clang++

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)
# set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-14")
# set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

# Project name and language
project(OpenMPTest LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Source files
# set(TOOL_FILES
#     src/tools/tools.cpp
# )

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/libomp/19.1.2")

# Create the executable, linking the source files (https://chatgpt.com/share/66ee33cd-837c-8007-b2a2-308d81ae9f0c) 
# main.cpp       => main.o
add_executable(basic src/basic.cpp ${LZ4_LIBRARY})
add_executable(lesson5_RiemannSum src/lesson5_RiemannSum.cpp)
add_executable(lesson16_linked_dst src/lesson16_linked_dst.cpp)

# # Link libraries
find_package(OpenMP REQUIRED)
target_link_libraries(basic PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(lesson5_RiemannSum PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(lesson16_linked_dst PRIVATE OpenMP::OpenMP_CXX)
# target_link_libraries(main PRIVATE /opt/homebrew/opt/llvm/lib/libomp.dylib)
# target_link_libraries(main PRIVATE /opt/homebrew/Cellar/libomp/19.1.2/lib/libomp.dylib)

find_package(OpenCV REQUIRED)
find_package(PCL 1.12 REQUIRED)
find_package(VTK REQUIRED)
find_package(Vulkan REQUIRED)
target_link_libraries(basic PRIVATE ${OpenCV_LIBS} ${PCL_LIBRARIES} ${VTK_LIBRARIES})
# target_compile_options(main PUBLIC -fopenmp)

# Specify the output directories for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)


# set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
# otool -L main | grep libomp
# /opt/homebrew/opt/llvm/lib/libomp.dylib
# DYLD_PRINT_LIBRARIES=1 ./main
# /opt/homebrew/Cellar/libomp/19.1.2/lib/libomp.dylib

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
# otool -L main | grep libomp
# <empty>
# DYLD_PRINT_LIBRARIES=1 ./main
# /opt/homebrew/Cellar/libomp/19.1.2/lib/libomp.dylib




# DYLD_INSERT_LIBRARIES=/opt/homebrew/opt/llvm/lib/libomp.dylib ./main

# DYLD_LIBRARY_PATH="/opt/homebrew/Cellar/libomp/19.1.2/lib:$DYLD_LIBRARY_PATH" ./main
# DYLD_LIBRARY_PATH="/opt/homebrew/opt/llvm/lib:$DYLD_LIBRARY_PATH" ./main


# unset DYLD_PRINT_LIBRARIES



# link_directories(/opt/homebrew/ellar/libomp/19.1.2/lib)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,/opt/homebrew/Cellar/libomp/19.1.2/lib")
# set(ENV{LDFLAGS} "-L/opt/homebrew/Cellar/libomp/19.1.2/lib")
# set(ENV{CPPFLAGS} "-I/opt/homebrew/Cellar/libomp/19.1.2/lib")
