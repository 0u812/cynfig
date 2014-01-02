

add_library(lyr_freetype SHARED main.cpp lyr_freetype.cpp)
target_link_libraries(lyr_freetype synfig)
target_link_libraries(lyr_freetype ${FREETYPE2_LIBRARY})
if(WITH_FONTCONFIG)
    target_link_libraries(lyr_freetype ${FONTCONFIG_LIBRARY})
endif()
target_link_libraries(lyr_freetype ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS lyr_freetype DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(lyr_freetype PROPERTIES PREFIX "")
endif()
