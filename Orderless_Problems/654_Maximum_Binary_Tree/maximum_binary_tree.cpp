#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    654) Maximum Binary Tree
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums with no duplicates. A maximum binary
    tree can be built recursively from nums using the following algorithm:

        1. Create a root node whose value is the maximum value in nums.

        2. Recursively build the left subtree on the subarray prefix to the
           left of the maximum value.

        3. Recursively build the right subtree on the subarray suffix to the
           right of the maximum value.

    Return the maximum binary tree built from nums.

    ==================================================================
    FUNCTION: TreeNode* constructMaximumBinaryTree(vector<int>& nums);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    6
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       3                         5
                         \                     /
                          \                   /
                           \                 /
                            \               /
                             \             /
                              2           0
                               \
                                \
                                 \
                                  1

    Input: nums = [3,2,1,6,0,5]
    Output: [6,3,5,null,2,0,null,null,1]
    Explanation: The recursive calls are as follow:
    - The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right
      suffix is [0,5].

        - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix
          is [2,1].

            - Empty array, so no child.
            - The largest value in [2,1] is 2. Left prefix is [] and right
              suffix is [1].

                - Empty array, so no child.
                - Only one element, so child is a node with value 1.

        - The largest value in [0,5] is 5. Left prefix is [0] and right suffix
          is [].

            - Only one element, so child is a node with value 0.
            - Empty array, so no child.




    --- Example 2 ---
    Input: nums = [3,2,1]
    Output: [3,null,2,null,1]


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] <= 1000
    All integers in nums are unique.

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

    Standard Binary Tree DFS-like approach.

*/

/* Time  Beats: 70.91% */
/* Space Beats: 80.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */ // Call Stack
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums)
    {
        const int n = nums.size();

        return construct(nums, 0, n-1);
    }

private:
    TreeNode* construct(std::vector<int>& nums, int start, int end)
    {
        if (start > end)
            return nullptr;

        int max     = INT_MIN;
        int max_idx = -1;
        for (int i = start; i <= end; i++)
        {
            if (max < nums[i])
            {
                max = nums[i];
                max_idx = i;
            }
        }

        TreeNode* root = new TreeNode(max);
        root->left  = construct(nums,   start  , max_idx-1);
        root->right = construct(nums, max_idx+1,    end   );

        return root;
    }
};
