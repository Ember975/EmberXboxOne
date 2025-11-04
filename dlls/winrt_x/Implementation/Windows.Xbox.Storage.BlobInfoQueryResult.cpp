#include "pch.h"
#include "Windows.Xbox.Storage.BlobInfoQueryResult.h"
#include "Windows.Xbox.Storage.BlobInfoQueryResult.g.cpp"
#include <winrt/Windows.Foundation.Collections.h>
#include "../ConnectedStorage/Windows.Xbox.Storage.ConnectedStorage.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <hstring.h>

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> BlobInfoQueryResult::GetBlobInfoAsync(uint32_t startIndex, uint32_t maxNumberOfItems)
    {
        LOG_WARNING("GetBlobInfoAsync");
        co_await winrt::resume_background( );
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Storage::BlobInfo>> BlobInfoQueryResult::GetBlobInfoAsync()
    {
		co_return co_await m_connectedStorage->GetBlobInfoAsync(parentName, prefix);
    }
    winrt::Windows::Foundation::IAsyncOperation<uint32_t> BlobInfoQueryResult::GetItemCountAsync()
    {
        LOG_WARNING("GetItemCountAsync");
        co_await winrt::resume_background( );
    }
}
