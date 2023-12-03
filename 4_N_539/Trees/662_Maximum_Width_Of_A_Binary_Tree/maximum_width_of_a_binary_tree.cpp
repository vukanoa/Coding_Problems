#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    662) Maximum Width of a Binary Tree
    ===================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the maximum width of the given
    tree.

    The maximum width of a tree is the maximum width among all levels.

    The width of one level is defined as the length between the end-nodes (the
    leftmost and rightmost non-null nodes), where the null nodes between the
    end-nodes that would be present in a complete binary tree extending down to
    that level are also counted into the length calculation.

    It is guaranteed that the answer will in the range of a 32-bit signed
    integer.

    ================================================
    FUNCTION: int widthOfBinaryTree(TreeNode* root);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,3,2,5,3,null,9]
    Output: 4
    Explanation: The maximum width exists in the third level with length 4
    (5,3,null,9).


    --- Example 2 ---
    Input: root = [1,3,2,5,null,null,9,6,null,7]
    Output: 7
    Explanation: The maximum width exists in the fourth level with length 7
    (6,null,null,null,null,null,7).


    --- Example 3 ---
    Input: root = [1,3,2,5]
    Output: 2
    Explanation: The maximum width exists in the second level with length 2
    (3,2).


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 3000].
    -100 <= Node.val <= 100

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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.95% */
/* Space Beats: 60.18% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root)
    {
        if(!root)
            return 0;

        long long result = 1;
        queue<pair<TreeNode*, long long>> queue;

        queue.push( {root, 0} );

        while(!queue.empty())
        {
            int size = queue.size();

            long long start = queue.front().second;
            long long end   = queue.back().second;

            result = std::max(result, end - start + 1);

            for(int i = 0; i < size; i++)
            {
                TreeNode* node       = queue.front().first;
                long long curr_start = queue.front().second;
                queue.pop();

                // Left  child will be 2 * idx + 1;
                // Right child will be 2 * idx + 2;
                long long idx = curr_start - start;

                if (node->left)
                    queue.push( {node->left,  2*idx + 1} );

                if (node->right)
                    queue.push( {node->right, 2*idx + 2} );
            }
        }

        return result;
    }
};
