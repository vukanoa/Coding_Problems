#include <iostream>
#include <unordered_map>

// For printing
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    437) Path Sum III
    ===========================

    ============
    Description:
    ============

    Given the "root" of a binary tree and an integer "targetSum", return the
    number of paths where the sum of the values along the path equals
    "targetSum".

    The path does not need to start or end at the root or a leaf, but it must
    go downwards (i.3., traveling only from parent nodes to child nodes).

    =====================================================
    FUNCTION: int pathSum(TreeNode* root, int targetSum);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [10, 5, -3, 3, 2, null, 11, 3, -2, null, 1],
            targetSum = 8
    Output: 3

    --- Example 2 ---
    Input:  root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1],
            targetSum = 22
    Output: 3

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 1000].
    -10^9 <= Node.val <= 10^9
    -1000 <= targetSum <= 1000

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

    The idea is very simple. It's a kind of Brute Force DFS solution.

    In function "pathSum" we have:
        return DFS(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);

    Let's go one by one:
    1) DFS(root, targetSum)
    2) pathSum(root->left, targetSum)
    3) pathSum(root->right, targetSum)

    1st one means do a DFS including current node.

    In the first example we have:
    _______________________
    ___________10__________
    _____5__________-3_____
    __3_____2__________11__
    3__-2_____1____________

    It means that we will consider both paths but INCLUDING this current node,
    10 in this case.

    2nd one means - Do a same problem starting with a current's left node as
    root node.

    3rd one means - Do a same problem starting with a current's right node as
    root node.



    Inside DFS, we have:
        return (node->val == sum ? 1 : 0) + DFS(node->left, sum - node->val) + DFS(node->right, sum - node->val);

    Again, let's unpack:
        a) (node->val == sum ? 1 : 0)
        b) DFS(node->left, sum - node->val)
        c) DFS(node->right, sum - node->val)

    a) means if the current node->val is equal to the sum we're searching for
    (this sum can be the absolute sum or the subSum since we always subtract
    current node->val from sum(or subSum) when going left or right).
    If it is then include 1 in equation we're returning.

    b) means do a DFS starting with the current's node LEFT as root, but
    include this current one so, the second argument is now:
        sum - node->val

    c) means do a DFS starting with the current's node RIGHT as root, but
    include this current one so, the second argument is now:
        sum - node->val

*/

/* Time  Beats: 30.83% */
/* Space Beats: 90.91% */

/*
    Worst Time  Complexity: O(n^2)
    Best  Time  Complexity: O(n * logn) // Balanced Tree
*/
/*
    Space Complexity: O(n)
    due to recursion
*/
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        if (root == nullptr)
            return 0;

        /* Counting the number of paths: Start with root, start left w/o root, start right w/o root */
        return DFS(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
    }

    int DFS(TreeNode* node, long long int sum)
    {
        if (node == nullptr)
            return 0;

        return (node->val == sum ? 1 : 0) + DFS(node->left, sum - node->val) + DFS(node->right, sum - node->val);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Go through the code. Stunningly clever idea.

    In the first example we have:
    _______________________
    ___________10__________
    _____5__________-3_____
    __3_____2__________11__
    3__-2_____1____________


    This part of the code is the Crux of this Solution:
        if(map.find(sum - target) != map.end())
            count += map[sum - target];

    We "ask" that each time before we do map[sum]++

    Let's go from the root to the left most node:

            Map
         key : val
        +----+----+
        |  EMPTY  |
        +----+----+


    sum = 10

        if ( (sum - target) exist in the Hash Map)
        if ( ( 10 -   8   ) exist in the Hash Map)
            count += map[2] // map[2] is 0

            Map
         key : val
        +----+----+
        | 10 | 1  |
        +----+----+


    sum = 15

        if ( (sum - target) exist in the Hash Map)
        if ( ( 15 -   8   ) exist in the Hash Map)
            count += map[7] // map[7] is 0

            Map
         key : val
        +----+----+
        | 10 | 1  |
        +----+----+
        | 15 | 1  |
        +----+----+


    sum = 18

        if ( (sum - target) exist in the Hash Map)
        if ( ( 18 -   8   ) exist in the Hash Map)
            count += map[10] // map[10] EXIST and it's 1. Meaning there is only
                             // one "10" up to this path.

            Map
         key : val
        +----+----+
        | 10 | 1  |
        +----+----+
        | 15 | 1  |
        +----+----+
        | 18 | 1  |
        +----+----+


    sum = 21

        if ( (sum - target) exist in the Hash Map)
        if ( ( 21 -   8   ) exist in the Hash Map)
            count += map[13] // map[13] is 0

            Map
         key : val
        +----+----+
        | 10 | 1  |
        +----+----+
        | 15 | 1  |
        +----+----+
        | 18 | 1  |
        +----+----+
        | 21 | 1  |
        +----+----+

    Then, once we've reached the end of the "left path". now go one node "up"
    and then go to the right. Once we go up, we decrease current map[sum].
    Now we have this:

    sum = 16

        if ( (sum - target) exist in the Hash Map)
        if ( ( 16 -   8   ) exist in the Hash Map)
            count += map[8] // map[8] is 0

            Map
         key : val
        +----+----+
        | 10 | 1  |
        +----+----+
        | 15 | 1  |
        +----+----+
        | 18 | 1  |
        +----+----+
        | 16 | 1  |
        +----+----+

    ...

*/

/* Time  Beats: 99.97% */
/* Space Beats: 42.76% */

/*
    Time  Complexity: O(N)
    Where N is the number of nodes in the binary tree. In the recursion we are
    visiting each node only once.
*/
/*
    Space Complexity: O(N)
    Our hashmap takes O(N) space, also we need to consider the space taken by
    the recursive function calls, in the worst case of a skew binary tree, our
    stack can contain up to N funciton calls.
*/
class Solution_DP{
public:
    std::unordered_map<long, int> map;
    int count = 0;

    void countPathSum(TreeNode* root, int target, long sum)
    {
        if(!root)
            return;

        // Path sum from root
        sum += root->val;

        if(sum == target)
            count++;

        // Checking whether any target sum path present in the path from root
        // to the current node
        if(map.find(sum - target) != map.end())
            count += map[sum - target];

        map[sum]++;

        countPathSum(root->left,  target, sum);
        countPathSum(root->right, target, sum);

        // After visiting the left and right subtree, we have to reduce this
        // path sum count from map since we are leaving this path
        map[sum]--;
    }

    int pathSum(TreeNode* root, int targetSum)
    {
        countPathSum(root, targetSum, 0);

        return count;
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
    std::cout << "]\n";
}


void
print_levelorder(TreeNode* root)
{
    if (root == nullptr)
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

            if (node == nullptr)
            {
                vector_print.push_back("null");
                continue;
            }
            else
                vector_print.push_back(std::to_string(node->val));

            if (node->left != nullptr)
                queue.push(node->left);
            else
                queue.push(nullptr);

            if (node->right != nullptr)
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
    Solution_DP sol_dp;


    /* Example 1 */
    /*
        _______________________
        ___________10__________
        _____5__________-3_____
        __3_____2__________11__
        3__-2_____1____________
    */
    TreeNode ten(10);
    TreeNode five(5);
    TreeNode minus_three(-3);
    TreeNode three(3);
    TreeNode two(2);
    TreeNode eleven(11);
    TreeNode three_2(3);
    TreeNode minus_two(-2);
    TreeNode one(1);

    ten.left          = &five;
    ten.right         = &minus_three;
    five.left         = &three;
    five.right        = &two;
    minus_three.right = &eleven;
    three.left        = &three_2;
    three.right       = &minus_two;
    two.right         = &one;

    TreeNode* root = &ten;
    int targetSum = 8;




    /* Example 2 */
    /*
        _______________________
        ___________5___________
        _____4___________8_____
        __11__________13____4__
        7____2____________5___1
    */
    // TreeNode five(5);
    // TreeNode four(4);
    // TreeNode eight(8);
    // TreeNode eleven(11);
    // TreeNode thirteen(13);
    // TreeNode four_2(4);
    // TreeNode seven(7);
    // TreeNode two(2);
    // TreeNode five_2(5);
    // TreeNode one(1);

    // five.left    = &four;
    // five.right   = &eight;
    // four.left    = &eleven;
    // eight.left   = &thirteen;
    // eight.right  = &four_2;
    // eleven.left  = &seven;
    // eleven.right = &two;
    // four_2.left  = &five_2;
    // four_2.right = &one;

    // TreeNode* root = &five;
    // int targetSum = 22;


    std::cout << "\n\t====================";
    std::cout << "\n\t=== PATH SUM III ===";
    std::cout << "\n\t====================\n";


    /* Write Input */
    print_levelorder(root);
    std::cout << "\n\tTarget: " << targetSum;
    std::cout << "\n";


    /* Solution */
    // int count = sol.pathSum(root, targetSum);
    int count = sol_dp.pathSum(root, targetSum);


    /* Write Output */
    std::cout << "\n\n\n\tOutput: " << count << "\n\n";


    return 0;
}
