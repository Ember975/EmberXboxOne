#pragma once
#include "Windows.Xbox.Storage.ConnectedStorageSpace.g.h"

#include <winrt/Windows.Foundation.Collections.h>

#include "../ConnectedStorage/Windows.Xbox.Storage.ConnectedStorage.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    struct ConnectedStorageSpace : ConnectedStorageSpaceT<ConnectedStorageSpace>
    {
        ConnectedStorageSpace() = default;
		ConnectedStorageSpace(WinDurango::impl::ConnectedStorage* connectedStorage)
		{
			m_connectedStorage = connectedStorage;
		}

        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetForUserAsync(winrt::Windows::Xbox::System::User user);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetForMachineAsync( );
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetForMachineAsync(hstring serviceConfigurationId);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId);
        winrt::Windows::Xbox::System::User User( );
        hstring ServiceConfigurationId( );
        bool IsReadOnly( );
        winrt::Windows::Xbox::Storage::ConnectedStorageContainer CreateContainer(hstring const& containerName);
        winrt::Windows::Foundation::IAsyncAction DeleteContainerAsync(hstring containerName);
        winrt::Windows::Xbox::Storage::ContainerInfoQueryResult CreateContainerInfoQuery(hstring const& containerNamePrefix);
        winrt::Windows::Foundation::IAsyncOperation<int32_t> GetRemainingBytesInQuotaAsync( );
        winrt::Windows::Foundation::IAsyncOperation<int64_t> GetRemainingBytesInQuota64Async( );
        inline static winrt::Windows::Xbox::Storage::ConnectedStorageSpace userStorageSpace = { nullptr };
        inline static winrt::Windows::Xbox::Storage::ConnectedStorageSpace machineStorageSpace = { nullptr };
        inline static winrt::Windows::Xbox::Storage::ConnectedStorageContainer staticContainer = { nullptr };

    private:
        inline static winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Xbox::Storage::ConnectedStorageContainer> containers;
		WinDurango::impl::ConnectedStorage* m_connectedStorage = nullptr;
    };
}
namespace winrt::Windows::Xbox::Storage::factory_implementation
{
    struct ConnectedStorageSpace : ConnectedStorageSpaceT<ConnectedStorageSpace, implementation::ConnectedStorageSpace>
    {
    };
}
