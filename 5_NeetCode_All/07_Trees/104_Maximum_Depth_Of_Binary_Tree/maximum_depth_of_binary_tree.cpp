/*
    ============
    === EASY ===
    ============

    =================================
    104) Maximum Depth of Binary Tree
    =================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return its maximum depth.

    A binary Tree's maximum depth is the nmber of nodes along the longest path
    from the root node down to the farthest leaf node.

    =======================================
    FUNCTION: int maxDepth(TreeNode* root);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 9, 20, null, null, 15, 7]
    Output: 3

    --- Example 2 ---
    Input:  root = [1, null, 2]
    Output: 2

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4]
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

    Let's assume that we know the max depth of the left subtree and the max
    depth od the right subtree.

    Ask yourself - How would you get the maximum depth of the entire tree
    including this current node?

    Simply take the deeper subtree of the two and add 1(the current node).


    The maxDpeth of an EMPTY subtree is 0, therefore if node == nullptr, simply
    return 0.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.77% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr)
            return 0;

        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Implemented using BFS.

*/

/* Time  Beats: 88.24% */
/* Space Beats:  9.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
public:
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr)
            return 0;

        int level = 0;
        queue<TreeNode*> queue;

        // Emplace is a bit faster than "push" for custom Data Types
        queue.emplace(root);

        while ( ! queue.empty())
        {
            int number_of_nodes_at_current_level = queue.size();

            for (int i = 0; i < number_of_nodes_at_current_level; i++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                if (node->left)
                    queue.emplace(node->left);

                if (node->right)
                    queue.emplace(node->right);
            }

            level++;
        }

        return level;
    }
};
