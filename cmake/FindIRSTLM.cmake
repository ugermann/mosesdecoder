# - Try to find IRSTLM
# Once done this will define
#  IRSTLM_FOUND
#  IRSTLM_INCLUDE_DIRS
#  IRSTLM_LIBRARIES

# MMT builds mosesdecoder in <MMT>/vendor/moses and install prefix is <MMT>, so
# we expect IRSTLM headers to be in <MMT>/include
#
# can either use CMAKE_SOURCE_DIR which will be <MMT> if built on that level, and
#   <MMT>/vendor/moses if only mosesdecoder is built.
#
# or, we can use PROJECT_SOURCE_DIR which should always point to <MMT>/vendor/moses
#   for the mosesdecoder project.
#
find_path(IRSTLM_INCLUDE_DIRS lmContainer.h
          HINTS "${PROJECT_SOURCE_DIR}/../../include/")

find_library(IRSTLM_LIBRARIES NAMES irstlm libirstlm
             HINTS "${PROJECT_SOURCE_DIR}/../../lib/")

# find_path(Moses_LIBRARIES build/lib/${CMAKE_SHARED_LIBRARY_PREFIX}moses${CMAKE_SHARED_LIBRARY_SUFFIX} PATHS ENV MOSESDECODER_HOME)
#mark_as_advanced(LIBXML2_INCLUDE_DIR LIBXML2_LIBRARY )

if (IRSTLM_LIBRARIES STREQUAL "IRSTLM_LIBRARIES-NOTFOUND")
  message(FATAL_ERROR "Could not locate IRSTLM shared library.")
else()
  set(IRSTLM_FOUND TRUE)
endif()
