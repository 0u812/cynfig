

add_library(mod_imagemagick SHARED main.cpp mptr_imagemagick.cpp trgt_imagemagick.cpp)
target_link_libraries(mod_imagemagick synfig)
target_link_libraries(mod_imagemagick ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_imagemagick DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_imagemagick PROPERTIES PREFIX "")
endif()
