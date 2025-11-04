#include "pch.h"
#include "Windows.Xbox.Storage.ConnectedStorageContainer.h"
#include "Windows.Xbox.Storage.ConnectedStorageContainer.g.cpp"
#include "../ConnectedStorage/Windows.Xbox.Storage.ConnectedStorage.h"
#include "Windows.Xbox.Storage.BlobInfoQueryResult.h"


namespace winrt::Windows::Xbox::Storage::implementation
{
    hstring ConnectedStorageContainer::Name()
    {
		return containerName;
    }
    winrt::Windows::Xbox::Storage::ConnectedStorageSpace ConnectedStorageContainer::OwningSpace()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitUpdatesAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete)
    {
        co_await m_connectedStorage->Upload(Name( ), blobsToWrite, blobsToDelete);
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::ReadAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToRead)
    {
        co_await m_connectedStorage->Read(Name( ), blobsToRead);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer>> ConnectedStorageContainer::GetAsync(winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToRead)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitPropertySetUpdatesAsync(winrt::Windows::Foundation::Collections::IPropertySet blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitUpdatesAsync(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Storage::Streams::IBuffer> blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete, hstring displayName)
    {
        co_await m_connectedStorage->Upload(Name(), blobsToWrite, blobsToDelete, displayName);
    }
    winrt::Windows::Foundation::IAsyncAction ConnectedStorageContainer::SubmitPropertySetUpdatesAsync(winrt::Windows::Foundation::Collections::IPropertySet blobsToWrite, winrt::Windows::Foundation::Collections::IIterable<hstring> blobsToDelete, hstring displayName)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Storage::BlobInfoQueryResult ConnectedStorageContainer::CreateBlobInfoQuery(hstring const& blobNamePrefix)
    {
        return winrt::make<winrt::Windows::Xbox::Storage::implementation::BlobInfoQueryResult>(Name(), blobNamePrefix, m_connectedStorage);
    }
}
