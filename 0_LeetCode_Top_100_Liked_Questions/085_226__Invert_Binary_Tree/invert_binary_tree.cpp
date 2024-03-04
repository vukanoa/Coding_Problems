#include <iostream>
#include <queue>

/*
    ============
    === EASY ===
    ============

    ===========================
    226) Invert Binary Tree
    ===========================

    ============
    Description:
    ============

    Given the "root" of a binary Tree, invert the tree, and return its root.

    ===============================================
    FUNCTION: TreeNode* invertTree(TreeNode* root);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [4, 2, 7, 1, 3, 6, 9]
    Output: [4, 7, 2, 9, 6, 3, 1]

    --- Example 2 ---
    Input:  root = [2, 1, 3]
    Output: [2, 1, 3]

    --- Example 3 ---
    Input:  []
    Output: []

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100

*/


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/*
    ------------
    --- IDEA ---
    ------------

    This is a classic tree problem that is best-suited for a recursive approach

    Algorithm
    The inverse of an empty tree is empty tree. The inverse of a tree with root
    "t", and subtrees "right" and "left", is a tree with root "r", whose right
    subtree is the inverse of "left", and whose left subtree is the inverse of
    "right".
*/


/* Time  Beats:   100% */
/* Space Beats: 77.34% */

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    where 'h' is the height of the tree. At worst 'h' can be 'n' and that makes
    it O(n)
*/
class Solution{
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        TreeNode* left  = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->left  = right;
        root->right = left;

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The same as above, but implemented on another occasion so I wanted to have
    another implementation of it.

*/

/* Time  Beats:  100% */
/* Space Beats: 77.34% */

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    In the worst case the queue will contain all nodes in one level of the
    binary tree. For a full binary tree, the leaf level has ceil(n / 2) = O(n)
    leaves.
*/
class Solution_Another {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        /* Invert (Swap) */
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Alternatively, we can solve the problem iteratively, in a manner similar
    to Breadth-first search(BFS). (Or DFS as well)

    Algorithm
    The idea is that we need to swap the left and right child of all nodes in
    the tree. So we create a queue to store nodes whose left and right child
    have not been swapped yet. Initially, only the root is in the queue. As
    long as the queue is not empty, remove the next node from the queue, swap
    its children, and add the children to the queue. Null nodes are not added
    to the queue. Eventually, the queue will be empty and all the children
    swapped, and we return the original root.

    Though, this Solution is a lot less Space efficient.

*/

/* Time  Beats:  100% */
/* Space Beats: 5.27% */

/*    Time  Complexity: O(n) */
/*
    Space Complexity: O(h)
    In the worst case the queue will contain al nodes in one level of the
    binary tree. For a full binary tree, the leaf level has ceil(n / 2) = O(n)
    leaves.
*/
class Solution_iterative {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        std::queue<TreeNode*> queue;
        queue.push(root);

        while (!queue.empty())
        {
            TreeNode* curr = queue.front();
            queue.pop();

            /* Invert (Swap) */
            TreeNode* tmp  = curr->left;
            curr->left  = curr->right;
            curr->right = tmp;

            if (curr->left)
                queue.push(curr->left);

            if (curr->right)
                queue.push(curr->right);
        }

        return root;
    }
};


/*
    =============================
    === This is just printing ===
    =============================
*/

void
print_array(std::vector<std::string>& nums)
{
    bool first = true;
    std::cout << "\n\t\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";
}


void
print_levelorder(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> queue;
    queue.push(root);

    std::vector<std::string> vector_print;

    while (!queue.empty())
    {
        int size = queue.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode* node = queue.front();
            queue.pop();

            if (!node)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right)
                queue.push(node->right);
            else
                queue.push(nullptr);
        }
    }

    int x = vector_print.size() - 1;
    while (vector_print[x] == "null")
    {
        vector_print.pop_back();
        x--;
    }

    print_array(vector_print);
}


int
main()
{
    Solution           sol;
    Solution_Another   sol_another;
    Solution_iterative sol_iter;

    /* Example 1 */
    TreeNode four(4);
    TreeNode two(2);
    TreeNode seven(7);
    TreeNode one(1);
    TreeNode three(3);
    TreeNode six(6);
    TreeNode nine(9);

    four.left   = &two;
    four.right  = &seven;
    two.left    = &one;
    two.right   = &three;
    seven.left  = &six;
    seven.right = &nine;

    TreeNode* root = &four;



    /* Example 2 */
    // TreeNode two(2);
    // TreeNode one(1);
    // TreeNode three(3);

    // two.left  = &one;
    // two.right = &three;

    // TreeNode* root = &two;



    /* Example 3 */
    // TreeNode* root = nullptr;

    std::cout << "\n\t==========================";
    std::cout << "\n\t=== INVERT BINARY TREE ===";
    std::cout << "\n\t==========================\n";


    /* Write Input */
    std::cout << "\n\t\t\t(TODO: Implement a Visual representation of a Binary Tree)\n\n";
    std::cout << "\n\tBefore: ";
    print_levelorder(root);
    std::cout << "\n";


    /* Solution */
    // sol.invertTree(root);
    sol_another.invertTree(root);
    // sol_iter.invertTree(root);


    /* Write Output */
    std::cout << "\n\tAfter:  ";
    print_levelorder(root);
    std::cout << "\n\n\n";


    return 0;
}
