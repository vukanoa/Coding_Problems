/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1448) Count Good Nodes In Binary Tree
    =====================================

    ============
    Description:
    ============

    Given a binary tree root, a node X in the tree is named good if in the path
    from root to X there are no nodes with a value greater than X.

    Return the number of good nodes in the binary tree.

    ========================================
    FUNCTION: int goodNodes(TreeNode* root);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
            ___________
            _____3_____
            __1_____4__
            3______1__5

    Input: root = [3,1,4,3,null,1,5]
    Output: 4
    Explanation: Nodes in blue are good.
    Root Node (3) is always a good node.
    Node 4 -> (3,4) is the maximum value in the path starting from the root.
    Node 5 -> (3,4,5) is the maximum value in the path
    Node 3 -> (3,1,3) is the maximum value in the path.




    --- Example 2 ---
            ___________
            _____3_____
            __3________
            4__2_______

    Input: root = [3,3,null,4,2]
    Output: 3
    Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.


    --- Example 3 ---
    Input: root = [1]
    Output: 1
    Explanation: Root is considered as good.


    *** Constraints ***
    The number of nodes in the binary tree is in the range [1, 10^5].
    Each node's value is between [-10^4, 10^4].

*/

#include <algorithm>
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

    Self-explanatory.

*/

/* Time  Beats: 75.82% */
/* Space Beats: 64.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS_1 {
public:
    int goodNodes(TreeNode* root)
    {
        const int MIN_NODE_VALUE = -1e4;

        int result = 0;
        dfs(root, MIN_NODE_VALUE - 1, result);

        return result;
    }

private:
    void dfs(TreeNode* root, int max_so_far, int& result)
    {
        if ( ! root)
            return;

        if (root->val >= max_so_far)
            result++;

        dfs(root->left,  max(max_so_far, root->val), result);
        dfs(root->right, max(max_so_far, root->val), result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in another way. It's always beneficial to look
    more than one implementation. Especially for Tree Problems.

*/

/* Time  Beats: 95.53% */
/* Space Beats: 64.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS_2 {
public:
    int goodNodes(TreeNode* root)
    {
        return dfs(root, root->val);
    }

private:
    int dfs(TreeNode* root, int max_so_far)
    {
        if ( ! root)
            return 0;

        int result = root->val >= max_so_far ? 1 : 0; 

        max_so_far = max(max_so_far, root->val);

        result += dfs(root->left,  max_so_far);
        result += dfs(root->right, max_so_far);

        return result;
    }
};
