#include <iostream>
#include <vector>
#include <stack>

// For printing
#include <queue>

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

    The Approach is similar to how Quick-Select works. At least in some sense.
    In Quick-Select we had to use the "partition" function and at the end of it
    swap pivot with nums[i].

    However, since over here we have a BST, we don't have to do that.
    Anyway, the part that is shared between both algorithms is:
        if you k == num_of_element_left_of_pivot + 1
            then that means the pivot itself(or in this problem, the root
            itself) is the solution.

    Here we call function "count_nodes_of_subtree" to recursively count both
    the left and the right subtree. (We're counting the number of nodes in each
    subtree)

    Since it is said that this is 1-indexed, meaning that if k = 1, we need to
    return the smallest element.
    Or if k = 2 we need to return the 2nd smallest element in the tree.

    Thus, previously stated, if number of nodes in the left subtree + 1 = k
    we've found it! Return the root and that's it.

    Else if k <= number of nodes in the left subtree
        That means out desired element is in the left subtree.
        Try to do this function recursively on root's left subtree.

    else
        It is certainly in the root's right subtree, but we cannot just
        recursively do the same on the root's right subtree because we need
        the SMALLEST and we've cut out the left subtree and the root itself,
        thus we HAVE to subtract num_of_nodes_in_root's_left_subtree - 1.
        -1 because we need to take root itself into account.

        Now just do recursively the same algorithm on root's right subtree, but
        with this new 'k' value.
*/

/* It's similar to Quick Select */

/* Time  Beats: 64.78% */
/* Space Beats: 85.90% */

/*    Average Time  Complexity: O(n) */
/*
    Worst   Time  Complexity: O(n^2)
    if the tree is essentially a Linked List
*/
/*
    Space Complexity: O(h)
    where 'h' is the height of three. At worst 'h' <==> 'n', therefore O(n)
*/
class Solution {
private:
    void count_nodes_of_subtree(TreeNode* root, int& cnt)
    {
        if (root == nullptr)
            return;

        cnt++;
        count_nodes_of_subtree(root->left, cnt);
        count_nodes_of_subtree(root->right, cnt);
    }

public:
    int kthSmallest(TreeNode* root, int k)
    {
        int left  = 0;
        int right = 0;
        count_nodes_of_subtree(root->left, left);
        count_nodes_of_subtree(root->right, right);

        if (left + 1 == k)
            return root->val;
        else if (k <= left)
            return kthSmallest(root->left, k);
        else
        {
            k = k - left - 1; // -1 indicates the root itself
            return kthSmallest(root->right, k);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's a very straightforward approach with O(N) time complexity. The idea is
    to build an inorder traversal of BST which is an array sorted in the
    ascending order. now the answer is the "k - 1"th element of this array.

*/

/* Time  Beats: 90.30% */
/* Space Beats: 19.42% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_inorder {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        std::vector<int> vec;
        inorder(root, vec);

        return vec[k - 1];
    }

private:
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
    ------------
    --- IDEA ---
    ------------

    This is even more simple than "inorder" Solution.
    We just start counting nodes once we reach the leftmost one.

    Then we count the current one and check if that element is k-th lowest.

    Everything else is so that we could immediately exit if we've already found
    it.

*/

/* Time  Beats: 91.55% */
/* Space Beats: 32.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Simple {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        int count = 0;

        return find(root, k, count);
    }

private:
    int find(TreeNode* root, int k, int& count)
    {
        if (!root)
            return -1;

        int left  = find(root->left,  k, count);
        if (left >= 0 && count == k)
            return left;

        if (++count == k)
            return root->val;

        int right = find(root->right, k, count);
        if (right >= 0 && count == k)
            return right;

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We have to go through several examples to prove why this has to be
    implemented this way.

    First, let's ask an obvious question: How can we know what is the smallest
    element in a BST?

    It's the first leftmost node that has no left subtree.

    Example 1: (k = 1)
    ___________
    _____3_____
    __1_____4__
    ____2______

    Once we get to the first node that node->left == nullptr, then that's the
    smallest. It's important not to count the nodes while we still haven't find
    the absolute smallest.

    We're making sure that's the case by having a "ith" variable as a reference
    argument in each call of "dfs" function.

    At the beginning ith is set to -1.
    Once we get to the first node that doesn't have a left subtree AND ith == -1
    then we should set ith to 0. (That indicates that from this point onwards
    we're going to count nodes until we get to kth smallest)

    Now that we have ith set to 0, we have to check:
        if ith + 1 == k
            if it is then return this current node.

    However we cannot write the "if statement" in this way because if it turns
    out that k > 1 then this statement won't be correct. Thus, we have to write
    it like this:

        if (ith + 1 == k && root->left == nullptr)
            return root;

    Okay, we're having an additional statement:
        root->left == nulltr

    Which prevents one particular case. Consider this example:

    Example 3: (k = 3)
    _______________________________________________10______________________________________________
    _______________________6_______________________________________________11______________________
    ___________1_______________________8___________________________________________________________
    _________________2___________7___________9_____________________________________________________
    ____________________5__________________________________________________________________________
    __________________3____________________________________________________________________________

    Once we get to 1, we see that there is no left subtree, thus we're setting
    variable "ith" to 0 and we're starting to count nodes.

    We're accounting the current node only right before we go in current node's
    right subtree.

    So we account 1 and we go to the right.
    Once we're in the node 2, there is no left subtree, but before we go to its
    right subtree, we account 2, as well. (Now variable "ith" is 2)

    Now we're at node 5 which has the left subtree, thus we FIRST have to go
    left and only afterwards we account the 5 and go right.

    This is the crux of this problem. Why are we doing this?
    Once we're at the node 5, variable "ith" is equal to 2, and k == 3, so if
    were had an if statement like this:

        if (ith + 1 == k)
            return root;

    We would've returned node 5 as the k=3(i.e. 3rd smallest) element in this
    BST which is not true.

    That's why we have to have this additional statement:
        if (ith + 1 == k && root->left == nullptr)
            return root;

    Okay, but do we have an additonal check up immediately after returning from
    dfs on current node's left subtree?

    This is very important. This is the part that is necessary when:
        k > count_nodes(smallest_node->right) + 1

    i.e. when the number of nodes of the smallest's right subtree(left tree is,
    as we've already concluded, nullptr) + 1 because we take into account the
    current one as well, then that means that we have to go BACK to find the
    kth smallest.

    Consider this example:

    Example 3: (k = 4)
    _______________________________________________10______________________________________________
    _______________________6_______________________________________________11______________________
    ___________1_______________________8___________________________________________________________
    _________________2___________7___________9_____________________________________________________
    ____________________5__________________________________________________________________________
    __________________3____________________________________________________________________________


    Once we return from the left subtree of node 5, variable "ith" is going to
    be 3. So we have to check if "ith" + 1(meaning we've accounted the current
    node as well) is equal to k.

    If we were to omit this "if statement" we would've gone into its right
    subtree(which is nullptr in this case) we would propagate upward to node 6
    where we would've taken 6 into account and go right and then we'd always
    "jump over" k, which would result in a Segmentation Fault at the end.

    Also consider the same example for k = 6
    After processing both left and right subtrees of node 5, we would now have
    to go UPWARDS to find the kth smallest.

    That's why that additional "if statement" is absolutely necessary.

*/

/* Time  Beats: 99.78% */
/* Space Beats: 85.90% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_My_Invention {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        int ith = -1;
        TreeNode* kth = dfs(root, k, ith);

        return kth->val;
    }

private:
    TreeNode* dfs(TreeNode* root, int k, int& ith)
    {
        if (root == nullptr)
            return nullptr;

        /* Smallest in a BST */
        if (ith == -1 && root->left == nullptr)
            ith = 0;

        /* This is the crux */
        if (ith + 1 == k && root->left == nullptr)
            return root;


        /* Left */
        TreeNode* left = dfs(root->left, k, ith);
        if (left != nullptr)
            return left;


        /* This is the crux also */
        if (ith + 1 == k)
            return root;

        ith++; // Account the current one


        /* Right */
        TreeNode* right = dfs(root->right, k, ith);
        if (right != nullptr)
            return right;

        return nullptr;
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

/* Time  Beats: 97.17% */
/* Space Beats: 85.90% */

/*
    Time  Complexity: O(H + k)
    where H is a tree height. This complexity is defined by the stack, which
    contains at least H + k elements, since before starting to pop out one has
    to go down to a leaf. This results in O(logN + k) for the balanced tree and
    O(N + k) for completely unbalanced tree with all the nodes in the left
    subtree.
*/
/*
    Space Complexity: O(H)
    to keep the stack, where H is a tree height. That makes O(N) in the worst
    case of the skewed tree, and O(log N) in the average case of the balanced
    tree.
*/
class Solution_follow_up{
public:
    int kthSmallest(TreeNode* root, int k)
    {
        std::stack<TreeNode*> stack;

        for(;;)
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
    std::cout << "\n\t\t[";
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
    Solution               sol;
    Solution_inorder       sol_ino;
    Solution_Simple        sol_simple;
    Solution_My_Invention  sol_my_invention;
    Solution_follow_up     sol_follow;

    /* Example 1 */
    // TreeNode three(3);
    // TreeNode one(1);
    // TreeNode four(4);
    // TreeNode two(2);

    // three.left  = &one;
    // three.right = &four;
    // one.right = &two;

    // TreeNode* root = &three;
    // int k = 1;



    /* Example 2 */
    TreeNode five(5);
    TreeNode three(3);
    TreeNode six(6);
    TreeNode two(2);
    TreeNode four(4);
    TreeNode one(1);

    five.left   = &three;
    five.right  = &six;
    three.left  = &two;
    three.right = &four;
    two.left    = &one;

    TreeNode* root = &five;
    int k = 3;


    std::cout << "\n\t=====================================";
    std::cout << "\n\t=== KTH SMALLEST ELEMENT IN A BST ===";
    std::cout << "\n\t=====================================\n\n";


    /* Write Input */
    std::cout << "\n\t\t\t(TODO: Implement a Visual representation of a Binary Tree)\n\n";
    std::cout << "\n\tTree: ";
    print_levelorder(root);
    std::cout << "\n";


    /* Solution */
    // int kth = sol.kthSmallest(root, k);
    // int kth = sol_ino.kthSmallest(root, k);
    int kth = sol_simple.kthSmallest(root, k);
    // int kth = sol_my_invention.kthSmallest(root, k);
    // int kth = sol_follow.kthSmallest(root, k);


    /* Write Output */
    if (k == 1)
        std::cout << "\n\t" << k << "st Smallest: " << kth << "\n\n";
    else if (k == 2)
        std::cout << "\n\t" << k << "nd Smallest: " << kth << "\n\n";
    else if (k == 3)
        std::cout << "\n\t" << k << "rd Smallest: " << kth << "\n\n";
    else
        std::cout << "\n\t" << k << "th Smallest: " << kth << "\n\n";


    return 0;
}
