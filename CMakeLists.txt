cmake_minimum_required(VERSION 2.8.8)
project(mosesdecoder)

# for FindIRSTLM.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")


if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "MMT install prefix" FORCE)
  MESSAGE(STATUS "Install prefix defaulted to ${CMAKE_INSTALL_PREFIX} -- for MMT, you should use cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/MMT")
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


# Set output paths to <MMT>/bin/ and <MMT>/lib/
# ---------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/lib)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# to build shared libmoses.so with KenLM inside (probably needed for KenLM only)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# for KenLMFunctions.cmake
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
find_package(GooglePerftools)  # for libtcmalloc_minimal


add_definitions(-DMAX_NUM_FACTORS=4 -DKENLM_MAX_ORDER=6 -DWITH_THREADS -DBOOST_TEST_DYN_LINK -DPT_UG -DLM_IRST)
# note: MOSES_VERSION_ID is defined in moses/CMakeLists.txt

# "use TRACE_ENABLE to turn off output of any debugging info" (moses/Util.h)
add_definitions(-DTRACE_ENABLE=1)

# . is for #include<moses/...> style includes
include_directories(${Boost_INCLUDE_DIRS} ${IRSTLM_INCLUDE_DIRS} .)

# KenLM
add_subdirectory(util)
add_subdirectory(lm)

set(MOSES_SRC
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

# defines pseudo-libraries (each a group of source files):
# moses_moses moses_tm_ug
add_subdirectory(moses)


add_library(moses SHARED ${MOSES_SRC} $<TARGET_OBJECTS:moses_moses> $<TARGET_OBJECTS:moses_tm_ug> $<TARGET_OBJECTS:kenlm> $<TARGET_OBJECTS:kenlm_util>)
target_link_libraries(moses ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${IRSTLM_LIBRARIES} pthread)

add_executable(moses-main moses-cmd/Main.cpp)
target_link_libraries(moses-main ${Boost_LIBRARIES} ${GooglePerftools_LIBRARIES} moses)
link_directories(${mosesdecoder_BINARY_DIR}/moses)  # link against libmoses.so
