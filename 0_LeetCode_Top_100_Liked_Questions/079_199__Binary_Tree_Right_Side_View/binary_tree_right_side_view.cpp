#include <iostream>
#include <vector>

// For printing
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    199) Binary Tree Right Side View
    ================================

    ============
    Description:
    ============

    Give the "root" of a binary tree, imagine yourself standing on the right
    side of it, return the values of the nodes you can see ordered from top
    to bottom.

    ====================================================
    FUNCTION: vector<int> rightSideView(TreeNode* root);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
         1
      2     3
        5    4

    Input:  root = [1, 2, 3, null, 5, null, 4]
    Output: [1, 3, 4]


    --- Example 2 ---
      1
         3

    Input:  root = [1, null, 3]
    Output: [1, 3]

    --- Example 3 ---


    Input:  root = []
    Output: []

    *** Constraints ***
    The number of nodes in thre tree is in the range [0, 100].
    -100 <= Node.val <= 100

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

/*
    ------------
    --- IDEA ---
    ------------

    Basic DFS.

    The only important thing here is to implement DFS going to the right first,
    since we are asked to return **Right Side View**.

    It's maybe not super-intuitive, but if say that the top level is "level 1",
    then we can use that to our advantage and each time we are at some level
    we shall ask if this level is greater than the size of "result".

    Why are we doing that?

    First of all, as I've said, we're always going to the right first!
    That will ensure that if there are multiple nodes in this level, only the
    rightmost node's value gets to be put in "result".

    However, if there is some deeper node somewhere in the tree that is NOT all
    the way to the right, such as this:

                 _______________________
    Level: 1     ___________1___________
    Level: 2     _____2___________3_____
    Level: 3     __4_____5_____6_____7__
    Level: 4     8_____9________________

    Here, as we can see, Level 4 nodes are not all the way to the right, thus
    the one we shall put in the "result" is the rightmost on that level, i.e.
    node "9".

    Since we'll always check the rightmost node of each level on the FIRST
    "entrance" to that level, then we only have to make sure that we put that
    one.

    In other words, if we have put [1, 3, 7] in our "result" so far and we
    enter "Level 4" for the very first time - We are GUARANTEED to "hit" the
    rightmost node in this "new level"(Deepest so far).

    Therefore we ask:

        If the current Level (level 4 in this case) is greater than the amount
        of elements in "result"(result.size()), then that means we still
        haven't put a node from current level(level 4 in this case) in vector
        "result".

        Therefore, we put "4" in "result" and now we have: [1, 3, 7, 4].

    Once we "hit" node 8, that is also at Level 4, we will not insert it in our
    vector "result" since now Level 4 is NOT greater than result.size().

    That is the crux of this problem.

    These 2 lines:
        if (level > result.size())
            result.push_back(root->val);

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        right_dfs(root, 1, result);

        return result;
    }

private:
    void right_dfs(TreeNode* root, int level, std::vector<int>& result)
    {
        if (!root)
            return;

        if (level > result.size())
            result.push_back(root->val);

        right_dfs(root->right, level+1, result);
        right_dfs(root->left,  level+1, result);
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
    std::cout << "\n\t\t\t(TODO: Implement a Visual representation of a Binary Tree)\n\n";
    std::cout << "\n\t*** Level Order ***";
    std::cout << "\n\tTree: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";
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

    int x = vector_print.size() - 1;
    while (vector_print[x] == "null")
    {
        vector_print.pop_back();
        x--;
    }

    print_array(vector_print);
}


int
main()
{
    Solution sol;

    /* Example 1 */
    /*
             1
          2     3
            5    4
    */
    // TreeNode one(1);
    // TreeNode two(2);
    // TreeNode three(3);
    // TreeNode five(5);
    // TreeNode four(4);

    // one.left = &two;
    // one.right = &three;
    // two.right = &five;
    // three.right = &four;

    // TreeNode* root = &one;



    /* Example 2 */
    /*
          1
             3
    */
    // TreeNode one(1);
    // TreeNode three(3);

    // one.right = &three;

    // TreeNode* root = &one;



    /* Example 3 */
    // TreeNode* root = nullptr;


    /* Example 4 */
    /*
                       1
               2            3
           5       6           7
        9       8
         10

    */
    TreeNode one(1);
    TreeNode two(2);
    TreeNode three(3);
    TreeNode four(4);
    TreeNode five(5);
    TreeNode six(6);
    TreeNode seven(7);
    TreeNode eight(8);
    TreeNode nine(9);
    TreeNode ten(10);

    one.left  = &two;
    one.right = &three;
    three.right = &seven;
    two.left = &five;
    two.right = &six;
    five.left = &nine;
    six.left = &eight;
    nine.right = &ten;

    TreeNode* root = &one;


    std::cout << "\n\t===================================";
    std::cout << "\n\t=== BINARY TREE RIGHT SIDE VIEW ===";
    std::cout << "\n\t===================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    std::vector<int> side_view = sol.rightSideView(root);

    /* Write Output */
    bool first = true;
    std::cout << "\n\tSide View: [";
    for (auto x: side_view)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
