#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === EASY ===
    ============

    ===============================================
    108) Convert Sorted Array To Binary Search Tree
    ===============================================

    ============
    Description:
    ============

    Given an integer array nums where the elements are sorted in ascending
    order, convert it to a height-balanced binary search tree.

    =============================================================
    FUNCTION: TreeNode* sortedArrayToBST(std::vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    ___________
    _____0_____
    _-3_____9__
    10____5____

    Input:  [-10, -3, 0, 5, 9]
    Output: [0, -3, 9, -10, null, 5] // Level-order
    Explanation: [0, -10, 5, null, -3, null, 9] is also accepted:
    ___________
    _____0_____
    _-10____5__
    ___-3_____9




    --- Example 2 ---
    _____      _____
    __3__      __1__
    1____      ____3

    Input: [1, 3]
    Output: [3, 1]
    Explanation: [1, null, 3] and [3, 1] are both height-balanced BSTs.

    *** Constraints ***
    1 <= nums.length <= 10^4
    -104 <= nums[i] <= 10^4
    nums is sorted in a strictly increasing order.

*/

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

    TODO

*/

/* Time  Beats: 98.21% */
/* Space Beats: 94.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums)
    {
        return construct_BST(nums, 0, nums.size()-1);
    }

private:
    TreeNode* construct_BST(std::vector<int>& nums, int left, int right)
    {
        if (right < left)
            return nullptr;

        int mid = left + (right - left) / 2;

        TreeNode* node = new TreeNode(nums[mid]);
        node->left  = construct_BST(nums, left , mid-1);
        node->right = construct_BST(nums, mid+1, right);

        return node;
    }
};




/*
    =============================
    === This is just printing ===
    =============================
*/

void
print_array(std::vector<std::string>& nums)
{
    bool first = true;
    std::cout << "\n\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]  *** LEVEL ORDER ***\n\n";
}


void
print_levelorder(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> queue;
    queue.push(root);

    std::vector<std::string> vector_print;

    while (!queue.empty())
    {
        int size = queue.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode* node = queue.front();
            queue.pop();

            if (!node)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right)
                queue.push(node->right);
            else
                queue.push(nullptr);
        }
    }

    int x = vector_print.size() - 1;
    while (vector_print[x] == "null")
    {
        vector_print.pop_back();
        x--;
    }

    print_array(vector_print);
}


int
main()
{
    Solution sol;

    /* Example 1 */
    std::vector<int> nums = {-10, -3, 0, 5, 9};

    /* Example 2 */
    // std::vector<int> nums = {1, 3};

    /* Example 3 */
    // std::vector<int> nums = {-10};


    std::cout << "\n\t==================================================";
    std::cout << "\n\t=== CONVERT SORTED ARRAY TO BINARY SEARCH TREE ===";
    std::cout << "\n\t==================================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    TreeNode* root = sol.sortedArrayToBST(nums);


    /* Write Output */
    print_levelorder(root);


    return 0;
}
