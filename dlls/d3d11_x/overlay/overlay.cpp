/*
================================================================================
DISCLAIMER AND LICENSE REQUIREMENT

This code is provided with the condition that if you use, modify, or distribute
this code in your project, you are required to make your project open source
under a license compatible with the GNU General Public License (GPL) or a
similarly strong copyleft license.

By using this code, you agree to:
1. Disclose your complete source code of any project incorporating this code.
2. Include this disclaimer in any copies or substantial portions of this file.
3. Provide clear attribution to the original author.

If you do not agree to these terms, you do not have permission to use this code.

================================================================================
*/
#include "overlay.h"
#define IMGUI_USE_WCHAR32
#include "../../../thirdparty/imgui/imgui.h"
#include "../../../thirdparty/imgui/backends/imgui_impl_dx11.h"
#include "../../../thirdparty/imgui_impl_uwp.h"
#include <Xinput.h>
#include <winrt/windows.graphics.display.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
#pragma comment(lib, "xinput.lib")

extern char g_KeyboardText[ 256 ];
extern HANDLE g_KeyboardFinished;

wd::Overlay::Overlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, IDXGISwapChain1* pSwapchain)
    : m_pDevice(pDevice), m_pContext(pContext), m_pSwapchain(pSwapchain), m_pRenderTargetView(nullptr), m_bKeyboard(false)
{
}

wd::Overlay::~Overlay( )
{
    Shutdown( );
    m_pDevice = nullptr;
    m_pContext = nullptr;
    m_pSwapchain = nullptr;
}
void SetupImGuiKeyboardInputUWP( );
ImGuiKey MapVirtualKeyToImGuiKey(winrt::Windows::System::VirtualKey key);

void wd::Overlay::Initialize( )
{
    g_KeyboardFinished = CreateEventA(NULL, FALSE, FALSE, "KeyboardFinished");

    ID3D11Texture2D* pBackBuffer = nullptr;
    m_pSwapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    if (pBackBuffer) pBackBuffer->Release( );

    IMGUI_CHECKVERSION( );
    ImGui::CreateContext( );
    ImGuiIO& io = ImGui::GetIO( );
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImFont* mainFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 18.0f);

    ImFontConfig config;
    config.MergeMode = true;

    static const ImWchar icon_ranges[] = { 0xE000, 0xF8FF, 0 };
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segmdl2.ttf", 25.0f, &config, icon_ranges);

    // 3️⃣ Build the font atlas
    io.Fonts->Build( );
    ImGui::StyleColorsDark( );

    ImGui_ImplUwp_InitForCurrentView( );
    ImGui_ImplDX11_Init(m_pDevice, m_pContext);
    SetupImGuiKeyboardInputUWP( );
}




void SetupImGuiKeyboardInputUWP( )
{
    CoreWindow window = CoreWindow::GetForCurrentThread( );

    window.KeyDown(TypedEventHandler<CoreWindow, KeyEventArgs>(
        [](CoreWindow const&, KeyEventArgs const& args)
        {
            ImGuiKey key = MapVirtualKeyToImGuiKey(args.VirtualKey( ));
            if (key != ImGuiKey_None)
                ImGui::GetIO( ).AddKeyEvent(key, true);
        }));

    window.KeyUp(TypedEventHandler<CoreWindow, KeyEventArgs>(
        [](CoreWindow const&, KeyEventArgs const& args)
        {
            ImGuiKey key = MapVirtualKeyToImGuiKey(args.VirtualKey( ));
            if (key != ImGuiKey_None)
                ImGui::GetIO( ).AddKeyEvent(key, false);
        }));

    window.CharacterReceived(TypedEventHandler<CoreWindow, CharacterReceivedEventArgs>(
        [](CoreWindow const&, CharacterReceivedEventArgs const& args)
        {
            ImGui::GetIO( ).AddInputCharacter(static_cast<unsigned int>(args.KeyCode( )));
        }));
}
ImGuiKey MapVirtualKeyToImGuiKey(VirtualKey key)
{
    switch (key)
    {
    case VirtualKey::Tab: return ImGuiKey_Tab;
    case VirtualKey::Enter: return ImGuiKey_Enter;
    case VirtualKey::Escape: return ImGuiKey_Escape;
    case VirtualKey::Back: return ImGuiKey_Backspace;
    case VirtualKey::Space: return ImGuiKey_Space;
    case VirtualKey::Left: return ImGuiKey_LeftArrow;
    case VirtualKey::Right: return ImGuiKey_RightArrow;
    case VirtualKey::Up: return ImGuiKey_UpArrow;
    case VirtualKey::Down: return ImGuiKey_DownArrow;

    case VirtualKey::A: return ImGuiKey_A;
    case VirtualKey::B: return ImGuiKey_B;
    case VirtualKey::C: return ImGuiKey_C;
    case VirtualKey::D: return ImGuiKey_D;
    case VirtualKey::E: return ImGuiKey_E;
    case VirtualKey::F: return ImGuiKey_F;
    case VirtualKey::G: return ImGuiKey_G;
    case VirtualKey::H: return ImGuiKey_H;
    case VirtualKey::I: return ImGuiKey_I;
    case VirtualKey::J: return ImGuiKey_J;
    case VirtualKey::K: return ImGuiKey_K;
    case VirtualKey::L: return ImGuiKey_L;
    case VirtualKey::M: return ImGuiKey_M;
    case VirtualKey::N: return ImGuiKey_N;
    case VirtualKey::O: return ImGuiKey_O;
    case VirtualKey::P: return ImGuiKey_P;
    case VirtualKey::Q: return ImGuiKey_Q;
    case VirtualKey::R: return ImGuiKey_R;
    case VirtualKey::S: return ImGuiKey_S;
    case VirtualKey::T: return ImGuiKey_T;
    case VirtualKey::U: return ImGuiKey_U;
    case VirtualKey::V: return ImGuiKey_V;
    case VirtualKey::W: return ImGuiKey_W;
    case VirtualKey::X: return ImGuiKey_X;
    case VirtualKey::Y: return ImGuiKey_Y;
    case VirtualKey::Z: return ImGuiKey_Z;

    case VirtualKey::Number0: return ImGuiKey_0;
    case VirtualKey::Number1: return ImGuiKey_1;
    case VirtualKey::Number2: return ImGuiKey_2;
    case VirtualKey::Number3: return ImGuiKey_3;
    case VirtualKey::Number4: return ImGuiKey_4;
    case VirtualKey::Number5: return ImGuiKey_5;
    case VirtualKey::Number6: return ImGuiKey_6;
    case VirtualKey::Number7: return ImGuiKey_7;
    case VirtualKey::Number8: return ImGuiKey_8;
    case VirtualKey::Number9: return ImGuiKey_9;

    default: return ImGuiKey_None;
    }
}

void wd::Overlay::Shutdown( )
{
    if (m_pRenderTargetView)
    {
        m_pRenderTargetView->Release( );
        m_pRenderTargetView = nullptr;
    }

    ImGui_ImplDX11_Shutdown( );
    ImGui_ImplUwp_Shutdown( );
    ImGui::DestroyContext( );
}

void wd::Overlay::EnableKeyboard( )
{
    m_bKeyboard = true;
}

void wd::Overlay::UpdateXInput( )
{
    XINPUT_STATE state = {};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        ImGuiIO& io = ImGui::GetIO( );

#define GAMEPAD_KEY(key, condition) io.AddKeyEvent(ImGuiKey_##key, (condition))

        // Digital buttons
        GAMEPAD_KEY(GamepadDpadUp, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
        GAMEPAD_KEY(GamepadDpadDown, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
        GAMEPAD_KEY(GamepadDpadLeft, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
        GAMEPAD_KEY(GamepadDpadRight, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
        GAMEPAD_KEY(GamepadFaceDown, state.Gamepad.wButtons & XINPUT_GAMEPAD_A);      // Accept
        GAMEPAD_KEY(GamepadFaceRight, state.Gamepad.wButtons & XINPUT_GAMEPAD_B);      // Cancel
        GAMEPAD_KEY(GamepadStart, state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
        GAMEPAD_KEY(GamepadBack, state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);

#undef GAMEPAD_KEY

        // Left analog stick as analog navigation
        const float deadzone = static_cast<float>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        const float maxValue = 32767.0f;

        float lx = static_cast<float>(state.Gamepad.sThumbLX);
        float ly = static_cast<float>(state.Gamepad.sThumbLY);

        float normX = 0.0f;
        float normY = 0.0f;

        if (fabsf(lx) > deadzone)
            normX = (fabsf(lx) - deadzone) / (maxValue - deadzone) * (lx > 0 ? 1.0f : -1.0f);
        if (fabsf(ly) > deadzone)
            normY = (fabsf(ly) - deadzone) / (maxValue - deadzone) * (ly > 0 ? 1.0f : -1.0f);

        normX = std::clamp(normX, -1.0f, 1.0f);
        normY = std::clamp(normY, -1.0f, 1.0f);

        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickLeft, normX < 0.0f, -normX);
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickRight, normX > 0.0f, normX);
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickUp, normY > 0.0f, normY); // Y+ is up
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickDown, normY < 0.0f, -normY);
    }
}


void wd::Overlay::Present( )
{
    UpdateXInput( );
    ImGui_ImplDX11_NewFrame( );
    ImGui_ImplUwp_NewFrame( );
    ImGui::NewFrame( );

    if (m_bKeyboard)
        RenderKeyboardWindow( );

    ImGui::Render( );
    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData( ));
}

static int cursorPos = 0;

void wd::Overlay::RenderKeyboardWindow()
{
    static bool isUppercase = false;
    static bool isSymbols = false;

    const char* keys[] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", "'",
        "Z", "X", "C", "V", "B", "N", "M", ",", ".", "?"
    };

    const char* symbols[] = {
        "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
        "~", "`", "|", "\\", "{", "}", "[", "]", ":", ";", "\"", "'",
        "<", ">", "?", "/", ",", ".", "=", "-"
    };

    const char** currentKeys = isSymbols ? symbols : keys;

    ImGuiIO& io = ImGui::GetIO( );
    ImVec2 displaySize = ImGui::GetIO( ).DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(displaySize.x / 2, displaySize.y / 2), ImGuiCond_Always);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0x05, 0x05, 0x05, 0xFF));
    ImGui::Begin("Keyboard", nullptr, windowFlags);

    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x37, 0x37, 0x37, 0xFF));
    ImGui::PushItemWidth(-FLT_MIN);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0x05, 0x05, 0x05, 0xFF));
    ImGui::InputText("", g_KeyboardText, IM_ARRAYSIZE(g_KeyboardText), ImGuiInputTextFlags_CallbackAlways,
    [](ImGuiInputTextCallbackData* data) -> int {
        data->CursorPos = cursorPos;
        return 0;
    });
    ImGui::PopStyleColor( );
    ImGui::PopItemWidth();

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3, 3));

    if (ImGui::Button("##symb", ImVec2(60, 30)))
        isSymbols = !isSymbols;

    ImVec2 pos = ImGui::GetItemRectMin( );
    ImVec2 size = ImGui::GetItemRectSize( );

    if (!isSymbols) {
        ImVec2 textSize = ImGui::CalcTextSize("#+=");
        ImGui::GetWindowDrawList( )->AddText(
            ImGui::GetFont( ), ImGui::GetFontSize( ),
            ImVec2((pos.x + (size.x - textSize.x) * 0.5f) - 10, pos.y + (size.y - textSize.y) * 0.5f),
            IM_COL32(255, 255, 255, 255),
            "#+="
        );
    } else {
        ImVec2 textSize = ImGui::CalcTextSize("ABC");
        ImGui::GetWindowDrawList( )->AddText(
            ImGui::GetFont( ), ImGui::GetFontSize( ),
            ImVec2((pos.x + (size.x - textSize.x) * 0.5f) - 10, pos.y + (size.y - textSize.y) * 0.5f),
            IM_COL32(255, 255, 255, 255),
            "ABC"
        );
    }

    ImVec2 iconSize = ImGui::CalcTextSize("\xEF\x84\x8A");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 12,
        ImVec2((pos.x + (size.x - iconSize.x) * 0.5f) + 18, (pos.y + (size.y - iconSize.y) * 0.5f) + 8),
        IM_COL32(255, 255, 255, 255),
        "\xEF\x84\x8A"
    );
        
    ImGui::SameLine();
    RenderKeyboardRow(currentKeys, 0, 10, isUppercase);

    ImGui::PopStyleVar( );
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 3));
    ImGui::SameLine( );
    if (ImGui::Button("##del", ImVec2(60, 30)) ||
        ImGui::IsKeyPressed(ImGuiKey_Backspace) ||
        ImGui::IsKeyPressed(ImGuiKey_GamepadFaceLeft)) {
        size_t len = strlen(g_KeyboardText);
        if (len > 0)
            g_KeyboardText[ len - 1 ] = '\0';
    }
    ImVec2 posa = ImGui::GetItemRectMin( );
    ImVec2 sizea = ImGui::GetItemRectSize( );

    ImVec2 textSizea = ImGui::CalcTextSize("\xEE\x9D\x90");

    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ),
        14,
        ImVec2((posa.x + (sizea.x - textSizea.x) * 0.5f) - 6, (posa.y + (sizea.y - textSizea.y) * 0.5f) + 7),
        IM_COL32(255, 255, 255, 255),
        "\xEE\x9D\x90"
    );

    textSizea = ImGui::CalcTextSize("\xEF\x82\x96");

    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ),
        10,
        ImVec2((posa.x + (sizea.x - textSizea.x) * 0.5f) + 18, (posa.y + (sizea.y - textSizea.y) * 0.5f) + 8),
        IM_COL32(0, 149, 209, 255),
        "\xEF\x82\x96"
    );
    ImGui::PopStyleVar( );
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3, 3));

    if (ImGui::Button("##bac", ImVec2(60.0f, 63)) ||
        ImGui::IsKeyPressed(ImGuiKey_LeftShift) ||
        ImGui::IsKeyPressed(ImGuiKey_GamepadL1))
        cursorPos = max(0, cursorPos - 1);

    pos = ImGui::GetItemRectMin( );
    size = ImGui::GetItemRectSize( );

    ImFont* bigFont = ImGui::GetFont( );
    float bigFontSize = 18.0f;
    ImVec2 bigTextSize = ImGui::CalcTextSize("\xEE\xA5\xAF");
    ImGui::GetWindowDrawList( )->AddText(
        bigFont, bigFontSize,
        ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) - 3, pos.y + 18),
        IM_COL32(255, 255, 255, 255),
        "\xEE\x80\x8E"
    );

    ImFont* smallFont = bigFont;
    float smallFontSize = 14.0f;
    ImVec2 smallTextSize = ImGui::CalcTextSize("\xEF\x84\x8C");
    ImGui::GetWindowDrawList( )->AddText(
        smallFont, smallFontSize,
        ImVec2(pos.x + (size.x - smallTextSize.x) * 0.5f, pos.y + 26 + bigTextSize.y),
        IM_COL32(255, 255, 255, 255),
        "\xEF\x84\x8C"
    );

    ImGui::SameLine();
    ImVec2 currPos = ImGui::GetCursorPos( );
    RenderKeyboardRow(currentKeys, 10, 20, isUppercase);

    ImGui::PopStyleVar( );
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 3));
    ImGui::SameLine( );
    ImGui::SetWindowFontScale(1.5f);
    if (ImGui::Button("##for", ImVec2(60.0f, 63)))
        cursorPos++;

    pos = ImGui::GetItemRectMin( );
    size = ImGui::GetItemRectSize( );

    bigTextSize = ImGui::CalcTextSize("\xEE\x80\x8F");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 18,
        ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) + 6, pos.y + 18),
        IM_COL32(255, 255, 255, 255),
        "\xEE\x80\x8F"
    );

    smallTextSize = ImGui::CalcTextSize("\xEF\x84\x8D");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 14,
        ImVec2((pos.x + (size.x - smallTextSize.x) * 0.5f) + 8, pos.y + 20 + bigTextSize.y),
        IM_COL32(255, 255, 255, 255),
        "\xEF\x84\x8D"
    );
    ImGui::SetWindowFontScale(1.0f);

    ImGui::PopStyleVar( );
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3, 3));

    ImVec2 row2Pos = ImGui::GetCursorPos( );
    row2Pos.x = currPos.x;
    row2Pos.y -= 33;
    ImGui::SetCursorPos(row2Pos);
    if (!isSymbols) RenderKeyboardRow(currentKeys, 20, 30, isUppercase);
    else            RenderKeyboardRow(currentKeys, 20, 30, isUppercase);

    if (ImGui::Button("##upper", ImVec2(60.0f, 63)))
        isUppercase = !isUppercase;

    pos = ImGui::GetItemRectMin( );
    size = ImGui::GetItemRectSize( );

    if (!isUppercase) {
        bigTextSize = ImGui::CalcTextSize("\xEE\x9D\x92");
        ImGui::GetWindowDrawList( )->AddText(
            ImGui::GetFont( ), 18,
            ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) - 3, pos.y + 18),
            IM_COL32(255, 255, 255, 255),
            "\xEE\x9D\x92"
        );
    } else {
        bigTextSize = ImGui::CalcTextSize("\xEE\xA2\x96");
        ImGui::GetWindowDrawList( )->AddText(
            ImGui::GetFont( ), 18,
            ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) - 3, pos.y + 18),
            IM_COL32(255, 255, 255, 255),
            "\xEE\xA2\x96"
        );
    }

    smallTextSize = ImGui::CalcTextSize("\xEF\x84\x88");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 14,
        ImVec2(pos.x + (size.x - smallTextSize.x) * 0.5f, pos.y + 26 + bigTextSize.y),
        IM_COL32(255, 255, 255, 255),
        "\xEF\x84\x88"
    );

    ImGui::SameLine( );
    currPos = ImGui::GetCursorPos( );
    if (!isSymbols) RenderKeyboardRow(currentKeys, 30, 40, isUppercase);

    ImGui::PopStyleVar( );
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 3));
    ImGui::SameLine( );
    if (ImGui::Button("##enter", ImVec2(60.0f, 63)) ||
        ImGui::IsKeyPressed(ImGuiKey_Enter) ||
        ImGui::IsKeyPressed(ImGuiKey_GamepadStart)) {
        m_bKeyboard = false;
        SetEvent(g_KeyboardFinished);
        cursorPos = 0;
    }
    pos = ImGui::GetItemRectMin( );
    size = ImGui::GetItemRectSize( );

    bigTextSize = ImGui::CalcTextSize("\xEE\xAF\xA7");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 18,
        ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) + 2, pos.y + 18),
        IM_COL32(255, 255, 255, 255),
        "\xEE\xAF\xA7"
    );

    smallTextSize = ImGui::CalcTextSize("\xEE\xB7\xA3");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 12,
        ImVec2((pos.x + (size.x - smallTextSize.x) * 0.5f) + 5, pos.y + 26 + bigTextSize.y),
        IM_COL32(255, 255, 255, 255),
        "\xEE\xB7\xA3"
    );
    ImGui::PopStyleVar();

    row2Pos = ImGui::GetCursorPos( );
    row2Pos.x = currPos.x;
    row2Pos.y -= 33;
    ImGui::SetCursorPos(row2Pos);

    HandleKeyboardSpecialKeys();

    ImGui::PopStyleVar( );
    ImGui::PopStyleColor( );
    ImGui::End( );
    ImGui::PopStyleColor( );
}

void wd::Overlay::RenderKeyboardRow(const char** keys, int start, int end, bool isUppercase)
{
    ImVec2 buttonSize(45, 30);
    for (int i = start; i < end; ++i)
    {
        ImGui::PushID(i);
        if (ImGui::Button(keys[ i ], buttonSize))
            AddKeyToBuffer(isUppercase ? keys[ i ][ 0 ] : tolower(keys[ i ][ 0 ]));
        ImGui::PopID( );
        ImGui::SameLine( );
    }
    ImGui::NewLine( );
}

void wd::Overlay::AddKeyToBuffer(char c)
{
    size_t len = strlen(g_KeyboardText);
    if (len >= 255 || cursorPos > len)
        return;

    for (size_t i = len; i > cursorPos; --i)
        g_KeyboardText[ i ] = g_KeyboardText[ i - 1 ];

    g_KeyboardText[ cursorPos ] = c;
    g_KeyboardText[ len + 1 ] = '\0';
    cursorPos++;
}

void wd::Overlay::HandleKeyboardSpecialKeys( )
{
    ImVec2 buttonSize(30, 30);

    if (ImGui::Button("##space", ImVec2((ImGui::GetContentRegionAvail().x - 63), 30)) || ImGui::IsKeyPressed(ImGuiKey_GamepadFaceUp))
        AddKeyToBuffer(' ');

    ImVec2 pos = ImGui::GetItemRectMin( );
    ImVec2 size = ImGui::GetItemRectSize( );

    ImVec2 bigTextSize = ImGui::CalcTextSize("\xEE\x9D\x9D");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 18,
        ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) - 18, pos.y + 18),
        IM_COL32(255, 255, 255, 255),
        "\xEE\x9D\x9D"
    );

    ImVec2 smallTextSize = ImGui::CalcTextSize("\xEF\x82\x95");
    ImGui::GetWindowDrawList( )->AddText(
        ImGui::GetFont( ), 14,
        ImVec2((pos.x + (size.x - bigTextSize.x) * 0.5f) + 12, pos.y + 14),
        IM_COL32(250, 161, 25, 255),
        "\xEF\x82\x95"
    );
}
