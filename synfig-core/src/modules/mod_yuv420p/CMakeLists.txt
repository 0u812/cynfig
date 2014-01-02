

add_library(mod_yuv420p SHARED main.cpp trgt_yuv.cpp)
target_link_libraries(mod_yuv420p synfig)
target_link_libraries(mod_yuv420p ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_yuv420p DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_yuv420p PROPERTIES PREFIX "")
endif()
