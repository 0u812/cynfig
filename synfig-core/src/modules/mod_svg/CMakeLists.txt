

add_library(mod_svg SHARED main.cpp layer_svg.cpp svg_parser.cpp)
target_link_libraries(mod_svg synfig)
target_link_libraries(mod_svg ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_svg DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_svg PROPERTIES PREFIX "")
endif()
