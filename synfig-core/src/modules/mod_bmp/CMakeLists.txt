

add_library(mod_bmp SHARED main.cpp trgt_bmp.cpp mptr_bmp.cpp)
target_link_libraries(mod_bmp synfig)
target_link_libraries(mod_bmp ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_bmp DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_bmp PROPERTIES PREFIX "")
endif()
