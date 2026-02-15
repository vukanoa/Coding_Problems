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

#include <queue>
using namespace std;

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

    How to come-up with with this Solution:

        Forget hat you know how to code for a second.
        Answer this question:"What does it mean to 'invert the tree'?"

        It means you should swap the pointers of children at every node.
        That's it. That's all.

        Once you say that aloud, it becomes painfully obvious - Go through the
        tree(using DFS, inorder traversal) and swap children of every node.

        Note that if we swap two NULL pointers, that's still fine, that's why
        we don't have to take care of this separately.

        The only thing you have to be careful about is this - What if the input
        is a nullptr?

        Nothing special, just return nullptr immediately.
        You cannot invert a non-existing tree, right?
*/

/* Time  Beats:   100% */
/* Space Beats: 77.34% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode* inverted_left_subtree  = invertTree(root->left);
        TreeNode* inverted_right_subtree = invertTree(root->right);

        root->left  = inverted_right_subtree;
        root->right = inverted_left_subtree;

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is that we need to swap the left and right child of all nodes in
    the tree(even Leaf nodes).

    We create a queue to store nodes whose left and right child have not been
    swapped yet.
    Initially, only the root is in the queue.

    As long as the queue is not empty, remove the next node from the queue,
    swap its children, and add the children to the queue. Null nodes are not
    added to the queue.

    Eventually, the queue will be empty and all the children swapped, and we
    return the original root.


    Note:
    This Solution is a lot less Space efficient.

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

        while ( ! queue.empty())
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
