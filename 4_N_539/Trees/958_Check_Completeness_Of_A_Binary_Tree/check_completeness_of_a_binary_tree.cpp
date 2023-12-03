#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    958) Check Completeness of a Binary Tree
    ========================================

    ============
    Description:
    ============

    Given the root of a binary tree, determine if it is a complete binary tree.

    In a complete binary tree, every level, except possibly the last, is
    completely filled, and all nodes in the last level are as far left as
    possible. It can have between 1 and 2h nodes inclusive at the last level h.

    ==============================================
    FUNCTION: bool isCompleteTree(TreeNode* root);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            ___________1___________
            _____2___________3_____
            __4_____5_____6________

    Input: root = [1,2,3,4,5,6]
    Output: true
    Explanation: Every level before the last is full (ie. levels with
    node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6})
    are as far left as possible.


    --- Example 2 ---
            ___________1___________
            _____2___________3_____
            __4_____5___________7__

    Input: root = [1,2,3,4,5,null,7]
    Output: false
    Explanation: The node with value 7 isn't as far left as possible.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 100].
    1 <= Node.val <= 1000

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/* Time  Beats:   100% */
/* Space Beats: 11.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isCompleteTree(TreeNode* root)
    {
        std::queue<TreeNode*> queue;
        queue.push(root);

        while (!queue.empty())
        {
            TreeNode* node = queue.front();
            queue.pop();

            if (node)
            {
                queue.push(node->left);
                queue.push(node->right);
            }
            else
            {
                while (!queue.empty())
                {
                    if (queue.front() != nullptr)
                        return false;

                    queue.pop();
                }
            }
        }

        return true;
    }
};
