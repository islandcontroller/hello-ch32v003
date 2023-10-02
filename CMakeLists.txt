cmake_minimum_required(VERSION 3.20)

# Toolchain configuration
set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_CONFIGS_PATH}/gcc-riscv-none-embed.cmake)

# Project configuration: executable name, linker script
project(hello-ch32v003)
set(EXECUTABLE ${PROJECT_NAME}.elf)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/Controller/CH32V003/linker_script_ch32v003x4.ld)

# General compiler configuration
enable_language(C ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# All ".c" and ".S" files selected as sources, excluding "Template" folder
file(GLOB_RECURSE SRC_FILES *.c *.S)
list(FILTER SRC_FILES EXCLUDE REGEX "build\/.*")
list(FILTER SRC_FILES EXCLUDE REGEX "Controller\/.*\/Template\/.*\.c")

# Add all sources to target executable
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines (-D)
target_compile_definitions(${EXECUTABLE} PRIVATE
        -DCH32V003
)

# List of include directories (-I)
target_include_directories(${EXECUTABLE} PRIVATE
        Controller
        Controller/CH32V003
        Controller/CH32V003/Core
        Controller/CH32V003/Peripheral/inc
        hw_layer
)

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
        # Machine configuration
        -march=rv32ec
        -mabi=ilp32e

        # Generate sections for symbols
        -fdata-sections
        -ffunction-sections
        -funwind-tables

        # Compiler warnings
        -Wall
        -Wextra
        
        # Optimisation strategy and debug options
        -Og
        -g

        # Include custom CSR definitions in assembly source
        $<$<COMPILE_LANGUAGE:ASM>:-include ${CMAKE_SOURCE_DIR}/Controller/CH32V003/Core/custom_csr.s>
)

# Linker options
cmake_path(GET LINKER_FILE FILENAME LINKER_FILE_FILENAME)
cmake_path(REMOVE_FILENAME LINKER_FILE OUTPUT_VARIABLE LINKER_FILE_FOLDER)
target_link_options(${EXECUTABLE} PRIVATE
        -L${LINKER_FILE_FOLDER}
        -T${LINKER_FILE_FILENAME}

        # Machine configuration (match compiler)
        -march=rv32ec
        -mabi=ilp32e

        # Linker specs
        -specs=nano.specs
        -specs=nosys.specs
        -nostartfiles

        # Discard unused sections
        -Wl,--gc-sections
        
        # Generate mapfile and print memory usage
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Xlinker -print-memory-usage
)

# Output code and data section size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE}
)

# Generate flash-able hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
)