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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 43.20% */
/* Space Beats: 39.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int maxSumBST(TreeNode* root)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int result = 0;

        int curr_max = INT_MIN;
        int curr_min = INT_MAX;

        dfs(root, curr_max, curr_min, result);

        return result;
    }

private:
    int dfs(TreeNode* root, int& curr_max, int& curr_min, int& result)
    {
        if ( ! root)
            return 0;

        /*
          left_min, left_max will find the minimum and maximum node in the
          left subtree.

          Similarly, right_min, right_max will find minimum and maximum node in
          the right subtree.
        */
        int left_min;
        int right_min;

        int left_max;
        int right_max;

        left_min  = right_min = INT_MAX;
        left_max = right_max = INT_MIN;

        int left  = dfs(root->left,  left_max,  left_min,  result);
        int right = dfs(root->right, right_max, right_min, result);

        int val = left + right + root->val;

        // If the left maximum is less than and right minimum is greater than
        // current node then the subtree rooted at current node is indeed BST.

        if (left_max < root->val && right_min > root->val)
        {
            result = std::max(result, val);

            curr_max = std::max(root->val, right_max);
            curr_min = std::min(root->val, left_min);
        }
        else
        {
            curr_max = INT_MAX;
            curr_min = INT_MIN;
        }

        return val;
    }
};
