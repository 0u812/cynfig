

add_library(mod_noise SHARED random_noise.cpp distort.cpp noise.cpp valuenode_random.cpp main.cpp)
target_link_libraries(mod_noise synfig)
target_link_libraries(mod_noise ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_noise DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_noise PROPERTIES PREFIX "")
endif()
