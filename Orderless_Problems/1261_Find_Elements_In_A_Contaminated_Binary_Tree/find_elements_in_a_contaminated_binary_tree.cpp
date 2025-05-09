/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1261) Find Elements in a Contaminated Binary Tree
    =================================================

    ============
    Description:
    ============


    Given a binary tree with the following rules:

        root.val == 0
        For any treeNode:
            + If treeNode.val has a value x and treeNode.left != null, then
              treeNode.left.val == 2 * x + 1

            + If treeNode.val has a value x and treeNode.right != null, then
              treeNode.right.val == 2 * x + 2

    Now the binary tree is contaminated, which means all treeNode.val have been
    changed to -1.

    Implement the FindElements class:

        + FindElements(TreeNode* root) Initializes the object with a
          contaminated binary tree and recovers it.

        + bool find(int target) Returns true if the target value exists in the
          recovered binary tree.

    ===============================
    CLASS:
    class FindElements {
    public:
        FindElements(TreeNode* root)
        {

        }

        bool find(int target)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["FindElements","find","find"]
    [[[-1,null,-1]],[1],[2]]
    Output
    [null,false,true]
    Explanation
    FindElements findElements = new FindElements([-1,null,-1]);
    findElements.find(1); // return False
    findElements.find(2); // return True

    --- Example 2 ---
    Input
    ["FindElements","find","find","find"]
    [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
    Output
    [null,true,true,false]
    Explanation
    FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
    findElements.find(1); // return True
    findElements.find(3); // return True
    findElements.find(5); // return False

    --- Example 3 ---
    ["FindElements","find","find","find","find"]
    [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
    Output
    [null,true,false,false,true]
    Explanation
    FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
    findElements.find(2); // return True
    findElements.find(3); // return False
    findElements.find(4); // return False
    findElements.find(5); // return True

    *** Constraints ***
    TreeNode.val == -1
    The height of the binary tree is less than or equal to 20
    The total number of nodes is between [1, 10^4]
    Total calls of find() is between [1, 10^4]
    0 <= target <= 10^6

*/

#include <queue>
#include <unordered_set>
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

    Do a BFS to recover the tree. Once the Tree is recovered, simply do a
    preordered-DFS to find a target in "find" function.

*/

/* Time  Beats: 22.99% */
/* Space Beats: 88.22% */
class FindElements {
public:

    /* Time  Complexity: O(N) */
    /* Space Complexity: O(N) */
    FindElements(TreeNode* root)
    {
        root->val = 0;

        queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                auto node = queue.front();
                queue.pop();

                if (node->left)
                {
                    node->left->val = node->val * 2 + 1;
                    queue.push(node->left);
                }

                if (node->right)
                {
                    node->right->val = node->val * 2 + 2;
                    queue.push(node->right);
                }
            }
        }

        m_root = root;
    }

    /* Time  Complexity: O(N) */
    /* Space Complexity: O(N) */
    bool find(int target)
    {
        return preorder(m_root, target);
    }

private:
    TreeNode* m_root;

    bool preorder(TreeNode* root, int target)
    {
        if ( ! root)
            return false;

        if (root->val == target)
            return true;

        return preorder(root->left, target) || preorder(root->right, target);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of doing a preorder-DFS each time i "find" function, we can put
    each processed value in "uset_seen" HashSet and thus we can in O(1) check
    whether some element exists or not.

    This is more efficient than the above approach, but it's nice to see both
    if you're just starting doing LeetCode.

    Also here, we don't even keep track of the m_root, we don't need it. We
    didn't need it up there either, but I've included it so that you could see
    the difference.

    Since it is passed by reference, we can change VALUES inside this passed
    Tree, however we cannot change what points to it and what it is pointing at

    But we don't need to change pointers anyway, thus we don't need to have a
    m_root variable.

*/

/* Time  Beats: 22.99% */
/* Space Beats: 88.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class FindElements_2 {
public:
    FindElements_2(TreeNode* root)
    {
        root->val = 0;

        queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                auto node = queue.front();
                queue.pop();

                if (node->left)
                {
                    node->left->val = node->val * 2 + 1;
                    queue.push(node->left);
                }

                if (node->right)
                {
                    node->right->val = node->val * 2 + 2;
                    queue.push(node->right);
                }
            }
        }
    }

    bool find(int target)
    {
        return uset_seen.find(target) != uset_seen.end();
    }

private:
    unordered_set<int> uset_seen;
};
