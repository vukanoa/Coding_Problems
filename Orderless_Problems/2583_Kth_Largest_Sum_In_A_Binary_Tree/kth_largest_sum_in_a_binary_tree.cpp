#include <iostream>
#include <vector>
#include <queue>
#include <priority_queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2583) Kth Largest Sum In a Binary Tree
    ======================================

    ============
    Description:
    ============

    You are given the root of a binary tree and a positive integer k.

    The level sum in the tree is the sum of the values of the nodes that are on
    the same level.

    Return the kth largest level sum in the tree (not necessarily distinct). If
    there are fewer than k levels in the tree, return -1.

    =====
    Note: Note that two nodes are on the same level if they have the same distance
          from the root.
    =====

    ==============================================================
    FUNCTION: long long kthLargestLevelSum(TreeNode* root, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,8,9,2,1,3,7,4,6], k = 2
    Output: 13
    Explanation: The level sums are the following:
    - Level 1: 5.
    - Level 2: 8 + 9 = 17.
    - Level 3: 2 + 1 + 3 + 7 = 13.
    - Level 4: 4 + 6 = 10.
    The 2nd largest level sum is 13.


    --- Example 2 ---
    Input: root = [1,2,null,3], k = 1
    Output: 3
    Explanation: The largest level sum is 3.


    *** Constraints ***
    The number of nodes in the tree is n.
    2 <= n <= 105
    1 <= Node.val <= 106
    1 <= k <= n

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    The very first thing is that they are asking us to find "level sum" in a
    Binary Tree. It should be clear as a bell ring that we need to perform a
    BFS on a Binary Tree to obtain that information.

    Let's assume we have each level's sum in, say, a vector. How can we find a
    k-th one?

    Well, one way is to sort that and then go either from the front or the back
    and then return the kth one.

    That is a valid approach, however, there is a slightly more optimized way
    of doing that.

        Using a Max Heap!

        Insert       takes O(log k).
        Retrieve top takes O(1).
        Pop          takes O(log k).

    For each level, insertion into the heap is done once, and there are at most
    n levels to process, therefore the TimeComplexity is O(n * logk).


    K is USUALLY smaller than the number of levels. We don't know which one is
    going to be smaller in the Examples, but it is safe and reasonable to
    assume that k is going to be smaller.

    If that is the case then: O(n * logk) is MORE efficient than O(n * logn).

    Therefore, that's why we've solved this problem using "Max Heap".



    How are we soling it using Heap?

    We're going to push all "level sum" values into the "Max Heap" and once we
    are done wih BFS, we can pop k-1 elements from the "Max Heap" and at that
    point we're left with our desired result at the top of "Max Heap".

    It as simple as that.

*/

/* Time  Beats: 99.41% */
/* Space Beats:  5.08% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(n + k)    */
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k)
    {
        priority_queue<long long> max_heap;

        /* BFS */
        queue<TreeNode*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            long long level_sum = 0;
            for (int x = 0; x < size; x++)
            {
                TreeNode* curr_node = queue.front();
                queue.pop();

                level_sum += curr_node->val;

                if (curr_node->left)
                    queue.push(curr_node->left);

                if (curr_node->right)
                    queue.push(curr_node->right);
            }

            max_heap.push(level_sum);
        }

        if (max_heap.size() < k) // Fewer than k levels
            return -1;

        int i = 0;
        while (i++ < k-1)
            max_heap.pop();

        return max_heap.top();
    }
};
