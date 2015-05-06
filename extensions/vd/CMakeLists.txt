set(ACE_EXTENSION_NAME "ace_vd")

file(GLOB SOURCES *.h *.hpp *.c *.cpp)
file(GLOB PENETRATION_SOURCES penetration/*.h penetration/*.hpp penetration/*.c penetration/*.cpp)

SOURCE_GROUP("main" FILES ${SOURCES})
SOURCE_GROUP("penetration models" FILES ${PENETRATION_SOURCES})

add_library( ${ACE_EXTENSION_NAME} SHARED ${SOURCES} ${PENETRATION_SOURCES} ${GLOBAL_SOURCES})
add_library( ${ACE_EXTENSION_NAME}_static STATIC ${SOURCES} ${PENETRATION_SOURCES} ${GLOBAL_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(USE_BULLET)
    set(LINK_LIBS ${BULLET_LIBS})
else()
    message(FATAL_ERROR "Bullet is required for vehicle damage!\nYou need to build out the bullet3 folder and define -DUSE_BULLET=On")
endif()

if(DEVEL AND USE_DIRECTX)
   set(LINK_LIBS directxtk ${LINK_LIBS} ${DirectX_D3DX11_LIBRARY} ${DirectX_D3D11_LIBRARY} ${DirectX_D3D11_1_LIBRARY} ${DirectX_D3D11_2_LIBRARY})
else()
   set(LINK_LIBS ${LINK_LIBS})
endif()

target_link_libraries(${ACE_EXTENSION_NAME} ace_common ${LINK_LIBS})
set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES PREFIX "")
set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES FOLDER vehicledamage)

target_link_libraries(${ACE_EXTENSION_NAME}_static ace_common ${LINK_LIBS})
set_target_properties(${ACE_EXTENSION_NAME}_static PROPERTIES PREFIX "")
set_target_properties(${ACE_EXTENSION_NAME}_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(${ACE_EXTENSION_NAME}_static PROPERTIES FOLDER vehicledamage)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${ACE_EXTENSION_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
