/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    215) Kth Largest Element in an Array
    =====================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the kth largest
    element in the array.

    Note that it is the kth largest element in the sorted order, not the kth
    distinct element.

    Can you solve it without sorting?


    =============================================================
    FUNCTION: int findKthLargest(std::vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [3, 2, 1, 5, 6, 4], k = 2
    Output: 5

    --- Example 2 ---
    Input:  nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4
    Output: 4

    *** Constraints ***
    1 <= k <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 12.59% */
/* Space Beats: 63.67% */

/* Time  Complexity: O(N * logK) */
/* Space Complexity: O(K)        */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        const int N = nums.size();

        priority_queue<int, vector<int>, greater<int>> min_heap;

        // O(N * logK) (entire block)
        for (const int& num : nums) // O(N)
        {
            min_heap.push(num); // O(logK)

            if (min_heap.size() > k)
                min_heap.pop(); // O(logK)
        }

        return min_heap.top();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is essentially the same as above, however we haven't explicitly
    used "min_heap", instead we "partially sorted it" by using
    "std::partial_sort" which uses the heap and heap_sort under the hood.

    It's beneficial to know about it if you're using C++.

*/

/* Time  Beats: 18.90% */
/* Space Beats: 97.12% */

/* Time  Complexity: O(N * logK) */
/* Space Complexity: O(1)        */
class Solution_Partial_Sort {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        const int N = nums.size();

        partial_sort(nums.begin(), nums.begin() + k, nums.end(), greater<int>());

        return nums[k-1];
    }
};
