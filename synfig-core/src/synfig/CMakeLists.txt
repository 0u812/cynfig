# === S Y N F I G =========================================================
# **
# **  \legal
# **  Copyright (c) 2013-2014 J Kyle Medley
# **
# **  This package is free software; you can redistribute it and/or
# **  modify it under the terms of the GNU General Public License as
# **  published by the Free Software Foundation; either version 2 of
# **  the License, or (at your option) any later version.
# **
# **  This package is distributed in the hope that it will be useful,
# **  but WITHOUT ANY WARRANTY; without even the implied warranty of
# **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# **  General Public License for more details.
# **  \endlegal
# =========================================================================

set(LAYERHEADERS
    layer_bitmap.h
    layer_composite.h
    layer_duplicate.h
    layer_mime.h
    layer_motionblur.h
    layer_pastecanvas.h
    layer_polygon.h
    layer_shape.h
    layer_solidcolor.h
    layer_skeleton.h)

set(LAYERSOURCES
    layer_bitmap.cpp
    layer_composite.cpp
    layer_duplicate.cpp
    layer_mime.cpp
    layer_motionblur.cpp
    layer_pastecanvas.cpp
    layer_polygon.cpp
    layer_shape.cpp
    layer_solidcolor.cpp
    layer_skeleton.cpp)

set(TARGETHEADERS
    target_multi.h
    target_null.h
    target_null_tile.h
    target_scanline.h
    target_cairo.h
    target_tile.h
    target_cairo_tile.h
    targetparam.h)

set(TARGETSOURCES
    target_multi.cpp
    target_null.cpp
    target_null_tile.cpp
    target_scanline.cpp
    target_cairo.cpp
    target_tile.cpp
    target_cairo_tile.cpp)


set(IMPORTERHEADERS
    listimporter.h
    cairolistimporter.h)

set(IMPORTERSOURCES
    listimporter.cpp
    cairolistimporter.cpp)

set(VALUENODEHEADERS
    valuenode_add.h
    valuenode_and.h
    valuenode_anglestring.h
    valuenode_animated.h
    valuenode_atan2.h
    valuenode_bline.h
    valuenode_blinecalctangent.h
    valuenode_blinecalcvertex.h
    valuenode_blinecalcwidth.h
    valuenode_blinereversetangent.h
    valuenode_compare.h
    valuenode_composite.h
    valuenode_const.h
    valuenode_cos.h
    valuenode_dilist.h
    valuenode_dotproduct.h
    valuenode_duplicate.h
    valuenode_dynamiclist.h
    valuenode_exp.h
    valuenode_gradientcolor.h
    valuenode_gradientrotate.h
    valuenode_greyed.h
    valuenode_integer.h
    valuenode_intstring.h
    valuenode_join.h
    valuenode_linear.h
    valuenode_log.h
    valuenode_not.h
    valuenode_or.h
    valuenode_pow.h
    valuenode_radialcomposite.h
    valuenode_range.h
    valuenode_real.h
    valuenode_realstring.h
    valuenode_reciprocal.h
    valuenode_reference.h
    valuenode_repeat_gradient.h
    valuenode_scale.h
    valuenode_segcalctangent.h
    valuenode_segcalcvertex.h
    valuenode_sine.h
    valuenode_step.h
    valuenode_stripes.h
    valuenode_subtract.h
    valuenode_switch.h
    valuenode_timedswap.h
    valuenode_timeloop.h
    valuenode_timestring.h
    valuenode_twotone.h
    valuenode_vectorangle.h
    valuenode_vectorlength.h
    valuenode_vectorx.h
    valuenode_vectory.h
    valuenode_boneinfluence.h
    valuenode_staticlist.h
    valuenode_bone.h
    valuenode_boneweightpair.h
    valuenode_wplist.h)

set(VALUENODESOURCES
    valuenode_add.cpp
    valuenode_and.cpp
    valuenode_anglestring.cpp
    valuenode_animated.cpp
    valuenode_atan2.cpp
    valuenode_bline.cpp
    valuenode_blinecalctangent.cpp
    valuenode_blinecalcvertex.cpp
    valuenode_blinecalcwidth.cpp
    valuenode_blinereversetangent.cpp
    valuenode_compare.cpp
    valuenode_composite.cpp
    valuenode_const.cpp
    valuenode_cos.cpp
    valuenode_dilist.cpp
    valuenode_dotproduct.cpp
    valuenode_duplicate.cpp
    valuenode_dynamiclist.cpp
    valuenode_exp.cpp
    valuenode_gradientcolor.cpp
    valuenode_gradientrotate.cpp
    valuenode_greyed.cpp
    valuenode_integer.cpp
    valuenode_intstring.cpp
    valuenode_join.cpp
    valuenode_linear.cpp
    valuenode_log.cpp
    valuenode_not.cpp
    valuenode_or.cpp
    valuenode_pow.cpp
    valuenode_radialcomposite.cpp
    valuenode_range.cpp
    valuenode_real.cpp
    valuenode_realstring.cpp
    valuenode_reciprocal.cpp
    valuenode_reference.cpp
    valuenode_repeat_gradient.cpp
    valuenode_scale.cpp
    valuenode_segcalctangent.cpp
    valuenode_segcalcvertex.cpp
    valuenode_sine.cpp
    valuenode_step.cpp
    valuenode_stripes.cpp
    valuenode_subtract.cpp
    valuenode_switch.cpp
    valuenode_timedswap.cpp
    valuenode_timeloop.cpp
    valuenode_timestring.cpp
    valuenode_twotone.cpp
    valuenode_vectorangle.cpp
    valuenode_vectorlength.cpp
    valuenode_vectorx.cpp
    valuenode_vectory.cpp
    valuenode_boneinfluence.cpp
    valuenode_staticlist.cpp
    valuenode_bone.cpp
    valuenode_boneweightpair.cpp
    valuenode_wplist.cpp)

set(VALUEHEADERS
    blinepoint.h
    widthpoint.h
    dashitem.h
    gradient.h
    value.h)

set(VALUESOURCES
    blinepoint.cpp
    widthpoint.cpp
    dashitem.cpp
    gradient.cpp
    value.cpp)

set(SYNFIGHEADERS
    angle.h
    canvasbase.h
    general.h
    guidset.h
    interpolation.h
    protocol.h
    quick_rng.h
    real.h
    releases.h
    segment.h
    smartfile.h
    string.h
    string_decl.h
    surfacenew.h
    types.h
    vector.h
    version.h
    boneweightpair.h
    activepoint.h
    blur.h
    bone.h
    cairo_operators.h
    cairo_renddesc.h
    canvas.h
    color.h
    context.h
    curve_helper.h
    curveset.h
    distance.h
    exception.h
    gamma.h
    guid.h
    importer.h
    cairoimporter.h
    keyframe.h
    layer.h
    loadcanvas.h
    main.h
    module.h
    mutex.h
    node.h
    palette.h
    paramdesc.h
    polynomial_root.h
    rect.h
    renddesc.h
    render.h
    rendermethod.h
    savecanvas.h
    surface.h
    target.h
    time.h
    timepointcollect.h
    transform.h
    uniqueid.h
    valuenode.h
    waypoint.h
    matrix.h
    filesystem.h
    filesystemnative.h
    filesystemgroup.h
    filecontainer.h
    filecontainerzip.h
    filecontainertemporary.h
    zstreambuf.h)

set(SYNFIGSOURCES
    activepoint.cpp
    bone.cpp
    blur.cpp
    cairo_operators.cpp
    cairo_renddesc.cpp
    canvas.cpp
    color.cpp
    context.cpp
    curve_helper.cpp
    curveset.cpp
    distance.cpp
    exception.cpp
    gamma.cpp
    guid.cpp
    importer.cpp
    cairoimporter.cpp
    keyframe.cpp
    layer.cpp
    loadcanvas.cpp
    main.cpp
    module.cpp
    mutex.cpp
    node.cpp
    palette.cpp
    paramdesc.cpp
    polynomial_root.cpp
    rect.cpp
    renddesc.cpp
    render.cpp
    savecanvas.cpp
    surface.cpp
    target.cpp
    time.cpp
    timepointcollect.cpp
    transform.cpp
    uniqueid.cpp
    valuenode.cpp
    waypoint.cpp
    matrix.cpp
    filesystem.cpp
    filesystemnative.cpp
    filesystemgroup.cpp
    filecontainer.cpp
    filecontainerzip.cpp
    filecontainertemporary.cpp
    zstreambuf.cpp)

set(SYNFIG_CORE_SOURCES
    ${VALUEHEADERS}
    ${VALUESOURCES}
    ${LAYERSOURCES}
    ${LAYERHEADERS}
    ${TARGETHEADERS}
    ${TARGETSOURCES}
    ${VALUENODEHEADERS}
    ${VALUENODESOURCES}
    ${SYNFIGHEADERS}
    ${SYNFIGSOURCES}
    ${IMPORTERHEADERS}
    ${IMPORTERSOURCES})

if(SYNFIG_MSVS_TARGET)
    # Boost pulls in additional libraries in the same directory
    link_directories(${SYNFIG_BOOST_LIB_PATH})
endif()

add_library(synfig SHARED ${SYNFIG_CORE_SOURCES})

set_target_properties(synfig
    PROPERTIES VERSION ${SYNFIG_CORE_VER} SOVERSION ${SYNFIG_CORE_MAJOR}
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

if(WITH_ZLIB)
    target_link_libraries(synfig ${LIBZ_LIBRARY})
endif()
if(WITH_MAGICKPP)
    target_link_libraries(synfig ${ImageMagickpp_LIBRARY})
endif()

target_link_libraries(synfig ${SYNFIG_CORE_REQUIRED_LIBRARIES})

install(TARGETS synfig DESTINATION lib)

set(SYNFIG_HEADERS_DIST
    ${SYNFIGHEADERS}
    ${LAYERHEADERS}
    ${TARGETHEADERS}
    ${VALUENODEHEADERS}
    ${IMPORTERHEADERS}
    ${VALUEHEADERS})

install(FILES ${SYNFIG_HEADERS_DIST} DESTINATION include/synfig)
