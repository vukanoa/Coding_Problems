#include <iostream>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    173) Binary Search Tree Iterator
    ================================

    ============
    Description:
    ============

    Implement the BSTIterator class that represents an iterator over the
    in-order traversal of a binary search tree (BST):

        BSTIterator(TreeNode root) Initializes an object of the BSTIterator
        class. The root of the BST is given as part of the constructor. The
        pointer should be initialized to a non-existent number smaller than any
        element in the BST.

        boolean hasNext() Returns true if there exists a number in the
        traversal to the right of the pointer, otherwise returns false.

        int next() Moves the pointer to the right, then returns the number at
        the pointer.

    Notice that by initializing the pointer to a non-existent smallest number,
    the first call to next() will return the smallest element in the BST.

    You may assume that next() calls will always be valid. That is, there will
    be at least a next number in the in-order traversal when next() is called.




    Follow up: Could you implement next() and hasNext() to run in average O(1)
               time and use O(h) memory, where h is the height of the tree?

    ===============================
    CLASS:
    class BSTIterator {
    public:
        BSTIterator(TreeNode* root)
        {
        }

        int next()
        {
        }

        bool hasNext()
        {
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        ___________7___________
        _____3__________15_____
        ______________9____20__


    Input
    ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next",
    "hasNext", "next", "hasNext"]
    [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
    Output
    [null, 3, 7, true, 9, true, 15, true, 20, false]

    Explanation
    BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
    bSTIterator.next();    // return 3
    bSTIterator.next();    // return 7
    bSTIterator.hasNext(); // return True
    bSTIterator.next();    // return 9
    bSTIterator.hasNext(); // return True
    bSTIterator.next();    // return 15
    bSTIterator.hasNext(); // return True
    bSTIterator.next();    // return 20
    bSTIterator.hasNext(); // return False


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 105].
    0 <= Node.val <= 106
    At most 105 calls will be made to hasNext, and next.

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

    Iterative DFS.

*/

/* Time  Beats: 86.91% */
/* Space Beats: 14.91% */

/*
    Time  Complexity: average O(1)
*/
/*
    Space Complexity: O(h)
    where 'h' is the height of the tree.
*/
class BSTIterator {
public:
    BSTIterator(TreeNode* root) : m_root(root)
    {
        while (m_root)
        {
            m_stack.push(m_root);
            m_root = m_root->left;
        }
    }

    int next()
    {
        TreeNode* ret = m_stack.top();
        m_stack.pop();

        TreeNode* curr = ret->right;
        while (curr)
        {
            m_stack.push(curr);
            curr = curr->left;
        }

        return ret->val;
    }

    bool hasNext()
    {
        if (m_stack.empty())
            return false;

        return true;
    }

private:
    std::stack<TreeNode*> m_stack;
    TreeNode* m_root = nullptr;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
