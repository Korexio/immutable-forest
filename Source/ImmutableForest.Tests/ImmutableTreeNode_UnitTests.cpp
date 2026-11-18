#include "ImmutableTreeNode.h"

#include "Testing.h"

#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ImmutableForest::Tests
{

    template <Concepts::ImmutableTreeNodeType TImmutableTreeNode>
    auto createTestTree()
    {
        using ImmutableTreeNode_t = TImmutableTreeNode;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t root{nullptr};

        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C"), 3)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "F"), 6)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "G"), 7)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A"), 1)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "E"), 5)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "B"), 2)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "B", "D"), 4)};
        root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("H"), 8)};

        return root;
    }

    // ImmutableTreeNode_t::setValue

    TEST(ImmutableTreeNode_UnitTests, setValue_create_Empty_Path)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;

        ASSERT_THROW(static_cast<void>(ImmutableTreeNode_t::setValue(nullptr, toArray<std::string_view>(), 100)), std::exception);
    }

    TEST(ImmutableTreeNode_UnitTests, setValue_create_A)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t const root{ImmutableTreeNode_t::setValue(nullptr, toArray<std::string_view>("A"), 100)};

        ASSERT_NE(root, nullptr);
        ASSERT_EQ(root->getKeyView(), "");
        ASSERT_EQ(root->getValueView(), 0);
        ASSERT_EQ(root->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& a = root->getNodesView()[0];

        ASSERT_NE(a, nullptr);
        ASSERT_EQ(a->getKeyView(), "A");
        ASSERT_EQ(a->getValueView(), 100);
        ASSERT_TRUE(a->getNodesView().empty());
    }

    TEST(ImmutableTreeNode_UnitTests, setValue_create_A_B)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t const root{ImmutableTreeNode_t::setValue(nullptr, toArray<std::string_view>("A", "B"), 200)};

        ASSERT_NE(root, nullptr);
        ASSERT_EQ(root->getKeyView(), "");
        ASSERT_EQ(root->getValueView(), 0);
        ASSERT_EQ(root->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& a = root->getNodesView()[0];

        ASSERT_NE(a, nullptr);
        ASSERT_EQ(a->getKeyView(), "A");
        ASSERT_EQ(a->getValueView(), 0);
        ASSERT_EQ(a->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& b = a->getNodesView()[0];

        ASSERT_NE(b, nullptr);
        ASSERT_EQ(b->getKeyView(), "B");
        ASSERT_EQ(b->getValueView(), 200);
        ASSERT_EQ(b->getNodesView().size(), 0);
    }

    TEST(ImmutableTreeNode_UnitTests, setValue_create_A_B_C)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t const root{ImmutableTreeNode_t::setValue(nullptr, toArray<std::string_view>("A", "B", "C"), 300)};

        ASSERT_NE(root, nullptr);
        ASSERT_EQ(root->getKeyView(), "");
        ASSERT_EQ(root->getValueView(), 0);
        ASSERT_EQ(root->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& a = root->getNodesView()[0];

        ASSERT_NE(a, nullptr);
        ASSERT_EQ(a->getKeyView(), "A");
        ASSERT_EQ(a->getValueView(), 0);
        ASSERT_EQ(a->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& b = a->getNodesView()[0];

        ASSERT_NE(b, nullptr);
        ASSERT_EQ(b->getKeyView(), "B");
        ASSERT_EQ(b->getValueView(), 0);
        ASSERT_EQ(b->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& c = b->getNodesView()[0];

        ASSERT_NE(c, nullptr);
        ASSERT_EQ(c->getKeyView(), "C");
        ASSERT_EQ(c->getValueView(), 300);
        ASSERT_EQ(c->getNodesView().size(), 0);
    }

    TEST(ImmutableTreeNode_UnitTests, Test_Tree_Can_Be_Created)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t const root{createTestTree<ImmutableTreeNode_t>()};

        ASSERT_NE(root, nullptr);
        ASSERT_EQ(root->getKeyView(), "");
        ASSERT_EQ(root->getValueView(), 0);
        ASSERT_EQ(root->getNodesView().size(), 2);

        SharedImmutableTreeNode_t const& a = root->getNodeView("A");

        ASSERT_EQ(a->getKeyView(), "A");
        ASSERT_NE(a, nullptr);
        ASSERT_EQ(a->getValueView(), 1);
        ASSERT_EQ(a->getNodesView().size(), 2);

        SharedImmutableTreeNode_t const& b = a->getNodeView("B");

        ASSERT_NE(b, nullptr);
        ASSERT_EQ(b->getKeyView(), "B");
        ASSERT_EQ(b->getValueView(), 2);
        ASSERT_EQ(b->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& c = a->getNodeView("C");

        ASSERT_NE(c, nullptr);
        ASSERT_EQ(c->getKeyView(), "C");
        ASSERT_EQ(c->getValueView(), 3);
        ASSERT_EQ(c->getNodesView().size(), 3);

        SharedImmutableTreeNode_t const& d = b->getNodeView("D");

        ASSERT_NE(d, nullptr);
        ASSERT_EQ(d->getKeyView(), "D");
        ASSERT_EQ(d->getValueView(), 4);
        ASSERT_EQ(d->getNodesView().size(), 0);

        SharedImmutableTreeNode_t const& e = c->getNodeView("E");

        ASSERT_NE(e, nullptr);
        ASSERT_EQ(e->getKeyView(), "E");
        ASSERT_EQ(e->getValueView(), 5);
        ASSERT_EQ(e->getNodesView().size(), 0);

        SharedImmutableTreeNode_t const& f = c->getNodeView("F");
        ASSERT_NE(f, nullptr);
        ASSERT_EQ(f->getKeyView(), "F");
        ASSERT_EQ(f->getValueView(), 6);
        ASSERT_EQ(f->getNodesView().size(), 0);

        SharedImmutableTreeNode_t const& g = c->getNodeView("G");

        ASSERT_NE(g, nullptr);
        ASSERT_EQ(g->getKeyView(), "G");
        ASSERT_EQ(g->getValueView(), 7);
        ASSERT_EQ(g->getNodesView().size(), 0);

        SharedImmutableTreeNode_t const& h = root->getNodeView("H");

        ASSERT_NE(h, nullptr);
        ASSERT_EQ(h->getKeyView(), "H");
        ASSERT_EQ(h->getValueView(), 8);
        ASSERT_EQ(h->getNodesView().size(), 0);
    }

    TEST(ImmutableTreeNode_UnitTests, setValue_update_B)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        SharedImmutableTreeNode_t const root{ImmutableTreeNode_t::setValue(ImmutableTreeNode_t::setValue(nullptr, toArray<std::string_view>("A", "B", "C"), 300), toArray<std::string_view>("A", "B"), 201)};

        ASSERT_NE(root, nullptr);
        ASSERT_EQ(root->getKeyView(), "");
        ASSERT_EQ(root->getValueView(), 0);
        ASSERT_EQ(root->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& a = root->getNodeView("A");

        ASSERT_EQ(a->getKeyView(), "A");
        ASSERT_NE(a, nullptr);
        ASSERT_EQ(a->getValueView(), 0);
        ASSERT_EQ(a->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& b = a->getNodesView()[0];

        ASSERT_NE(b, nullptr);
        ASSERT_EQ(b->getKeyView(), "B");
        ASSERT_EQ(b->getValueView(), 201);
        ASSERT_EQ(b->getNodesView().size(), 1);

        SharedImmutableTreeNode_t const& c = b->getNodesView()[0];

        ASSERT_NE(c, nullptr);
        ASSERT_EQ(c->getKeyView(), "C");
        ASSERT_EQ(c->getValueView(), 300);
        ASSERT_EQ(c->getNodesView().size(), 0);
    }

} // namespace ImmutableForest::Tests
