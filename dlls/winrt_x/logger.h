/*
================================================================================
DISCLAIMER AND LICENSE REQUIREMENT

This code is provided with the condition that if you use, modify, or distribute
this code in your project, you are required to make your project open source
under a license compatible with the GNU General Public License (GPL) or a
similarly strong copyleft license.

By using this code, you agree to:
1. Disclose your complete source code of any project incorporating this code.
2. Include this disclaimer in any copies or substantial portions of this file.
3. Provide clear attribution to the original author.

If you do not agree to these terms, you do not have permission to use this code.

================================================================================
*/

#pragma once

#include <string>
#include <cstdarg>
#include <mutex>
#include <fstream>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <source_location> // C++20 support

#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#if defined(__GNUC__) || defined(__clang__)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define FUNCTION_NAME __FUNCSIG__
#else
#define FUNCTION_NAME __FUNCTION__
#endif

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
    NotImplemented
};

class Logger {
private:
    struct LoggerConfig {
        bool EnableLogging = true;
        bool EnableVerbose = false;
        bool DebuggerOnly = false;
        LogLevel MinimumLogLevel = LogLevel::Debug;
    };

    static inline std::mutex logMutex;
    static inline LoggerConfig config;

    static std::string GenerateLogFileName() {
        auto t = std::time(nullptr);
        std::tm tm{};
        localtime_s(&tm, &t);
        char buf[ 64 ];
        std::strftime(buf, sizeof(buf), "debug_%Y-%m-%d_%H-%M-%S.log", &tm);
        return buf;
    }
    static inline std::ofstream logFile{ GenerateLogFileName(), std::ios::app };

    static inline std::string FormatString(const char* fmt, va_list args) {
        char buffer[ 1024 ];
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        return std::string(buffer);
    }

    static const char* ToString(LogLevel level) {
        switch (level) {
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Fatal: return "FATAL";
        case LogLevel::NotImplemented: return "NOT_IMPLEMENTED";
        default: return "UNKNOWN";
        }
    }

    static std::string CurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm timeinfo{};
        char buffer[ 32 ];
        if (localtime_s(&timeinfo, &now) == 0) {
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S %p", &timeinfo);
            return buffer;
        }
        else {
            return "Unknown Time";
        }
    }

    static std::wstring CurrentTimeW() {
        std::time_t now = std::time(nullptr);
        std::tm timeinfo{};
        wchar_t buffer[ 32 ];
        if (localtime_s(&timeinfo, &now) == 0) {
            std::wcsftime(buffer, sizeof(buffer) / sizeof(wchar_t), L"%Y-%m-%d %I:%M:%S %p", &timeinfo);
            return buffer;
        }
        else {
            return L"Unknown Time";
        }
    }
    static void PrintWithContext(int line, const char* file, const char* function, const char* fmt, va_list args) {
        char formatted[ 1024 ];
        vsnprintf(formatted, sizeof(formatted), fmt, args);
        Logf(LogLevel::NotImplemented, formatted, file, line, function);
    }
public:
    static void NotImplemented(const char* file, int line, const char* function, const char* fmt = "", ...) {
        va_list args;
        va_start(args, fmt);
        PrintWithContext(line, file, function, fmt, args);
        va_end(args);
    }
    static void Log(LogLevel level, const char* file, int line, const char* function, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        std::string message = FormatString(fmt, args);
        va_end(args);
        Logf(level, message, file, line, function);
    }
    // -------------------------------
    // Narrow logging (std::string)
    // -------------------------------
    static void Logf(LogLevel level, const std::string& message, const char* file, int line, const char* function) {
        std::lock_guard<std::mutex> lock(logMutex);
        std::string timeStr = CurrentTime();
        std::string func = ExtractFunctionName(function);
        const char* project = ExtractProjectName(file);
        const char* levelStr = ToString(level);

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        WORD originalAttributes = 0;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            originalAttributes = csbi.wAttributes;
            SetConsoleTextAttribute(hConsole, GetConsoleColor(level));
        }

        std::cout << timeStr << " - " << levelStr << " - " << project << " - " << func;
        if (level == LogLevel::Error || level == LogLevel::Fatal)
            std::cout << " - Line " << line;
        if (!message.empty())
            std::cout << " - " << message;
        std::cout << std::endl;

        if (hConsole) SetConsoleTextAttribute(hConsole, originalAttributes);

        if (logFile.is_open()) {
            logFile << timeStr << " - " << levelStr << " - " << project << " - " << func;
            if (level == LogLevel::Error || level == LogLevel::Fatal)
                logFile << " - Line " << line;
            if (!message.empty())
                logFile << " - " << message;
            logFile << std::endl;
        }
    }

    // -------------------------------
    // Wide logging (std::wstring)
    // -------------------------------
    static void Log(LogLevel level, const std::wstring& message, const wchar_t* file, int line, const wchar_t* function) {
        std::lock_guard<std::mutex> lock(logMutex);
        std::wstring timeStr = CurrentTimeW();
        std::wstring func = ExtractFunctionNameW(function);
        std::wstring project = ExtractProjectNameW(file);
        std::wstring levelStr = ConvertToWString(ToString(level));

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        WORD originalAttributes = 0;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            originalAttributes = csbi.wAttributes;
            SetConsoleTextAttribute(hConsole, GetConsoleColor(level));
        }

        std::wcout << timeStr << L" - " << levelStr << L" - " << project << L" - " << func;
        if (level == LogLevel::Error || level == LogLevel::Fatal)
            std::wcout << L" - Line " << line;
        if (!message.empty())
            std::wcout << L" - " << message;
        std::wcout << std::endl;

        if (hConsole) SetConsoleTextAttribute(hConsole, originalAttributes);

        static std::wofstream logFileW{ L"debug_wide.log", std::ios::app };
        if (logFileW.is_open()) {
            logFileW << timeStr << L" - " << levelStr << L" - " << project << L" - " << func;
            if (level == LogLevel::Error || level == LogLevel::Fatal)
                logFileW << L" - Line " << line;
            if (!message.empty())
                logFileW << L" - " << message;
            logFileW << std::endl;
        }
    }

    // Utility: Convert const char* to std::wstring
    static std::wstring ConvertToWString(const char* str) {
        if (!str) return L"";
        int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
        std::wstring wstr(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, str, -1, &wstr[ 0 ], size);
        wstr.pop_back(); // remove null terminator
        return wstr;
    }
    static WORD GetColorForProject(const char* projectName) {
        size_t hash = 0;
        while (*projectName) {
            hash = hash * 101 + *projectName++;
        }
        WORD colors[] = {
            FOREGROUND_RED,
            FOREGROUND_GREEN,
            FOREGROUND_BLUE,
            FOREGROUND_RED | FOREGROUND_GREEN,
            FOREGROUND_RED | FOREGROUND_BLUE,
            FOREGROUND_GREEN | FOREGROUND_BLUE,
            FOREGROUND_INTENSITY
        };
        return colors[ hash % (sizeof(colors) / sizeof(colors[ 0 ])) ];
    }

    static WORD GetConsoleColor(LogLevel level) {
        switch (level) {
        case LogLevel::Debug: return FOREGROUND_BLUE | FOREGROUND_GREEN;
        case LogLevel::Info: return FOREGROUND_GREEN;
        case LogLevel::Warning: return FOREGROUND_RED | FOREGROUND_GREEN;
        case LogLevel::Error: return FOREGROUND_RED;
        case LogLevel::Fatal: return BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case LogLevel::NotImplemented: return FOREGROUND_RED | FOREGROUND_BLUE;
        default: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }

    // Extract function name (narrow)
    static std::string ExtractFunctionName(const char* fullSignature) {
        const char* paren = strchr(fullSignature, '(');
        if (!paren) return fullSignature;
        const char* end = paren;
        const char* lastColon = nullptr;
        for (const char* p = fullSignature; p < end; ++p) {
            if (p[ 0 ] == ':' && p[ 1 ] == ':')
                lastColon = p;
        }
        const char* start = lastColon ? lastColon + 2 : fullSignature;
        static char functionName[ 256 ];
        size_t length = static_cast<size_t>(end - start);
        length = (length < sizeof(functionName) - 1) ? length : sizeof(functionName) - 1;
        strncpy_s(functionName, sizeof(functionName), start, length);
        functionName[ length ] = '\0';
        return functionName;
    }

    // Extract function name (wide)
    static std::wstring ExtractFunctionNameW(const wchar_t* fullSignature) {
        const wchar_t* paren = wcschr(fullSignature, L'(');
        if (!paren) return fullSignature;
        const wchar_t* end = paren;
        const wchar_t* lastColon = nullptr;
        for (const wchar_t* p = fullSignature; p < end; ++p) {
            if (p[ 0 ] == L':' && p[ 1 ] == L':')
                lastColon = p;
        }
        const wchar_t* start = lastColon ? lastColon + 2 : fullSignature;
        static wchar_t functionName[ 256 ];
        size_t length = static_cast<size_t>(end - start);
        length = (length < sizeof(functionName) / sizeof(wchar_t) - 1) ? length : sizeof(functionName) / sizeof(wchar_t) - 1;
        wcsncpy_s(functionName, start, length);
        functionName[ length ] = L'\0';
        return functionName;
    }

    // Extract project name
    static const char* ExtractProjectName(const char* filePath) {
        const char* lastSlash = strrchr(filePath, '/');
        if (!lastSlash) lastSlash = strrchr(filePath, '\\');
        const char* fileName = lastSlash ? lastSlash + 1 : filePath;
        const char* dot = strrchr(fileName, '.');
        static char project[ 256 ];
        size_t length = dot ? static_cast<size_t>(dot - fileName) : strlen(fileName);
        length = (length < sizeof(project) - 1) ? length : sizeof(project) - 1;
        strncpy_s(project, sizeof(project), fileName, length);
        project[ length ] = '\0';
        return project;
    }

    // Extract project name (wide)
    static std::wstring ExtractProjectNameW(const wchar_t* filePath) {
        const wchar_t* lastSlash = wcsrchr(filePath, L'/');
        if (!lastSlash) lastSlash = wcsrchr(filePath, L'\\');
        const wchar_t* fileName = lastSlash ? lastSlash + 1 : filePath;
        const wchar_t* dot = wcsrchr(fileName, L'.');
        static wchar_t project[ 256 ];
        size_t length = dot ? static_cast<size_t>(dot - fileName) : wcslen(fileName);
        length = (length < sizeof(project) / sizeof(wchar_t) - 1) ? length : sizeof(project) / sizeof(wchar_t) - 1;
        wcsncpy_s(project, fileName, length);
        project[ length ] = L'\0';
        return project;
    }
};

// ------------------------------------------------------------------------------------------------
// Macro-based log wrappers (captures callsite info)
// ------------------------------------------------------------------------------------------------
#define LOG_DEBUG(fmt, ...) Logger::Log(LogLevel::Debug, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) Logger::Log(LogLevel::Info, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) Logger::Log(LogLevel::Warning, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::Log(LogLevel::Error, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) Logger::Log(LogLevel::Fatal, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOG_NOT_IMPLEMENTED(...) Logger::NotImplemented(__FILE__, __LINE__, FUNCTION_NAME, ##__VA_ARGS__)

// ------------------------------------------------------------------------------------------------
// Macro-based log wrappers (captures callsite info) WIDE CHARACTER VERSION
// ------------------------------------------------------------------------------------------------
#define LOG_DEBUG_W(msg) Logger::Log(LogLevel::Debug, msg, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME))
#define LOG_INFO_W(msg) Logger::Log(LogLevel::Info, msg, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME))
#define LOG_WARNING_W(msg) Logger::Log(LogLevel::Warning, msg, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME))
#define LOG_ERROR_W(msg) Logger::Log(LogLevel::Error, msg, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME))
#define LOG_FATAL_W(msg) Logger::Log(LogLevel::Fatal, msg, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME))
#define LOG_NOT_IMPLEMENTED_W(...) Logger::NotImplementedW(_CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(FUNCTION_NAME), ##__VA_ARGS__)
// ------------------------------------------------------------------------------------------------
// printf-style logging macros (captures callsite info) 
// ------------------------------------------------------------------------------------------------
#define LOGF_DEBUG(fmt, ...) Logger::Log(LogLevel::Debug, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOGF_INFO(fmt, ...) Logger::Log(LogLevel::Info, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOGF_WARNING(fmt, ...) Logger::Log(LogLevel::Warning, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOGF_ERROR(fmt, ...) Logger::Log(LogLevel::Error, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)
#define LOGF_FATAL(fmt, ...) Logger::Log(LogLevel::Fatal, __FILE__, __LINE__, FUNCTION_NAME, fmt, ##__VA_ARGS__)

// ------------------------------------------------------------------------------------------------
// Debug-only short macros (auto-disables in Release)
// ------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT() printf("Line: %d --> %s --> %s \r\n", __LINE__,ExtractProjectName(__FILE__) ,ExtractFunctionName(FUNCTION_NAME))
#define DEBUGPRINT(fmt, ...) printf("Line: %d --> %s --> %s " fmt "\r\n", __LINE__ , ExtractProjectName(__FILE__), __FUNCTION__ , ##__VA_ARGS__)
#else
#define DEBUG_PRINT()
#define DEBUGPRINT(fmt, ...)
#endif
#endif // DEBUG_LOGGER_H
