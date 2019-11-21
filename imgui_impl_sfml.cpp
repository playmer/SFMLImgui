#include "imgui.h"
#include "imgui_impl_sfml.h"

// SDL
#include "SFML/Window.hpp"
#include "SFML/Window/Clipboard.hpp"

#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif

//#define SDL_HAS_CAPTURE_AND_GLOBAL_MOUSE    SDL_VERSION_ATLEAST(2,0,4)
//#define SDL_HAS_VULKAN                      SDL_VERSION_ATLEAST(2,0,6)

// Data
//static SDL_Window*  g_Window = NULL;
//static Uint64       g_Time = 0;
static bool         g_MousePressed[3] = { false, false, false };
//static SDL_Cursor*  g_MouseCursors[ImGuiMouseCursor_COUNT] = {};
static std::string g_ClipboardTextData;

static const char* ImGui_ImplSFML_GetClipboardText(void*)
{
	g_ClipboardTextData.assign((char*)sf::Clipboard::getString().toUtf8().c_str());
    return g_ClipboardTextData.c_str();
}

static void ImGui_ImplSFML_SetClipboardText(void*, const char* text)
{
	g_ClipboardTextData = text;
	sf::Clipboard::setString(g_ClipboardTextData);
}

// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
// If you have multiple SDL events and some of them are not meant to be used by dear imgui, you may need to filter events based on their windowID field.
bool ImGui_ImplSFML_ProcessEvent(const sf::Event* event)
{
    ImGuiIO& io = ImGui::GetIO();
    switch (event->type)
    {
		case sf::Event::MouseWheelScrolled:
		{
			if (event->mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) io.MouseWheelH += event->mouseWheelScroll.delta;
			if (event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) io.MouseWheel += event->mouseWheelScroll.delta;
			return true;
		}
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		{
			auto pressed = event->type == sf::Event::MouseButtonPressed;

		    if (event->mouseButton.button == sf::Mouse::Left) io.MouseClicked[0] = pressed;
		    if (event->mouseButton.button == sf::Mouse::Right) io.MouseClicked[1] = pressed;
		    if (event->mouseButton.button == sf::Mouse::Middle) io.MouseClicked[2] = pressed;

		    return true;
		}
		case sf::Event::MouseMoved:
		{
			io.MousePos.x = event->mouseMove.x;
			io.MousePos.y = event->mouseMove.y;
		    return true;
		}
		case sf::Event::TextEntered:
		{
			sf::String temp{ event->text.unicode };
		    io.AddInputCharactersUTF8((const char*)temp.toUtf8().c_str());
		    return true;
		}
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
		{
			auto code = event->key.code;
		    int key = code;
		    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
		    io.KeysDown[key] = (event->type == sf::Event::KeyPressed);
		    io.KeyShift = (sf::Keyboard::LShift == code) || (sf::Keyboard::RShift == code);
			io.KeyCtrl = (sf::Keyboard::LControl == code) || (sf::Keyboard::RControl == code);
		    io.KeyAlt = (sf::Keyboard::LAlt == code) || (sf::Keyboard::RAlt == code);
		    io.KeySuper = (sf::Keyboard::LSystem == code) || (sf::Keyboard::RSystem == code);
		    return true;
		}
    }
    return false;
}

static bool ImGui_ImplSFML_Init(sf::Window* window)
{
    //g_Window = window;
	
    // Setup back-end capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;       // We can honor GetMouseCursor() values (optional)
    //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;        // We can honor io.WantSetMousePos requests (optional, rarely used)
    io.BackendPlatformName = "imgui_impl_sfml";
	
    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
    io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
    io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
    io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
    io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
    io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
    io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
    io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
    io.KeyMap[ImGuiKey_Insert] = sf::Keyboard::Insert;
    io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
    io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
    io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Space;
    io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Enter;
    io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
    io.KeyMap[ImGuiKey_KeyPadEnter] = sf::Keyboard::Return;
    io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
    io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
    io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
    io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
    io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
    io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;
	
    io.SetClipboardTextFn = ImGui_ImplSFML_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplSFML_GetClipboardText;
    io.ClipboardUserData = NULL;
	
    //g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    //g_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    //g_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    //g_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    //g_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    //g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    //g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    //g_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	//
#ifdef _WIN32
    //SDL_SysWMinfo wmInfo;
    //SDL_VERSION(&wmInfo.version);
    //SDL_GetWindowWMInfo(window, &wmInfo);
    //io.ImeWindowHandle = wmInfo.info.win.window;
#else
    //(void)window;
#endif
	//
    //return true;
}

IMGUI_IMPL_API void ImGui_ImplSFML_NewFrame(sf::Window* window)
{
	static sf::Clock sClock;
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");
	
    // Setup display size (every frame to accommodate for window resizing)
	auto size = window->getSize();
	
	int w; 
	int h;
	int display_w; 
	int display_h;

    io.DisplaySize = ImVec2((float)size.x, (float)size.y);
    if (w > 0 && h > 0)
        io.DisplayFramebufferScale = ImVec2((float)size.x, (float)size.y);
	
    // Setup time step (we don't use SDL_GetTicks() because it is using millisecond resolution)
    //static Uint64 frequency = SDL_GetPerformanceFrequency();
    //Uint64 current_time = SDL_GetPerformanceCounter();
	auto elapsedTime = sClock.getElapsedTime().asSeconds();

    io.DeltaTime = elapsedTime > 0 ? elapsedTime : (1.0f / 60.0f);
	sClock.restart();
}
