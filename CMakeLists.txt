cmake_minimum_required(VERSION 2.8.8)
project(mosesdecoder)

# for FindIRSTLM.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")


if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "MMT install prefix" FORCE)
    MESSAGE(STATUS "Install prefix defaulted to ${CMAKE_INSTALL_PREFIX} -- for MMT, you should use cmake -DCMAKE_INSTALL_PREFIX=/home/ubuntu/MMT")
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


# Set output paths to <MMT>/bin/ and <MMT>/lib/
# ---------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/lib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# to build shared libmoses.so with KenLM inside (probably needed for KenLM only)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# for KenLMFunctions.cmake
include(cmake/KenLMFunctions.cmake)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED COMPONENTS
        system
        thread
        filesystem
        unit_test_framework
        program_options
        iostreams
        )

find_package(ZLIB REQUIRED)
find_package(GooglePerftools)  # for libtcmalloc_minimal

if (USE_IRSTLM)
    find_package(IRSTLM REQUIRED)
    add_definitions(-DLM_IRST)
endif (USE_IRSTLM)

add_definitions(-DHAVE_ZLIB=1)
#add_definitions(-DMAX_NUM_FACTORS=4 -DKENLM_MAX_ORDER=6 -DWITH_THREADS -DBOOST_TEST_DYN_LINK -DPT_UG)
add_definitions(-DMAX_NUM_FACTORS=4 -DKENLM_MAX_ORDER=6 -DWITH_THREADS -DPT_UG)
# note: MOSES_VERSION_ID is defined in moses/CMakeLists.txt

# "use TRACE_ENABLE to turn off output of any debugging info" (moses/Util.h)
add_definitions(-DTRACE_ENABLE=1)

# . is for #include<moses/...> style includes
include_directories(${Boost_INCLUDE_DIRS} .)

if (USE_IRSTLM)
    include_directories(${IRSTLM_INCLUDE_DIRS})
endif (USE_IRSTLM)

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


add_library(moses STATIC ${MOSES_SRC} $<TARGET_OBJECTS:moses_moses> $<TARGET_OBJECTS:moses_tm_ug> $<TARGET_OBJECTS:kenlm> $<TARGET_OBJECTS:kenlm_util>)
target_link_libraries(moses ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} pthread)

if (USE_IRSTLM)
    target_link_libraries(moses ${IRSTLM_LIBRARIES})
endif (USE_IRSTLM)

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBRARIES OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(moses-main moses-cmd/Main.cpp)
target_link_libraries(moses-main moses ${Boost_LIBRARIES} ${GooglePerftools_LIBRARIES})
link_directories(${mosesdecoder_BINARY_DIR}/moses)  # link against libmoses.so

# Mert
add_subdirectory(mert)

set(MMSAPT_EXECUTABLES ptable-lookup ptable-lookup-corpus check-coverage3)

foreach (exe ${MMSAPT_EXECUTABLES})
    add_executable(${exe} moses/TranslationModel/UG/${exe}.cc)
    target_link_libraries(${exe} ${Boost_LIBRARIES} ${GooglePerftools_LIBRARIES} moses)
endforeach (exe)
