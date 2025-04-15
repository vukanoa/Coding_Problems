/*
    ============
    === HARD ===
    ============

    =====================================
    2179) Count Good Triplets in an Array
    =====================================

    ============
    Description:
    ============

    You are given two 0-indexed arrays nums1 and nums2 of length n, both of
    which are permutations of [0, 1, ..., n - 1].

    A good triplet is a set of 3 distinct values which are present in
    increasing order by position both in nums1 and nums2. In other words, if we
    consider pos1v as the index of the value v in nums1 and pos2v as the index
    of the value v in nums2, then a good triplet will be a set (x, y, z) where
    0 <= x, y, z <= n - 1, such that:

        pos1x < pos1y < pos1z and
        pos2x < pos2y < pos2z.

    Return the total number of good triplets.

    =========================================================================
    FUNCTION: long long goodTriplets(vector<int>& nums1, vector<int>& nums2);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
    Output: 1
    Explanation: 
    There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are
    (2,0,1), (2,0,3), (2,1,3), and (0,1,3). Out of those triplets, only the
    triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1
    good triplet.


    --- Example 2 ---
    Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
    Output: 4
    Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2)


    *** Constraints ***
    n == nums1.length == nums2.length
    3 <= n <= 10^5
    0 <= nums1[i], nums2[i] <= n - 1
    nums1 and nums2 are permutations of [0, 1, ..., n - 1].

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.39% */
/* Space Beats: 79.39% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class FenwickTree {
private:
    vector<int> fenwick_tree;

public:
    FenwickTree(int size) : fenwick_tree(size + 1, 0) {}

    void update(int index, int delta)
    {
        index++;
        while (index < fenwick_tree.size())
        {
            fenwick_tree[index] += delta;
            index += index & -index;
        }
    }

    int query(int index)
    {
        index++;
        int result = 0;

        while (index > 0)
        {
            result += fenwick_tree[index];
            index -= index & -index;
        }

        return result;
    }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2)
    {
        int n = nums1.size();
        long long result = 0;

        vector<int> idx_in_nums2(n);
        vector<int> reversed_index_mapping(n);

        for (int i = 0; i < n; i++)
            idx_in_nums2[nums2[i]] = i;

        for (int i = 0; i < n; i++)
            reversed_index_mapping[idx_in_nums2[nums1[i]]] = i;

        FenwickTree fenwick_tree(n);

        for (int value = 0; value < n; value++)
        {
            int pos  = reversed_index_mapping[value];

            int left  = fenwick_tree.query(pos);
            int right = (n - 1 - pos) - (value - left);

            fenwick_tree.update(pos, 1);

            result += (long long)left * right;
        }

        return result;
    }
};
