cmake_minimum_required(VERSION 2.8.8)
project(mosesdecoder)

# for FindIRSTLM.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")


# Set install prefix to use <MMT>/bin/ and <MMT>/lib/
# ---------------------------------------------------
#
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "MMT install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


# Set output paths to <MMT>/bin/ and <MMT>/lib/
# ---------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/lib)



# maybe Decoder (using C++11) needs to link vs. C++11 stuff???
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# to build shared libmoses.so with KenLM inside (probably needed for KenLM only)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# for KenLMFunctions.cmake
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/KenLMFunctions.cmake)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS
  system
  thread
  filesystem
  unit_test_framework
  program_options
  iostreams
)

find_package(ZLIB REQUIRED)
find_package(IRSTLM REQUIRED)

# note: this one should only apply to a single source file. 
# moses/Parameter.cpp:460:16: error: ‘MOSES_VERSION_ID’ was not declared in this scope
# TODO: the others should NOT recompile when we have a new revision.
#execute_process(COMMAND git describe --dirty OUTPUT_VARIABLE MOSES_VERSION_ID OUTPUT_STRIP_TRAILING_WHITESPACE)

# see also https://ccache.samba.org/

# TODO: these should be on the moses level, they should not affect kenlm, ideally...
add_definitions(-DMAX_NUM_FACTORS=4 -DKENLM_MAX_ORDER=6 -DWITH_THREADS -DBOOST_TEST_DYN_LINK -DPT_UG -DLM_IRST)
# -DMOSES_VERSION_ID="${MOSES_VERSION_ID}"

# TODO: this should come from a find_package(irstlm)
# alas, IRSTLM does not define irstlm-config.cmake nor is there FindIRSTLM.cmake
# lazyness wins me this time.
#
# this points to the MMT/include folder now.
#set(IRSTLM_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../../include/")
#set(IRSTLM_LIBRARIES "${CMAKE_SOURCE_DIR}/../../lib/libirstlm.so")

# . is for #include<moses/...> style includes
include_directories(${Boost_INCLUDE_DIRS} ${IRSTLM_INCLUDE_DIRS} .)

# KenLM
add_subdirectory(util)
add_subdirectory(lm)

set(MOSES_SRC
moses-cmd/Main.cpp
phrase-extract/PhraseOrientation.cpp
search/edge_generator.cc
search/nbest.cc
search/rule.cc
search/vertex.cc

# MMT specific: disable syntax decoding, unused phrase tables, unused features
contrib/other-builds/mmt/FF/Factory.cpp
contrib/other-builds/mmt/IOWrapper.cpp
contrib/other-builds/mmt/TranslationTask.cpp
)

# defines pseudo-library (group of source files) moses_moses
add_subdirectory(moses)

# to do: above source files should be mentioned in their subdirectories.
# and then, e.g., add_subdirectory(TranslationModel/UG), ...



#add_executable(moses-main ${MOSES_SRC} $<TARGET_OBJECTS:moses_moses> $<TARGET_OBJECTS:kenlm> $<TARGET_OBJECTS:kenlm_util>)
#target_link_libraries(moses-main ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${IRSTLM_LIBRARIES} pthread)

add_library(moses SHARED ${MOSES_SRC} $<TARGET_OBJECTS:moses_moses> $<TARGET_OBJECTS:kenlm> $<TARGET_OBJECTS:kenlm_util>)
target_link_libraries(moses ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${IRSTLM_LIBRARIES} pthread)

add_executable(moses-main moses-cmd/Main.cpp)
target_link_libraries(moses-main ${Boost_LIBRARIES} moses)
link_directories(${mosesdecoder_BINARY_DIR}/moses)
