set(ACE_EXTENSION_NAME "ace_p3d_parser")

file(GLOB SOURCES *.h *.hpp *.c *.cpp)
add_executable( ${ACE_EXTENSION_NAME} ${SOURCES})
target_link_libraries(${ACE_EXTENSION_NAME} ace_common)
SET_TARGET_PROPERTIES(${ACE_EXTENSION_NAME} PROPERTIES PREFIX "")

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()