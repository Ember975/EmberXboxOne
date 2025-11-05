#include "pch.h"
#include "Windows.Xbox.Storage.ContainerInfoQueryResult.h"
#include "Windows.Xbox.Storage.ContainerInfoQueryResult.g.cpp"
#include <winrt/Windows.ApplicationModel.h>
#include "../ConnectedStorage/Windows.Xbox.Storage.ConnectedStorage.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "../ConnectedStorage/Windows.Xbox.Storage.ConnectedStorage.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo>> ContainerInfoQueryResult::GetContainerInfoAsync(uint32_t startIndex, uint32_t maxNumberOfItems)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo>> ContainerInfoQueryResult::GetContainerInfoAsync()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<uint32_t> ContainerInfoQueryResult::GetItemCountAsync()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> ContainerInfoQueryResult::GetContainerInfo2Async(uint32_t startIndex, uint32_t maxNumberOfItems)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::ContainerInfo2>> ContainerInfoQueryResult::GetContainerInfo2Async()
    {
		co_return co_await m_connectedStorage->GetContainerInfo2Async();
    }
}
