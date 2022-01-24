

#pragma once
#pragma warning(disable : 5039)   // pointer or reference to potentially throwing function passed
                                  // to 'extern "C"' function under -EHc. Undefined behavior may occur if this
                                  // function throws an exception.

#ifndef _DEBUG
#    pragma warning(disable : 4710)   // <function> function not inlined
#    pragma warning(disable : 4711)   // <function> selected for automatic inline expansion
#endif

#pragma warning(disable : 5045)   // Compiler will insert Spectre mitigation for memory
                                  // load if /Qspectre switch specified

#pragma warning(disable: )