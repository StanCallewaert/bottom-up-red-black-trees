#include "rbtree.h"
#include "rbnode.h"

#include <cstdlib>

int main(int argc, char** argv) {
    RBTree<int> tree{};
    
    // Construct a red-black tree
    // While maintaining a red-black tree after each addition
    tree.addBottomUp(50);
    tree.addBottomUp(0);
    tree.addBottomUp(75);
    tree.addBottomUp(100); // Case 1        (see Github images bottom-up add)
    tree.addBottomUp(125); // Case 2        (see Github images bottom-up add)
    tree.addBottomUp(175); // Case 1        (see Github images bottom-up add)
    tree.addBottomUp(150); // Case 3        (see Github images bottom-up add)
    tree.addBottomUp(200); // Case 1 and 2  (see Github images bottom-up add)
    tree.addBottomUp(25);
    
    // Write the red-black tree to a file
    // If you copy the text from this file (in the same directory as this cpp file)
    // Then you can paste it in the textarea of the website: http://webgraphviz.com
    // To see what the red-black tree looks like
    // You can use this line to visualize the red-black tree in other parts of the code as well
    tree.visualize("ConstructedRedBlackTree.txt");
    
    // Delete the nodes from the red-black tree one by one
    // While maintaining a red-black tree after each deletion
    tree.deleteBottomUp(100); // Case 2        (see Github images bottom-up delete)
    tree.deleteBottomUp(25);  // Case 3        (see Github images bottom-up delete)
    tree.deleteBottomUp(150); // Case 1        (see Github images bottom-up delete)
    tree.deleteBottomUp(175);
    tree.deleteBottomUp(125); // Case 4        (see Github images bottom-up delete)
    tree.deleteBottomUp(50);
    tree.deleteBottomUp(0);   // Case 1        (see Github images bottom-up delete)
    tree.deleteBottomUp(75);  // Case 1        (see Github images bottom-up delete)
    tree.deleteBottomUp(200);
    
    return 0;
}
