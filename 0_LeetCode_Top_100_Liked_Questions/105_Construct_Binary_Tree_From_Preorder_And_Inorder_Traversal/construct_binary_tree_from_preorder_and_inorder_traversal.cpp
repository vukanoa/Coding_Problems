/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    105) Construct Binary Tree from Preorder and Inorder Traversal
    ==============================================================

    ============
    Description:
    ============

    Given two integer arrays "preorder" and "inorder" where "preorder" is the
    preorder traversal of a binary tree and "inorder" is the inorder traversal
    of the same tree, construct and return the binary tree.

    ===========================================================================
    FUNCTION: TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
    Output: [3, 9, 20, null, null, 15, 7]

    --- Example 2 ---
    Input:  preorder = [-1], inorder = [-1]
    Output: [-1]

    *** Constraints ***
    1 <= preorder.length <= 3000
    inorder.length == preorder.length
    -3000 <= preorder[i], inorder[i] <= 3000
    "preorder" and "inorder" consist of unique values
    Each value of "inorder" also appears in "preorder"
    "preorder" is guaranteed to be the preorder traversal of the tree.
    "inorder" is guaranteed to be the inorder traversal of the tree.

*/

#include <vector>
#include <unordered_map>
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

    Two key observations are:
        1. Preorder traversal follows:
            Root -> Left -> Right
           therefore given the preorder array "preorder", we have an easy
           access to the root which is preorder[0].

        2. Inorder traversal follows:
            Left -> Root -> Right
           therefore if we know the position of "Root", we can recursively
           split the entire array into two subtrees.

    Now the idea should be clear enough. We will design a recursive function:
    It will set the first element of "preorder" as the root, and then construct
    the entire tree recursively, by finding the left and right subtrees.

    We will look for the root in "inorder", so that everything on the left
    should be the left subtree. Both subtrees can be constructed by making
    another recursion call.

    It is worth noting that, while we recursively construct the subtrees, we
    always choose the next element in "preorder" to initialize as the new root.

    This is because the current one has already been initialized to a parent
    node for the subtrees.

        ___________
        _____3_____
        __9_____20_
        1___2_15__7

        preorder: [3, 9, 1, 2, 20, 15, 7]
                   ^
                   |                  ------ end
          root -------------          |
                           |          |
         start ----        |          |
                  |        |          |
                  |        |          v
                  S        v          E
        inorder: [1, 9, 2, 3, 15, 20, 7]
                  ~~~~~~~     #########
                      ^           ^
                      |           |
        left_subtree --           |
                                  |
        right_subtree -------------


                          |
                          |
                          |
                          V
                  construct left subtree

        _____
        __9__
        1___2

        preorder: [3, 9, 1, 2, 20, 15, 7]
                      ^
                      |           
          root --------  
                     |   
         start ----  |  ----- end
                  |  |  |
                  |  |  v
                  S  v  E
        inorder: [1, 9, 2, 3, 15, 20, 7]
                  ~     #
                  ^     ^
                  |     |
        left_subtree    |
                        |
        right_subtree ---


                ...
                ...
                etc.
                ...
                ...

*/

/* Time  Beats: 98.46% */
/* Space Beats: 33.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_efficient {
private:
    int preorder_index;
    unordered_map<int, int> umap_inorder_val_to_idx;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        const int N = inorder.size();

        // Build a hashmap to store {value, index} of inorder vector
        for (int i = 0; i < inorder.size(); i++)
            umap_inorder_val_to_idx.insert( {inorder[i], i} );

        return array_to_tree(preorder, 0, preorder.size() - 1);
    }

    TreeNode* array_to_tree(vector<int>& preorder, int first_index, int last_index)
    {
        // If there are no elements to construct the tree
        if (first_index > last_index)
            return nullptr;

        // Select the preorder_index element as the root and increment it
        int root_value = preorder[preorder_index++];
        TreeNode* root = new TreeNode(root_value);

        /* Build left and right subtree */
        // Excluding inorder_value_index_hashmap[root_value] element because that's the root
        root->left  = array_to_tree(preorder,               first_index                     , umap_inorder_val_to_idx.at(root_value) - 1);
        root->right = array_to_tree(preorder, umap_inorder_val_to_idx.at(root_value) + 1,              last_index                       );

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 89.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_My_Way {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        int n = inorder.size();
        TreeNode* root = nullptr;

        for (int i = 0; i < inorder.size(); i++)
        {
            if (inorder[i] == preorder[0])
            {
                root = new TreeNode(preorder[0]);

                int x = 1;
                root->left  = make_tree(preorder, inorder, x,   0, i-1);
                root->right = make_tree(preorder, inorder, x, i+1, n-1);
            }
        }

        return root;
    }

private:
    TreeNode* make_tree(vector<int>& preorder,
                        vector<int>& inorder,
                        int& x,
                        int start,
                        int end)
    {
        if (x >= preorder.size())
            return nullptr;

        TreeNode* node = nullptr;

        for (int i = end; i >= start; i--)
        {
            if (preorder[x] == inorder[i])
            {
                node = new TreeNode(preorder[x]);
                x++;

                node->left  = make_tree(preorder, inorder, x, start, i-1);
                node->right = make_tree(preorder, inorder, x,   i+1, end);
                break;
            }
        }

        return node;
    }
};
