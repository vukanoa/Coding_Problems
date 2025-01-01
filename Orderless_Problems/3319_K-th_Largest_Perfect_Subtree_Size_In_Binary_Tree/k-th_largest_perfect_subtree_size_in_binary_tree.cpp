/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    3319) K-th Largest Perfect Subtree Size in Binary Tree
    ======================================================

    ============
    Description:
    ============

    You are given the root of a binary tree and an integer k.

    Return an integer denoting the size of the kth largest perfect binary
    subtree, or -1 if it doesn't exist.

    A perfect binary tree is a tree where all leaves are on the same level, and
    every parent has two children.

    ==============================================================
    FUNCTION: int kthLargestPerfectSubtree(TreeNode* root, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
    Output: 3
    Explanation:
    The roots of the perfect binary subtrees are highlighted in black. Their
     sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
     The 2nd largest size is 3.


    --- Example 2 ---
    Input: root = [1,2,3,4,5,6,7], k = 1
    Output: 7
    Explanation:
    The sizes of the perfect binary subtrees in non-increasing order are:
    [7, 3, 3, 1, 1, 1, 1]. The size of the largest perfect binary subtree is 7.


    --- Example 3 ---
    Input: root = [1,2,3,null,4], k = 3
    Output: -1
    The sizes of the perfect binary subtrees in non-increasing order are [1, 1].
    There are fewer than 3 perfect binary subtrees.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 2000].
    1 <= Node.val <= 2000
    1 <= k <= 1024

*/

#include <algorithm>
#include <map>
#include <vector>
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

    Simple DFS. If both left and right child is nullptr, then current node is
    indeed a PerfectSubtree of size 1.

    However, if both left and right child exist, then we just check if their
    respective sizes are both equal. If one of them is -1(not a PerfectSubtree)
    then current node is also not a PerfectSubtree, i.e. we'll push it into a
    HashMap as {address_of_node, -1}.

    If left_child or right_child doesn't exist, then it's certainly true that
    current element is NOT a PerfectSubtree.

    If both left and right child do exist and if they are both PerfectSubtrees
    of same size, then the current node's PerfectSubtrees is:

        size = map[root->left] + map[root->right];
        map.insert( {root, size + 1} );

    Once we're done traversing the entire BinaryTree, we simply create a vector
    out of "map" and sort it by second value, ie. by the size of PerfectSubtree
    and we return "k-1"-th one. However we must be careful. Maybe k-1 index is
    greater than vec.size(), in that case we must return -1, to prevent
    Out-Of-Bounds error.

*/

/* Time  Beats: 17.36% */
/* Space Beats:  8.47% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k)
    {
        map<TreeNode*, int> map;

        dfs(root, map);
        vector<pair<TreeNode*, int>> vec(map.begin(), map.end());

        sort(vec.begin(), vec.end(), [](const auto& p1, const auto& p2){
            return p1.second > p2.second;
        });

        if (k-1 >= vec.size())
            return -1;

        return vec[k-1].second;
    }

private:
    void dfs(TreeNode* root, map<TreeNode*, int>& map)
    {
        if (!root)
            return;

        if (!root->left && !root->right)
        {
            map.insert( {root, 1} );
            return;
        }

        dfs(root->left, map);
        dfs(root->right, map);

        if (root->left && root->right && map[root->left] == map[root->right])
        {
            int size = map[root->left] + map[root->right];
            map.insert( {root, size + 1} );
        }
        else
            map.insert( {root, -1} );
    }
};
