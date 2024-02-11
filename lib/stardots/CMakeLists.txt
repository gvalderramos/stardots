set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_library(StarDots ${LIB_SRC_FILES}
        core/node.cpp
        core/node.h
        core/plug.h
        core/node_manager.cpp
        core/node_manager.h
        stardots.h)

target_sources(StarDots PUBLIC FILE_SET HEADERS FILES ${LIB_INC_FILES})

install(TARGETS
        StarDots
        RUNTIME           # Following options apply to runtime artifacts.
        COMPONENT Runtime
        LIBRARY           # Following options apply to library artifacts.
        COMPONENT Runtime
        NAMELINK_COMPONENT Development
        ARCHIVE           # Following options apply to archive artifacts.
        COMPONENT Development
        DESTINATION lib/static
        FILE_SET HEADERS  # Following options apply to file set HEADERS.
        COMPONENT Development
)