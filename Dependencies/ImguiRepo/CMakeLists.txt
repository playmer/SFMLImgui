add_library(imgui STATIC)

target_sources(imgui
    PRIVATE
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/imgui)


add_library(imgui_opengl3 STATIC)

target_sources(imgui_opengl3
    PRIVATE
        imgui/examples/imgui_impl_opengl3.cpp
        imgui/examples/imgui_impl_opengl3.h
)

if (NOT TARGET imgui)
 MESSAGE(ooooohhhhhh nnnnnnnoooooooooooooo)
endif()

target_link_libraries(imgui_opengl3
    PUBLIC 
        imgui
        glbinding
)

target_compile_definitions(imgui_opengl3 
    PUBLIC 
        IMGUI_IMPL_OPENGL_LOADER_CUSTOM="glbinding/gl/gl.h"
)

target_include_directories(imgui_opengl3 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/imgui/examples)
