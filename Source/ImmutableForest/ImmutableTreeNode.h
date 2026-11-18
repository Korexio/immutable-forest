#pragma once

#include "ImmutableTreeConcepts.h"

#include <algorithm>
#include <format>
#include <iterator>
#include <memory>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ImmutableForest
{

    template <Concepts::KeyType TKey, Concepts::ValueType TValue>
    class ImmutableTreeNode final
    {
      public:

        using Key_t = TKey;
        using Value_t = TValue;
        using ImmutableTreeNode_t = ImmutableTreeNode;
        using SharedImmutableTreeNode_t = std::shared_ptr<ImmutableTreeNode_t const>;

      private:

        struct PrivateAccess
        {
            explicit PrivateAccess() = default;
        };

        using Vector_t = std::vector<SharedImmutableTreeNode_t>;

        Key_t const m_key;
        Value_t const m_value;
        Vector_t const m_nodes;

        static void assume(bool value, std::string_view message)
        {
            if (!value)
            {
                throw std::runtime_error(std::string(message));
            }
        }

        template <Concepts::KeyViewType<Key_t> TKeyView>
        [[nodiscard]] static auto search(Vector_t const& vector, TKeyView const& keyView)
        {
            return std::lower_bound(vector.begin(), vector.end(), keyView, [](SharedImmutableTreeNode_t const& node, auto const& keyView) { return node->m_key < keyView; });
        }

        template <Concepts::KeyViewType<Key_t> TKeyView, Concepts::ValueViewType<Value_t> TValueView, typename TNodesView>
        requires(std::constructible_from<Vector_t, TNodesView>)
        [[nodiscard]] static SharedImmutableTreeNode_t create(TKeyView&& keyView, TValueView&& valueView, TNodesView&& nodesView)
        {
            return std::make_shared<ImmutableTreeNode_t const>(std::forward<TKeyView>(keyView), std::forward<TValueView>(valueView), std::forward<TNodesView>(nodesView), PrivateAccess{});
        }

        template <Concepts::KeyViewType<Key_t> TKeyView, Concepts::PathViewIteratorType<Key_t> TBegin, std::sentinel_for<TBegin> TEnd, Concepts::ValueViewType<Value_t> TValueView>
        [[nodiscard]] static SharedImmutableTreeNode_t setValue(SharedImmutableTreeNode_t const& node, TKeyView&& keyView, TBegin const& begin, TEnd const& end, TValueView&& valueView)
        {
            if (node == nullptr)
            {
                Vector_t vector{};
                vector.emplace_back(setValue(nullptr, begin, end, std::forward<TValueView>(valueView)));
                return create(keyView, Value_t{}, std::move(vector));
            }
            else
            {
                assume(keyView == node->m_key, "Key view must match node key.");

                auto iterator = search(node->m_nodes, *begin);

                Vector_t vector{};
                if ((iterator == node->m_nodes.end()) || ((*iterator)->m_key != (*begin)))
                {
                    // Add new node.
                    vector.reserve(node->m_nodes.size() + 1u);
                    std::copy(node->m_nodes.begin(), iterator, std::back_inserter(vector));
                    vector.emplace_back(setValue(nullptr, begin, end, std::forward<TValueView>(valueView)));
                    std::copy(iterator, node->m_nodes.end(), std::back_inserter(vector));
                }
                else
                {
                    if ((*iterator)->m_value == valueView)
                    {
                        return node;
                    }

                    // Replace node.
                    vector.reserve(node->m_nodes.size());
                    std::copy(node->m_nodes.begin(), iterator, std::back_inserter(vector));
                    vector.emplace_back(setValue(*iterator, begin, end, std::forward<TValueView>(valueView)));
                    std::copy(std::ranges::next(iterator), node->m_nodes.end(), std::back_inserter(vector));
                }

                return create(node->m_key, node->m_value, std::move(vector));
            }
        }

        template <Concepts::PathViewIteratorType<Key_t> TBegin, std::sentinel_for<TBegin> TEnd, Concepts::ValueViewType<Value_t> TValueView>
        [[nodiscard]] static SharedImmutableTreeNode_t setValue(SharedImmutableTreeNode_t const& node, TBegin const& begin, TEnd const& end, TValueView&& valueView)
        {
            if (begin == end)
            {
                throw std::invalid_argument("Path must no be empty.");
            }

            auto const next{std::ranges::next(begin)};
            if (next == end)
            {
                // Leaf node.
                if (node == nullptr)
                {
                    return create(*begin, std::forward<TValueView>(valueView), Vector_t{});
                }
                else
                {
                    assume(*begin == node->m_key, "Key view must match node key.");

                    if (node->m_value == valueView)
                    {
                        return node;
                    }

                    return create(node->m_key, std::forward<TValueView>(valueView), node->m_nodes);
                }
            }

            return setValue(node, *begin, next, end, std::forward<TValueView>(valueView));
        }

      public:

        ImmutableTreeNode() = delete;
        ImmutableTreeNode(ImmutableTreeNode const&) = delete;
        ImmutableTreeNode& operator=(ImmutableTreeNode const&) = delete;
        ImmutableTreeNode(ImmutableTreeNode&&) = delete;
        ImmutableTreeNode& operator=(ImmutableTreeNode&&) = delete;
        ~ImmutableTreeNode() = default;

        template <Concepts::KeyViewType<Key_t> TKeyView, Concepts::ValueViewType<Value_t> TValueView, typename TNodesView>
        requires(std::constructible_from<Vector_t, TNodesView>)
        ImmutableTreeNode(TKeyView&& keyView, TValueView&& valueView, TNodesView&& nodesView, [[maybe_unused]] PrivateAccess)
            : m_key(std::forward<TKeyView>(keyView)), m_value(std::forward<TValueView>(valueView)), m_nodes(std::forward<TNodesView>(nodesView))
        {
        }

        // Key

        [[nodiscard]] Key_t const& getKeyView() const& { return m_key; }

        Key_t const& getKeyView() const&& = delete;

        // Value

        [[nodiscard]] Value_t const& getValueView() const& { return m_value; }

        Value_t const& getValueView() const&& = delete;

        // Nodes

        [[nodiscard]] std::span<SharedImmutableTreeNode_t const> getNodesView() const& { return m_nodes; }

        std::span<SharedImmutableTreeNode_t const> getNodesView() const&& = delete;

        template <Concepts::KeyViewType<Key_t> TKeyView>
        [[nodiscard]] SharedImmutableTreeNode_t const& getNodeView(TKeyView const& keyView) const&
        {
            auto iterator = search(m_nodes, keyView);

            if ((iterator == this->m_nodes.end() || (*iterator)->m_key != keyView))
            {
                throw std::out_of_range(std::format("Node with key '{0}' not found.", keyView));
            }

            return *iterator;
        }

        template <Concepts::KeyViewType<Key_t> TKeyView>
        SharedImmutableTreeNode_t const& getNodeView(TKeyView const& keyView) const&& = delete;

        // Factory methods

        template <Concepts::PathViewType<Key_t> TPath, Concepts::ValueViewType<Value_t> TValueView>
        [[nodiscard]] static SharedImmutableTreeNode_t setValue(SharedImmutableTreeNode_t const& root, TPath const& path, TValueView&& valueView)
        {
            return setValue(root, Key_t{}, std::ranges::begin(path), std::ranges::end(path), std::forward<TValueView>(valueView));
        }

        template <Concepts::PathViewType<Key_t> TPath>
        [[nodiscard]] static SharedImmutableTreeNode_t remove(SharedImmutableTreeNode_t const& root, TPath const& path)
        {
            return remove(root, std::ranges::begin(path), std::ranges::end(path));
        }
    };

} // namespace ImmutableForest

namespace ImmutableForest::Concepts::Detail
{

    template <typename T>
    inline constexpr bool IsImmutableTreeNodeType_v = false;

    template <Concepts::KeyType TKey, Concepts::ValueType TValue>
    inline constexpr bool IsImmutableTreeNodeType_v<ImmutableTreeNode<TKey, TValue>> = true;

} // namespace ImmutableForest::Concepts::Detail

namespace ImmutableForest::Concepts
{

    template <typename T>
    concept ImmutableTreeNodeType = Detail::IsImmutableTreeNodeType_v<T>;

} // namespace ImmutableForest::Concepts
