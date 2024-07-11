#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1373) Maximum Sum BST in Binary Tree
    =====================================

    ============
    Description:
    ============

    Given a binary tree root, return the maximum sum of all keys of any
    sub-tree which is also a Binary Search Tree (BST).

    Assume a BST is defined as follows:

        + The left subtree of a node contains only nodes with keys less than
          the node's key.

        + The right subtree of a node contains only nodes with keys greater
          than the node's key.

        + Both the left and right subtrees must also be binary search trees.

    ========================================
    FUNCTION: int maxSumBST(TreeNode* root);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
    Output: 20
    Explanation: Maximum sum in a valid Binary search tree is obtained in root
                 node with key equal to 3.

    --- Example 2 ---
    Input: root = [4,3,null,1,2]
    Output: 2
    Explanation: Maximum sum in a valid Binary search tree is obtained in a
                 single root node with key equal to 2.

    --- Example 3 ---
    Input: root = [-4,-2,-5]
    Output: 0
    Explanation: All values are negatives. Return an empty BST.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 4 * 10^4].
    -4 * 104 <= Node.val <= 4 * 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.04% */
/* Space Beats: 26.60% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Node_Value {
public:
    int min_node, max_node, max_sum;

    Node_Value(int min_node, int max_node, int max_sum)
    {
        this->min_node = min_node;
        this->max_node = max_node;
        this->max_sum = max_sum;
    }
};

class Solution {
public:
    int sum = 0;

    int maxSumBST(TreeNode* root)
    {
        dfs(root);
        return sum>0 ? sum : 0;

    }

private:
    Node_Value* dfs(TreeNode* root)
    {
        if ( ! root)
            return new Node_Value(INT_MAX, INT_MIN, 0);

        auto left  = dfs(root->left);
        auto right = dfs(root->right);

        if(left->max_node < root->val && root->val < right->min_node)
        {
            // If BT is BST
            sum = std::max(sum, root->val + left->max_sum + right->max_sum);

            return new Node_Value(std::min(root->val, left->min_node), std::max(root->val, right->max_node), root->val + left->max_sum + right->max_sum);
        }

        return new Node_Value(INT_MIN, INT_MAX, std::max(left->max_sum, right->max_sum));
    }
};
