/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2415) Reverse Old Levels of Binary Tree
    =======================================

    ============
    Description:
    ============

    Given the root of a perfect binary tree, reverse the node values at each odd
    level of the tree.

    For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18],
    then it should become [18,29,11,7,4,3,1,2].

    Return the root of the reversed tree.

    A binary tree is perfect if all parent nodes have two children and all
    leaves are on the same level.

    The level of a node is the number of edges along the path between it and
    the root node.

    =====================================================
    FUNCTION: TreeNode* reverseOddLevels(TreeNode* root);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [2,3,5,8,13,21,34]
    Output: [2,5,3,8,13,21,34]
    Explanation:
    The tree has only one odd level.
    The nodes at level 1 are 3, 5 respectively, which are reversed and become 5, 3.

    --- Example 2 ---
    Input: root = [7,13,11]
    Output: [7,11,13]
    Explanation:
    The nodes at level 1 are 13, 11, which are reversed and become 11, 13.

    --- Example 3 ---
    Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
    Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
    Explanation:
    The odd levels have non-zero values.
    The nodes at level 1 were 1, 2, and are 2, 1 after the reversal.
    The nodes at level 3 were 1, 1, 1, 1, 2, 2, 2, 2, and are 2, 2, 2, 2, 1, 1, 1, 1 after the reversal.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 214].
    0 <= Node.val <= 105
    root is a perfect binary tree.

*/

#include <queue>
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

    At first you might think you need a few "deque"s, but it's more simple than
    you think.

    It's a classic, fundamental, BFS algorithm plus reversing the values of
    the current row of nodes if the level is odd.

    To achieve that, everything we take element from the front of the "queue",
    as we usually do in BFS, we're going to push it to the end of the vector
    "curr_level_nodes".

    Then once we're done processing, and pushing, all the elements from this
    row and once we've pushed children of current row's nodes to "queue", we
    can proceed to reverse the VALUES(only values) of nodes that are present in
    "curr_level_nodes" vector.

    First value  should be swapped with (1st to)  last value and vice verca.
    Second value should be swapped with second to last value and vice verca.
    And so on.

*/

/* Time  Beats: 42.65% */
/* Space Beats: 13.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root)
    {
        if ( ! root)
            return nullptr;  // Return null if the tree is empty.

        queue<TreeNode*> queue;
        queue.push(root);  // Start BFS with the root node.
        int level = 0;

        while ( ! queue.empty())
        {
            int size = queue.size();
            vector<TreeNode*> curr_level_nodes;

            // Process all nodes at the current level.
            for (int i = 0; i < size; i++)
            {
                TreeNode* node = queue.front();
                queue.pop();
                curr_level_nodes.push_back(node);

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);
            }

            // Reverse all nodes in the current level if level is odd
            if (level & 1)
            {
                int left  = 0;
                int right = curr_level_nodes.size() - 1;

                while (left < right)
                {
                    swap(curr_level_nodes[left]->val, curr_level_nodes[right]->val);

                    left++;
                    right--;
                }
            }

            level++;
        }

        return root;
    }
};
