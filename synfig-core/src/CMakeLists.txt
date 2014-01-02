
# generated header
configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h DESTINATION ${SYNFIG_CORE_INCLUDE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ETL_INCLUDE_PATH})

add_subdirectory(synfig)
# add_subdirectory(modules)
# add_subdirectory(tool)