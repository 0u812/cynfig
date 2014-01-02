

add_library(mod_openexr SHARED main.cpp mptr_openexr.cpp trgt_openexr.cpp)
target_link_libraries(mod_openexr synfig)
target_link_libraries(mod_openexr ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_openexr DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_openexr PROPERTIES PREFIX "")
endif()
