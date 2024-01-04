#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    95) Unique Binary Search Trees II
    =================================

    ============
    Description:
    ============

    Given an integer n, return all the structurally unique BST's (binary search
    trees), which has exactly n nodes of unique values from 1 to n. Return the
    answer in any order.

    =================================================
    FUNCTION: vector<TreeNode*> generateTrees(int n);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

    _____1_____   _____1_____   _____2_____   _____3_____   _____3_____
    ________3__   ________2__   __1_____3__   __2________   __1________
    ______2____   __________3   ___________   1__________   ____2______

    Input: n = 3
    Output:
    [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]


    --- Example 2 ---
    Input: n = 1
    Output: [[1]]


    *** Constraints ***
    1 <= n <= 8

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

/* Time  Beats: 82.78% */
/* Space Beats: 58.59% */

/* Time  Complexity: O(I have no idea) */
/* Space Complexity: O(I have no idea) */
class Solution {
public:
    std::vector<TreeNode*> generateTrees(int n)
    {
        return generate(1, n);
    }

private:
    std::vector<TreeNode*> generate(int start, int end)
    {
        if(start > end)
            return {NULL};

        if(start == end)
        {
            TreeNode* root = new TreeNode(start);
            return {root};
        }

        std::vector<TreeNode*> result;

        for(int val = start; val <= end; val++)
        {
            vector<TreeNode*> left  = generate(start, val-1);
            vector<TreeNode*> right = generate(val+1,   end);

            for(TreeNode* l : left)
            {
                for(TreeNode* r: right)
                {
                    TreeNode*  root = new TreeNode(val);
                    root->left  = l;
                    root->right = r;

                    result.push_back(root);
                }
            }
        }

        return result;
    }
};
