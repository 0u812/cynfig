set(SYNFIG_STUDIO_REQUIRED_SRC main.cpp)

set(ACTION_MANAGERS_HH
    actionmanagers/groupactionmanager.h
    actionmanagers/keyframeactionmanager.h
    actionmanagers/layeractionmanager.h)

set(ACTION_MANAGERS_CC
    actionmanagers/groupactionmanager.cpp
    actionmanagers/keyframeactionmanager.cpp
    actionmanagers/layeractionmanager.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${ACTION_MANAGERS_HH}
    ${ACTION_MANAGERS_CC})

set(CELLRENDERER_HH
    cellrenderer/cellrenderer_gradient.h
    cellrenderer/cellrenderer_time.h
    cellrenderer/cellrenderer_timetrack.h
    cellrenderer/cellrenderer_value.h)

set(CELLRENDERER_CC
    cellrenderer/cellrenderer_gradient.cpp
    cellrenderer/cellrenderer_time.cpp
    cellrenderer/cellrenderer_timetrack.cpp
    cellrenderer/cellrenderer_value.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${CELLRENDERER_HH}
    ${CELLRENDERER_CC})

set(DIALOGS_HH
    dialogs/about.h
    dialogs/canvasoptions.h
    dialogs/canvasproperties.h
    dialogs/dialog_color.h
    dialogs/dialog_gradient.h
    dialogs/dialog_keyframe.h
    dialogs/dialog_preview.h
    dialogs/dialog_setup.h
    dialogs/dialog_soundselect.h
    dialogs/dialog_targetparam.h
    dialogs/dialog_waypoint.h)

set(DIALOGS_CC
    dialogs/about.cpp
    dialogs/canvasoptions.cpp
    dialogs/canvasproperties.cpp
    dialogs/dialog_color.cpp
    dialogs/dialog_gradient.cpp
    dialogs/dialog_keyframe.cpp
    dialogs/dialog_preview.cpp
    dialogs/dialog_setup.cpp
    dialogs/dialog_soundselect.cpp
    dialogs/dialog_targetparam.cpp
    dialogs/dialog_waypoint.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${DIALOGS_HH}
    ${DIALOGS_CC})

set(DIALS_HH
    dials/zoomdial.h
    dials/framedial.h
    dials/keyframedial.h
    dials/toggleducksdial.h
    dials/resolutiondial.h)

set(DIALS_CC
    dials/zoomdial.cpp
    dials/framedial.cpp
    dials/keyframedial.cpp
    dials/toggleducksdial.cpp
    dials/resolutiondial.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${DIALS_HH}
    ${DIALS_CC})

set(DOCKS_HH
    docks/dialog_tooloptions.h
    docks/dock_canvases.h
    docks/dock_canvasspecific.h
    docks/dock_children.h
    docks/dock_curves.h
    docks/dock_history.h
    docks/dock_info.h
    docks/dock_keyframes.h
    docks/dock_layergroups.h
    docks/dock_layers.h
    docks/dock_metadata.h
    docks/dock_navigator.h
    docks/dock_params.h
    docks/dock_timetrack.h
    docks/dock_toolbox.h
    docks/dockable.h
    docks/dockbook.h
    docks/dockdialog.h
    docks/dockdroparea.h
    docks/dockmanager.h)

set(DOCKS_CC
    docks/dialog_tooloptions.cpp
    docks/dock_canvases.cpp
    docks/dock_canvasspecific.cpp
    docks/dock_children.cpp
    docks/dock_curves.cpp
    docks/dock_history.cpp
    docks/dock_info.cpp
    docks/dock_keyframes.cpp
    docks/dock_layergroups.cpp
    docks/dock_layers.cpp
    docks/dock_metadata.cpp
    docks/dock_navigator.cpp
    docks/dock_params.cpp
    docks/dock_timetrack.cpp
    docks/dock_toolbox.cpp
    docks/dockable.cpp
    docks/dockbook.cpp
    docks/dockdialog.cpp
    docks/dockdroparea.cpp
    docks/dockmanager.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${DOCKS_HH}
    ${DOCKS_CC})

set(PALETTE_HH
    modules/mod_palette/dock_palbrowse.h
    modules/mod_palette/dock_paledit.h
    modules/mod_palette/mod_palette.h)

set(PALETTE_CC
    modules/mod_palette/dock_palbrowse.cpp
    modules/mod_palette/dock_paledit.cpp
    modules/mod_palette/mod_palette.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${PALETTE_HH}
    ${PALETTE_CC})

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    modules/module.h
    modules/module.cpp)

set(STATES_HH
    states/state_bline.h
    states/state_circle.h
    states/state_draw.h
    states/state_eyedrop.h
    states/state_fill.h
    states/state_gradient.h
    states/state_mirror.h
    states/state_normal.h
    states/state_polygon.h
    states/state_rectangle.h
    states/state_rotate.h
    states/state_scale.h
    states/state_sketch.h
    states/state_smoothmove.h
    states/state_star.h
    states/state_stroke.h
    states/state_text.h
    states/state_width.h
    states/state_zoom.h)

set(STATES_CC
    states/state_bline.cpp
    states/state_circle.cpp
    states/state_draw.cpp
    states/state_eyedrop.cpp
    states/state_fill.cpp
    states/state_gradient.cpp
    states/state_mirror.cpp
    states/state_normal.cpp
    states/state_polygon.cpp
    states/state_rectangle.cpp
    states/state_rotate.cpp
    states/state_scale.cpp
    states/state_sketch.cpp
    states/state_smoothmove.cpp
    states/state_star.cpp
    states/state_stroke.cpp
    states/state_text.cpp
    states/state_width.cpp
    states/state_zoom.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${STATES_HH}
    ${STATES_CC})

set(TREEVIEW_HH
    trees/childrentree.h
    trees/keyframetree.h
    trees/layergrouptree.h
    trees/layertree.h
    trees/metadatatree.h)

set(TREEVIEW_CC
    trees/childrentree.cpp
    trees/keyframetree.cpp
    trees/layergrouptree.cpp
    trees/layertree.cpp
    trees/metadatatree.cpp)

set(TREESTORE_HH
    trees/canvastreestore.h
    trees/childrentreestore.h
    trees/historytreestore.h
    trees/keyframetreestore.h
    trees/layergrouptreestore.h
    trees/layerparamtreestore.h
    trees/layertreestore.h
    trees/metadatatreestore.h)

set(TREESTORE_CC
    trees/canvastreestore.cpp
    trees/childrentreestore.cpp
    trees/historytreestore.cpp
    trees/keyframetreestore.cpp
    trees/layergrouptreestore.cpp
    trees/layerparamtreestore.cpp
    trees/layertreestore.cpp
    trees/metadatatreestore.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${TREEVIEW_HH}
    ${TREEVIEW_CC}
    ${TREESTORE_HH}
    ${TREESTORE_CC})

set(WIDGETS_HH
    widgets/widget_canvaschooser.h
    widgets/widget_color.h
    widgets/widget_coloredit.h
    widgets/widget_compselect.h
    widgets/widget_curves.h
    widgets/widget_defaults.h
    widgets/widget_distance.h
    widgets/widget_enum.h
    widgets/widget_filename.h
    widgets/widget_gradient.h
    widgets/widget_sound.h
    widgets/widget_time.h
    widgets/widget_timeslider.h
    widgets/widget_value.h
    widgets/widget_vector.h
    widgets/widget_waypoint.h
    widgets/widget_waypointmodel.h
    widgets/widget_keyframe_list.h
    widgets/widget_bonechooser.h)

set(WIDGETS_CC
    widgets/widget_canvaschooser.cpp
    widgets/widget_color.cpp
    widgets/widget_coloredit.cpp
    widgets/widget_compselect.cpp
    widgets/widget_curves.cpp
    widgets/widget_defaults.cpp
    widgets/widget_distance.cpp
    widgets/widget_enum.cpp
    widgets/widget_filename.cpp
    widgets/widget_gradient.cpp
    widgets/widget_sound.cpp
    widgets/widget_time.cpp
    widgets/widget_timeslider.cpp
    widgets/widget_value.cpp
    widgets/widget_vector.cpp
    widgets/widget_waypoint.cpp
    widgets/widget_waypointmodel.cpp
    widgets/widget_keyframe_list.cpp
    widgets/widget_bonechooser.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${WIDGETS_HH}
    ${WIDGETS_CC})

set(WORKAREARENDERER_HH
    workarearenderer/renderer_background.h
    workarearenderer/renderer_bbox.h
    workarearenderer/renderer_canvas.h
    workarearenderer/renderer_dragbox.h
    workarearenderer/renderer_ducks.h
    workarearenderer/renderer_grid.h
    workarearenderer/renderer_guides.h
    workarearenderer/renderer_timecode.h
    workarearenderer/renderer_bonesetup.h
    workarearenderer/workarearenderer.h)

set(WORKAREARENDERER_CC
    workarearenderer/renderer_background.cpp
    workarearenderer/renderer_bbox.cpp
    workarearenderer/renderer_canvas.cpp
    workarearenderer/renderer_dragbox.cpp
    workarearenderer/renderer_ducks.cpp
    workarearenderer/renderer_grid.cpp
    workarearenderer/renderer_guides.cpp
    workarearenderer/renderer_timecode.cpp
    workarearenderer/renderer_bonesetup.cpp
    workarearenderer/workarearenderer.cpp)

list( APPEND SYNFIG_STUDIO_REQUIRED_SRC
    ${WORKAREARENDERER_CC}
    ${WORKAREARENDERER_HH})

    
set(DUCKTRANSFORM_HH
    ducktransform_rotate.h
    ducktransform_scale.h
    ducktransform_translate.h
    ducktransform_matrix.h
    ducktransform_origin.h
    duck.h)

set(DUCKTRANSFORM_CC
    duck.cpp)

set(EVENTS_HH
    event_keyboard.h
    event_layerclick.h
    event_mouse.h)

set(OTHER_HH
    compview.h
    eventkey.h
    smach.h
    adjust_window.h
    app.h
    asyncrenderer.h
    audiocontainer.h
    autorecover.h
    canvasview.h
    devicetracker.h
    dialogsettings.h
    duckmatic.h
    general.h
    iconcontroller.h
    instance.h
    ipc.h
    keymapsettings.h
    onemoment.h
    preview.h
    renddesc.h
    render.h
    splash.h
    statemanager.h
    valuelink.h
    workarea.h
    mainwindow.h)

set(OTHER_CC
    adjust_window.cpp
    app.cpp
    asyncrenderer.cpp
    audiocontainer.cpp
    autorecover.cpp
    canvasview.cpp
    devicetracker.cpp
    dialogsettings.cpp
    duckmatic.cpp
    iconcontroller.cpp
    instance.cpp
    ipc.cpp
    keymapsettings.cpp
    onemoment.cpp
    preview.cpp
    renddesc.cpp
    render.cpp
    splash.cpp
    statemanager.cpp
    valuelink.cpp
    workarea.cpp
    mainwindow.cpp)
    
set(SYNFIG_STUDIO_SOURCES
    ${}
    ${DUCKTRANSFORM_CC}
    ${OTHER_CC})