#include <iostream>
#include <vector>
#include <unordered_set>

// For Printing
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    98) Validate Binary Search Tree
    ===============================

    ============
    Description:
    ============

    Given the "root" of a binary tree, determine if it is a valid binary search
    tree(BST)

    A valid BST is defined as follows:
        - The left subtree of a node containts only nodes with keys less than
          the node's key.

        - The right subtree of a node contains only nodes with keys greater
          than the node's key.

        - Both the left and right subtrees must also be binary search trees.

    ==========================================
    FUNCTION: bool isValidBST(TreeNode* root);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [2, 1, 3]
    Output: true

    --- Example 2 ---
    Input:  root = [5, 1, 4, null, null, 3, 6]

    *** Constraints ***
    - The number of nodes in the tree is in the range [1, 10^4]
    - -2^31 <= Nodel.val <= 2^31 - 1

*/


/*
    ------------
    --- IDEA ---
    ------------

    It's obvious that if you go to the right subtree, that all the elements
    must be greater than the root node. However, it's not so obvious to notice
    almost the same thing - The lowest value that is allowed to appear in the
    right subtree is bounded by the root node's value.


    For example:
                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___4_X__________
                                    ^
                                    |
                                  this value MUST BE GREATER than 5.

    It must be greater than 5 because otherwise it would NOT be a BST anymore.

    So whenever we are going to the right subtree of current's root node, we
    must say that the current node is the LEFT or LOWER_BOUND.

    Similarly, whenever we are going to the left subtree of current's root node
    we must say that the current node is the RIGHT or UPPER_BOUND.
                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___X_6__________
                                  ^
                                  |
                         this value MUST BE LOWER than 5.
                         (and since it's a right subtree of root node 3, it
                          also must be GREATER than value 3)

    However, we can't pass simple values since maybe there is no constraint
    for either lower or upper bound and we don't want to erroneously check
    when we don't have to since it could lead to a incorrect result.

    Therefore, instead of passing a value as an lower_bound or upper_bound, we
    are going to pass a pointer to entire node that represents the bound.

    In that case, if there is not lower or upper bound, we won't be checking
    if the rule is infringed and will just continue as normal.

    Here is an example where we don't have a limit for how low values can be.
    I.e. there is no lower_bound, it's nullptr.


                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        X_____2___4_6__________
                        ^
                        |
                This value does NOT have a lower_bound.

    You are, hopefully, noticing a pattern.

    If we go to the right subtree, lower_bound becomes the current root.
    However, upper_bound is INHERITED. Meaning, if it's nullptr, there is no
    upper_bound.

    If we go to the left  subtree, upper_bound becomes the current root.
    However, lower_bound is INHERITED. Meaning, if it's nullptr, there is no
    lower_bound.


    In the 2nd Example in this IDEA, we had this Tree.

                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____9__
                        ______2___X_6__________

    Once we are at node 3 and we want to go to its right subtree, then the
    lower_bound becomes 3 itself, however upper_bound is INHERITED. What does
    that mean?

    It means that if there is any upper_bound so far, it will persist. When we
    are going to the right, we are never going to update the "upper_bound" in
    that step, therefore if there is any upper_bound, use it.



    Let's see an example where upper_bound is INHERITED, but is a nullptr.

                        _______________________
                        ___________5___________
                        _____1___________8_____
                        __0_____3_____7_____X__
                        ______2___4_6__________

    Once we are at node 8 and we go to the right, again we'll say that our
    lower_bound is equal to 8, however the upper_bound is inherited.

    Since at this point, upper_bound is nullptr, we will use that. That means
    that in the right subtree of root 8, there are no limits in how big values
    can be found in nodes to the right.

    However, as we've already concluded the left bound is value 8.

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* Time  Beats: 95.81% */
/* Space Beats: 83.78% */

/* Recursive Traversal with Valid Range */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isValidBST(TreeNode* root)
    {
        return dfs(root, nullptr, nullptr);
    }

private:
    bool dfs(TreeNode* root, TreeNode* lower_bound, TreeNode* upper_bound)
    {
        if (!root)
            return true;

        if (lower_bound && lower_bound->val >= root->val)
            return false;

        if (upper_bound && upper_bound->val <= root->val)
            return false;

        return dfs(root->left,  lower_bound,   root     ) &&
               dfs(root->right,    root    , upper_bound);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The crux of this idea is to visit every node in an "inorder" fashion and
    while visiting, store values in vector "vec".

    Once you return from that "inorder" traversal, check if at any point the
    description of what constitutes a BST is infringed or not.

    It must NOT have duplicates and since we've done an "inorder" traversal,
    all the elements must be in strictly increasing order. (The first thing is
    implicit in the second, but wanted to be explicit here).



    It's important to note that this will work only because this is not a
    usual BST. What do I mean with that?

    In a usual BST, for every node, this is true:
        left->val <= current->val < right->val

    i.e. Duplicates can happen and they, usually, are on the left side(Note
    that this can be reversed, however it's important to emphasize that BOTH
    CAN NEVER BE TRUE AT THE SAME TIME!)

    _____
    __5__  ===> This one is usually considered valid
    5____

    _____
    __5__  ===> This one is usually considered INVALID!
    ____5


    However, in this problem - DUPLICATES ARE NOT ALLOWED ON EITHER SIDE!

    Therefore, we are able to put this approach as well, however it should be
    noted that this would not be possible if we had the above case, i.e.:

    _____
    __5__  ===> This one is usually considered valid
    5____

    _____
    __5__  ===> This one is usually considered INVALID!
    ____5

    Why?
    Because putting all the nodes in an inorder traversal in the vector "vec"
    would look the same for both trees, however the first one is a valid one,
    whereas the second one is NOT.

    We wouldn't be able to tell, just from looking at the vector "vec" if the
    tree was of type 1 or type 2.

    Therefore keep in mind that this Solution works for LeetCode because
    duplicates aren't allowed on either side!

*/

/* Time  Beats: 5.22% */
/* Space Beats: 6.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool isValidBST(TreeNode* root)
    {
        std::vector<int> vec;

        inorder(root, vec);

        std::unordered_set<int> uset;
        uset.insert(vec[0]);
        for (int i = 1; i < vec.size(); i++)
        {
            if (uset.count(vec[i]) > 0 || vec[i-1] >= vec[i])
                return false;

            uset.insert(vec[i]);
        }

        return true;
    }

    void inorder(TreeNode* root, std::vector<int>& vec)
    {
        if (!root)
            return;

        inorder(root->left,  vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }
};


/*
    =============================
    === This is just printing ===
    =============================
*/

void
print_array(std::vector<std::string>& nums)
{
    bool first = true;
    std::cout << "\n\t*** Level Order ***";
    std::cout << "\n\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
}


void
print_levelorder(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> queue;
    queue.push(root);

    std::vector<std::string> vector_print;

    while (!queue.empty())
    {
        int size = queue.size();

        for (int i = 0; i < size; i++)
        {
            TreeNode* node = queue.front();
            queue.pop();

            if (!node)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right)
                queue.push(node->right);
            else
                queue.push(nullptr);
        }
    }

    print_array(vector_print);
}


int
main()
{
    Solution sol;
    // Solution_2 sol_2;

    /* Example 1 */
    TreeNode three(3);
    TreeNode one(1);
    TreeNode two(2, &one, &three);
    TreeNode *root = &two;

    /* Example 2 */
    // TreeNode three(3);
    // TreeNode six(6);
    // TreeNode one(1);
    // TreeNode four(6, &three, &six);
    // TreeNode five(5, &one, &four);
    // TreeNode *root = &five;

    /* Example 3 */
    // TreeNode three(3);
    // TreeNode two(2, &three, nullptr);
    // TreeNode one(1, nullptr, &two);
    // TreeNode *root = &one;

    std::cout << "\n\t===================================";
    std::cout << "\n\t=== VALIDATE BINARY SEARCH TREE ===";
    std::cout << "\n\t===================================\n";


    /* Write Input */
    std::cout << "\n\t\t\t~~~ TODO: Write a visual print of BST ~~~\n";
    print_levelorder(root);


    /* Solution */
    bool valid = sol.isValidBST(root);
    // bool valid = sol_2.isValidBST(root);


    /* Write Output */
    if (valid)
        std::cout << "\n\tValid BST: True\n\n";
    else
        std::cout << "\n\tValid BST: False\n\n";


    return 0;
}
