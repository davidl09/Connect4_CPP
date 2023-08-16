#include "minimaxtree.hpp"

int main()
{
    MinimaxTreeNode root(BitBoard(), ai, 7);
    //root.increase_depth(1);
    std::cout << root.best_node(ai) << "\n";
}