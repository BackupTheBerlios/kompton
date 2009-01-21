project(kompton)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

include_directories(${KDE4_INCLUDES})

set(kompton_SRCS
	main.cpp
	diagramview.cpp
	node.cpp
	ownscene.cpp
)

kde4_add_executable(kompton ${kompton_SRCS})
target_link_libraries(kompton ${KDE4_KDEUI_LIBS})

install(TARGETS kompton ${INSTALL_TARGETS_DEFAULT_ARGS})
