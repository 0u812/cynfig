

add_library(mod_ppm SHARED main.cpp trgt_ppm.cpp mptr_ppm.cpp)
target_link_libraries(mod_ppm synfig)
target_link_libraries(mod_ppm ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_ppm DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_ppm PROPERTIES PREFIX "")
endif()
