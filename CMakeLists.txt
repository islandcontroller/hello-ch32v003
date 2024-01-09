cmake_minimum_required(VERSION 3.20)

#- Project setup ---------------------------------------------------------------
project(hello-ch32v003)

# Language configuration
enable_language(C ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default file endings
set(TARGET_EXECUTABLE_SUFFIX ".elf")
set(TARGET_HEXFILE_SUFFIX ".hex")
set(TARGET_LISTING_SUFFIX ".lst")
set(TARGET_MAPFILE_SUFFIX ".map")
set(CMAKE_EXECUTABLE_SUFFIX ${TARGET_EXECUTABLE_SUFFIX})

#- Common build setup ----------------------------------------------------------
# Toolchain common options
set(MACHINE_OPTIONS
	-march=rv32ec
	-mabi=ilp32e
)

# Processor-specific CSR definitions
file(GLOB COMPILER_CSR_FILE Controller/CH32V003/Core/custom_csr.s)
set(COMPILER_CSR_INCLUDE -include ${COMPILER_CSR_FILE})

# Project-wide compiler options
add_compile_options(
	${MACHINE_OPTIONS}
	
	-fdata-sections
	-ffunction-sections
	-nostartfiles
	
	-Wall
	-Wextra
	
	-O1
	-g

	# Include custom CSR definitions in assembly source
	"$<$<COMPILE_LANGUAGE:ASM>:${COMPILER_CSR_INCLUDE}>"
)
add_compile_definitions(
	-DCH32V003
)
include_directories(
	Controller
	Controller/CH32V003
	Controller/CH32V003/Core
	Controller/CH32V003/Peripheral/inc
	hw_layer
)

# Project-wide linker options
file(GLOB LINKER_FILE Controller/CH32V003/linker_script_ch32v003x4.ld)
cmake_path(REMOVE_FILENAME LINKER_FILE OUTPUT_VARIABLE LINKER_BASEDIR)
cmake_path(GET LINKER_FILE FILENAME LINKER_FILE)
add_link_options(
	-L${LINKER_BASEDIR}
	-T${LINKER_FILE}

	${MACHINE_OPTIONS}

	-specs=nano.specs
	-specs=nosys.specs
	-nostartfiles
	
	-lc
	-lm

	-Wl,--gc-sections
	-Wl,--print-memory-usage
)

#- Target specific setup -------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME})
set(TARGET_ADD_EXECUTABLE_MARKER ${CMAKE_CURRENT_LIST_LINE})
add_executable(${TARGET_NAME})

# Source files
file(GLOB_RECURSE TARGET_SOURCES *.c *.S)
list(FILTER TARGET_SOURCES EXCLUDE REGEX "build\/.*")
list(FILTER TARGET_SOURCES EXCLUDE REGEX "Controller\/.*\/Template\/.*")
target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCES})

# Linker options
target_link_options(${TARGET_NAME} PRIVATE
	-Wl,-Map=${TARGET_NAME}${TARGET_MAPFILE_SUFFIX},--cref
)

# Post-Build: register generated mapfile
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	BYPRODUCTS ${TARGET_NAME}${TARGET_MAPFILE_SUFFIX}
)

# Post-Build: print section sizes
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_SIZE_UTIL} ${TARGET_NAME}${TARGET_EXECUTABLE_SUFFIX}
)

# Post-Build: generate listings
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND echo "Generating listings..."
	COMMAND ${CMAKE_OBJDUMP} -d -S ${TARGET_NAME}${TARGET_EXECUTABLE_SUFFIX} > ${TARGET_NAME}${TARGET_LISTING_SUFFIX}
	BYPRODUCTS ${TARGET_NAME}${TARGET_LISTING_SUFFIX}
)

# Post-Build: generate HEX file
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND echo "Generating HEX file..."
	COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET_NAME}${TARGET_EXECUTABLE_SUFFIX} ${TARGET_NAME}${TARGET_HEXFILE_SUFFIX}
)

# Post-Build: status message
math(EXPR TARGET_DEF_LINE "${TARGET_ADD_EXECUTABLE_MARKER} + 1")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND echo ${CMAKE_CURRENT_LIST_FILE}:${TARGET_DEF_LINE}:1: info: Finished build for target ${TARGET_NAME}.
)