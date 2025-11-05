#pragma once
#include "Windows.Xbox.Input.Gamepad.g.h"
#include <Xinput.h>
#include <windows.h>
#include <winrt/Windows.UI.Core.h>

namespace winrt::Windows::Xbox::Input::implementation
{

    struct Gamepad : GamepadT<Gamepad>
    {
        Gamepad() = default;
        Gamepad(uint64_t id) : m_id(id) {}

        static winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IGamepad> Gamepads();
        static winrt::event_token GamepadAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs> const& handler);
        static void GamepadAdded(winrt::event_token const& token) noexcept;
        static winrt::event_token GamepadRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs> const& handler);
        static void GamepadRemoved(winrt::event_token const& token) noexcept;
        uint64_t Id();
        hstring Type();
        winrt::Windows::Xbox::System::User User();
        winrt::Windows::Xbox::Input::INavigationReading GetNavigationReading();
        winrt::Windows::Xbox::Input::RawNavigationReading GetRawNavigationReading();
        winrt::event_token NavigationReadingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Input::NavigationController, winrt::Windows::Xbox::Input::INavigationReadingChangedEventArgs> const& handler);
        void NavigationReadingChanged(winrt::event_token const& token) noexcept;
        void SetVibration(winrt::Windows::Xbox::Input::GamepadVibration const& value);
        winrt::Windows::Xbox::Input::IGamepadReading GetCurrentReading();
        winrt::Windows::Xbox::Input::RawGamepadReading GetRawCurrentReading();
        winrt::event_token ReadingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Input::Gamepad, winrt::Windows::Xbox::Input::IGamepadReadingChangedEventArgs> const& handler);
        void ReadingChanged(winrt::event_token const& token) noexcept;
        bool IsTrusted();
        inline static winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IGamepad> staticGamepads = { nullptr };
        uint64_t m_id{ 0 };
        RawGamepadReading reading = {};
        POINT prev{ 0, 0 };
        float deltasumX = 0.0f;
        float deltasumY = 0.0f;
        bool firstFrame = true;

        inline static std::pair<WORD, GamepadButtons> const gamepadButtons[] =
        {
            { XINPUT_GAMEPAD_DPAD_UP, GamepadButtons::DPadUp },
            { XINPUT_GAMEPAD_DPAD_DOWN, GamepadButtons::DPadDown },
            { XINPUT_GAMEPAD_DPAD_LEFT, GamepadButtons::DPadLeft },
            { XINPUT_GAMEPAD_DPAD_RIGHT, GamepadButtons::DPadRight },
            { XINPUT_GAMEPAD_START, GamepadButtons::Menu },
            { XINPUT_GAMEPAD_BACK, GamepadButtons::View },
            { XINPUT_GAMEPAD_LEFT_THUMB, GamepadButtons::LeftThumbstick },
            { XINPUT_GAMEPAD_RIGHT_THUMB, GamepadButtons::RightThumbstick },
            { XINPUT_GAMEPAD_LEFT_SHOULDER, GamepadButtons::LeftShoulder },
            { XINPUT_GAMEPAD_RIGHT_SHOULDER, GamepadButtons::RightShoulder },
            { XINPUT_GAMEPAD_A, GamepadButtons::A },
            { XINPUT_GAMEPAD_B, GamepadButtons::B },
            { XINPUT_GAMEPAD_X, GamepadButtons::X },
            { XINPUT_GAMEPAD_Y, GamepadButtons::Y },
        };
        
        inline static std::pair<WORD, GamepadButtons> const keyboardButtons[] =
        {
            { VK_UP, GamepadButtons::DPadUp },
            { VK_DOWN, GamepadButtons::DPadDown },
            { VK_LEFT, GamepadButtons::DPadLeft },
            { VK_RIGHT, GamepadButtons::DPadRight },
            { VK_RETURN, GamepadButtons::Menu },
            { VK_ESCAPE, GamepadButtons::View },
            { VK_LSHIFT, GamepadButtons::LeftThumbstick },
            { VK_RSHIFT, GamepadButtons::RightThumbstick },
            { VK_LCONTROL, GamepadButtons::LeftShoulder },
            { VK_RCONTROL, GamepadButtons::RightShoulder },
            { VK_SPACE, GamepadButtons::A },
            { 'X', GamepadButtons::B},
            { 'C', GamepadButtons::X },
            { 'V', GamepadButtons::Y},
        };
    };
}
namespace winrt::Windows::Xbox::Input::factory_implementation
{
    struct Gamepad : GamepadT<Gamepad, implementation::Gamepad>
    {
    };
}
