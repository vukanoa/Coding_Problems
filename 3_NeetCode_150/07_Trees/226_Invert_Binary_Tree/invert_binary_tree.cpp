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
class Solution_DFS {
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

    Simple BFS implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (root == nullptr)
            return nullptr;

        queue<TreeNode*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            TreeNode* node = queue.front();
            queue.pop();

            /* Swap Pointers */
            swap(node->left, node->right);

            if (node->left)
                queue.push(node->left);

            if (node->right)
                queue.push(node->right);
        }

        return root;
    }
};
