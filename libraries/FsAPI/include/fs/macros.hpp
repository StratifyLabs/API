#ifndef FSAPI_FS_MACROS_HPP
#define FSAPI_FS_MACROS_HPP

#if !defined __link
#define MCU_INT_CAST(var) ((void *)(u32)var)
#define FSAPI_LINK_DEFAULT_PAGE_SIZE 512
#else
#define FSAPI_LINK_DEFAULT_PAGE_SIZE 4096
#undef fileno
#define MCU_INT_CAST(var) ((void *)(u64)var)
#endif

#endif // FSAPI_FS_MACROS_HPP
