#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1161) Maximum Level Sum Of a Binary Tree
    ========================================

    ============
    Description:
    ============

    Given the root of a binary tree, the level of its root is 1, the level of
    its children is 2, and so on.

    Return the smallest level x such that the sum of all the values of nodes at
    level x is maximal.

    ==========================================
    FUNCTION: int maxLevelSum(TreeNode* root);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ___________
        _____1_____
        __7_____0__
        2__-8______

    Input: root = [1,7,0,7,-8,null,null]
    Output: 2
    Explanation:
    Level 1 sum = 1.
    Level 2 sum = 7 + 0 = 7.
    Level 3 sum = 7 + -8 = -1.
    So we return the level with the maximum sum which is level 2.


    --- Example 2 ---
    ______________________989______________________
    _________________________________10250_________
    ___________________________98693______-89388___
    _________________________________________-32127

    Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
    Output: 2


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    -10^5 <= Node.val <= 10^5

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

    THe most Basic BFS.

*/

/* Time  Beats: 98.42% */
/* Space Beats: 14.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxLevelSum(TreeNode* root)
    {
        /* BFS */
        std::queue<TreeNode*> queue;
        queue.push(root);

        long long max_sum = LLONG_MIN;
        int result = 0;

        int level = 0;
        while(!queue.empty())
        {
            level++;
            long long sum = 0;

            int size = queue.size();
            while (size--)
            {
                TreeNode* curr = queue.front();
                queue.pop();

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);

                sum += curr->val;
            }

            if (sum > max_sum) // It's not >= since we need the SMALLEST level
            {
                max_sum = sum;
                result = level;
            }
        }

        return result;
    }
};
