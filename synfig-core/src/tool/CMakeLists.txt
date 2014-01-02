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

add_executable(synfig ${SYF_TOOL_SOURCES})

target_link_libraries(synfig synfig ${SYNFIG_CORE_REQUIRED_LIBRARIES})