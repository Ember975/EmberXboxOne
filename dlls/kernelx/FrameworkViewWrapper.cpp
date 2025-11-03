#include "pch.h"
#include "FrameworkViewWrapper.h"
#include <winrt/Windows.Foundation.h>

HRESULT __stdcall FrameworkViewWrapper::Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* applicationView)
{
    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in Initialize()\n");
        return E_POINTER;
    }

    HRESULT hr = m_realView->Initialize(applicationView);
    if (FAILED(hr))
    {
        wprintf(L"Initialize failed with HRESULT=0x%08X\n", hr);
    }
    return hr;
}

HRESULT __stdcall FrameworkViewWrapper::SetWindow(ABI::Windows::UI::Core::ICoreWindow* window)
{
    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in SetWindow()\n");
        return E_POINTER;
    }

    if (!window)
    {
        wprintf(L"ERROR: window parameter is null in SetWindow()\n");
        return E_INVALIDARG;
    }

    // Wrap the CoreWindow with Xbox CoreWindow wrapper
    ICoreWindow* wrappedWindow = reinterpret_cast<ICoreWindow*>(
        new (std::nothrow) CoreWindowWrapperX(reinterpret_cast<CoreWindow*>(window)));

    if (!wrappedWindow)
    {
        wprintf(L"ERROR: Failed to create CoreWindowWrapperX\n");
        return E_OUTOFMEMORY;
    }

    // Pass to real view (it should AddRef if it needs to keep it)
    HRESULT hr = m_realView->SetWindow(wrappedWindow);

    // Release our reference
    wrappedWindow->Release();

    if (FAILED(hr))
    {
        wprintf(L"SetWindow failed with HRESULT=0x%08X\n", hr);
    }

    return hr;
}

HRESULT __stdcall FrameworkViewWrapper::Load(HSTRING entryPoint)
{
    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in Load()\n");
        return E_POINTER;
    }

    HRESULT hr = m_realView->Load(entryPoint);
    if (FAILED(hr))
    {
        wprintf(L"Load failed with HRESULT=0x%08X\n", hr);
    }
    return hr;
}

HRESULT __stdcall FrameworkViewWrapper::Run()
{
    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in Run()\n");
        return E_POINTER;
    }

    try
    {
        wprintf(L"Entering Run()\n");
        HRESULT hr = m_realView->Run();

        if (FAILED(hr))
        {
            wprintf(L"Run failed with HRESULT=0x%08X\n", hr);
        }
        else
        {
            wprintf(L"Run completed successfully\n");
        }

        return hr;
    }
    catch (winrt::hresult_error const& ex)
    {
        wprintf(L"winrt::hresult_error caught in Run: HRESULT=0x%08X, Message=%s\n",
            ex.code(), ex.message().c_str());
        return ex.code();
    }
    catch (std::exception const& ex)
    {
        wprintf(L"std::exception caught in Run: %S\n", ex.what());
        return E_FAIL;
    }
    catch (...)
    {
        wprintf(L"Unknown exception caught in Run\n");
        return E_FAIL;
    }
}

HRESULT __stdcall FrameworkViewWrapper::Uninitialize(void)
{
    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in Uninitialize()\n");
        return E_POINTER;
    }

    HRESULT hr = m_realView->Uninitialize();
    if (FAILED(hr))
    {
        wprintf(L"Uninitialize failed with HRESULT=0x%08X\n", hr);
    }
    return hr;
}

HRESULT FrameworkViewWrapper::QueryInterface(const IID& riid, void** ppvObject)
{
    if (!ppvObject)
    {
        return E_POINTER;
    }

    *ppvObject = nullptr;

    LPOLESTR str = nullptr;
    if (SUCCEEDED(StringFromIID(riid, &str)))
    {
        wprintf(L"FrameworkViewWrapper [QI] IID Requested: %s\n", str);
        CoTaskMemFree(str);
    }

    // Check for interfaces we implement directly
    if (riid == __uuidof(IFrameworkView) ||
        riid == __uuidof(ICoreApplicationExit) ||
        riid == __uuidof(IUnknown) ||
        riid == __uuidof(IInspectable))
    {
        *ppvObject = static_cast<IFrameworkView*>(this);
        AddRef();
        return S_OK;
    }

    // Delegate to real view
    if (m_realView)
    {
        return m_realView->QueryInterface(riid, ppvObject);
    }

    return E_NOINTERFACE;
}

ULONG FrameworkViewWrapper::AddRef()
{
    ULONG refCount = InterlockedIncrement(&m_RefCount);
    wprintf(L"FrameworkViewWrapper::AddRef() -> %lu\n", refCount);
    return refCount;
}

ULONG FrameworkViewWrapper::Release()
{
    ULONG refCount = InterlockedDecrement(&m_RefCount);
    wprintf(L"FrameworkViewWrapper::Release() -> %lu\n", refCount);

    if (refCount == 0)
    {
        wprintf(L"FrameworkViewWrapper: Deleting instance\n");
        delete this;
    }

    return refCount;
}

HRESULT FrameworkViewWrapper::GetIids(ULONG* iidCount, IID** iids)
{
    if (!iidCount || !iids)
    {
        return E_POINTER;
    }

    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in GetIids()\n");
        return E_POINTER;
    }

    return m_realView->GetIids(iidCount, iids);
}

HRESULT FrameworkViewWrapper::GetRuntimeClassName(HSTRING* className)
{
    if (!className)
    {
        return E_POINTER;
    }

    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in GetRuntimeClassName()\n");
        return E_POINTER;
    }

    return m_realView->GetRuntimeClassName(className);
}

HRESULT FrameworkViewWrapper::GetTrustLevel(TrustLevel* trustLevel)
{
    if (!trustLevel)
    {
        return E_POINTER;
    }

    if (!m_realView)
    {
        wprintf(L"ERROR: m_realView is null in GetTrustLevel()\n");
        return E_POINTER;
    }

    return m_realView->GetTrustLevel(trustLevel);
}