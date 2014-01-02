

add_library(mod_mng SHARED main.cpp trgt_mng.cpp)
target_link_libraries(mod_mng synfig)
target_link_libraries(mod_mng ${MNG_LIBRARY})
target_link_libraries(mod_mng ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_mng DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_mng PROPERTIES PREFIX "")
endif()
