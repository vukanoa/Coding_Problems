/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    145) Binary Tree Postorder Traversal
    ====================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the postorder traversal of its
    nodes' values.

    Follow up: Recursive solution is trivial, could you do it iteratively?

    =========================================================
    FUNCTION: vector<int> postorderTraversal(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,2,3]
    Output: [3,2,1]

    --- Example 2 ---
    Input: root = []
    Output: []

    --- Example 3 ---
    Input: root = [1]
    Output: [1]

    *** Constraints ***
    The number of the nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100

*/

#include <vector>
#include <stack>
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

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 67.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> result;
        postorder(root, result);

        return result;
    }

private:
    void postorder(TreeNode* root, vector<int>& result)
    {
        if ( ! root)
            return;

        postorder(root->left, result);  // Left
        postorder(root->right, result); // Right
        result.push_back(root->val);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative using two Stacks.

*/

/* Time  Beats:   100% */
/* Space Beats: 67.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iterative_Two_Stacks {
public:
    vector<int> postorderTraversal(TreeNode* root)
    {
        if ( ! root)
            return {};

        stack<TreeNode*> s1;
        stack<TreeNode*> s2;

        s1.push(root);
        while ( ! s1.empty())
        {
            root = s1.top();
            s1.pop();

            s2.push(root);

            if (root->left)  s1.push(root->left);
            if (root->right) s1.push(root->right);
        }

        vector<int> result;
        while ( ! s2.empty())
        {
            result.push_back(s2.top()->val);
            s2.pop();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative using a single stack with pair<TreeNode*, bool>.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  16.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iterative_Single_Stack_With_Pair {
public:
    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> result;

        stack<pair<TreeNode*, bool>> stack; // {node, right_subtree_traversed}
        stack.push( {root, false} );

        while ( ! stack.empty())
        {
            auto [curr, right_subtree_traversed] = stack.top();
            stack.pop();

            if (right_subtree_traversed)
            {
                result.push_back(curr->val);
            }
            else
            {
                while (curr)
                {
                    stack.push( {curr, true} );

                    if (curr->right)
                        stack.push( {curr->right, false} );

                    curr = curr->left;
                }
            }
        }

        return result;
    }
};
