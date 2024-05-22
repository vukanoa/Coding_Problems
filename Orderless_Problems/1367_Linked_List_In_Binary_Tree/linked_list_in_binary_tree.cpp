#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1367) Linked List in Binary Tree
    ================================

    ============
    Description:
    ============

    Given a binary tree root and a linked list with head as the first node.

    Return True if all the elements in the linked list starting from the head
    correspond to some downward path connected in the binary tree otherwise
    return False.

    In this context downward path means a path that starts at some node and
    goes downwards.

    =========================================================
    FUNCTION: bool isSubPath(ListNode* head, TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    (nodes that have a '#' left of them are of different color in the picture)
                _______________________1_______________________
                ___________4______________________#4___________
                _________________2__________#2_________________
                ______________1___________6____#8______________
                ______________________________1___3____________

    Input: head = [4,2,8],
           root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
    Output: true
    Explanation: Nodes in blue form a subpath in the binary Tree.


    --- Example 2 ---
    (nodes that have a '#' left of them are of different color in the picture)
                ______________________#1_______________________
                ___________4______________________#4___________
                _________________2__________#2_________________
                ______________1__________#6_____8______________
                ______________________________1___3____________


    --- Example 3 ---
    Input: head = [1,4,2,6,8],
           root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
    Output: false
    Explanation: There is no path in the binary tree that contains all the
                 elements of the linked list from head.


    *** Constraints ***
    The number of nodes in the tree will be in the range [1, 2500].
    The number of nodes in the list will be in the range [1, 100].
    1 <= Node.val <= 100 for each node in the linked list and binary tree.

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

    If you know how to do a basic DFS on a Binary Tree, then it comes down to
    intuition and logical thinking. There aren' any "catches" or "tricks".

    Just "do it in your mind" and write the code.

*/

/* Time  Beats: 91.17% */
/* Space Beats: 43.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root)
    {
        if ( ! root)
            return false;

        if (dfs(head, root))
            return true;

        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }

private:
    bool dfs(ListNode* head, TreeNode* root)
    {
        if ( ! head) return true;
        if ( ! root) return false;

        if (head->val == root->val)
            return dfs(head->next, root->left) || dfs(head->next, root->right);

        return false;
    }
};
