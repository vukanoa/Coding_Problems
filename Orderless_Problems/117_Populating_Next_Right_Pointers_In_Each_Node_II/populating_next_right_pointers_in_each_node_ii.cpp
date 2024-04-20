#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    117) Populating Next Right Pointers in Each Node II
    ===================================================

    ============
    Description:
    ============

    Given a binary tree

    struct Node {
      int val;
      Node *left;
      Node *right;
      Node *next;
    }

    Populate each next pointer to point to its next right node. If there is no
    next right node, the next pointer should be set to NULL.

    Initially, all next pointers are set to NULL.


    You may only use constant extra space.
    The recursive approach is fine. You may assume implicit stack space does
    not count as extra space for this problem.

    ====================================
    FUNCTION: Node* connect(Node* root);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4,5,null,7]
    Output: [1,#,2,3,#,4,5,7,#]
    Explanation: Given the above binary tree (Figure A), your function should
                 populate each next pointer to point to its next right node,
                 just like in Figure B. The serialized output is in level order
                 as connected by the next pointers, with '#' signifying the end
                 of each level.


    --- Example 2 ---
    Input: root = []
    Output: []


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 6000].
    -100 <= Node.val <= 100

*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

/* Time  Beats: 84.30% */
/* Space Beats: 32.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    Node* connect(Node* root)
    {
        if ( ! root)
            return nullptr;

        std::queue<Node*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                Node* curr = queue.front();
                queue.pop();

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);

                // Only the rightmost's next doesn't need to be updated
                if (x < size-1)
                    curr->next = queue.front();
            }
        }

        return root;
    }
};
