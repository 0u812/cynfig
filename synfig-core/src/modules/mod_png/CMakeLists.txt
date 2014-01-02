

add_library(mod_png SHARED main.cpp trgt_png.cpp trgt_cairo_png.cpp mptr_png.cpp mptr_cairo_png.cpp)
target_link_libraries(mod_png synfig)
target_link_libraries(mod_png ${PNG_LIBRARY})
target_link_libraries(mod_png ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_png DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_png PROPERTIES PREFIX "")
endif()
