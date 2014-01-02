

add_library(mod_gradient SHARED curvegradient.cpp lineargradient.cpp conicalgradient.cpp spiralgradient.cpp radialgradient.cpp main.cpp)
target_link_libraries(mod_gradient synfig)
target_link_libraries(mod_gradient ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_gradient DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_gradient PROPERTIES PREFIX "")
endif()
