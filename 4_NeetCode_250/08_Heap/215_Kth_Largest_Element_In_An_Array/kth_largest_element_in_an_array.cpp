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




/*
    ------------
    --- IDEA ---
    ------------

    This one gives TLE for Inputs such as:

        [1, 2, 3, 4, 5, 1, 1, 1, 1, 1, ..., 1, 1, 1, -5, -4, -3, -2, -1]
                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                    ^
                                    |
                                    |
                                    |
                                a LOT of 1s

    However, for most Inputs, this one is faster than the above two Solutions.

*/

/* Time  Complexity: O(N^2), but O(N) AVERAGE */
/* Space Complexity: O(1)                     */
class Solution_Quick_Select_TLE {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        const int N = nums.size();

        int left  = 0;
        int right = N-1;

        int pivot_idx = N;
        while (pivot_idx != (N - k))
        {
            pivot_idx = quick_select(nums, left, right);

            if (pivot_idx < (N - k))
                left  = pivot_idx + 1;
            else
                right = pivot_idx - 1;
        }

        return nums[pivot_idx];
    }

private:
    int quick_select(vector<int>& nums, int left, int right)
    {
        int pivot_idx = right;

        int i = left - 1;
        int j = left;
        while (j < pivot_idx)
        {
            if (nums[j] <= nums[pivot_idx])
                swap(nums[++i], nums[j]);

            // Increment
            j++;
        }
        swap(nums[++i], nums[pivot_idx]);

        return i;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Quickselect works by partitioning around a pivot and recursing only into
    the side that contains the desired order statistic. Unlike Quicksort, it
    does NOT recurse into both sides.

    That is precisely why its average time complexity is O(N), not O(N log N).

    However, naive Quickselect can degrade to O(N^2) if bad pivots are
    repeatedly chosen.

    Modern standard libraries avoid that by using Introselect, an introspective
    selection algorithm. It starts as Quickselect, but if recursion depth grows
    too large, it switches to a guaranteed O(N log N) fallback such as
    heapsort-based selection. This design mirrors Introsort for sorting.

*/

/* Time  Beats: 95.12% */
/* Space Beats: 86.81% */

/* Time  Complexity: O(N * logN), but O(N) AVERAGE */
/* Space Complexity: O(N)                          */
class Solution_Nth_Element___Builtin_Quick_Select {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        const int N = nums.size();

        nth_element(nums.begin(), nums.end() - k, nums.end());
        return nums[N - k];
    }
};
