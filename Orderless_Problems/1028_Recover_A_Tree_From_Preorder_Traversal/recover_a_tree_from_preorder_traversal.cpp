/*
    ============
    === HARD ===
    ============

    ============================================
    1028) Recover a Tree From Preorder Traversal
    ============================================

    ============
    Description:
    ============

    We run a preorder depth-first search (DFS) on the root of a binary tree.

    At each node in this traversal, we output D dashes (where D is the depth of
    this node), then we output the value of this node.  If the depth of a node
    is D, the depth of its immediate child is D + 1.  The depth of the root
    node is 0.

    If a node has only one child, that child is guaranteed to be the left
    child.

    Given the output traversal of this traversal, recover the tree and return
    its root.

    ==========================================================
    FUNCTION: TreeNode* recoverFromPreorder(string traversal);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: traversal = "1-2--3--4-5--6--7"
    Output: [1,2,5,3,4,6,7] // Levelorder

    --- Example 2 ---
    Input: traversal = "1-2--3---4-5--6---7"
    Output: [1,2,5,3,null,6,null,4,null,7] // Levelorder

    --- Example 3 ---
    Input: traversal = "1-401--349---90--88"
    Output: [1,401,null,349,88,90] // Levelorder


    *** Constraints ***
    The number of nodes in the original tree is in the range [1, 1000].
    1 <= Node.val <= 10^9

*/

#include <string>
using namespace std;

/**
 * Definition for a binary tree node.
 */
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

    This is a kind of Brute-Force in a way, but given the Constraints it's not
    too bad.

    We have to USE the property "If there is only one child, then it's ALWAYS
    a left child".

    That's used when we are creating a node, however--more importantly--it's
    used when we are traversing the nodes from the root, to try and get to our
    desired node at certain depth. ("dfs" functions).
    
    The best way to understand what I'm doing is to literally try to read the
    code and "simulate" it on paper for yourself.

    It's really self-explanatory.

*/

/* Time  Beats: 62.80% */
/* Space Beats: 44.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal)
    {
        const int N = traversal.length();

        if (traversal.find("-") == string::npos)
            return new TreeNode(stoi(traversal.substr(0)));

        int idx_of_first_hyphen = traversal.find("-");
        TreeNode* root = new TreeNode(stoi(traversal.substr(0, idx_of_first_hyphen)));

        TreeNode* curr_node = root;
        int curr_level = 0;

        // Skip over first_number which is always the value of the first node
        int i = idx_of_first_hyphen;
        while (i < N)
        {
            int depth = 0;
            int value = 0;
            while (traversal[i] == '-')
            {
                depth++;
                i++;
            }

            int start_val = i;
            while (i < N && traversal[i] != '-')
                i++;

            string value_str = traversal.substr(start_val, i - start_val);
            value = stoi(value_str);

            if ( ! (depth > curr_level))
            {
                curr_node  = dfs(root, depth-1);
                curr_level = depth - 1;
            }

            if ( ! curr_node->left)
            {
                curr_node->left  = new TreeNode(value);
                curr_node = curr_node->left;
                curr_level++;
            }
            else
            {
                curr_node->right = new TreeNode(value);
                curr_node = curr_node->right;
                curr_level++;
            }
        }

        return root;
    }

private:
    TreeNode* dfs(TreeNode* root, int depth)
    {
        if ( ! root)
            return nullptr;

        if (depth == 0)
            return root;

        TreeNode* right = dfs(root->right, depth - 1); // Always go right first
        if (right)
            return right;

        TreeNode* left  = dfs(root->left , depth - 1);
        return left;
    }
};
