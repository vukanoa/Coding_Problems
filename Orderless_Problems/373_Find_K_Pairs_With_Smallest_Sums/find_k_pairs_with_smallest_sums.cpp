/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    373) Find K Pairs with Smallest Sums
    ====================================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2 sorted in non-decreasing
    order and an integer k.

    Define a pair (u, v) which consists of one element from the first array and
    one element from the second array.

    Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest
    sums.

    ============================================================================================
    FUNCTION: vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k);
    ============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
    Output: [[1,2],[1,4],[1,6]]
    Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

    --- Example 2 ---
    Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
    Output: [[1,1],[1,1]]
    Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 10^5
    -10^9 <= nums1[i], nums2[i] <= 10^9
    nums1 and nums2 both are sorted in non-decreasing order.
    1 <= k <= 10^4
    k <= nums1.length * nums2.length

*/

using namespace std;


#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.67% */
/* Space Beats: 18.08% */

/* Time  Complexity: O(K * logK) */
/* Space Complexity: O(K)        */
class Solution {
private:
    // Static comparator for the min-heap
    struct Compare
    {
        bool operator()(const vector<int>& a, const vector<int>& b) const
        {
            return a[0] + a[1] > b[0] + b[1];
        }
    };

public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        priority_queue<vector<int>, vector<vector<int>>, Compare> min_heap;

        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty() || k == 0)
            return result;

        // Initialize the heap with the first element from nums2 paired with up
        // to k elements from nums1
        for(int i = 0; i < nums1.size() && i < k; i++)
            min_heap.push( {nums1[i], nums2[0], 0} ); // {num1, num2, index_in_nums2}

        while (k > 0 && ! min_heap.empty())
        {
            vector<int> top = min_heap.top();
            min_heap.pop();

            result.push_back( {top[0], top[1]} );

            int idx = top[2];
            if (idx + 1 < nums2.size())
                min_heap.push( {top[0], nums2[idx + 1], idx + 1} );

            // Decrement
            k--;
        }

        return result;
    }
};
