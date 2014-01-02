

add_library(mod_dv SHARED main.cpp trgt_dv.cpp)
target_link_libraries(mod_dv synfig)
target_link_libraries(mod_dv ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_dv DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_dv PROPERTIES PREFIX "")
endif()
