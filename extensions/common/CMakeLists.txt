file(GLOB_RECURSE ACE_COMMON_SOURCES *.h *.hpp *.c *.cpp)
add_library(ace_common STATIC ${ACE_COMMON_SOURCES})
