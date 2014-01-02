

add_library(mod_ffmpeg SHARED main.cpp mptr_ffmpeg.cpp trgt_ffmpeg.cpp)
target_link_libraries(mod_ffmpeg synfig)
target_link_libraries(mod_ffmpeg ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_ffmpeg DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_ffmpeg PROPERTIES PREFIX "")
endif()
