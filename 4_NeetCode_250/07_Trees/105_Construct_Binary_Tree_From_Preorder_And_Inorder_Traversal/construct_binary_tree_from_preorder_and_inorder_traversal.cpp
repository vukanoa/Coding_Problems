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

/* Time  Beats:   100% */
/* Space Beats: 89.93% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        const int N = preorder.size();

        int curr_idx = 0;
        return helper(preorder, inorder, curr_idx, 0, N-1);
    }

private:
    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int& curr_idx, int start, int end)
    {
        if (start > end)
            return nullptr;

        int i = start;
        while (i <= end)
        {
            if (preorder[curr_idx] == inorder[i])
                break;

            // Increment
            i++;
        }

        TreeNode* node = new TreeNode(preorder[curr_idx]);
        curr_idx++;

        node->left  = helper(preorder, inorder, curr_idx, start, i-1);
        node->right = helper(preorder, inorder, curr_idx,  i+1 , end);

        return node;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, however, we can optimize the inner "searching" part by
    pre-computing {val, idx} of inorder vector.

    By using this HashMap we're reducing the Overall Time Complexity from
    O(N^2) down to O(N).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_efficient {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        const int N = preorder.size();

        /* Create a Hash Map to speed up the Search */
        unordered_map<int, int> umap_inorder_val_to_idx;
        for (int i = 0; i < N; i++)
            umap_inorder_val_to_idx.insert( {inorder[i], i} );

        int curr_preorder_root_idx = 0;
        return helper(preorder, umap_inorder_val_to_idx, curr_preorder_root_idx, 0, N-1);
    }

private:
    TreeNode* helper(vector<int>& preorder, unordered_map<int,int>& umap_inorder_val_to_idx, int& curr_preorder_root_idx, int start, int end)
    {
        if (start > end)
            return nullptr;

        int i = umap_inorder_val_to_idx[preorder[curr_preorder_root_idx]];

        TreeNode* node = new TreeNode(preorder[curr_preorder_root_idx]);
        curr_preorder_root_idx++;

        node->left  = helper(preorder, umap_inorder_val_to_idx, curr_preorder_root_idx, start, i-1);
        node->right = helper(preorder, umap_inorder_val_to_idx, curr_preorder_root_idx,  i+1 , end);

        return node;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    It is really difficult to try and explain this. I highly suggest you take
    pen and paper and go through one example by going through the code line by
    line.

    But let me roughly try to explain how this works.

    First, let's consider this example:

        preorder = [3, 9, 1,  2, 8, 11, 4, 5, 20, 15, 16, 7]
         inorder = [2, 1, 8, 11, 9,  5, 4, 3, 15, 16, 20, 7]
                    0  1  2   3  4   5  6  7   8   9  10 11


    First, notice the obivous -- The first node(vlaue at index 0) of inorder
    vector is the LEFTMOST node in the entire tree.

    On the other hand -- The first node(value at index 0) of preorder vector
    is the ROOT node.


            _______________________3_______________________
            ___________9_______________________X___________
            _____1___________4__________15___________7_____
            __2_____8_____5________________16______________
            _________11____________________________________


                                    3 
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       9                        20
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                1             4          15             7
               / \           /             \
              /   \         /               \
             /     \       /                 \
            2       8     5                  16              
                     \
                     11


    So, what we're doing here is -- "Go through preorder vector and build nodes
    as long as we don't hit the leftmost node(i.e. the j-th(0 initially) value
    of inorder vector) of the tree."

    However, if we were just building and going to the left, we would have to
    use recursion. This Solution tries to REMOVE recursion, thus making this
    entire Solution run in O(1) Space Complexity(the tree itself doesn't count
    since we always have to build and return that. There's no way around it)

    So, instead of doing a recursion, i.e. having a "Call Stack" and knowing
    where to go next, we're going to use a "Morris Traversal", which remembers
    the "call stack" by pointing to the previous, non fully traversed nodes,
    with its "right" pointer.

    As soon as we hit the leftmost node, we want to go to our previous node
    (i.e. the node we're point at with our "right" pointer currently), thus we
    assign "prev" to point to that node and we set our current "right" to point
    at nullptr, since we've hit the bottom of the lefmost part.

    Then, as long as the current j-th value is the "prev" node, we repeat this
    above paragraph part. (It sounds confusing, but it's impossible to explain
    without simulating on pen and paper)

    Once we're done with that, we simply try to do this entire process again
    and we repeat it as long as there are nodes in the tree.


    I know this sounds confusing, but--Trust me, if you go through this example
    by hand on pen and paper, slowly, I guarantee that you will have the "AHA!
    WOOOOW" moment, if you've never heard of "Morris Traversal".


*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.93% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Result Tree isn't "Extra" Space
class Solution_Morris_Traversal {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        const int N = preorder.size();

        TreeNode dummy_root(-1);
        TreeNode* curr = &dummy_root;

        int i = 0;
        int j = 0;
        while (i < N && j < N)
        {
            TreeNode* node = new TreeNode(preorder[i]);
            node->right = curr->right;

            curr->right = node;

            // Move forward
            curr = curr->right;
            i++;

            while (i < N && curr->val != inorder[j])
            {
                TreeNode* new_node = new TreeNode(preorder[i]);
                new_node->right = curr;

                curr->left = new_node;

                // Move forward
                curr = curr->left;
                i++;
            }

            j++; // Since we've hit and created the j-th value of INORDER vec

            while (j < N && curr->right && curr->right->val == inorder[j])
            {
                TreeNode* prev = curr->right;
                curr->right = nullptr;

                // Simulate popping the Call Stack
                curr = prev;
                j++;
            }
        }

        return dummy_root.right;
    }
};
