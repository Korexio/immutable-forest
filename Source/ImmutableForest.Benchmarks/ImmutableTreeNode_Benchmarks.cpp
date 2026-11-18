#include "ImmutableTreeNode.h"

#include "Benchmarking.h"

#include <cstddef>
#include <numeric>
#include <string_view>
#include <vector>

namespace ImmutableForest::Benchmarks
{

    static void ImmutableTreeNode_Benchmark_Create(benchmark::State& state)
    {
        using ImmutableTreeNode_t = ImmutableTreeNode<std::string, int>;
        using SharedImmutableTreeNode_t = ImmutableTreeNode_t::SharedImmutableTreeNode_t;

        for (auto _ : state)
        {
            SharedImmutableTreeNode_t root{nullptr};

            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C"), 3)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "F"), 6)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "G"), 7)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A"), 1)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "C", "E"), 5)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "B"), 2)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("A", "B", "D"), 4)};
            root = {ImmutableTreeNode_t::setValue(root, toArray<std::string_view>("H"), 8)};

            benchmark::DoNotOptimize(root);
        }
    }

    BENCHMARK(ImmutableTreeNode_Benchmark_Create);

} // namespace ImmutableForest::Benchmarks
