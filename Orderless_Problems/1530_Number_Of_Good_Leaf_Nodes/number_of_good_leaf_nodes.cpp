#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    1530) Number of Good Leaf Nodes
    ===============================

    ============
    Description:
    ============

    You are given the root of a binary tree and an integer distance. A pair of
    two different leaf nodes of a binary tree is said to be good if the length
    of the shortest path between them is less than or equal to distance.

    Return the number of good leaf node pairs in the tree.

    =======================================================
    FUNCTION: int countPairs(TreeNode* root, int distance); 
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,null,4], distance = 3
    Output: 1
    Explanation: The leaf nodes of the tree are 3 and 4 and the length of the
                 shortest path between them is 3. This is the only good pair.

    --- Example 2 ---
    Input: root = [1,2,3,4,5,6,7], distance = 3
    Output: 2
    Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2. The
                 pair [4,6] is not good because the length of ther shortest
                 path between them is 4.

    --- Example 3 ---
    Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
    Output: 1
    Explanation: The only good pair is [2,5].


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 2^10].
    1 <= Node.val <= 100
    1 <= distance <= 10

*/

using namespace std;

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

    TODO

*/

/* Time  Beats: 43.81% */
/* Space Beats: 50.79% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countPairs(TreeNode* root, int distance)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        int pairs = 0;

        dfs(root, distance, pairs);

        return pairs;
    }

private:
    vector<int> dfs(TreeNode* root, const int& distance, int& pairs)
    {
        if ( ! root)
            return {};

        if ( !root->left && !root->right)
            return {1};

        vector<int> left_distances  = dfs(root->left,  distance, pairs);
        vector<int> right_distances = dfs(root->right, distance, pairs);

        for (const int& d1 : left_distances)
        {
            for (const int& d2 : right_distances)
            {
                if (d1 + d2 <= distance)
                    pairs++;
            }
        }

        vector<int> all_distances = left_distances;
        all_distances.insert(all_distances.end(), right_distances.begin(), right_distances.end());

        for (int& d : all_distances)
            d++;

        return all_distances;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since there can be more than one leaf on the left(or right) side with the
    same distance to its mutual parent, then we can use a Hash Map instead
    where the distance is the key and number of such nodes is the value.

*/

/* Time  Beats: 46.68% */
/* Space Beats: 17.94% */

/* Time  Complexity: O(n * d^2) */
/* Space Complexity: O(n)       */
class Solution_Hash_Map {
class Solution {
public:
    int countPairs(TreeNode* root, int distance)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        int pairs = 0;

        dfs(root, distance, pairs);

        return pairs;
    }

private:
    unordered_map<int, int> dfs(TreeNode* root, const int& distance, int& pairs)
    {
        if (!root)
            return {};

        if (!root->left && !root->right)
        {
            unordered_map<int, int> count_umap;
            count_umap.insert({1, 1});

            return count_umap;
        }

        unordered_map<int, int> left_distances = dfs(root->left, distance, pairs);
        unordered_map<int, int> right_distances = dfs(root->right, distance, pairs);

        for (const auto& d1 : left_distances)
        {
            for (const auto& d2 : right_distances)
            {
                if (d1.first + d2.first <= distance)
                    pairs += d1.second * d2.second;
            }
        }

        unordered_map<int, int> all_distances;

        for (const auto& d : left_distances)
        {
            if (d.first + 1 <= distance)
                all_distances[d.first + 1] = d.second;
        }

        for (const auto& d : right_distances)
        {
            if (d.first + 1 <= distance)
                all_distances[d.first + 1] += d.second;
        }

        return all_distances;
    }
};
