#include "pch.h"
#include "CoreApplicationWrapperX.h"
#include "FrameworkViewSourceWrapper.h"

using namespace ABI::Windows::ApplicationModel::Core;

// ============================================================================
// ICoreApplicationExit Implementation
// ============================================================================

HRESULT CoreApplicationWrapperX::Exit()
{
    printf("[CoreApplicationWrapperX] ICoreApplicationExit::Exit() called — forwarding to realExit.\n");

    if (!realExit)
    {
        printf("[CoreApplicationWrapperX] WARNING: realExit is null!\n");
        return E_POINTER;
    }

    HRESULT hr = realExit->Exit();
    if (FAILED(hr))
    {
        printf("[CoreApplicationWrapperX] Exit() failed with HRESULT=0x%08X\n", hr);
    }

    return hr;
}

HRESULT CoreApplicationWrapperX::add_Exiting(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
    printf("[CoreApplicationWrapperX] add_Exiting called\n");

    if (!realExit)
    {
        printf("[CoreApplicationWrapperX] WARNING: realExit is null in add_Exiting!\n");
        return E_POINTER;
    }

    return realExit->add_Exiting(handler, token);
}

HRESULT CoreApplicationWrapperX::remove_Exiting(EventRegistrationToken token)
{
    printf("[CoreApplicationWrapperX] remove_Exiting called\n");

    if (!realExit)
    {
        printf("[CoreApplicationWrapperX] WARNING: realExit is null in remove_Exiting!\n");
        return E_POINTER;
    }

    return realExit->remove_Exiting(token);
}

// ============================================================================
// IInspectable Implementation
// ============================================================================

HRESULT CoreApplicationWrapperX::GetIids(ULONG* iidCount, IID** iids)
{
    printf("[CoreApplicationWrapperX] GetIids\n");

    if (!iidCount || !iids)
    {
        return E_POINTER;
    }

    if (!m_realFactory)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realFactory is null in GetIids!\n");
        return E_POINTER;
    }

    return m_realFactory->GetIids(iidCount, iids);
}

HRESULT CoreApplicationWrapperX::GetRuntimeClassName(HSTRING* className)
{
    printf("[CoreApplicationWrapperX] GetRuntimeClassName\n");

    if (!className)
    {
        return E_POINTER;
    }

    if (!m_realFactory)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realFactory is null in GetRuntimeClassName!\n");
        return E_POINTER;
    }

    return m_realFactory->GetRuntimeClassName(className);
}

HRESULT CoreApplicationWrapperX::GetTrustLevel(TrustLevel* trustLevel)
{
    printf("[CoreApplicationWrapperX] GetTrustLevel\n");

    if (!trustLevel)
    {
        return E_POINTER;
    }

    if (!m_realFactory)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realFactory is null in GetTrustLevel!\n");
        return E_POINTER;
    }

    return m_realFactory->GetTrustLevel(trustLevel);
}

// ============================================================================
// ICoreApplicationX Implementation (Resuming/Suspending)
// ============================================================================

INT32 CoreApplicationWrapperX::_abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
    printf("[CoreApplicationWrapperX] _abi_add_Resuming\n");

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] WARNING: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    // Actually forward the call - don't just return S_OK
    return m_realCoreApplication->add_Resuming(handler, token);
}

INT32 CoreApplicationWrapperX::_abi_remove_Resuming(EventRegistrationToken token)
{
    printf("[CoreApplicationWrapperX] _abi_remove_Resuming\n");

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] WARNING: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    return m_realCoreApplication->remove_Resuming(token);
}

INT32 CoreApplicationWrapperX::_abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token)
{
    printf("[CoreApplicationWrapperX] _abi_add_Suspending\n");

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] WARNING: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    // Actually forward the call - don't just return S_OK
    return m_realCoreApplication->add_Suspending(handler, token);
}

INT32 CoreApplicationWrapperX::_abi_remove_Suspending(EventRegistrationToken token)
{
    printf("[CoreApplicationWrapperX] _abi_remove_Suspending\n");

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] WARNING: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    return m_realCoreApplication->remove_Suspending(token);
}

// ============================================================================
// ICoreApplicationResourceAvailabilityX Implementation
// ============================================================================

HRESULT CoreApplicationWrapperX::_abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability)
{
    printf("[CoreApplicationWrapperX] _abi_get_ResourceAvailability\n");

    if (!resourceAvailability)
    {
        return E_POINTER;
    }

    // Stubbed: Always return full availability for Xbox
    *resourceAvailability = ResourceAvailability_Full;
    return S_OK;
}

HRESULT CoreApplicationWrapperX::_abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token)
{
    printf("[CoreApplicationWrapperX] _abi_add_ResourceAvailabilityChanged (stubbed)\n");

    if (!token)
    {
        return E_POINTER;
    }

    // Stubbed: Return a dummy token
    token->value = 0;
    return S_OK;
}

HRESULT CoreApplicationWrapperX::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
    printf("[CoreApplicationWrapperX] _abi_remove_ResourceAvailabilityChanged (stubbed)\n");
    // Stubbed: Nothing to do
    return S_OK;
}

// ============================================================================
// ICoreApplicationGpuPolicy Implementation
// ============================================================================

HRESULT CoreApplicationWrapperX::get_DisableKinectGpuReservation(bool* pOutValue)
{
    printf("[CoreApplicationWrapperX] get_DisableKinectGpuReservation -> %d\n", m_KinectGpuReservation);

    if (!pOutValue)
    {
        return E_POINTER;
    }

    *pOutValue = m_KinectGpuReservation;
    return S_OK;
}

HRESULT CoreApplicationWrapperX::set_DisableKinectGpuReservation(bool value)
{
    printf("[CoreApplicationWrapperX] set_DisableKinectGpuReservation <- %d\n", value);
    m_KinectGpuReservation = value;
    return S_OK;
}

// ============================================================================
// ICoreApplication Implementation
// ============================================================================

INT32 CoreApplicationWrapperX::_abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value)
{
    printf("[CoreApplicationWrapperX] _abi_GetCurrentView\n");

    if (!value)
    {
        return E_POINTER;
    }

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    return m_realCoreApplication->GetCurrentView(value);
}

INT32 CoreApplicationWrapperX::_abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource)
{
    printf("[CoreApplicationWrapperX] _abi_Run - Wrapping IFrameworkViewSource\n");

    if (!viewSource)
    {
        printf("[CoreApplicationWrapperX] ERROR: viewSource is null!\n");
        return E_POINTER;
    }

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    // Wrap the ViewSource and pass it to the original function
    FrameworkViewSourceWrapper* wrappedViewSource = new (std::nothrow) FrameworkViewSourceWrapper(viewSource);

    if (!wrappedViewSource)
    {
        printf("[CoreApplicationWrapperX] ERROR: Failed to allocate FrameworkViewSourceWrapper!\n");
        return E_OUTOFMEMORY;
    }

    HRESULT hr = m_realCoreApplication->Run(wrappedViewSource);

    // Release our reference (m_realCoreApplication should have AddRef'd if it needs it)
    wrappedViewSource->Release();

    if (FAILED(hr))
    {
        printf("[CoreApplicationWrapperX] Run() failed with HRESULT=0x%08X\n", hr);
    }

    return hr;
}

INT32 CoreApplicationWrapperX::_abi_get_Id(HSTRING* value)
{
    printf("[CoreApplicationWrapperX] _abi_get_Id\n");

    if (!value)
    {
        return E_POINTER;
    }

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    return m_realCoreApplication->get_Id(value);
}

INT32 CoreApplicationWrapperX::_abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value)
{
    printf("[CoreApplicationWrapperX] _abi_get_Properties\n");

    if (!value)
    {
        return E_POINTER;
    }

    if (!m_realCoreApplication)
    {
        printf("[CoreApplicationWrapperX] ERROR: m_realCoreApplication is null!\n");
        return E_POINTER;
    }

    return m_realCoreApplication->get_Properties(value);
}

// ============================================================================
// IUnknown Implementation (QueryInterface, AddRef, Release)
// ============================================================================

HRESULT CoreApplicationWrapperX::QueryInterface(const IID& riid, void** ppvObject)
{
    if (!ppvObject)
    {
        return E_POINTER;
    }

    *ppvObject = nullptr;

    LPOLESTR str = nullptr;
    if (SUCCEEDED(StringFromIID(riid, &str)))
    {
        wprintf(L"CoreApplicationWrapperX [QI] IID Requested: %s\n", str);
        CoTaskMemFree(str);
    }

    // Handle our wrapper interfaces first
    if (riid == __uuidof(IActivationFactory) || riid == __uuidof(IUnknown))
    {
        *ppvObject = static_cast<IActivationFactory*>(this);
        AddRef();
        printf("  -> Returning IActivationFactory/IUnknown\n");
        return S_OK;
    }

    if (riid == __uuidof(IInspectable))
    {
        // Use IActivationFactory as the path to IInspectable to avoid ambiguity
        *ppvObject = static_cast<IInspectable*>(static_cast<IActivationFactory*>(this));
        AddRef();
        printf("  -> Returning IInspectable\n");
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationX))
    {
        *ppvObject = static_cast<ICoreApplicationX*>(this);
        AddRef();
        printf("  -> Returning ICoreApplicationX\n");
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationExit))
    {
        *ppvObject = static_cast<ICoreApplicationExit*>(this);
        AddRef();
        printf("  -> Returning ICoreApplicationExit\n");
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationResourceAvailabilityX))
    {
        *ppvObject = static_cast<ICoreApplicationResourceAvailabilityX*>(this);
        AddRef();
        printf("  -> Returning ICoreApplicationResourceAvailabilityX\n");
        return S_OK;
    }

    if (riid == __uuidof(ICoreApplicationGpuPolicy))
    {
        *ppvObject = static_cast<ICoreApplicationGpuPolicy*>(this);
        AddRef();
        printf("  -> Returning ICoreApplicationGpuPolicy\n");
        return S_OK;
    }

    // Try delegating to the real factory
    if (m_realFactory)
    {
        HRESULT hr = m_realFactory->QueryInterface(riid, ppvObject);

        if (SUCCEEDED(hr))
        {
            printf("  -> Delegated to m_realFactory (SUCCESS)\n");
            return hr;
        }
        else
        {
            printf("  -> Delegated to m_realFactory (FAILED: 0x%08X)\n", hr);
        }
    }

    // Show MessageBox for debugging unhandled interfaces
    char iidstr[64];
    OLECHAR iidwstr[64];
    StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
    WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);

    printf("  -> E_NOINTERFACE for IID: %s\n", iidstr);
    MessageBoxA(nullptr, iidstr, "CoreApplicationWrapperX - Unhandled Interface", MB_OK | MB_ICONWARNING);

    return E_NOINTERFACE;
}

ULONG CoreApplicationWrapperX::AddRef()
{
    ULONG refCount = InterlockedIncrement(&m_RefCount);
    printf("[CoreApplicationWrapperX] AddRef() -> %lu\n", refCount);
    return refCount;
}

ULONG CoreApplicationWrapperX::Release()
{
    ULONG refCount = InterlockedDecrement(&m_RefCount);
    printf("[CoreApplicationWrapperX] Release() -> %lu\n", refCount);

    if (refCount == 0)
    {
        printf("[CoreApplicationWrapperX] Deleting instance\n");
        delete this;
    }

    return refCount;
}