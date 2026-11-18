#pragma once

#include <gtest/gtest.h>

#include <array>

#define COMPILE_TIME_TEST(X, Y) [[maybe_unused]] consteval void X##_##Y()

namespace ImmutableForest::Tests
{

    template <typename T, typename... TViewPack>
    [[nodiscard]] static consteval auto toArray(TViewPack&&... viewPack)
    {
        if constexpr (sizeof...(TViewPack) == 0)
        {
            return std::array<T, 0>{};
        }
        else
        {
            return std::to_array<T>({T{std::forward<TViewPack>(viewPack)}...});
        }
    }

} // namespace ImmutableForest::Tests
