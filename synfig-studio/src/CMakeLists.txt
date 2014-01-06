
# generated header
configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h DESTINATION ${SYNFIG_STUDIO_INCLUDE_PATH})
add_definitions(-DHAVE_CONFIG_H)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ETL_INCLUDE_PATH})

add_subdirectory(synfigapp)
# add_subdirectory(gui)
