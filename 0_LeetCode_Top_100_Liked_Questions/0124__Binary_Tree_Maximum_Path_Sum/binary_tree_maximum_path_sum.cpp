#include <iostream>
#include <climits>

// Printing
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    =================================
    124) Binary Tree Maximum Path Sum
    =================================

    ============
    Description:
    ============

    A path in a binary tree is a sequence of nodes where each pair of adjacent
    nodes in the sequence has an edge connecting them. A node can only appear
    in the sequence at most once. Note that the path does not need to pass
    through the root.

    The path sum of a path is the sum of the node's values in the path.

    Given the root of a binary tree, return the maximum path sum of any
    non-empty path.

    =========================================
    FUNCTION: int maxPathSum(TreeNode* root);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        _____
        __1__
        2___3

    Input:  root = [1, 2, 3]
    Output: 6



    --- Example 2 ---
        ___________
        ____-10____
        __9_____20_
        ______15__7

    Input:  root = [-10, 9, 20, null, null, 15, 7]
    Output: 42

    *** Constraints ***
    The number of nodes in the tree is in the range [1, 3 * 10^4]
    -1000 <= Node.val <= 1000

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

    I tried to think of base cases and expanded the logic.

    I went through it this way:
        If you have a single node, what is the maximum path?
            The node itself.

        If you have a small tree of root and both root's left node and root's
        right node, what is the max?

            _____X_____
            __X_____X__

            It's either:
                1. Sum of all three, or
                2. Sum of root and left, or
                3. Sum of root and right, or
                4. A single node, out of those three, with the highest value

        What if we add another level to the previous example. What if we had
        something like this? (As in Example 2)

            ___________
            ____-10____
            __9_____20_
            ______15__7

        Every time we're returning from a subtree in "dfs" function, we should
        return the PATH with max value considering that the current node will
        not be the absolute root of the tree/subtree with a maximum path.

        It's a bit confusing if you just read it like this.

        Look at node 20. Once it processes both left and right subtrees, we can
        see that the max path in the entire tree is 42(15 + 20 + 7), however
        if there were a greater path, we cannot return 42 once we're on
        root=20 because that's not possible to be the path that we can
        concatenate further. (Since we have already split once)

        If we've used both the left and the right subtree, that's it. We cannot
        concatenate on top of that.

        However if we want to use the current root as the node of a larger
        tree/subtree, then in that case we have to pick either:
            1. current node's left subtree PATH or
            2. right subtree PATH
        since that is a Path and we CAN concatenate to it.
        (also we do that only if either left or right are greater than 0,
        otherwise just return root->val, or right->val + 0 to be exact)

        Consider another Example:

            _______________________
            ___________5___________
            _____4___________8_____
            __11_________13_____4__
            7___2_________________1

        Look at node 8.
        13 + 8 + 5 = 21

        However, if we want to use 8 as a single node in a larger tree, then
        we have to pick either 13 or 5.

        We pick 13.

        And at the end, maximum path is 48. How?

        7 + 11 + 4 + 5 + 8 + 13

        Notice how we excluded right subtree of node 11, and right subtree of
        node 8, since we have to form a LINEAR PATH. We can't "fork" while
        traversing.

*/

/* Time  Beats: 97.22% */
/* Space Beats: 71.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Elegant {
public:
    int maxPathSum(TreeNode* root)
    {
        int result = INT_MIN;
        dfs(root, result);

        return result;
    }

private:
    int dfs(TreeNode* root, int& result)
    {
        if (!root)
            return 0;

        int left_path_max  = std::max(0, dfs(root->left, result));
        int right_path_max = std::max(0, dfs(root->right, result));

        // THis is WITH Split
        result = std::max(result, root->val + left_path_max + right_path_max);

        // Return PATH(ie. without Split)
        return root->val + std::max(left_path_max, right_path_max);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is how I think about this problem. I was just trying to solve it
    without thinking about the code and, intuitively, I've come up with this
    Solution.

    This is a good example to try this code on:

    ______________________________________________-21______________________________________________
    _______________________9______________________________________________17_______________________
    ___________1______________________-15______________________18______________________2___________
    _________________8_______________________55_________-4___________12_____________________41_____
    ____________________29__________________________________30_________________________________-50_
    __________________________________________________________________________________________3____

*/

/* Time  Beats: 97.65% */
/* Space Beats: 22.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Intuitive {
public:
    int maxPathSum(TreeNode* root)
    {
        int max = INT_MIN;
        dfs(root, max);

        return max;
    }

private:
    int dfs(TreeNode* root, int& max)
    {
        if (!root)
            return 0;

        int left  = dfs(root->left, max);
        int right = dfs(root->right, max);

        max = std::max(max, left  + root->val + right); // All 3
        max = std::max(max, left  + root->val);         // Left  + Root
        max = std::max(max, right + root->val);         // Right + Root
        max = std::max(max, root->val);                 // Only Root

        //          max(  Root   ,      max(Left+Root, Right+Root)   )
        return std::max(root->val, std::max(left + root->val, right + root->val));
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
    Solution_Elegant   sol_elegant;
    Solution_Intuitive sol_intuitive;


    /* Example 1 */
    /*
        _____
        __1__
        2___3
    */
    // TreeNode three(3);
    // TreeNode two(2);
    // TreeNode one(1, &two, &three);
    // TreeNode* root = &one;


    /* Example 2 */
    /*
        ___________
        ____-10____
        __9_____20_
        ______15__7
    */
    // TreeNode nine(9);
    // TreeNode seven(7);
    // TreeNode fifteen(15);
    // TreeNode twenty(20, &fifteen, &seven);
    // TreeNode minus_ten(-10, &nine, &twenty);
    // TreeNode* root = &minus_ten;


    /* Example 3 */
    /*
        ___________
        ____-2_____
        _-3_____5__
        2__-1_1___2
    */
    // TreeNode two1(2);
    // TreeNode minus_one(-1);
    // TreeNode minus_three(-3, &two1, &minus_one);
    // TreeNode one(1);
    // TreeNode two2(2);
    // TreeNode five(5, &one, &two2);
    // TreeNode minus_two(-2, &minus_three, &five);
    // TreeNode* root = &minus_two;


    /* Example 4 */
    /*
        _____
        __1__
        2___3
    */
    // TreeNode four(4);
    // TreeNode minus_two(-2, &four, nullptr);
    // TreeNode one(1);
    // TreeNode five(5, &one, &minus_two);
    // TreeNode three(3);
    // TreeNode two1(2);
    // TreeNode minus_four(-4, &three, &two1);
    // TreeNode two2(2, &five, &minus_four);
    // TreeNode* root = &two2;


    /* Example 5 */
    /*
        _______________________
        ___________3___________
        ____-3__________-2_____
        __2____-2_____7_____2__
        ______4________________
    */
    // TreeNode four(4);
    // TreeNode minus_two1(-2, &four, nullptr);
    // TreeNode two1(2);
    // TreeNode minus_three(-3, &two1, &minus_two1);
    // TreeNode seven(7);
    // TreeNode two2(2);
    // TreeNode minus_two2(-2, &seven, &two2);
    // TreeNode three(3, &minus_three, &minus_two2);
    // TreeNode *root = &three;


    /* Example 6 */
    /*
        _______________________
        ___________5___________
        _____4___________8_____
        __11__________13____4__
        7____2________________1
    */
    TreeNode seven(7);
    TreeNode two(2);
    TreeNode eleven(11, &seven, &two);
    TreeNode four1(4, &eleven, nullptr);
    TreeNode one(1);
    TreeNode four2(4, nullptr, &one);
    TreeNode thirteen(13);
    TreeNode eight(8, &thirteen, &four2);
    TreeNode five(5, &four1, &eight);
    TreeNode *root = &five;


    /* Example 7 */
    /*
        _______________________
        ___________2___________
        ____-3__________-2_____
        __2_____4_____5_____2__
        _____-1________________
    */
    // TreeNode minus_one(-1);
    // TreeNode four(4, &minus_one, nullptr);
    // TreeNode two1(2);
    // TreeNode minus_three(-3, &two1, &four);
    // TreeNode five(5);
    // TreeNode two2(2);
    // TreeNode minus_two(-2, &five, &two2);
    // TreeNode two3(2, &minus_three, &minus_two);
    // TreeNode *root = &two3;


    /* Example 8 */
    /*
        _______________________
        ___________3___________
        ____-3__________-4_____
        __2_____1_____2_____1__
        _____-1________________
    */
    // TreeNode minus_one(-1);
    // TreeNode one1(1, &minus_one, nullptr);
    // TreeNode two1(2);
    // TreeNode minus_three(-3, &two1, &one1);
    // TreeNode two2(2);
    // TreeNode one2(2);
    // TreeNode minus_four(-4, &two2, &one2);
    // TreeNode three(3, &minus_three, &minus_four);
    // TreeNode *root = &three;


    /* Example 9 */
    /*
        _____
        _-3__
    */
    // TreeNode minus_three(-3);
    // TreeNode* root = &minus_three;


    /* Example 9 */
    /*
        _____
    */
    // TreeNode* root = nullptr;


    /* Example 11 */
    /*
        _______________________
        ___________1___________
        ____-2__________-3_____
        __1_____3____-2________
        -1_____________________
    */
    // TreeNode minus_one(-1);
    // TreeNode one1(1, &minus_one, nullptr);
    // TreeNode three(3);
    // TreeNode minus_two1(-2, &one1, &three);
    // TreeNode minus_two2(-2);
    // TreeNode minus_three(-3, &minus_two2, nullptr);
    // TreeNode one(1, &minus_two1, &minus_three);
    // TreeNode* root = &one;


    std::cout << "\n\t====================================";
    std::cout << "\n\t=== BINARY TREE MAXIMUM PATH SUM ===";
    std::cout << "\n\t====================================\n";


    /* Write Input */
    print_levelorder(root);


    /* Solution */
    int max = sol_elegant.maxPathSum(root);
    // int max = sol_intuitive.maxPathSum(root);


    /* Write Output */
    std::cout << "\n\tMax Path Sum is: " << max << "\n\n";


    return 0;
}
