#pragma once

namespace sf
{
    class Window;
    class Event;
}

//IMGUI_IMPL_API bool ImGui_ImplSFML_InitForOpenGL(sf::Window* window);
//IMGUI_IMPL_API bool ImGui_ImplSFML_InitForVulkan(sf::Window* window);
//IMGUI_IMPL_API bool ImGui_ImplSFML_InitForD3D(sf::Window* window);
//IMGUI_IMPL_API void ImGui_ImplSFML_Shutdown();
IMGUI_IMPL_API void ImGui_ImplSFML_NewFrame(sf::Window* window);
IMGUI_IMPL_API bool ImGui_ImplSFML_ProcessEvent(const sf::Event* event);