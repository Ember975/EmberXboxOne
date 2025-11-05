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
// ReSharper disable CppInconsistentNaming
#ifndef D3D11_X
#define D3D11_X

#include <d3d11.h>
#include <format>

#include "dxgi1_5.h"

// remove all XBOX only flags passed to CreateDevice 
#define CREATE_DEVICE_FLAG_MASK (D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SWITCH_TO_REF | \
        D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS | D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUGGABLE | \
        D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY | D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT | D3D11_CREATE_DEVICE_VIDEO_SUPPORT)

typedef GUID DXGI_DEBUG_ID;

typedef enum D3D11_GRAPHICS_MEMORY_ACCESS_FLAG
{
    D3D11_GRAPHICS_MEMORY_ACCESS_CPU_CACHE_COHERENT = 0,
    D3D11_GRAPHICS_MEMORY_ACCESS_CPU_WRITECOMBINE_NONCOHERENT = 1,
    D3D11_GRAPHICS_MEMORY_ACCESS_CPU_CACHE_NONCOHERENT_GPU_READONLY = 2
} D3D11_GRAPHICS_MEMORY_ACCESS_FLAG;

typedef struct D3D11X_CREATE_DEVICE_PARAMETERS {
    UINT Version;
    UINT Flags;
    void* pOffchipTessellationBuffer;
    void* pTessellationFactorsBuffer;
    UINT DeferredDeletionThreadAffinityMask;
    UINT ImmediateContextDeRingSizeBytes;
    UINT ImmediateContextCeRingSizeBytes;
    UINT ImmediateContextDeSegmentSizeBytes;
    UINT ImmediateContextCeSegmentSizeBytes;
} D3D11X_CREATE_DEVICE_PARAMETERS;

typedef struct _DXGIX_FRAME_STATISTICS
{
    UINT64 CPUTimePresentCalled;
    UINT64 CPUTimeAddedToQueue;
    UINT32 QueueLengthAddedToQueue;
    UINT64 CPUTimeFrameComplete;
    UINT64 GPUTimeFrameComplete;
    UINT64 GPUCountTitleUsed;
    UINT64 GPUCountSystemUsed;
    UINT64 CPUTimeVSync;
    UINT64 GPUTimeVSync;
    UINT64 CPUTimeFlip;
    UINT64 GPUTimeFlip;
    UINT64 VSyncCount;
    FLOAT  PercentScanned;
    VOID* Cookie[ 2 ];
} DXGIX_FRAME_STATISTICS;

struct D3D11X_VIRTUAL_MEMORY_CONFIGURATION
{
    UINT Flags;
    UINT PageTableMemory4MBPageCount;
    UINT64 MinimumValidGraphicsAddress;
    UINT64 MaximumValidGraphicsAddress;
};

struct D3D_SEQ_COUNTER_DATA
{
    unsigned int ReadCount[ 12 ];
    unsigned int ReadEdcCount[ 12 ];
    unsigned int WriteCount[ 12 ];
    unsigned int WriteEdcCount[ 12 ];
};

typedef struct _DXGIX_PRESENTARRAY_PARAMETERS
{
    BOOL        Disable;
    BOOL        UsePreviousBuffer;
    D3D11_RECT  SourceRect;
    POINT       DestRectUpperLeft;
    FLOAT       ScaleFactorVert;
    FLOAT       ScaleFactorHorz;
    void*       Cookie;
    UINT        Flags;
} DXGIX_PRESENTARRAY_PARAMETERS;

typedef enum DXGIX_FRAME_NOTIFICATION
{
    FRAME_NOTIFICATION_QUEUED = 0,
    FRAME_NOTIFICATION_COMPLETED = 1,
    FRAME_NOTIFICATION_FLIPPED = 2
} DXGIX_FRAME_NOTIFICATION;

typedef enum DXGIX_VLINECOUNTER
{
    VLINECOUNTER0 = 0,
    VLINECOUNTER1 = 1
} DXGIX_VLINECOUNTER;
// @Patoke todo: reimplement
//struct D3D11_TEXTURE2D_DESC_X
//{
//    UINT Width;
//    UINT Height;
//    UINT MipLevels;
//    UINT ArraySize;
//    DXGI_FORMAT Format;
//    DXGI_SAMPLE_DESC SampleDesc;
//    D3D11_USAGE Usage;
//    UINT BindFlags;
//    UINT CPUAccessFlags;
//    UINT MiscFlags;
//    UINT ESRAMOffsetBytes;
//    UINT ESRAMUsageBytes;
//};
HRESULT __stdcall DeviceIoControlHelper(HANDLE hDevice);
HRESULT __stdcall VdMapAddressToEsram(
    HANDLE hDevice,
    DWORD flags,
    uintptr_t virtualAddress,
    UINT numPages,
    const UINT* pageList);

typedef enum WDEVENT_TYPE : int
{
	WDEVENT_TYPE_INVALID = 0,
    WDEVENT_TYPE_KEYBOARD_ENGAGE
} WDEVENT_TYPE;

extern "C" const GUID  DXGI_DEBUG_ALL;
DEFINE_GUID(DXGI_DEBUG_DX, 0x35cdd7fc, 0x13b2, 0x421d, 0xa5, 0xd7, 0x7e, 0x44, 0x51, 0x28, 0x7d, 0x64);
DEFINE_GUID(DXGI_DEBUG_DXGI, 0x25cddaa4, 0xb1c6, 0x47e1, 0xac, 0x3e, 0x98, 0x87, 0x5b, 0x5a, 0x2e, 0x2a);
DEFINE_GUID(DXGI_DEBUG_APP, 0x6cd6e01, 0x4219, 0x4ebd, 0x87, 0x9, 0x27, 0xed, 0x23, 0x36, 0xc, 0x62);
DEFINE_GUID(DXGI_DEBUG_D3D11, 0x4b99317b, 0xac39, 0x4aa6, 0xbb, 0xb, 0xba, 0xa0, 0x47, 0x84, 0x79, 0x8f);

#define DX_MAJOR 2
#define DX_MINOR 18

#define MAKEINTVERSION(major, minor) (((0LL + (major)) << 48) | ((0LL + (minor)) << 32))
#define DX_VERSION (((0LL + (DX_MAJOR)) << 48) | ((0LL + (DX_MINOR)) << 32))

#define D3DDECL_UUID(Uuid) __declspec(uuid(#Uuid))
#define D3DINTERFACE(Name, Guid0, Guid1, Guid2, Guid3, Guid4, \
            Guid5, Guid6, Guid7, Guid8, Guid9, Guid10) \
            class D3DDECL_UUID(Guid0-Guid1-Guid2-Guid3##Guid4-Guid5##Guid6##Guid7##Guid8##Guid9##Guid10) Name

#define TRACE_INTERFACE_NOT_HANDLED(class_name) \
    char iidstr[ sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}") ]; \
	OLECHAR iidwstr[ sizeof(iidstr) ]; \
	StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr)); \
	WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr); \
    MessageBoxA(NULL, std::format("[{}] INTERFACE NOT HANDLED: {}", class_name, iidstr).c_str(), "WD - d3d11_x", MB_OK) \

#define IGU_DEFINE_REF \
    ULONG AddRef( ) override {                                \
		wrapped_interface->AddRef( );                         \
		return InterlockedIncrement(&m_RefCount);             \
	}                                                         \
                                                              \
	ULONG Release( ) override {                               \
	    ULONG refCount = InterlockedDecrement(&m_RefCount);   \
		wrapped_interface->Release( );                        \
                                                              \
        if (refCount == 0)                                    \
        {                                                     \
            wrapped_interface->Release( );                    \
            delete this;                                      \
        }                                                     \
                                                              \
		return refCount;                                      \
	}                                                         \

#define TRACE_NOT_IMPLEMENTED(class_name) \
    MessageBoxA(NULL, std::format("[{}] NOT IMPLEMENTED\n{} - line {}", class_name, __FILE__, __LINE__).c_str(), "WD - d3d11_x", MB_OK) \

#endif

extern "C" __declspec(dllexport) void WD11XNotify_X(WDEVENT_TYPE event);
extern "C" __declspec(dllexport) void WDWaitForKeyboard(const char** outText);