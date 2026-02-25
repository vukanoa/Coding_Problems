/*
    ============
    === EASY ===
    ============

    =================================
    94) Binary Tree Inorder Traversal
    =================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the inorder traversal of its
    nodes' values.

    =======================================================
    FUNCTION: vector<int> inorderTraversal(TreeNode* root);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [1, null, 2, 3]
    Output: [1, 3, 2]

    --- Example 2 ---
    Input:  root = []
    Output: []

    --- Example 3 ---
    Input:  root = [1]
    Output: [1]

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 100]
    -100 <= Node.val <= 100

*/

#include <stack>
#include <vector>
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

    Recursive Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Recursive {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> result;

        inorder(root, result);

        return result;
    }

private:
    void inorder(TreeNode* root, vector<int>& result)
    {
        if ( ! root)
            return;

        inorder(root->left, result);  // Left
        result.push_back(root->val);
        inorder(root->right, result); // Right
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative Implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iter {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> result;
        stack<TreeNode*> stack;

        while (root || ! stack.empty())
        {
            while (root)
            {
                stack.push(root);
                root = root->left;
            }

            root = stack.top();
            stack.pop();

            result.push_back(root->val);

            root = root->right;
        }

        return result;
    }
};
