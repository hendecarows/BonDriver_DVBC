# cmake version
cmake_minimum_required(VERSION 3.5)

# C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# no prefix "lib" library
set(CMAKE_SHARED_LIBRARY_PREFIX_CXX "")

# package
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# library file
add_library(
	${PROJECT_NAME}
	SHARED
	BonDriver_DVBC.cpp
	TSMF.cpp
	crc32.cpp
)

# compiler option
set(COMPILER_FLAGS_GNU -Wall -Wextra -pedantic -Wno-psabi -Wno-unused-parameter -Wno-ignored-qualifiers)
set(COMPILER_FLAGS_CLANG -Wall -Wextra -Wno-unused-parameter -Wno-ignored-qualifiers)

target_compile_options(
	${PROJECT_NAME}
	PRIVATE	$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:${COMPILER_FLAGS_GNU}>
	PRIVATE	$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:${COMPILER_FLAGS_GNU}>
)

# linker option
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE Threads::Threads
	PRIVATE m
)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION lib/edcb)
