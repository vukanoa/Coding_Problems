#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    109) Convert Sorted List To Binary Search Tree
    ==============================================

    ============
    Description:
    ============

    Given the head of a singly linked list where elements are sorted in
    ascending order, convert it to a height-balanced binary search tree.

    ====================================================
    FUNCTION: TreeNode* sortedListToBST(ListNode* head);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                        1 --> 2 --> 3 --> 4 --> 5

                                    |
                                    |
                                    V

                                    0
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                            -3             9
                            /             /
                           /             /
                          /             /
                       -10             5


    Input: head = [-10,-3,0,5,9]
    Output: [0,-3,9,-10,null,5]
    Explanation: One possible answer is [0,-3,9,-10,null,5], which represents
                 the shown height balanced BST.


    --- Example 2 ---
    Input: head = []
    Output: []


    *** Constraints ***
    The number of nodes in head is in the range [0, 2 * 10^4].
    -10^5 <= Node.val <=

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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

    1. Iterate through nodes in List and each time make a TreeNode out of the
       current ListNode and put that TreeNode pointer in vector<TreeNode* nodes

    2. Do exactly the same as in Problem LeetCode 105:
       "Construct Binary Tree from Preorder and Inorder Traversal"

*/

/* Time  Beats: 82.08% */
/* Space Beats: 99.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        if ( ! head)
            return nullptr;

        vector<TreeNode*> nodes;

        while (head)
        {
            TreeNode* curr = new TreeNode(head->val);

            nodes.push_back(curr);
            head = head->next;
        }

        return dfs(nodes, 0, nodes.size()-1);
    }

private:
    TreeNode* dfs(std::vector<TreeNode*>& nodes, int start, int end)
    {
        if (start > end)
            return nullptr;

        const int n = end - start + 1;
        int half = n / 2;

        int node_idx = start + half;

        TreeNode* root = nodes[node_idx];
        root->left  = dfs(nodes,    start    , node_idx - 1);
        root->right = dfs(nodes, node_idx + 1,     end     );

        return root;
    }
};
