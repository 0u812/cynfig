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
set_target_properties(siftool PROPERTIES OUTPUT_NAME synfig)
target_link_libraries(siftool synfig ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS siftool DESTINATION bin)

# -- IMAGES --------------------------------------------------------

set(SYNFIG_IMAGES "")

macro (add_image sif time output)
    add_custom_command(OUTPUT ${output}.png COMMAND synfig -q ${SYNFIG_SOURCE_IMAGES_DIR}/${sif}.sif -o ${output}.png --time ${time} DEPENDS siftool)
    list(APPEND SYNFIG_IMAGES ${output}.png)
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${output}.png DESTINATION ${SYNFIG_DATA_PATH}/pixmaps/synfigstudio)
endmacro (add_image)

set(IMAGES
#     installer_logo.bmp
    installer_logo_osx
    clear_redo_icon
    clear_undo_icon
    reset_colors_icon
    swap_colors_icon
    select_all_child_layers_icon
    sif_icon
    synfig_icon
    saveall_icon
    about_icon
    splash_screen-0.64.1
    valuenode_icon
    duplicate_icon
    group_icon
   
#     keyframe_lock_past_on_icon
#     keyframe_lock_past_off_icon
#     keyframe_lock_future_on_icon
#     keyframe_lock_future_off_icon
   
#     animate_seek_next_keyframe_icon
#     animate_seek_prev_keyframe_icon
#     animate_seek_next_frame_icon
#     animate_seek_prev_frame_icon
#     animate_seek_begin_icon
#     animate_seek_end_icon
#     animate_play_icon
#     animate_stop_icon
#     animate_pause_icon
#     animate_loop_icon
#     animate_mode_off_icon
#     animate_mode_on_icon
   
    rename_icon
    set_fill_color
    set_outline_color
    duck_position_icon
    duck_vertex_icon
    duck_tangent_icon
    duck_radius_icon
    duck_width_icon
    duck_angle_icon
    show_grid_icon
    snap_grid_icon
    onion_skin_icon
    incr_resolution_icon
    decr_resolution_icon
    render_options_icon
    preview_options_icon
    action_set_layer_description_icon
    action_add_to_set_icon
    action_remove_from_set_icon
    action_export_icon
    action_unexport_icon
    action_flat_interpolation_icon
    action_interpolate_interpolation_icon
    action_peak_interpolation_icon
    action_rounded_interpolation_icon
    action_squared_interpolation_icon
   
#     interpolation_type_tcb_icon
#     interpolation_type_ease_icon
#     interpolation_type_const_icon
#     interpolation_type_linear_icon
#     interpolation_type_clamped_icon
#     valuenode_forbidanimation_icon
   
    layer_blur_blur_icon
    layer_blur_motion_icon
    layer_blur_radial_icon
    layer_distortion_curvewarp_icon
    layer_distortion_insideout_icon
    layer_distortion_noise_icon
    layer_distortion_spherize_icon
    layer_distortion_stretch_icon
    layer_distortion_twirl_icon
    layer_distortion_warp_icon
    layer_example_filledrectangle_icon
    layer_example_metaballs_icon
    layer_example_simplecircle_icon
    layer_filter_clamp_icon
    layer_filter_colorcorrect_icon
    layer_filter_halftone2_icon
    layer_filter_halftone3_icon
    layer_filter_lumakey_icon
    layer_fractal_julia_icon
    layer_fractal_mandelbrot_icon
    layer_geometry_checkerboard_icon
    layer_geometry_circle_icon
    layer_geometry_outline_icon
    layer_geometry_advanced_outline_icon
    layer_geometry_polygon_icon
    layer_geometry_rectangle_icon
    layer_geometry_region_icon
    layer_geometry_solidcolor_icon
    layer_geometry_star_icon
    layer_gradient_conical_icon
    layer_gradient_curve_icon
    layer_gradient_lineal_icon
    layer_gradient_noise_icon
    layer_gradient_radial_icon
    layer_gradient_spiral_icon
    layer_other_duplicate_icon
#     layer_other_importimage_icon
    layer_other_group_icon
    layer_other_plant_icon
    layer_other_stroboscope_icon
    layer_other_supersample_icon
    layer_other_skeleton_icon
    layer_other_text_icon
    layer_other_timeloop_icon
    layer_other_xorpattern_icon
    layer_stylize_bevel_icon
    layer_stylize_shade_icon
    layer_transform_rotate_icon
    layer_transform_scale_icon
    layer_transform_translate_icon
   
    tool_spline_icon
    tool_circle_icon
    tool_draw_icon
    tool_eyedrop_icon
    tool_fill_icon
    tool_gradient_icon
    tool_mirror_icon
    tool_normal_icon
    tool_polyline_icon
    tool_rectangle_icon
    tool_rotate_icon
    tool_scale_icon
    tool_sketch_icon
    tool_smooth_move_icon
    tool_star_icon
    tool_text_icon
    tool_width_icon
    tool_zoom_icon
   
    type_angle_icon
    type_splinepoint_icon
    type_bool_icon
    type_canvas_icon
    type_color_icon
    type_gradient_icon
    type_integer_icon
    type_list_icon
    type_real_icon
    type_segment_icon
    type_string_icon
    type_time_icon
    type_vector_icon
   
#     canvas_icon
    library_icon
    graphs_icon
    set_icon
    history_icon
    info_icon
    keyframe_icon
    layer_icon
    meta_data_icon
    navigator_icon
    palette_icon
    parameters_icon
    time_track_icon)

foreach(image ${IMAGES})
    add_image(${image} 0 ${image})
endforeach()

# keyframe lock
add_image(keyframe_lock_icons 0 keyframe_lock_past_on_icon)
add_image(keyframe_lock_icons 1 keyframe_lock_past_off_icon)
add_image(keyframe_lock_icons 2 keyframe_lock_future_on_icon)
add_image(keyframe_lock_icons 3 keyframe_lock_future_off_icon)

# framedial icons
add_image(framedial_icons 0 animate_seek_next_keyframe_icon)
add_image(framedial_icons 1 animate_seek_prev_keyframe_icon)
add_image(framedial_icons 2 animate_seek_next_frame_icon)
add_image(framedial_icons 3 animate_seek_prev_frame_icon)
add_image(framedial_icons 4 animate_seek_begin_icon)
add_image(framedial_icons 5 animate_seek_end_icon)
add_image(framedial_icons 6 animate_play_icon)
add_image(framedial_icons 7 animate_stop_icon)
add_image(framedial_icons 8 animate_pause_icon)
add_image(framedial_icons 9 animate_loop_icon)

# animate mode icons
add_image(animate_mode_icons 0 animate_mode_off_icon)
add_image(animate_mode_icons 1 animate_mode_on_icon)

# interpolation type
add_image(interpolation_type_icons 1 interpolation_type_tcb_icon)
add_image(interpolation_type_icons 2 interpolation_type_linear_icon)
add_image(interpolation_type_icons 3 interpolation_type_ease_icon)
add_image(interpolation_type_icons 4 interpolation_type_const_icon)
add_image(interpolation_type_icons 5 interpolation_type_clamped_icon)
add_image(interpolation_type_icons 7 valuenode_forbidanimation_icon)

# canvas & import image
add_image(canvas_and_importimage_icons 2 canvas_icon)
add_image(canvas_and_importimage_icons 1 layer_other_importimage_icon)



add_custom_target(images ALL DEPENDS ${SYNFIG_IMAGES})