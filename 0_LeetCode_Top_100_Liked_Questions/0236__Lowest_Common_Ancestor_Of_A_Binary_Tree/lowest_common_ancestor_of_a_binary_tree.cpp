/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    236) Lowest Common Ancestor of a Binary Tree
    ============================================

    ============
    Description:
    ============

    Given a binary tree, find the lowest common ancestor (LCA) of two given
    nodes in the tree.

    According to the *definition of LCA on Wikipedia:*"The lowest common
    ancestor is defined between two nodes 'p' and 'q' as the lowest node in 'T'
    that has both 'p' and 'q' as descendants(where we allow a node to be a
    descendant of itself)

    =====
    Note: *We allow a node to be a descendant of itself*
    =====

    ===================================================================================
    FUNCTION: TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 1
    Output: 3

    --- Example 2 ---
    Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 4
    Output: 5

    --- Example 3 ---
    Input:  root = [1, 2], p = 1, q = 2
    Output: 1

    *** Constraints ***
    The number of nodes in the tree is in the range [2, 10^5]
    -10^9 <= Node.val <= 10^9
    All Node.val are unique.
    p != q
    p and q will exist in thre tree

*/

#include <stack>
#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
    ------------
    --- IDEA ---
    ------------

    Since we're told that both 'p' and 'q' exist in the Tree, we do an inorder
    search where we push nodes as we go down, until we find our 'p' or 'q'.
    Also, if we end up going down the wrong path, at the end we pop that node
    since it does not represent the path to our 'p' or 'q'.

    We push p's path in stack_p, and q's path in stack_q.

    Note: We do not push the nodes themselves, only their parent nodes.
          If it happens that either 'p' or 'q' is the root, that means that
          stack_p in case of p == root, or stack_q in case of q == root, will
          be empty. As we've said - We don't keep the nodes themselves in the
          stack.

    After that we're in a situation similar to LeetCode Problem:
        160: Intersection of two Linked Lists

    In that problem, first we count the number of nodes in each of them and
    then we cut-off the difference, meaning we cut-off the difference of:
        longer - shorter
    from a longer one.

    Now both are of the same length and then just go one by one and find where
    they intersect.

    However, this is not it. But it's very similar. It would actually be the
    exact same if we weren't told this:
        *We allow a node to be a descendant of itself*

    Consider 2nd Example:
    _______________________
    ___________3___________
    _____5___________1_____
    __6_____2_____0_____8__
    ______7___4____________

    Input:  root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4], p = 5, q = 4
    Output: 5

    Since 'p' = 5, stack_p will be [3]
    Since 'q' = 4, stack_q will be [3, 5, 2]

    If we were just to "cut-off the difference" we would return 3 as LSA, which
    is not true.

    So how should go resolve this?
    It's actually very simple.

    As you're trying to "pop" TreeNodes, one by one, before you pop you should
    check if:
        (if stack_p is longer than stack_q)
            if (stack_p.top == q)

        (or if stack_q is longer than stack_p)
            if (stack_q.top == p)

    That way we covered that case as well and the problem is resolved.
*/

/* Time  Beats: 74.13% */
/* Space Beats: 13.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
private:
    int inorder_search(TreeNode* root, TreeNode* x, std::stack<TreeNode*>& stack_x)
    {
        if (root == nullptr)
            return 0;
        else if (root == x)
            return 1;
        else
            stack_x.push(root);

        if (inorder_search(root->left, x, stack_x))
            return 1;

        if (inorder_search(root->right, x, stack_x))
            return 1;

        stack_x.pop();
        return 0;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        std::stack<TreeNode*> stack_p;
        std::stack<TreeNode*> stack_q;

        inorder_search(root, p, stack_p);
        inorder_search(root, q, stack_q);

        while (stack_p.size() > stack_q.size())
        {
            if (stack_p.top() == q)
                return q;
            else
                stack_p.pop();
        }

        while (stack_q.size() > stack_p.size())
        {
            if (stack_q.top() == p)
                return p;
            else
                stack_q.pop();
        }

        while (!stack_p.empty() && !stack_q.empty())
        {
            if (stack_p.top() != stack_q.top())
            {
                stack_p.pop();
                stack_q.pop();
            }
            else
                return stack_p.top();
        }

        return nullptr;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    Similar idea, much more concisely written.

*/

/* Time  Beats: 96.11% */
/* Space Beats: 57.80% */

/* Faster */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Clean {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == nullptr || root == p || root == q)
            return root;

        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left == nullptr)  // Both == nullptr or only left == nullptr
            return right;

        if (right == nullptr) // Only right == nullptr
            return left;

        // If both are not null that means that we have found our solution
        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's an equivalent IDEA to the one above(Solution_Clean) however I think
    this one is easier to read and to grasp.

    This is much more in alignment with the way I think about this problem.

*/

/* Time  Beats: 99.94% */
/* Space Beats: 36.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Clean_2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root)
            return nullptr;

        if (root == p || root == q)
            return root;

        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        return left ? left : right;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Solution is almost equivalent to Solution_Clean, however, it's maybe
    easier to read and, therefore, grasp the idea.

*/

/* Time  Beats: 77.11% */
/* Space Beats: 82.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        return dfs(root, p, q);
    }

    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || root == p || root == q)
            return root;

        TreeNode* left  = dfs( root->left, p, q);
        TreeNode* right = dfs(root->right, p, q);

        if (left && !right)  // Only right == nullptr
            return left;

        if (!left && right)  // Only left == nullptr
            return right;

        if (!left && !right) // Both == nullptr
            return nullptr;

        // if (left && right)
        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA, just implemented on another occasion so I wanted to have it here
    as well.

    It can also be divided into 3 parts:
        1)  Since we're told that both 'p' and 'q' exist in the Tree, we do an
            inorder search where we push nodes as we go down, until we find our
            'p' or 'q'.
            Also, if we end up going down the wrong path, at the end we pop
            that node since it does not represent the path to our 'p' or 'q'.

        2) Intersection of Two Linked Lists

        3) Find LCA iterating from the back of each vector until they match


    It uses preorder instead of inorder so it's a bit less Space efficient,
    however it turns out that it's a lot more Time efficient for some reason.

    At least on LeetCode.

*/

/* Time  Beats: 99.99% */
/* Space Beats: 6.31% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Intersection {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        std::vector<TreeNode*> p_vec;
        std::vector<TreeNode*> q_vec;

        /* Fill p_vec and q_vec with preorder_dfs*/
        dfs(root, p, p_vec);
        dfs(root, q, q_vec);

        int p_cnt = p_vec.size();
        int q_cnt = q_vec.size();

        /* Intersection of Two Linked Lists */
        if (p_vec.size() > q_vec.size())
        {
            while (p_cnt > q_cnt)
                p_cnt--;
        }
        else if (p_vec.size() < q_vec.size())
        {
            while (p_cnt < q_cnt)
                q_cnt--;
        }

        /* Find LCA */
        while(p_vec[p_cnt - 1]->val != q_vec[q_cnt - 1]->val)
        {
            p_cnt--;
            q_cnt--;
        }

        return p_vec[p_cnt - 1];
    }

private:
    /* Preorder */
    bool dfs(TreeNode* root, TreeNode* x, std::vector<TreeNode*>& x_vec)
    {
        if (root == nullptr)
            return false;

        x_vec.push_back(root);

        if (root == x)
            return true;

        /* Go Left */
        if (dfs(root->left , x, x_vec))
            return true;

        /* Pop all the nodes up to this one */
        while (x_vec[x_vec.size() - 1] != root)
            x_vec.pop_back();

        /* Go Right */
        if(dfs(root->right, x, x_vec))
            return true;

        /* Pop all the nodes up to this one */
        while (x_vec[x_vec.size() - 1] != root)
            x_vec.pop_back();

        return false;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    There are so many ways to solve this problem, so it's great to include as
    many different solutions as possible.

    If you are a beginner, make sure to read each and every one of them.

*/

/* Time  Beats: 89.70% */
/* Space Beats: 41.24% */

/* Time  Complexity: O() */
/* Space Complexity: O(`) */
class Solution_Counting {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == p || root == q)
            return root;

        TreeNode* lca = nullptr;
        dfs(root, p, q, &lca);

        return lca;
    }

private:
    int dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** lca)
    {
        if ( ! root)
            return 0;

        if (root == p || root == q) // Beacuse every Node.val is UNIQUE
        {
            if (*lca == nullptr)
                *lca = root; // Assume that the current node is LCA

            return 1;
        }

        int left  = dfs(root->left,  p, q, lca);
        if (left == 2) return 2; // We already found LCA

        int right = dfs(root->right, p, q, lca);
        if (right == 2) return 2; // We already found LCA

        if (left + right == 2) // If our assumption was wrong--update
            *lca = root;

        return left + right;
    }
};
