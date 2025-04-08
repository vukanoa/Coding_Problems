/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    865) Subtree With All the Deepest Nodes
    =======================================

    ============
    Description:
    ============

    Given the root of a binary tree, the depth of each node is the shortest
    distance to the root.

    Return the smallest subtree such that it contains all the deepest nodes in
    the original tree.

    A node is called the deepest if it has the largest depth possible among any
    node in the entire tree.

    The subtree of a node is a tree consisting of that node, plus the set of
    all descendants of that node.

    ==========================================================
    FUNCTION: TreeNode* subtreeWithAllDeepest(TreeNode* root);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,5,1,6,2,0,8,null,null,7,4]
    Output: [2,7,4]
    Explanation: We return the node with value 2, colored in yellow in the
                 diagram. The nodes coloured in blue are the deepest nodes of
                 the tree. Notice that nodes 5, 3 and 2 contain the deepest
                 nodes in the tree but node 2 is the smallest subtree among
                 them, so we return it.

    --- Example 2 ---
    Input: root = [1]
    Output: [1]
    Explanation: The root is the deepest node in the tree.

    --- Example 3 ---
    Input: root = [0,1,3,null,2]
    Output: [2]
    Explanation: The deepest node in the tree is 2, the valid subtrees are the
                 subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the
                 smallest.


    *** Constraints ***
    The number of nodes in the tree will be in the range [1, 500].
    0 <= Node.val <= 500
    The values of the nodes in the tree are unique.

*/

#include <utility>
using namespace std;

/**
 * Definition for a binary tree node.
*/
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

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        return dfs(root).first;
    }

private:
    pair<TreeNode*, int> dfs(TreeNode* root)
    {
        if ( ! root)
            return {nullptr, 0};

        // left.first  <==> left_subtree_root
        // left.second <==> left_subtree_depth
        auto left_pair  = dfs(root->left);
        auto right_pair = dfs(root->right);

        if (left_pair.second > right_pair.second)
            return {left_pair.first, left_pair.second + 1};

        if (left_pair.second < right_pair.second)
            return {right_pair.first, right_pair.second + 1};

        return {root, left_pair.second + 1};
    }
};
