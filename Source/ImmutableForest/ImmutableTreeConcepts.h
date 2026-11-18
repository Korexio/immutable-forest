#pragma once

#include <concepts>
#include <iterator>
#include <ranges>

namespace ImmutableForest::Concepts::Detail
{

    template <typename T>
    concept UnqualifiedType = std::same_as<std::remove_cvref_t<T>, T>;

} // namespace ImmutableForest::Concepts::Detail

namespace ImmutableForest::Concepts
{

    template <typename TKey>
    concept KeyType = Detail::UnqualifiedType<TKey> && std::totally_ordered<TKey>;

    template <typename TKeyView, typename TKey>
    concept KeyViewType = KeyType<TKey> && std::constructible_from<TKey, TKeyView> && std::totally_ordered_with<TKey, TKeyView>;


    template <typename TValue>
    concept ValueType = Detail::UnqualifiedType<TValue> && std::equality_comparable<TValue>;

    template <typename TValueView, typename TValue>
    concept ValueViewType = ValueType<TValue> && std::constructible_from<TValue, TValueView> && std::equality_comparable_with<TValue, TValueView>;


    template <typename TPath, typename TKey>
    concept PathViewType = std::ranges::input_range<TPath> && KeyViewType<std::ranges::range_reference_t<TPath const&>, TKey>;

    template <typename TPathIterator, typename TKey>
    concept PathViewIteratorType = std::input_iterator<TPathIterator> && KeyViewType<std::iter_reference_t<TPathIterator const&>, TKey>;

} // namespace ImmutableForest::Concepts
