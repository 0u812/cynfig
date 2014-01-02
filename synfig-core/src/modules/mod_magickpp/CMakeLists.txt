

add_library(mod_magickpp SHARED main.cpp trgt_magickpp.cpp)
target_link_libraries(mod_magickpp synfig)
target_link_libraries(mod_magickpp ${MAGICKPP_LIBRARY})
target_link_libraries(mod_magickpp ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_magickpp DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_magickpp PROPERTIES PREFIX "")
endif()
