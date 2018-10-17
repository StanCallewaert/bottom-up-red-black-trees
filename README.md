# red-black trees

The characteristics of a red-black tree are as follows:

1. Each node has the color of red or black
2. The color of a virtual node (a node that has the value of a nullptr) is black
3. A red node always has two black children.
4. Each possible route from a node to a virtual node has to have the same number of black nodes. This number is called the black height of a node.
5. The root is black. This is not necessary per se, but makes the process of maintaining a red-black tree easier.

Red-black tree search, add and delete by using bottom-up are coded and explained in this repository. Cases will be used to explain how red-black trees can keep their characteristics. The cases described below also count in case the tree is mirrored (left part becomes right part and vice versa).

## bottom-up add

In bottom-up add, the characteristics of the red-black tree are only violated if a node is added as a child of a red node. This is the case since an added node is always red which means that the parent of the added node is red an only has one black child. This violates rule three of a red-black tree its characteristics.

The three following cases are used to resolve this violation:

### case 1

![case 1](images/add/case1.png)

### case 2

![case 2](images/add/case2.png)

### case 3

![case 3](images/add/case3.png)

After case three is executed, it becomes case two.

## bottom-up delete

In bottom-up delete, the successor (or predecessor) of the node that needs to be deleted is searched. If a successor is found, the values of the successor node and the node that needs to be deleted are swapped and then the successor node gets deleted. The black depth of the red-black three is not affected if the successor was red or if the successor had a child that was red (if the successor is black and the child is red than the red child takes the place of the successor and becomes black).

If however, the successor is black and has no red childs than the characteristics of the red-black tree are violated. The deleted successor becomes a double black node. This double black node needs to be removed from the red-black tree and this can be done according to the following cases:

## case 1

![case 1](images/delete/case1.png)

### case 2

![case 2](images/delete/case2.png)

### case 3

![case 3](images/delete/case3.png)

After case three is executed, it becomes case two.

### case 4

![case 4](images/delete/case4.png)

After case four is executed, it becomes one of the cases above.