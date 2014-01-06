
set(LAYER_ACTION_HH 
    actions/layeractivate.h
    actions/layeradd.h
    actions/layerduplicate.h
    actions/layerembed.h
    actions/layerencapsulate.h
    actions/layerextract.h
    actions/layerfit.h
    actions/layerlower.h
    actions/layermove.h
    actions/layermakebline.h
    actions/layerparamconnect.h
    actions/layerparamdisconnect.h
    actions/layerparamset.h
    actions/layerparamsetstatic.h
    actions/layerparamunsetstatic.h
    actions/layerraise.h
    actions/layerremove.h
    actions/layersetdesc.h
    actions/layersetexcludefromrendering.h
    actions/layerzdepthrangeset.h)

set(LAYER_ACTION_CC 
    actions/layeractivate.cpp
    actions/layeradd.cpp
    actions/layerduplicate.cpp
    actions/layerembed.cpp
    actions/layerencapsulate.cpp
    actions/layerextract.cpp
    actions/layerfit.cpp
    actions/layerlower.cpp
    actions/layermove.cpp
    actions/layermakebline.cpp
    actions/layerparamconnect.cpp
    actions/layerparamdisconnect.cpp
    actions/layerparamset.cpp
    actions/layerparamsetstatic.cpp
    actions/layerparamunsetstatic.cpp
    actions/layerraise.cpp
    actions/layerremove.cpp
    actions/layersetdesc.cpp
    actions/layersetexcludefromrendering.cpp
    actions/layerzdepthrangeset.cpp)


set(VALUEDESC_ACTION_HH 
    actions/valuedescconnect.h
    actions/valuedescconvert.h
    actions/valuedescdisconnect.h
    actions/valuedescexport.h
    actions/valuedesclink.h
    actions/valuedescblinelink.h
    actions/valuedescset.h
    actions/valuedescsetinterpolation.h
    actions/valuedescremovesmart.h)

set(VALUEDESC_ACTION_CC 
    actions/valuedescconnect.cpp
    actions/valuedescconvert.cpp
    actions/valuedescdisconnect.cpp
    actions/valuedescexport.cpp
    actions/valuedesclink.cpp
    actions/valuedescblinelink.cpp
    actions/valuedescset.cpp
    actions/valuedescsetinterpolation.cpp
    actions/valuedescremovesmart.cpp)


set(VALUENODE_ACTION_HH 
    actions/valuenodeadd.h
    actions/valuenodeconstset.h
    actions/valuenodeconstsetstatic.h
    actions/valuenodeconstunsetstatic.h
    actions/valuenodedynamiclistinsert.h
    actions/valuenodedynamiclistinsertsmart.h
    actions/valuenodedynamiclistloop.h
    actions/valuenodedynamiclistremove.h
    actions/valuenodedynamiclistremovesmart.h
    actions/valuenodedynamiclistrotateorder.h
    actions/valuenodedynamiclistunloop.h
    actions/valuenodestaticlistinsert.h
    actions/valuenodestaticlistinsertsmart.h
    actions/valuenodestaticlistloop.h
    actions/valuenodestaticlistremove.h
    actions/valuenodestaticlistremovesmart.h
    actions/valuenodestaticlistrotateorder.h
    actions/valuenodestaticlistunloop.h
    actions/valuenodelinkconnect.h
    actions/valuenodelinkdisconnect.h
    actions/valuenoderemove.h
    actions/valuenoderename.h
    actions/valuenodereplace.h)

set(VALUENODE_ACTION_CC 
    actions/valuenodeadd.cpp
    actions/valuenodeconstset.cpp
    actions/valuenodeconstsetstatic.cpp
    actions/valuenodeconstunsetstatic.cpp
    actions/valuenodedynamiclistinsert.cpp
    actions/valuenodedynamiclistinsertsmart.cpp
    actions/valuenodedynamiclistloop.cpp
    actions/valuenodedynamiclistremove.cpp
    actions/valuenodedynamiclistremovesmart.cpp
    actions/valuenodedynamiclistrotateorder.cpp
    actions/valuenodedynamiclistunloop.cpp
    actions/valuenodestaticlistinsert.cpp
    actions/valuenodestaticlistinsertsmart.cpp
    actions/valuenodestaticlistloop.cpp
    actions/valuenodestaticlistremove.cpp
    actions/valuenodestaticlistremovesmart.cpp
    actions/valuenodestaticlistrotateorder.cpp
    actions/valuenodestaticlistunloop.cpp
    actions/valuenodelinkconnect.cpp
    actions/valuenodelinkdisconnect.cpp
    actions/valuenoderemove.cpp
    actions/valuenoderename.cpp
    actions/valuenodereplace.cpp)


set(WAYPOINT_ACTION_HH 
    actions/waypointadd.h
    actions/waypointremove.h
    actions/waypointset.h
    actions/waypointsetsmart.h
    actions/waypointsimpleadd.h
    actions/waypointconnect.h
    actions/waypointdisconnect.h)

set(WAYPOINT_ACTION_CC 
    actions/waypointadd.cpp
    actions/waypointremove.cpp
    actions/waypointset.cpp
    actions/waypointsetsmart.cpp
    actions/waypointsimpleadd.cpp
    actions/waypointconnect.cpp
    actions/waypointdisconnect.cpp)


set(TIMEPOINT_ACTION_HH 
    actions/timepointscopy.h
    actions/timepointsdelete.h
    actions/timepointsmove.h
    timegather.h)

set(TIMEPOINT_ACTION_CC 
    actions/timepointscopy.cpp
    actions/timepointsdelete.cpp
    actions/timepointsmove.cpp
    timegather.cpp)


set(ACTIVEPOINT_ACTION_HH 
    actions/activepointadd.h
    actions/activepointremove.h
    actions/activepointset.h
    actions/activepointsetoff.h
    actions/activepointseton.h
    actions/activepointsetsmart.h
    actions/activepointsimpleadd.h)

set(ACTIVEPOINT_ACTION_CC 
    actions/activepointadd.cpp
    actions/activepointremove.cpp
    actions/activepointset.cpp
    actions/activepointsetoff.cpp
    actions/activepointseton.cpp
    actions/activepointsetsmart.cpp
    actions/activepointsimpleadd.cpp)


set(KEYFRAME_ACTION_HH 
    actions/keyframeadd.h
    actions/keyframeduplicate.h
    actions/keyframeremove.h
    actions/keyframetoggl.h
    actions/keyframeset.h
    actions/keyframesetdelta.h
    actions/keyframewaypointset.h)

set(KEYFRAME_ACTION_CC 
    actions/keyframeadd.cpp
    actions/keyframeduplicate.cpp
    actions/keyframeremove.cpp
    actions/keyframetoggl.cpp
    actions/keyframeset.cpp
    actions/keyframesetdelta.cpp
    actions/keyframewaypointset.cpp)


set(CANVAS_ACTION_HH 
    actions/canvasadd.h
    actions/canvasdescriptionset.h
    actions/canvasidset.h
    actions/canvasmetadataerase.h
    actions/canvasmetadataset.h
    actions/canvasnameset.h
    actions/canvasremove.h
    actions/canvasrenddescset.h)

set(CANVAS_ACTION_CC 
    actions/canvasadd.cpp
    actions/canvasdescriptionset.cpp
    actions/canvasidset.cpp
    actions/canvasmetadataerase.cpp
    actions/canvasmetadataset.cpp
    actions/canvasnameset.cpp
    actions/canvasremove.cpp
    actions/canvasrenddescset.cpp)


set(GROUP_ACTION_HH 
    actions/groupaddlayers.h
    actions/groupremove.h
    actions/groupremovelayers.h
    actions/grouprename.h)

set(GROUP_ACTION_CC 
    actions/groupaddlayers.cpp
    actions/groupremove.cpp
    actions/groupremovelayers.cpp
    actions/grouprename.cpp)


set(OTHER_ACTION_HH 
    actions/blinepointtangentmerge.h
    actions/blinepointtangentsplit.h
    actions/colorset.h
    actions/editmodeset.h
    actions/gradientset.h)

set(OTHER_ACTION_CC 
    actions/blinepointtangentmerge.cpp
    actions/blinepointtangentsplit.cpp
    actions/colorset.cpp
    actions/editmodeset.cpp
    actions/gradientset.cpp)


set(ACTIONHH 
    ${ACTIVEPOINT_ACTION_HH}
    ${CANVAS_ACTION_HH}
    ${GROUP_ACTION_HH}
    ${KEYFRAME_ACTION_HH}
    ${LAYER_ACTION_HH}
    ${OTHER_ACTION_HH}
    ${TIMEPOINT_ACTION_HH}
    ${VALUEDESC_ACTION_HH}
    ${VALUENODE_ACTION_HH}
    ${WAYPOINT_ACTION_HH})

set(ACTIONCC 
    ${ACTIVEPOINT_ACTION_CC}
    ${CANVAS_ACTION_CC}
    ${GROUP_ACTION_CC}
    ${KEYFRAME_ACTION_CC}
    ${LAYER_ACTION_CC}
    ${OTHER_ACTION_CC}
    ${TIMEPOINT_ACTION_CC}
    ${VALUEDESC_ACTION_CC}
    ${VALUENODE_ACTION_CC}
    ${WAYPOINT_ACTION_CC})


set(SYNFIGAPPHH 
    editmode.h
    selectionmanager.h
    ${ACTIONHH}
    action.h
    action_param.h
    action_system.h
    blineconvert.h
    wplistconverter.h
    canvasinterface.h
    cvs.h
    inputdevice.h
    instance.h
    main.h
    pluginmanager.h
    settings.h
    uimanager.h
    value_desc.h
    general.h)

set(SYNFIGAPPCC 
    ${ACTIONCC}
    action.cpp
    action_param.cpp
    action_system.cpp
    blineconvert.cpp
    wplistconverter.cpp
    canvasinterface.cpp
    cvs.cpp
    inputdevice.cpp
    instance.cpp
    main.cpp
    pluginmanager.cpp
    settings.cpp
    uimanager.cpp
    value_desc.cpp)

# set(SYNFIG_STUDIO_SOURCES
#     ${VALUEHEADERS}
#     ${VALUESOURCES}
#     ${LAYERSOURCES}
#     ${LAYERHEADERS}
#     ${TARGETHEADERS}
#     ${TARGETSOURCES}
#     ${VALUENODEHEADERS}
#     ${VALUENODESOURCES}
#     ${SYNFIGHEADERS}
#     ${SYNFIGSOURCES}
#     ${IMPORTERHEADERS}
#     ${IMPORTERSOURCES})
# 
add_library(synfigapp SHARED ${SYNFIGAPPCC})

set_target_properties(synfigapp
    PROPERTIES VERSION ${SYNFIG_STUDIO_VER} SOVERSION ${SYNFIG_STUDIO_MAJOR})

target_link_libraries(synfigapp synfig ${GTKmm_LIBRARIES})

install(TARGETS synfigapp DESTINATION lib)
