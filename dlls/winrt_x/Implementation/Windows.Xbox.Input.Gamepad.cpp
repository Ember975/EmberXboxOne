#include "pch.h"
#include "Windows.h"
#include "Windows.Xbox.Input.GamepadReading.h"
#include "Windows.Xbox.Input.Gamepad.h"
#include "Windows.Xbox.Input.Gamepad.g.cpp"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Input.h>
#include <windowsx.h>
#include <Xinput.h>
#include "Windows.Xbox.System.User.h"

namespace winrt::Windows::Xbox::Input::implementation
{
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IGamepad> Gamepad::Gamepads( )
    {
        if (staticGamepads == Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IGamepad>(nullptr) || staticGamepads.Size( ) == 0) {
            staticGamepads = winrt::single_threaded_vector<Input::IGamepad>( );
            LOG_INFO_W(L"Gamepad || Gamepads Queried!\n");
            for (DWORD gamepad = 0; gamepad < XUSER_MAX_COUNT; gamepad++)
            {
                XINPUT_CAPABILITIES capabilities;
                if (XInputGetCapabilities(gamepad, XINPUT_FLAG_GAMEPAD, &capabilities) == ERROR_SUCCESS)
                {
                    wprintf(L"Gamepad || Gamepad %d Created!\n", gamepad);
                    IGamepad newGamepad = winrt::make<Gamepad>(gamepad);
                    staticGamepads.Append(newGamepad);
                    continue;
                }
            }
        }

        if (staticGamepads.Size( ) == 0) {
            wprintf(L"Gamepad || No Gamepads Found!\n");
            IGamepad dummyGamepad = winrt::make<Gamepad>(0);
            staticGamepads.Append(dummyGamepad);
        }

        HWND hwnd = GetFocus( );
        ShowCursor(FALSE);
        RECT rc;
        GetClientRect(hwnd, &rc);
        POINT tl = { rc.left, rc.top };
        POINT br = { rc.right, rc.bottom };
        MapWindowPoints(hwnd, nullptr, &tl, 1);
        MapWindowPoints(hwnd, nullptr, &br, 1);
        RECT screenRect = { tl.x, tl.y, br.x, br.y };
        ClipCursor(&screenRect);
        ShowCursor(FALSE);

        return staticGamepads.GetView( );
    }

    winrt::event_token Gamepad::GamepadAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadAddedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Gamepad || Gamepad Added!\n");
        LOG_WARNING("Gamepad || GamepadAdded event is not implemented, returning empty token.");
        return {};
    }

    void Gamepad::GamepadAdded(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Gamepad || Gamepad Added!\n");
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    winrt::event_token Gamepad::GamepadRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::GamepadRemovedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Gamepad || Gamepad Removed!\n");
        LOG_NOT_IMPLEMENTED( );
        return {};
    }

    void Gamepad::GamepadRemoved(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Gamepad || Gamepad Removed!\n");
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    uint64_t Gamepad::Id( )
    {
        LOG_INFO_W(L"Gamepad || Gamepad ID ( %d ) Queried!\n", m_id);
        return m_id;
    }

    hstring Gamepad::Type( )
    {
        return L"Windows.Xbox.Input.Gamepad";
    }

    winrt::Windows::Xbox::System::User Gamepad::User( )
    {
        LOG_INFO_W(L"Gamepad || User Queried!\n");
        return System::implementation::User::Users( ).GetAt(Id( ));
    }

    winrt::Windows::Xbox::Input::INavigationReading Gamepad::GetNavigationReading( )
    {
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    winrt::Windows::Xbox::Input::RawNavigationReading Gamepad::GetRawNavigationReading( )
    {
        RawNavigationReading dummyNavigationReading = RawNavigationReading( );
        dummyNavigationReading.Timestamp = GetTickCount64( );
        dummyNavigationReading.Buttons |= NavigationButtons::Up;
        return dummyNavigationReading;
    }

    winrt::event_token Gamepad::NavigationReadingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Input::NavigationController, winrt::Windows::Xbox::Input::INavigationReadingChangedEventArgs> const& handler)
    {
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    void Gamepad::NavigationReadingChanged(winrt::event_token const& token) noexcept
    {
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    void Gamepad::SetVibration(winrt::Windows::Xbox::Input::GamepadVibration const& value)
    {
        XINPUT_VIBRATION vibration;
        ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
        vibration.wLeftMotorSpeed = static_cast<WORD>(value.LeftMotorLevel * 65535);
        vibration.wRightMotorSpeed = static_cast<WORD>(value.RightMotorLevel * 65535);
        XInputSetState(m_id, &vibration);
    }

    winrt::Windows::Xbox::Input::IGamepadReading Gamepad::GetCurrentReading( )
    {
        return winrt::make<implementation::GamepadReading>(GetRawCurrentReading( ));
    }

    winrt::Windows::Xbox::Input::RawGamepadReading Gamepad::GetRawCurrentReading( )
    {
        XINPUT_STATE xiState;
        ZeroMemory(&xiState, sizeof(XINPUT_STATE));
        reading = {};

        DWORD result = XInputGetState(m_id, &xiState);
        if (result == ERROR_SUCCESS)
        {
            // Debug logging - remove after testing
            if (xiState.Gamepad.wButtons != 0)
            {
                LOG_INFO_W(L"Gamepad || Controller %d - Button mask: 0x%04X\n", m_id, xiState.Gamepad.wButtons);
            }

            for (int i = 0; i < ARRAYSIZE(gamepadButtons); i++)
            {
                if (xiState.Gamepad.wButtons & gamepadButtons[ i ].first)
                {
                    reading.Buttons |= gamepadButtons[ i ].second;

                    // Debug: Log when Start button is detected
                    if (gamepadButtons[ i ].first == XINPUT_GAMEPAD_START)
                    {
                        LOG_INFO_W(L"Gamepad || START BUTTON DETECTED!\n");
                    }
                }
            }

            reading.LeftTrigger = xiState.Gamepad.bLeftTrigger / 255.f;
            reading.RightTrigger = xiState.Gamepad.bRightTrigger / 255.f;
            reading.LeftThumbstickX = xiState.Gamepad.sThumbLX / 32768.f;
            reading.LeftThumbstickY = xiState.Gamepad.sThumbLY / 32768.f;
            reading.RightThumbstickX = xiState.Gamepad.sThumbRX / 32768.f;
            reading.RightThumbstickY = xiState.Gamepad.sThumbRY / 32768.f;
        }
        else
        {
            LOG_WARNING_W(L"Gamepad || XInputGetState failed for controller %d with error: %d\n", m_id, result);
        }

        float lx = 0.0f;
        float ly = 0.0f;

        for (int i = 0; i < ARRAYSIZE(keyboardButtons); i++)
        {
			if (GetAsyncKeyState(keyboardButtons[ i ].first))
			{
				reading.Buttons |= keyboardButtons[ i ].second;
            }
            else if (GetAsyncKeyState('W') & 0x8000) {
                ly = 1.0f;
            }
            else if (GetAsyncKeyState('A') & 0x8000) {
                lx = -1.0f;
            }
            else if (GetAsyncKeyState('S') & 0x8000) {
                ly = -1.0f;
            }
            else if (GetAsyncKeyState('D') & 0x8000) {
                lx = 1.0f;
            }
        }

        lx = std::clamp(lx, -1.0f, 1.0f);
        ly = std::clamp(ly, -1.0f, 1.0f);

        if (lx != 0.0f || ly != 0.0f) {
            reading.LeftThumbstickX = lx;
            reading.LeftThumbstickY = ly;
        }        

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            reading.RightTrigger = 1.0f;
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            reading.LeftTrigger = 1.0f;
        }

        /*
        * Mouse Input
        */
        POINT pos;
        GetCursorPos(&pos);

        if (firstFrame) {
            prev = pos;
            firstFrame = false;
        }

        int dx = pos.x - prev.x;
        int dy = pos.y - prev.y;

        deltasumX += dx;
        deltasumY += dy;
        prev = pos;
        
        int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
        int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;
        SetCursorPos(centerX, centerY);
        prev.x = centerX;
        prev.y = centerY;
        
        auto sign = [](float v) { return (v > 0) - (v < 0); };
        float x = -std::exp((-1.0f / 20.0f) * std::abs(deltasumX)) + 1.0f;
        float y = -std::exp((-1.0f / 20.0f) * std::abs(deltasumY)) + 1.0f;
        x *= sign(deltasumX);
        y *= -sign(deltasumY);

        reading.RightThumbstickX = std::clamp(x, -1.0f, 1.0f);
        reading.RightThumbstickY = std::clamp(y, -1.0f, 1.0f);

        deltasumX = 0.0f;
        deltasumY = 0.0f;

        return reading;
    }

    winrt::event_token Gamepad::ReadingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Input::Gamepad, winrt::Windows::Xbox::Input::IGamepadReadingChangedEventArgs> const& handler)
    {
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    void Gamepad::ReadingChanged(winrt::event_token const& token) noexcept
    {
        LOG_NOT_IMPLEMENTED( );
        throw hresult_not_implemented( );
    }

    bool Gamepad::IsTrusted( )
    {
        return true;
    }
}