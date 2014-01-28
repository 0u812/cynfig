set(SYF_TOOL_HEADERS
    named_type.h
    definitions.h
    progress.h
    renderprogress.h
    job.h
    synfigtoolexception.h
    printing_functions.h
    optionsprocessor.h
    joblistprocessor.h)

set(SYF_TOOL_SOURCES
    printing_functions.cpp
    optionsprocessor.cpp
    joblistprocessor.cpp
    main.cpp)

add_executable(siftool ${SYF_TOOL_SOURCES})
target_link_libraries(siftool synfig ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS siftool DESTINATION bin)

# -- IMAGES --------------------------------------------------------

set(SYNFIG_IMAGES "")

macro (add_image sif time output)
    add_custom_command(OUTPUT ${output}.png COMMAND siftool -q ${SYNFIG_SOURCE_IMAGES_DIR}/${sif}.sif -o ${output}.png --time ${time})
    list(APPEND SYNFIG_IMAGES ${output}.png)
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${output}.png DESTINATION share/pixmaps)
endmacro (add_image)

add_image(keyframe_lock_icons 0 keyframe_lock_past_on_icon)

add_custom_target(images ALL DEPENDS ${SYNFIG_IMAGES})