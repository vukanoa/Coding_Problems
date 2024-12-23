/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    2471) Minimum Number of Operations to Sort a Binary Tree by Level
    =================================================================

    ============
    Description:
    ============

    You are given the root of a binary tree with unique values.

    In one operation, you can choose any two nodes at the same level and swap
    their values.

    Return the minimum number of operations needed to make the values at each
    level sorted in a strictly increasing order.

    The level of a node is the number of edges along the path between it and the
    root node.

    ================================================
    FUNCTION: int minimumOperations(TreeNode* root);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
    Output: 3
    Explanation:
    - Swap 4 and 3. The 2nd level becomes [3,4].
    - Swap 7 and 5. The 3rd level becomes [5,6,8,7].
    - Swap 8 and 7. The 3rd level becomes [5,6,7,8].
    We used 3 operations so return 3.
    It can be proven that 3 is the minimum number of operations needed.

    --- Example 2 ---
    Input: root = [1,3,2,7,6,5,4]
    Output: 3
    Explanation:
    - Swap 3 and 2. The 2nd level becomes [2,3].
    - Swap 7 and 4. The 3rd level becomes [4,6,5,7].
    - Swap 6 and 5. The 3rd level becomes [4,5,6,7].
    We used 3 operations so return 3.
    It can be proven that 3 is the minimum number of operations needed.

    --- Example 3 ---
    Input: root = [1,2,3,4,5,6]
    Output: 0
    Explanation: Each level is already sorted in increasing order so return 0.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^5].
    1 <= Node.val <= 10^5
    All the values of the tree are unique.

*/

#include <algorithm>
#include <queue>
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

    TODO

*/

/* Time  Beats: 46.33% */
/* Space Beats: 27.56% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int minimumOperations(TreeNode* root)
    {
        queue<TreeNode*> queue;
        queue.push(root);

        int total_swaps = 0;

        // BFS
        while ( ! queue.empty())
        {
            int size = queue.size();
            vector<int> level_values(size);

            for (int i = 0; i < size; i++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                level_values[i] = node->val;

                if (node->left  != nullptr)
                    queue.push(node->left);

                if (node->right != nullptr)
                    queue.push(node->right);
            }

            total_swaps += calculate_min_swaps(level_values);
        }

        return total_swaps;
    }

private:
    // Calculate minimum swaps needed to sort an array
    int calculate_min_swaps(vector<int>& original)
    {
        int swaps = 0;
        vector<int> target = original;

        /* Sort */
        sort(target.begin(), target.end());

        // Map to track current positions of values
        unordered_map<int, int> umap;
        for (int i = 0; i < original.size(); i++)
            umap[original[i]] = i;

        // For each position, swap until correct value is placed
        for (int i = 0; i < original.size(); i++)
        {
            if (original[i] != target[i])
            {
                swaps++;

                // Update position of swapped values
                int curr_idx = umap[target[i]];

                umap[original[i]] = curr_idx;
                swap(original[curr_idx], original[i]);
            }
        }

        return swaps;
    }
};
