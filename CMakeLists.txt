cmake_minimum_required(VERSION 3.2)
project(cdna_node)

# setup build directory
set(CFLAGS -m64)
set(CXXFLAGS -m64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup header files
include_directories(/usr/local/include/sphinxbase/)
include_directories(/usr/local/include/pocketsphinx/)
include_directories(/usr/include/sphinxbase/)

# setup libraries
link_directories(/usr/lib/)
link_directories(/usr/local/lib/)

# setup source files
file(GLOB NODE_SOURCE_FILES ./src/node/*)
file(GLOB NODE_CORE_SOURCE_FILES ./src/node-core/*)
file(GLOB NODE_TEXT_SOURCE_FILES ./src/node-text/*)
file(GLOB NODE_SPEAKER_SOURCE_FILES ./src/node-speaker/*)
file(GLOB NODE_MICRO_SOURCE_FILES ./src/node-micro/*)

# define libaries
add_library(cdna-node SHARED ${NODE_SOURCE_FILES})

# define executable file
add_executable(cdna-node-core ${NODE_CORE_SOURCE_FILES})
add_executable(cdna-node-text ${NODE_TEXT_SOURCE_FILES})
add_executable(cdna-node-speaker ${NODE_SPEAKER_SOURCE_FILES})
add_executable(cdna-node-micro ${NODE_MICRO_SOURCE_FILES})

# link libraries
target_link_libraries(cdna-node-core cdna-node)
target_link_libraries(cdna-node-text cdna-node)
target_link_libraries(cdna-node-speaker cdna-node)
list(APPEND SHELL_MICRO_LIBS libsphinxbase.so.3 libpocketsphinx.so.3 libpulse.so libpulse-simple.so libsphinxad.so)
target_link_libraries(cdna-node-micro cdna-node ${SHELL_MICRO_LIBS})

# copy specifition files
file(GLOB SPEC_FILES ./src/spec/*.spec)
file(REMOVE ${CMAKE_BINARY_DIR}/bin/*.spec)
file(COPY ${SPEC_FILES} DESTINATION ${CMAKE_BINARY_DIR}/bin)