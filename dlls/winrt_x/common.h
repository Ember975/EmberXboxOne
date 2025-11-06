#pragma once

#include <mutex>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "WinDurangoConfig.h"
#include "logger.h"

#define LOG_FUNCTION_NAME() printf("[%s]\n", __FUNCSIG__)
#define PRINT_UNIMPLEMENTED_FUNCTION() printf("Unimplemented function: %s\n", __FUNCSIG__)
#define MAKE_HSTRING(str) winrt::hstring(std::wstring(str, (str) + strlen(str)))
#define DATETIME_NOW() \
    []() -> Windows::Foundation::DateTime { \
        const auto now = std::chrono::system_clock::now(); \
        const auto duration = now.time_since_epoch(); \
        const auto hundred_nanoseconds = std::chrono::duration_cast<Windows::Foundation::TimeSpan>(duration); \
        return Windows::Foundation::DateTime{ hundred_nanoseconds }; \
    }()
#define EMPTY_IVECTOR(T) winrt::single_threaded_vector<T>()
#define EMPTY_IMAP(K, V) winrt::single_threaded_map<K, V>();
#define EMPTY_IMAPVIEW(K, V) winrt::single_threaded_map<K, V>().GetView()


#define MEMBER_ID                               1234567890
#define TEAM_ID                                 MAKE_HSTRING("0987654321")
#define XBOX_USER_ID                            MAKE_HSTRING("0987612345")
#define CUSTOM_JSON_CONSTANTS                   MAKE_HSTRING("{}")
#define CUSTOM_JSON_PROPS                       MAKE_HSTRING("{}")
#define SECURE_BASE_64                          MAKE_HSTRING("1234567890qwerty")
#define GAMERTAG                                MAKE_HSTRING("Durangler")
#define RESULTS_SERVER_MEASUREMENTS_JSON        MAKE_HSTRING("{}")
#define SERVER_MEASUREMENTS_JSON                MAKE_HSTRING("{}")
#define DEVICE_ID                               MAKE_HSTRING("device01234567890")
#define ACTIVE_TITLE_ID                         69420