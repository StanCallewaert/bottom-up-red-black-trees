#include "rbtree.h"
#include "rbnode.h"

#include <cstdlib>

int main(int argc, char** argv) {
    RBTree<int> tree{};
    
    tree.addBottomUp(50);
    tree.addBottomUp(25);
    tree.addBottomUp(75);
    tree.addBottomUp(100); // Case 1        (see Github images bottom-up add)
    tree.addBottomUp(125); // Case 2        (see Github images bottom-up add)
    tree.addBottomUp(175); // Case 1        (see Github images bottom-up add)
    tree.addBottomUp(150); // Case 3        (see Github images bottom-up add)
    tree.addBottomUp(200); // Case 1 and 2  (see Github images bottom-up add)
    
    tree.visualize("test.txt");
    
    return 0;
}