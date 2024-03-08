#ifndef __TYPEDEFS_HPP__
#define __TYPEDEFS_HPP__

#include <memory>

template<class T>
using deleteFuncType = void(*)(T*);

template<class T, class D = std::default_delete<T>>
using Unp = std::unique_ptr<T, D>;
template<class T>
using Shp = std::shared_ptr<T>;
template<class T>
using Wkp = std::weak_ptr<T>;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#endif // __TYPEDEFS_HPP__
