#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    894) All Possible Full Binary Trees
    ===================================

    ============
    Description:
    ============

    Given an integer n, return a list of all possible full binary trees with n
    nodes. Each node of each tree in the answer must have Node.val == 0.

    Each element of the answer is the root node of one possible tree. You may
    return the final list of trees in any order.

    A full binary tree is a binary tree where each node has exactly 0 or 2
    children.

    ==================================================
    FUNCTION: vector<TreeNode*> allPossibleFBT(int n);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 7
    _______________________  _______________________  _______________________
    ___________0___________  ___________0___________  ___________0___________
    _____0___________0_____  _____0___________0_____  _____0___________0_____
    ______________0_____0__  ______________0_____0__  __0_____0_____0_____0__
    __________________0___0  ____________0___0______  _______________________

            _______________________  _______________________
            ___________0___________  ___________0___________
            _____0___________0_____  _____0___________0_____
            __0_____0______________  __0_____0______________
            ______0___0____________  0___0__________________

    Output:
    [[0,0,0,null,null,0,0,null,null,0,0],
     [0,0,0,null,null,0,0,0,0],
     [0,0,0,0,0,0,0],
     [0,0,0,0,0,null,null,null,null,0,0],
     [0,0,0,0,0,null,null,0,0]]



    --- Example 2 ---
    Input: n = 3
        _____
        __1__
        2___3

    Output: [[0,0,0]]



    *** Constraints ***
    1 <= n <= 20

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

/* Time  Beats: 93.17% */
/* Space Beats: 50.16% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<TreeNode*> allPossibleFBT(int n)
    {
        if (n == 1)
            return {new TreeNode(0)};

        std::vector<TreeNode*> empty = {};

        std::unordered_map<int, std::vector<TreeNode*>> cache;
        cache.insert( {0, empty} );
        cache.insert( {1, {new TreeNode(0)}} );

        return dfs(n, cache);
    }

private:
    std::vector<TreeNode*> dfs(int n, std::unordered_map<int, std::vector<TreeNode*>>& cache)
    {
        if (cache.find(n) != cache.end())
            return cache[n];

        std::vector<TreeNode*> result;

        for (int left = 0; left < n; left++)
        {
            int right = n - 1 - left;

            std::vector<TreeNode*> left_subtrees  = dfs(left,  cache);
            std::vector<TreeNode*> right_subtrees = dfs(right, cache);

            for (auto& curr_left_subtree : left_subtrees)
            {
                for (auto& curr_right_subtree : right_subtrees)
                    result.push_back(new TreeNode(0, curr_left_subtree, curr_right_subtree));
            }
        }

        cache.insert({n, result});

        return result;
    }
};
