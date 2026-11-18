#pragma once

#include <benchmark/benchmark.h>

#include <array>

namespace ImmutableForest::Benchmarks
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

} // namespace ImmutableForest::Benchmarks
