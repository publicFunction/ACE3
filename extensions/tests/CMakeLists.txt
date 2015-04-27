add_executable( ace_p3d_parser p3d_parser.cpp)
target_link_libraries(ace_p3d_parser ace_common)
SET_TARGET_PROPERTIES(ace_p3d_parser PROPERTIES PREFIX "")

add_executable( ace_pbo_search pbo_search.cpp)
target_link_libraries(ace_pbo_search ace_common)
SET_TARGET_PROPERTIES(ace_pbo_search PROPERTIES PREFIX "")
