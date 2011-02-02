
#ifndef PBGE_EXPORT_
#define PBGE_EXPORT_ 1

#include <vector>
#include <string>

#ifdef _MSC_VER
    // Disable the deprecation warning
    #pragma warning(disable: 4996)
    #pragma warning(disable: 4251)
    #pragma warning(disable: 4275)

    #ifndef PBGE_LIBRARY
        #define PBGE_EXPORT __declspec(dllimport)
        #define EXP_TEMPLATE
    #else
        #define PBGE_EXPORT __declspec(dllexport)
        #define EXP_TEMPLATE
    #endif
    EXP_TEMPLATE template class PBGE_EXPORT std::allocator<std::string>; 
   // EXP_TEMPLATE template class PBGE_EXPORT std::vector<std::string>;
#else
    #define PBGE_EXPORT 
#endif

#endif

