

add_library(mod_gif SHARED main.cpp trgt_gif.cpp)
target_link_libraries(mod_gif synfig)
target_link_libraries(mod_gif ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_gif DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_gif PROPERTIES PREFIX "")
endif()
