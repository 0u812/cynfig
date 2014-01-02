

add_library(mod_filter SHARED blur.cpp colorcorrect.cpp halftone2.cpp lumakey.cpp radialblur.cpp main.cpp halftone.cpp halftone3.cpp)
target_link_libraries(mod_filter synfig)
target_link_libraries(mod_filter ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_filter DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_filter PROPERTIES PREFIX "")
endif()
