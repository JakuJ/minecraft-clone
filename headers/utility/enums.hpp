#pragma once

#define GENERATE_ENUM_OPERATORS(eEnumType) \
inline void operator++(eEnumType& eVal) \
{ \
    eVal = eEnumType(eVal+1); \
} \
\
inline void operator++(eEnumType& eVal, int)  \
{ \
    eVal = eEnumType(eVal+1); \
} \
\
inline void operator--(eEnumType& eVal) \
{ \
    eVal = eEnumType(eVal-1); \
} \
\
inline void operator--(eEnumType& eVal, int) \
{ \
    eVal = eEnumType(eVal-1); \
}
