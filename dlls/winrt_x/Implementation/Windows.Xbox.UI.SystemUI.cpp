#include "pch.h"
#include "Windows.Xbox.UI.SystemUI.h"
#include <iostream>
#include "Windows.Xbox.UI.AccountPickerResult.h"
#include "Windows.Xbox.UI.SystemUI.g.cpp"


void* g_pD3D11XEventFunc = nullptr;
void* g_pWDWaitForKeyboardFunc = nullptr;


namespace winrt::Windows::Xbox::UI::implementation
{
    winrt::Windows::Xbox::UI::NotificationPositionHint SystemUI::m_notificationPositionHint =
        winrt::Windows::Xbox::UI::NotificationPositionHint::TopRight;
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowEpgAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Foundation::IInspectable>> propertySet)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowMiniguideAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowProfileCardAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring targetXuid)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowSendInvitesAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::AccountPickerResult> SystemUI::ShowAccountPickerAsync(winrt::Windows::Xbox::Input::IController controller, winrt::Windows::Xbox::UI::AccountPickerOptions options)
    {
		LOG_WARNING("TODO: SystemUI::ShowAccountPickerAsync (this function just returns the first user in User::Users)\n");
        co_return winrt::make<implementation::AccountPickerResult>( );
    }
    winrt::Windows::Foundation::IAsyncOperation<hstring> SystemUI::ShowVirtualKeyboardAsync(hstring defaultText, hstring titleText, hstring descriptionText, winrt::Windows::Xbox::UI::VirtualKeyboardInputScope inputScope)
    {
        co_await resume_background( );

        auto hD3D11X = GetModuleHandle(L"d3d11_x.dll");
        if (!hD3D11X) {
            OutputDebugString(L"[ERROR] d3d11_x.dll not loaded\n");
            co_return L"";
        }

        g_pD3D11XEventFunc = GetProcAddress(hD3D11X, "WD11XNotify_X");
        g_pWDWaitForKeyboardFunc = GetProcAddress(hD3D11X, "WDWaitForKeyboard");

        if (!g_pD3D11XEventFunc || !g_pWDWaitForKeyboardFunc) {
            OutputDebugString(L"[ERROR] Could not find WD11XNotify or WDWaitForKeyboard\n");
            co_return L"";
        }

        reinterpret_cast<void(__stdcall*)(int)>(g_pD3D11XEventFunc)(1);

		const char* text = nullptr;
		reinterpret_cast<void(__stdcall*)(const char**)>(g_pWDWaitForKeyboardFunc)(&text);

        co_return winrt::to_hstring(text);
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchPartyAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchAchievementsAsync(winrt::Windows::Xbox::System::IUser requestingUser, uint32_t titleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowPartyAndSendPartyInvitesAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> recipientUserIdList)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowCreateLookingForGroupAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> preselectedTags, hstring preselectedDescription, uint32_t defaultNeedCount)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowUserLookingForGroupsAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowLookingForGroupResultsAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Foundation::Collections::IVectorView<hstring> tags)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchKinectSetupAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::LaunchRecentPlayersAsync(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::SnapDefaultBroadcastApp(winrt::Windows::Xbox::System::IUser requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowComposeMessageAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring defaultMessageText, winrt::Windows::Foundation::Collections::IVector<hstring> recipientUserIdList)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::AddRemoveFriendResult> SystemUI::ShowAddRemoveFriendAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring targetUserId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<hstring>> SystemUI::ShowPeoplePickerAsync(winrt::Windows::Xbox::System::IUser requestingUser, hstring promptText, winrt::Windows::Foundation::Collections::IVectorView<hstring> selectFromUserIdList, winrt::Windows::Foundation::Collections::IVectorView<hstring> preselectedUserIdList, uint32_t minimumSelectionCount, uint32_t maximumSelectionCount)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> SystemUI::TrySnapSelf()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> SystemUI::TrySnapOther(winrt::Windows::Foundation::Uri snapTargetUri, winrt::Windows::Xbox::System::IUser user)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction SystemUI::ShowMiniguideWithCommandAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Xbox::UI::MiniguideCommand initialCommand)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<hstring> SystemUI::ShowVirtualKeyboardWithOptionsAsync(winrt::Windows::Xbox::UI::KeyboardOptions options)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void SystemUI::SetNotificationPositionHint(winrt::Windows::Xbox::UI::NotificationPositionHint const& value)
    {
		LOG_WARNING("SystemUI::SetNotificationPositionHint called.. Function Stubbed!!!");
            switch (value)
            {
            case winrt::Windows::Xbox::UI::NotificationPositionHint::BottomCenter:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to BottomCenter.\n");
                m_notificationPositionHint = value;
                break;

            case winrt::Windows::Xbox::UI::NotificationPositionHint::BottomLeft:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to BottomLeft.\n");
                m_notificationPositionHint = value;
                break;

            case winrt::Windows::Xbox::UI::NotificationPositionHint::BottomRight:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to BottomRight.\n");
                m_notificationPositionHint = value;
                break;

            case winrt::Windows::Xbox::UI::NotificationPositionHint::TopCenter:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to TopCenter.\n");
                m_notificationPositionHint = value;
                break;

            case winrt::Windows::Xbox::UI::NotificationPositionHint::TopLeft:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to TopLeft.\n");
                m_notificationPositionHint = value;
                break;

            case winrt::Windows::Xbox::UI::NotificationPositionHint::TopRight:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Setting NotificationPositionHint to TopRight.\n");
                m_notificationPositionHint = value;
                break;

            default:
                LOG_WARNING("SystemUI::SetNotificationPositionHint: Received unknown value! Defaulting to TopRight.\n");
                m_notificationPositionHint = winrt::Windows::Xbox::UI::NotificationPositionHint::TopRight;
                break;
            }
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::WebAuthenticationResult> SystemUI::AuthenticateAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Xbox::UI::WebAuthenticationOptions options, winrt::Windows::Foundation::Uri requestUri, winrt::Windows::Foundation::Uri callbackUri)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::UI::WebAuthenticationResult> SystemUI::AuthenticateAsync(winrt::Windows::Xbox::System::IUser requestingUser, winrt::Windows::Xbox::UI::WebAuthenticationOptions options, winrt::Windows::Foundation::Uri requestUri)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Uri SystemUI::GetCurrentApplicationCallbackUri(winrt::Windows::Xbox::System::IUser const& requestingUser)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
