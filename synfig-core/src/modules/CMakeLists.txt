
set(SYNFIG_MODULES_REMOVE_PREFIX 0 CACHE BOOL "Remove lib prefix from loadable modules where applicable")

add_subdirectory(mod_particle)
add_subdirectory(mod_filter)
add_subdirectory(mod_yuv420p)
add_subdirectory(mod_gif)
add_subdirectory(mod_gradient)
add_subdirectory(mod_geometry)
add_subdirectory(mod_noise)
# if(WITH_LIBAVCODEC)
#     add_subdirectory(mod_libavcodec)
# endif()
# add_subdirectory(mod_jpeg)
if(WITH_OPENEXR)
    add_subdirectory(mod_openexr)
endif()
add_subdirectory(mod_bmp)
add_subdirectory(mod_ppm)
if(WITH_PNG)
    add_subdirectory(mod_png)
endif()
if(WITH_LIBDV)
    add_subdirectory(mod_dv)
endif()

if(MAGICK_CONVERT)
    add_subdirectory(mod_imagemagick)
endif()

if(WITH_FFMPEG)
    add_subdirectory(mod_ffmpeg)
endif()

if(WITH_FREETYPE2)
    add_subdirectory(lyr_freetype)
endif()

add_subdirectory(lyr_std)

if(WITH_MNG)
    add_subdirectory(mod_mng)
endif()

add_subdirectory(mod_svg)

if(WITH_MAGICKPP)
    add_subdirectory(mod_magickpp)
endif()

add_subdirectory(mod_example)

# So the tool can generate the images/icons online
configure_file(synfig_modules.cfg ${CMAKE_CURRENT_BINARY_DIR}/../tool/synfig_modules.cfg COPYONLY)
# Actually install the modules config
install(FILES synfig_modules.cfg DESTINATION ${SYNFIG_MODULES_DIR})
