#include "ImmutableTreeConcepts.h"

#include "Testing.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace ImmutableForest::Tests
{

    enum class MyEnum
    {
    };

    class MyKey
    {
      public:

        MyKey() = delete;
        MyKey(MyKey const&) = default;
        MyKey& operator=(MyKey const&) = delete;
        MyKey(MyKey&&) = default;
        MyKey& operator=(MyKey&&) = delete;

        bool operator<(MyKey const&) const;
        bool operator<=(MyKey const&) const;
        bool operator==(MyKey const&) const;
        bool operator!=(MyKey const&) const;
        bool operator>=(MyKey const&) const;
        bool operator>(MyKey const&) const;
    };

    class MyKeyView
    {
      public:

        MyKeyView() = delete;
        MyKeyView(MyKeyView const&) = delete;
        MyKeyView& operator=(MyKeyView const&) = delete;
        MyKeyView(MyKeyView&&) = delete;
        MyKeyView& operator=(MyKeyView&&) = delete;

        operator MyKey() const;
        bool operator<(MyKey const&) const;
        bool operator<=(MyKey const&) const;
        bool operator==(MyKey const&) const;
        bool operator!=(MyKey const&) const;
        bool operator>=(MyKey const&) const;
        bool operator>(MyKey const&) const;
    };

    class MyValue
    {
      public:

        MyValue() = delete;
        MyValue(MyValue const&) = default;
        MyValue& operator=(MyValue const&) = delete;
        MyValue(MyValue&&) = default;
        MyValue& operator=(MyValue&&) = delete;

        bool operator==(MyValue const&) const;
        bool operator!=(MyValue const&) const;
    };

    class MyValueView
    {
      public:

        MyValueView() = delete;
        MyValueView(MyValueView const&) = delete;
        MyValueView& operator=(MyValueView const&) = delete;
        MyValueView(MyValueView&&) = delete;
        MyValueView& operator=(MyValueView&&) = delete;

        operator MyValue() const;
        bool operator==(MyValue const&) const;
        bool operator!=(MyValue const&) const;
    };

    COMPILE_TIME_TEST(ImmutableTreeConcepts_UnitTests, UnqualifiedType)
    {
        using T = int;

        static_assert(Concepts::Detail::UnqualifiedType<T>);
        static_assert(!Concepts::Detail::UnqualifiedType<T&>);
        static_assert(!Concepts::Detail::UnqualifiedType<T&&>);
        static_assert(Concepts::Detail::UnqualifiedType<T *>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const&>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const&&>);
        static_assert(Concepts::Detail::UnqualifiedType<T const *>);
        static_assert(!Concepts::Detail::UnqualifiedType<T volatile>);
        static_assert(!Concepts::Detail::UnqualifiedType<T volatile&>);
        static_assert(!Concepts::Detail::UnqualifiedType<T volatile&&>);
        static_assert(Concepts::Detail::UnqualifiedType<T volatile *>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const volatile>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const volatile&>);
        static_assert(!Concepts::Detail::UnqualifiedType<T const volatile&&>);
        static_assert(Concepts::Detail::UnqualifiedType<T const volatile *>);

        using P = int *;

        static_assert(Concepts::Detail::UnqualifiedType<P>);
        static_assert(!Concepts::Detail::UnqualifiedType<P&>);
        static_assert(!Concepts::Detail::UnqualifiedType<P&&>);
        static_assert(Concepts::Detail::UnqualifiedType<P *>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const&>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const&&>);
        static_assert(Concepts::Detail::UnqualifiedType<P const *>);
        static_assert(!Concepts::Detail::UnqualifiedType<P volatile>);
        static_assert(!Concepts::Detail::UnqualifiedType<P volatile&>);
        static_assert(!Concepts::Detail::UnqualifiedType<P volatile&&>);
        static_assert(Concepts::Detail::UnqualifiedType<P volatile *>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const volatile>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const volatile&>);
        static_assert(!Concepts::Detail::UnqualifiedType<P const volatile&&>);
        static_assert(Concepts::Detail::UnqualifiedType<P const volatile *>);
    }

    COMPILE_TIME_TEST(ImmutableTreeConcepts_UnitTests, KeyType)
    {
        static_assert(Concepts::KeyType<bool>);
        static_assert(Concepts::KeyType<char>);
        static_assert(Concepts::KeyType<signed char>);
        static_assert(Concepts::KeyType<unsigned char>);
        static_assert(Concepts::KeyType<wchar_t>);
        static_assert(Concepts::KeyType<char8_t>);
        static_assert(Concepts::KeyType<char16_t>);
        static_assert(Concepts::KeyType<char32_t>);
        static_assert(Concepts::KeyType<short>);
        static_assert(Concepts::KeyType<unsigned short>);
        static_assert(Concepts::KeyType<int>);
        static_assert(Concepts::KeyType<unsigned int>);
        static_assert(Concepts::KeyType<long>);
        static_assert(Concepts::KeyType<unsigned long>);
        static_assert(Concepts::KeyType<long long>);
        static_assert(Concepts::KeyType<unsigned long long>);
        static_assert(Concepts::KeyType<float>);
        static_assert(Concepts::KeyType<double>);
        static_assert(Concepts::KeyType<long double>);

        static_assert(!Concepts::KeyType<void>);
        static_assert(!Concepts::KeyType<std::nullptr_t>);

        static_assert(Concepts::KeyType<std::uint8_t>);
        static_assert(Concepts::KeyType<std::int8_t>);
        static_assert(Concepts::KeyType<std::uint16_t>);
        static_assert(Concepts::KeyType<std::int16_t>);
        static_assert(Concepts::KeyType<std::uint32_t>);
        static_assert(Concepts::KeyType<std::int32_t>);
        static_assert(Concepts::KeyType<std::uint64_t>);
        static_assert(Concepts::KeyType<std::int64_t>);

        static_assert(Concepts::KeyType<std::string>);
        static_assert(Concepts::KeyType<std::wstring>);
        static_assert(Concepts::KeyType<std::u8string>);
        static_assert(Concepts::KeyType<std::u16string>);
        static_assert(Concepts::KeyType<std::u32string>);

        static_assert(Concepts::KeyType<MyEnum>);
        static_assert(Concepts::KeyType<MyKey>);
    }

    COMPILE_TIME_TEST(ImmutableTreeConcepts_UnitTests, KeyViewType)
    {
        static_assert(Concepts::KeyViewType<bool, bool>);
        static_assert(Concepts::KeyViewType<bool const&, bool>);
        static_assert(Concepts::KeyViewType<bool&&, bool>);

        static_assert(Concepts::KeyViewType<char, char>);
        static_assert(Concepts::KeyViewType<char const&, char>);
        static_assert(Concepts::KeyViewType<char&&, char>);

        static_assert(Concepts::KeyViewType<signed char, signed char>);
        static_assert(Concepts::KeyViewType<signed char const&, signed char>);
        static_assert(Concepts::KeyViewType<signed char&&, signed char>);

        static_assert(Concepts::KeyViewType<unsigned char, unsigned char>);
        static_assert(Concepts::KeyViewType<unsigned char const&, unsigned char>);
        static_assert(Concepts::KeyViewType<unsigned char&&, unsigned char>);

        static_assert(Concepts::KeyViewType<wchar_t, wchar_t>);
        static_assert(Concepts::KeyViewType<wchar_t const&, wchar_t>);
        static_assert(Concepts::KeyViewType<wchar_t&&, wchar_t>);

        static_assert(Concepts::KeyViewType<char8_t, char8_t>);
        static_assert(Concepts::KeyViewType<char8_t const&, char8_t>);
        static_assert(Concepts::KeyViewType<char8_t&&, char8_t>);

        static_assert(Concepts::KeyViewType<char16_t, char16_t>);
        static_assert(Concepts::KeyViewType<char16_t const&, char16_t>);
        static_assert(Concepts::KeyViewType<char16_t&&, char16_t>);

        static_assert(Concepts::KeyViewType<char32_t, char32_t>);
        static_assert(Concepts::KeyViewType<char32_t const&, char32_t>);
        static_assert(Concepts::KeyViewType<char32_t&&, char32_t>);

        static_assert(Concepts::KeyViewType<short, short>);
        static_assert(Concepts::KeyViewType<short const&, short>);
        static_assert(Concepts::KeyViewType<short&&, short>);

        static_assert(Concepts::KeyViewType<unsigned short, unsigned short>);
        static_assert(Concepts::KeyViewType<unsigned short const&, unsigned short>);
        static_assert(Concepts::KeyViewType<unsigned short&&, unsigned short>);

        static_assert(Concepts::KeyViewType<int, int>);
        static_assert(Concepts::KeyViewType<int const&, int>);
        static_assert(Concepts::KeyViewType<int&&, int>);

        static_assert(Concepts::KeyViewType<unsigned int, unsigned int>);
        static_assert(Concepts::KeyViewType<unsigned int const&, unsigned int>);
        static_assert(Concepts::KeyViewType<unsigned int&&, unsigned int>);

        static_assert(Concepts::KeyViewType<long, long>);
        static_assert(Concepts::KeyViewType<long const&, long>);
        static_assert(Concepts::KeyViewType<long&&, long>);

        static_assert(Concepts::KeyViewType<unsigned long, unsigned long>);
        static_assert(Concepts::KeyViewType<unsigned long const&, unsigned long>);
        static_assert(Concepts::KeyViewType<unsigned long&&, unsigned long>);

        static_assert(Concepts::KeyViewType<long long, long long>);
        static_assert(Concepts::KeyViewType<long long const&, long long>);
        static_assert(Concepts::KeyViewType<long long&&, long long>);

        static_assert(Concepts::KeyViewType<unsigned long long, unsigned long long>);
        static_assert(Concepts::KeyViewType<unsigned long long const&, unsigned long long>);
        static_assert(Concepts::KeyViewType<unsigned long long&&, unsigned long long>);

        static_assert(Concepts::KeyViewType<float, float>);
        static_assert(Concepts::KeyViewType<float const&, float>);
        static_assert(Concepts::KeyViewType<float&&, float>);

        static_assert(Concepts::KeyViewType<double, double>);
        static_assert(Concepts::KeyViewType<double const&, double>);
        static_assert(Concepts::KeyViewType<double&&, double>);

        static_assert(Concepts::KeyViewType<long double, long double>);
        static_assert(Concepts::KeyViewType<long double const&, long double>);
        static_assert(Concepts::KeyViewType<long double&&, long double>);

        static_assert(Concepts::KeyViewType<std::uint8_t, std::uint8_t>);
        static_assert(Concepts::KeyViewType<std::uint8_t const&, std::uint8_t>);
        static_assert(Concepts::KeyViewType<std::uint8_t&&, std::uint8_t>);

        static_assert(Concepts::KeyViewType<std::int8_t, std::int8_t>);
        static_assert(Concepts::KeyViewType<std::int8_t const&, std::int8_t>);
        static_assert(Concepts::KeyViewType<std::int8_t&&, std::int8_t>);

        static_assert(Concepts::KeyViewType<std::uint16_t, std::uint16_t>);
        static_assert(Concepts::KeyViewType<std::uint16_t const&, std::uint16_t>);
        static_assert(Concepts::KeyViewType<std::uint16_t&&, std::uint16_t>);

        static_assert(Concepts::KeyViewType<std::int16_t, std::int16_t>);
        static_assert(Concepts::KeyViewType<std::int16_t const&, std::int16_t>);
        static_assert(Concepts::KeyViewType<std::int16_t&&, std::int16_t>);

        static_assert(Concepts::KeyViewType<std::uint32_t, std::uint32_t>);
        static_assert(Concepts::KeyViewType<std::uint32_t const&, std::uint32_t>);
        static_assert(Concepts::KeyViewType<std::uint32_t&&, std::uint32_t>);

        static_assert(Concepts::KeyViewType<std::int32_t, std::int32_t>);
        static_assert(Concepts::KeyViewType<std::int32_t const&, std::int32_t>);
        static_assert(Concepts::KeyViewType<std::int32_t&&, std::int32_t>);

        static_assert(Concepts::KeyViewType<std::uint64_t, std::uint64_t>);
        static_assert(Concepts::KeyViewType<std::uint64_t const&, std::uint64_t>);
        static_assert(Concepts::KeyViewType<std::uint64_t&&, std::uint64_t>);

        static_assert(Concepts::KeyViewType<std::int64_t, std::int64_t>);
        static_assert(Concepts::KeyViewType<std::int64_t const&, std::int64_t>);
        static_assert(Concepts::KeyViewType<std::int64_t&&, std::int64_t>);

        static_assert(Concepts::KeyViewType<std::string, std::string>);
        static_assert(Concepts::KeyViewType<std::string const&, std::string>);
        static_assert(Concepts::KeyViewType<std::string&&, std::string>);
        static_assert(Concepts::KeyViewType<std::string_view, std::string>);
        static_assert(Concepts::KeyViewType<std::string_view const&, std::string>);
        static_assert(Concepts::KeyViewType<std::string_view&&, std::string>);
        static_assert(Concepts::KeyViewType<char const[123], std::string>);
        static_assert(Concepts::KeyViewType<char const *, std::string>);

        static_assert(Concepts::KeyViewType<std::wstring, std::wstring>);
        static_assert(Concepts::KeyViewType<std::wstring const&, std::wstring>);
        static_assert(Concepts::KeyViewType<std::wstring&&, std::wstring>);
        static_assert(Concepts::KeyViewType<std::wstring_view, std::wstring>);
        static_assert(Concepts::KeyViewType<std::wstring_view const&, std::wstring>);
        static_assert(Concepts::KeyViewType<std::wstring_view&&, std::wstring>);
        static_assert(Concepts::KeyViewType<wchar_t const[123], std::wstring>);
        static_assert(Concepts::KeyViewType<wchar_t const *, std::wstring>);

        static_assert(Concepts::KeyViewType<std::u8string, std::u8string>);
        static_assert(Concepts::KeyViewType<std::u8string const&, std::u8string>);
        static_assert(Concepts::KeyViewType<std::u8string&&, std::u8string>);
        static_assert(Concepts::KeyViewType<std::u8string_view, std::u8string>);
        static_assert(Concepts::KeyViewType<std::u8string_view const&, std::u8string>);
        static_assert(Concepts::KeyViewType<std::u8string_view&&, std::u8string>);
        static_assert(Concepts::KeyViewType<char8_t const[123], std::u8string>);
        static_assert(Concepts::KeyViewType<char8_t const *, std::u8string>);

        static_assert(Concepts::KeyViewType<std::u16string, std::u16string>);
        static_assert(Concepts::KeyViewType<std::u16string const&, std::u16string>);
        static_assert(Concepts::KeyViewType<std::u16string&&, std::u16string>);
        static_assert(Concepts::KeyViewType<std::u16string_view, std::u16string>);
        static_assert(Concepts::KeyViewType<std::u16string_view const&, std::u16string>);
        static_assert(Concepts::KeyViewType<std::u16string_view&&, std::u16string>);
        static_assert(Concepts::KeyViewType<char16_t const[123], std::u16string>);
        static_assert(Concepts::KeyViewType<char16_t const *, std::u16string>);

        static_assert(Concepts::KeyViewType<std::u32string, std::u32string>);
        static_assert(Concepts::KeyViewType<std::u32string const&, std::u32string>);
        static_assert(Concepts::KeyViewType<std::u32string&&, std::u32string>);
        static_assert(Concepts::KeyViewType<std::u32string_view, std::u32string>);
        static_assert(Concepts::KeyViewType<std::u32string_view const&, std::u32string>);
        static_assert(Concepts::KeyViewType<std::u32string_view&&, std::u32string>);
        static_assert(Concepts::KeyViewType<char32_t const[123], std::u32string>);
        static_assert(Concepts::KeyViewType<char32_t const *, std::u32string>);

        static_assert(Concepts::KeyViewType<MyEnum, MyEnum>);
        static_assert(Concepts::KeyViewType<MyEnum const&, MyEnum>);
        static_assert(Concepts::KeyViewType<MyEnum&&, MyEnum>);

        static_assert(Concepts::KeyViewType<MyKey, MyKey>);
        static_assert(Concepts::KeyViewType<MyKey const&, MyKey>);
        static_assert(Concepts::KeyViewType<MyKey&&, MyKey>);
        static_assert(Concepts::KeyViewType<MyKeyView, MyKey>);
        static_assert(Concepts::KeyViewType<MyKeyView const&, MyKey>);
        static_assert(Concepts::KeyViewType<MyKeyView&&, MyKey>);
    }

    COMPILE_TIME_TEST(ImmutableTreeConcepts_UnitTests, ValueType)
    {
        static_assert(Concepts::ValueType<bool>);
        static_assert(Concepts::ValueType<char>);
        static_assert(Concepts::ValueType<signed char>);
        static_assert(Concepts::ValueType<unsigned char>);
        static_assert(Concepts::ValueType<wchar_t>);
        static_assert(Concepts::ValueType<char8_t>);
        static_assert(Concepts::ValueType<char16_t>);
        static_assert(Concepts::ValueType<char32_t>);
        static_assert(Concepts::ValueType<short>);
        static_assert(Concepts::ValueType<unsigned short>);
        static_assert(Concepts::ValueType<int>);
        static_assert(Concepts::ValueType<unsigned int>);
        static_assert(Concepts::ValueType<long>);
        static_assert(Concepts::ValueType<unsigned long>);
        static_assert(Concepts::ValueType<long long>);
        static_assert(Concepts::ValueType<unsigned long long>);
        static_assert(Concepts::ValueType<float>);
        static_assert(Concepts::ValueType<double>);
        static_assert(Concepts::ValueType<long double>);
        static_assert(Concepts::ValueType<std::nullptr_t>);

        static_assert(!Concepts::ValueType<void>);

        static_assert(Concepts::ValueType<std::uint8_t>);
        static_assert(Concepts::ValueType<std::int8_t>);
        static_assert(Concepts::ValueType<std::uint16_t>);
        static_assert(Concepts::ValueType<std::int16_t>);
        static_assert(Concepts::ValueType<std::uint32_t>);
        static_assert(Concepts::ValueType<std::int32_t>);
        static_assert(Concepts::ValueType<std::uint64_t>);
        static_assert(Concepts::ValueType<std::int64_t>);

        static_assert(Concepts::ValueType<std::string>);
        static_assert(Concepts::ValueType<std::wstring>);
        static_assert(Concepts::ValueType<std::u8string>);
        static_assert(Concepts::ValueType<std::u16string>);
        static_assert(Concepts::ValueType<std::u32string>);

        static_assert(Concepts::ValueType<MyEnum>);
        static_assert(Concepts::ValueType<MyKey>);
        static_assert(Concepts::ValueType<MyValue>);
    }

    COMPILE_TIME_TEST(ImmutableTreeConcepts_UnitTests, ValueViewType)
    {
        static_assert(Concepts::ValueViewType<bool, bool>);
        static_assert(Concepts::ValueViewType<bool const&, bool>);
        static_assert(Concepts::ValueViewType<bool&&, bool>);

        static_assert(Concepts::ValueViewType<char, char>);
        static_assert(Concepts::ValueViewType<char const&, char>);
        static_assert(Concepts::ValueViewType<char&&, char>);

        static_assert(Concepts::ValueViewType<signed char, signed char>);
        static_assert(Concepts::ValueViewType<signed char const&, signed char>);
        static_assert(Concepts::ValueViewType<signed char&&, signed char>);

        static_assert(Concepts::ValueViewType<unsigned char, unsigned char>);
        static_assert(Concepts::ValueViewType<unsigned char const&, unsigned char>);
        static_assert(Concepts::ValueViewType<unsigned char&&, unsigned char>);

        static_assert(Concepts::ValueViewType<wchar_t, wchar_t>);
        static_assert(Concepts::ValueViewType<wchar_t const&, wchar_t>);
        static_assert(Concepts::ValueViewType<wchar_t&&, wchar_t>);

        static_assert(Concepts::ValueViewType<char8_t, char8_t>);
        static_assert(Concepts::ValueViewType<char8_t const&, char8_t>);
        static_assert(Concepts::ValueViewType<char8_t&&, char8_t>);

        static_assert(Concepts::ValueViewType<char16_t, char16_t>);
        static_assert(Concepts::ValueViewType<char16_t const&, char16_t>);
        static_assert(Concepts::ValueViewType<char16_t&&, char16_t>);

        static_assert(Concepts::ValueViewType<char32_t, char32_t>);
        static_assert(Concepts::ValueViewType<char32_t const&, char32_t>);
        static_assert(Concepts::ValueViewType<char32_t&&, char32_t>);

        static_assert(Concepts::ValueViewType<short, short>);
        static_assert(Concepts::ValueViewType<short const&, short>);
        static_assert(Concepts::ValueViewType<short&&, short>);

        static_assert(Concepts::ValueViewType<unsigned short, unsigned short>);
        static_assert(Concepts::ValueViewType<unsigned short const&, unsigned short>);
        static_assert(Concepts::ValueViewType<unsigned short&&, unsigned short>);

        static_assert(Concepts::ValueViewType<int, int>);
        static_assert(Concepts::ValueViewType<int const&, int>);
        static_assert(Concepts::ValueViewType<int&&, int>);

        static_assert(Concepts::ValueViewType<unsigned int, unsigned int>);
        static_assert(Concepts::ValueViewType<unsigned int const&, unsigned int>);
        static_assert(Concepts::ValueViewType<unsigned int&&, unsigned int>);

        static_assert(Concepts::ValueViewType<long, long>);
        static_assert(Concepts::ValueViewType<long const&, long>);
        static_assert(Concepts::ValueViewType<long&&, long>);

        static_assert(Concepts::ValueViewType<unsigned long, unsigned long>);
        static_assert(Concepts::ValueViewType<unsigned long const&, unsigned long>);
        static_assert(Concepts::ValueViewType<unsigned long&&, unsigned long>);

        static_assert(Concepts::ValueViewType<long long, long long>);
        static_assert(Concepts::ValueViewType<long long const&, long long>);
        static_assert(Concepts::ValueViewType<long long&&, long long>);

        static_assert(Concepts::ValueViewType<unsigned long long, unsigned long long>);
        static_assert(Concepts::ValueViewType<unsigned long long const&, unsigned long long>);
        static_assert(Concepts::ValueViewType<unsigned long long&&, unsigned long long>);

        static_assert(Concepts::ValueViewType<float, float>);
        static_assert(Concepts::ValueViewType<float const&, float>);
        static_assert(Concepts::ValueViewType<float&&, float>);

        static_assert(Concepts::ValueViewType<double, double>);
        static_assert(Concepts::ValueViewType<double const&, double>);
        static_assert(Concepts::ValueViewType<double&&, double>);

        static_assert(Concepts::ValueViewType<long double, long double>);
        static_assert(Concepts::ValueViewType<long double const&, long double>);
        static_assert(Concepts::ValueViewType<long double&&, long double>);

        static_assert(Concepts::ValueViewType<std::nullptr_t, std::nullptr_t>);
        static_assert(Concepts::ValueViewType<std::nullptr_t const&, std::nullptr_t>);
        static_assert(Concepts::ValueViewType<std::nullptr_t&&, std::nullptr_t>);

        static_assert(Concepts::ValueViewType<std::uint8_t, std::uint8_t>);
        static_assert(Concepts::ValueViewType<std::uint8_t const&, std::uint8_t>);
        static_assert(Concepts::ValueViewType<std::uint8_t&&, std::uint8_t>);

        static_assert(Concepts::ValueViewType<std::int8_t, std::int8_t>);
        static_assert(Concepts::ValueViewType<std::int8_t const&, std::int8_t>);
        static_assert(Concepts::ValueViewType<std::int8_t&&, std::int8_t>);

        static_assert(Concepts::ValueViewType<std::uint16_t, std::uint16_t>);
        static_assert(Concepts::ValueViewType<std::uint16_t const&, std::uint16_t>);
        static_assert(Concepts::ValueViewType<std::uint16_t&&, std::uint16_t>);

        static_assert(Concepts::ValueViewType<std::int16_t, std::int16_t>);
        static_assert(Concepts::ValueViewType<std::int16_t const&, std::int16_t>);
        static_assert(Concepts::ValueViewType<std::int16_t&&, std::int16_t>);

        static_assert(Concepts::ValueViewType<std::uint32_t, std::uint32_t>);
        static_assert(Concepts::ValueViewType<std::uint32_t const&, std::uint32_t>);
        static_assert(Concepts::ValueViewType<std::uint32_t&&, std::uint32_t>);

        static_assert(Concepts::ValueViewType<std::int32_t, std::int32_t>);
        static_assert(Concepts::ValueViewType<std::int32_t const&, std::int32_t>);
        static_assert(Concepts::ValueViewType<std::int32_t&&, std::int32_t>);

        static_assert(Concepts::ValueViewType<std::uint64_t, std::uint64_t>);
        static_assert(Concepts::ValueViewType<std::uint64_t const&, std::uint64_t>);
        static_assert(Concepts::ValueViewType<std::uint64_t&&, std::uint64_t>);

        static_assert(Concepts::ValueViewType<std::int64_t, std::int64_t>);
        static_assert(Concepts::ValueViewType<std::int64_t const&, std::int64_t>);
        static_assert(Concepts::ValueViewType<std::int64_t&&, std::int64_t>);

        static_assert(Concepts::ValueViewType<std::string, std::string>);
        static_assert(Concepts::ValueViewType<std::string const&, std::string>);
        static_assert(Concepts::ValueViewType<std::string&&, std::string>);
        static_assert(Concepts::ValueViewType<std::string_view, std::string>);
        static_assert(Concepts::ValueViewType<std::string_view const&, std::string>);
        static_assert(Concepts::ValueViewType<std::string_view&&, std::string>);
        static_assert(Concepts::ValueViewType<char const[123], std::string>);
        static_assert(Concepts::ValueViewType<char const *, std::string>);

        static_assert(Concepts::ValueViewType<std::wstring, std::wstring>);
        static_assert(Concepts::ValueViewType<std::wstring const&, std::wstring>);
        static_assert(Concepts::ValueViewType<std::wstring&&, std::wstring>);
        static_assert(Concepts::ValueViewType<std::wstring_view, std::wstring>);
        static_assert(Concepts::ValueViewType<std::wstring_view const&, std::wstring>);
        static_assert(Concepts::ValueViewType<std::wstring_view&&, std::wstring>);
        static_assert(Concepts::ValueViewType<wchar_t const[123], std::wstring>);
        static_assert(Concepts::ValueViewType<wchar_t const *, std::wstring>);

        static_assert(Concepts::ValueViewType<std::u8string, std::u8string>);
        static_assert(Concepts::ValueViewType<std::u8string const&, std::u8string>);
        static_assert(Concepts::ValueViewType<std::u8string&&, std::u8string>);
        static_assert(Concepts::ValueViewType<std::u8string_view, std::u8string>);
        static_assert(Concepts::ValueViewType<std::u8string_view const&, std::u8string>);
        static_assert(Concepts::ValueViewType<std::u8string_view&&, std::u8string>);
        static_assert(Concepts::ValueViewType<char8_t const[123], std::u8string>);
        static_assert(Concepts::ValueViewType<char8_t const *, std::u8string>);

        static_assert(Concepts::ValueViewType<std::u16string, std::u16string>);
        static_assert(Concepts::ValueViewType<std::u16string const&, std::u16string>);
        static_assert(Concepts::ValueViewType<std::u16string&&, std::u16string>);
        static_assert(Concepts::ValueViewType<std::u16string_view, std::u16string>);
        static_assert(Concepts::ValueViewType<std::u16string_view const&, std::u16string>);
        static_assert(Concepts::ValueViewType<std::u16string_view&&, std::u16string>);
        static_assert(Concepts::ValueViewType<char16_t const[123], std::u16string>);
        static_assert(Concepts::ValueViewType<char16_t const *, std::u16string>);

        static_assert(Concepts::ValueViewType<std::u32string, std::u32string>);
        static_assert(Concepts::ValueViewType<std::u32string const&, std::u32string>);
        static_assert(Concepts::ValueViewType<std::u32string&&, std::u32string>);
        static_assert(Concepts::ValueViewType<std::u32string_view, std::u32string>);
        static_assert(Concepts::ValueViewType<std::u32string_view const&, std::u32string>);
        static_assert(Concepts::ValueViewType<std::u32string_view&&, std::u32string>);
        static_assert(Concepts::ValueViewType<char32_t const[123], std::u32string>);
        static_assert(Concepts::ValueViewType<char32_t const *, std::u32string>);

        static_assert(Concepts::ValueViewType<MyEnum, MyEnum>);
        static_assert(Concepts::ValueViewType<MyEnum const&, MyEnum>);
        static_assert(Concepts::ValueViewType<MyEnum&&, MyEnum>);

        static_assert(Concepts::ValueViewType<MyKey, MyKey>);
        static_assert(Concepts::ValueViewType<MyKey const&, MyKey>);
        static_assert(Concepts::ValueViewType<MyKey&&, MyKey>);

        static_assert(Concepts::ValueViewType<MyValue, MyValue>);
        static_assert(Concepts::ValueViewType<MyValue const&, MyValue>);
        static_assert(Concepts::ValueViewType<MyValue&&, MyValue>);
        static_assert(Concepts::ValueViewType<MyValueView, MyValue>);
        static_assert(Concepts::ValueViewType<MyValueView const&, MyValue>);
        static_assert(Concepts::ValueViewType<MyValueView&&, MyValue>);
    }

} // namespace ImmutableForest::Tests
