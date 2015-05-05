add_executable( ace_p3d_parser p3d_parser.cpp)
target_link_libraries(ace_p3d_parser ace_common)
add_dependencies(ace_p3d_parser ace_common)
SET_TARGET_PROPERTIES(ace_p3d_parser PROPERTIES PREFIX "")
set_target_properties(ace_p3d_parser PROPERTIES FOLDER Tests)

add_executable( ace_pbo_search pbo_search.cpp)
add_dependencies(ace_pbo_search ace_common)
target_link_libraries(ace_pbo_search ace_common)
SET_TARGET_PROPERTIES(ace_pbo_search PROPERTIES PREFIX "")
set_target_properties(ace_pbo_search PROPERTIES FOLDER Tests)

add_executable( ace_vd_ext_test vd_ext_test.cpp)
add_dependencies(ace_vd_ext_test ace_common ace_vd_static)
target_link_libraries(ace_vd_ext_test ace_vd_static ace_common ${BULLET_LIBS})
SET_TARGET_PROPERTIES(ace_vd_ext_test PROPERTIES PREFIX "")
set_target_properties(ace_vd_ext_test PROPERTIES FOLDER Tests)

if(USE_DIRECTX)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
    find_package (DirectX REQUIRED)
    link_directories (BEFORE ${DirectX_D3DX11_LIBRARY})
    include_directories (BEFORE ${DirectX_D3DX11_INCLUDE_DIR} )
    
    add_executable( ace_test_render test_render.cpp test_render.hpp)
    target_link_libraries(ace_test_render ace_common ${BULLET_LIBS} 
        ${DirectX_D3DX11_LIBRARY} ${DirectX_D3D11_LIBRARY} ${DirectX_D3D11_1_LIBRARY} ${DirectX_D3D11_2_LIBRARY})
    add_dependencies(ace_test_render ace_common)
    SET_TARGET_PROPERTIES(ace_test_render PROPERTIES PREFIX "")
    set_target_properties(ace_test_render PROPERTIES FOLDER Tests)
    
    add_executable( ace_dxtk_test dxtk_test.cpp)
    target_link_libraries(ace_dxtk_test ace_common directxtk ${BULLET_LIBS} 
        ${DirectX_D3DX11_LIBRARY} ${DirectX_D3D11_LIBRARY} ${DirectX_D3D11_1_LIBRARY} ${DirectX_D3D11_2_LIBRARY})
    add_dependencies(ace_dxtk_test ace_common directxtk)
    SET_TARGET_PROPERTIES(ace_dxtk_test PROPERTIES PREFIX "")
    set_target_properties(ace_dxtk_test PROPERTIES FOLDER Tests)
endif()

add_custom_command(TARGET ace_vd_ext_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:ace_vd>/ace_vd.dll"
        $<TARGET_FILE_DIR:ace_vd_ext_test>
)
       
add_custom_command(TARGET ace_vd_ext_test PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove -f "$<TARGET_FILE_DIR:ace_vd_ext_test>/ace_vd.dll"
)
        