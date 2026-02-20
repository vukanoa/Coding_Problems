/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    230) Kth Smallest Element in a BST
    ==================================

    ============
    Description:
    ============

    Given the "root" of a binary search tree, and an integer 'k', return the
    k-th smallest value (1-indexed) of all the values of the nodes in tree.

    Follow up: If the BST is modified often(i.e., we can do insert and delete
    operations) and you need to find the kth smallest frequently, how would you
    optimize?

    =================================================
    FUNCTION: int kthSmallest(TreeNode* root, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 1, 4, null, 2], k = 1
    Output: 1

    --- Example 2 ---
    Input:  root = [5, 3, 6, 2, 4, null, null, 1], k = 3
    Output: 3

    *** Constraints ***
    The number of nodes in the tree is 'n'.
    1 <= k <= n <= 10^4
    0 <= Nodelva. <= 10^4

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

    The idea is to build an array as we traverse the BST in an inorder way.
    An inorder traversal is in and of itself a sorted traversal in a BST.

    Then just return (k - 1)th element from that array.

*/

/* Time  Beats: 90.30% */
/* Space Beats: 19.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Inorder_plus_Array {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        vector<int> vec;
        inorder(root, vec);

        return vec[k - 1];
    }

private:
    void inorder(TreeNode* root, vector<int>& vec)
    {
        if ( ! root)
            return;

        inorder(root->left,  vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of traversing the entire Tree and only then finding the (k - 1)th
    node, we can simply count kth_smallest nodes as we go.

    We count the node ONLY AFTER we're DONE with its LEFT SUBTREE.

    If at any point we find out that the current node is kth smallest, we
    propagate its value all the way up the call stack.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Pure_Inorder {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        int kth_smallest = 0;
        return inorder_dfs(root, kth_smallest, k);
    }

private:
    int inorder_dfs(TreeNode* root, int& kth_smallest, int& k)
    {
        if ( ! root)
            return -1;

        int left = inorder_dfs(root->left,  kth_smallest, k);
        if (left != -1) return left;

        kth_smallest++; // Count the current node we're at
        if (kth_smallest == k)
            return root->val;

        int right = inorder_dfs(root->right,  kth_smallest, k);
        if (right != -1) return right;

        if (kth_smallest == k)
            return root->val;

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is the same as above, however it uses O(1) Space instead of O(N),
    which is a huge improvement.

    It's called "Morris Traversal". (There's also a "postorder" version)

    The idea is:

        If the left subtree does NOT exist -- Count the current node as the
        "kth_smallest".

        Otherwise, if the left subtree does INDEED exist -- Find a predecessor
        of the current node(which is the rightmost node in current node's LEFT
        subtree), and link its right pointer(which is a nullptr right now) to
        point to the current node.

        For example, if the current node is 9, then its predecessor is 8.
        (Again, predecessor <==> rightmost node of the LEFT subtree)

        Then we LINK 8's RIGHT POINTER with the current node(i.e. 5).

                                    9
                                  / ^ \
                                 /  |  \
                                /   |   \
                               /    |    \
                              /     |     \
                             /      |___   \
                            /          |    \
                           /           |     \
                          /            |      \
                         /             |       \
                        /              |        \
                       5               |         30
                     /   \             |           \
                    /     \            |            \
                   /       \           |             \
                  /         \          |              \
                 /           \         |               \
               -2             6        |                40
                 \             \       |
                  \             \      |
                   \             \     |
                    2             8    |                     
                   /               \___|
                  1   



    Similarly, predecessor of 5 is 2:


                                    9
                                  / ^ \
                                 /  |  \
                                /   |   \
                               /    |    \
                              /     |     \
                             /      |___   \
                            /          |    \
                           /           |     \
                          /            |      \
                         /             |       \
                        /              |        \
                       5               |         30
                     / ^ \             |           \
                    /  |  \            |            \
                   /   |   \           |             \
                  /    |_   \          |              \
                 /      |    \         |               \
               -2       |     6        |                40
                 \      |      \       |
                  \     |       \      |
                   \    |        \     |
                    2   |         8    |                     
                   / \__|          \___|
                  1




    And predecessor of 2 is 1:


                                    9
                                  / ^ \
                                 /  |  \
                                /   |   \
                               /    |    \
                              /     |     \
                             /      |___   \
                            /          |    \
                           /           |     \
                          /            |      \
                         /             |       \
                        /              |        \
                       5               |         30
                     / ^ \             |           \
                    /  |  \            |            \
                   /   |   \           |             \
                  /    |_   \          |              \
                 /      |    \         |               \
               -2       |     6        |                40
                 \      |      \       |
                  \     |       \      |
                   \    |        \     |
                    2   |         8    |                     
                   /^\__|          \___|
                  1 |_
                   \  |
                    \_|


    Also it's VERY important that we do NOT immeditely return the correct
    result as soon as we find it.

    Why?

    Because some right pointers may still be changed, i.e. the Input Tree is
    NOT the same, therefore if there's a Destructor, it wil try to access a
    nullptr and dereference it at some point, creating a Segmentation Fault.

    So be careful with that. That's why we just assign "result" to the value of
    the curr_node and we continue until all of the pointers are restored.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */  // Efficient Space
class Solution_Morris_Inorder_Traversal {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        int result = -1;

        TreeNode* curr_node = root;
        int kth_smallest = 0;

        while (curr_node)
        {
            if ( ! curr_node->left) // Left Subtree does NOT exist
            {
                kth_smallest++; // Count curr_node
                if (kth_smallest == k)
                    result = curr_node->val; 

                curr_node = curr_node->right;
            }
            else // LEFT SUBTREE exists, therefore there a PREDECESSOR exists
            {
                TreeNode* predecessor = curr_node->left;

                /* Find predecessor of the current node */
                while (predecessor->right && predecessor->right != curr_node)
                    predecessor = predecessor->right;

                if ( ! predecessor->right)
                {
                    predecessor->right = curr_node; // Link temporarily
                    curr_node = curr_node->left;
                }
                else
                {
                    predecessor->right = nullptr;   // Unlink. Restore original

                    kth_smallest++;
                    if (kth_smallest == k)
                        result = curr_node->val; 

                    curr_node = curr_node->right;
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative Inorder Traversal

    The above recursion could be converted into iteration, with the help of
    stack. This way one could speed up the solution because there is no need
    to build the entire inroder traversal, and one could stop after the kth
    element.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Iterative {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        stack<TreeNode*> stack;

        while (true)
        {
            while (root != nullptr)
            {
                stack.push(root);
                root = root->left;
            }

            root = stack.top();
            stack.pop();

            if (--k == 0)
                return root->val;

            root = root->right;
        }

        return -1; // Unreachable
    }
};
