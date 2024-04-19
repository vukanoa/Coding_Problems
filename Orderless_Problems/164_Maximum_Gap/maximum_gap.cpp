#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    164) Maximum gap
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return the maximum difference between two
    successive elements in its sorted form. If the array contains less than two
    elements, return 0.

    You must write an algorithm that runs in linear time and uses linear extra
    space.

    =================================================
    FUNCTION: int maximumGap(std::vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,6,9,1]
    Output: 3
    Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or
                 (6,9) has the maximum difference 3.


    --- Example 2 ---
    Input: nums = [10]
    Output: 0
    Explanation: The array contains less than 2 elements, therefore return 0.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Suppose in our integer array N elements, the min value is min and the max
    value is max. Then the maximum gap will be greater or equal to ceiling
    [(max - min ) / (N - 1)].

    Let bucketSize = ceiling[(max - min ) / (N - 1)].

    We divide all numbers in the array into N buckets, each bucket has size of
    bucketSize, where i-th (zero-based index) bucket contains all numbers in
    range [min + i*bucketSize, min + (i+1)*bucketSize).

    Because maximum gap is always greater or equal to bucketSize so in each
    bucket, we only need to store max element and min element, skip middle
    elements (min < middle < max) in the same bucket.

    Finally, we only need to compare max number in current bucket and min
    number in next bucket to get the relatively large gap and find out which
    two bucket have the maximum gap.


    Picture: (Buckets)

    |  3-9  |    | 10-16 |    | 17-23 |    | 24-30 |    | 31-37 |    | 38-44 |    | 48-51 |
    +-------+    +-------+    +-------+    +-------+    +-------+    +-------+    +-------+
    |   3   |    |       |    |       |  /-|->24   |    |       |    |       |    |       |
    +-------+    +       +    +       + /  +-------+    +-------+    +       +    +-------+
    |   9   |    |       |  /-|-------|-   |  25   |   -|->37 <-|----|-------|----|-> 45  |
    +-------+    +       + /  +       +    +-------+  / +-------+    +       +    +-------+
    |  43 <-|----|-------|-   |       |    |  29 <-|--  |       |    |       |    |       |
    +-------+    +-------+    +-------+    +-------+    +-------+    +-------+    +-------+

*/

/* Time  Beats: 95.19% */
/* Space Beats: 28.80% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maximumGap(std::vector<int>& nums)
    {
        const int n = nums.size();

        int min = *std::min_element(nums.begin(), nums.end());
        int max = *std::max_element(nums.begin(), nums.end());

        if (min == max) // All elements are the same
            return 0;

        int bucket_size = static_cast<int>(std::ceil(1.0 * (max-min) / (n-1)));
        std::vector<int> min_bucket(n, INT_MAX);
        std::vector<int> max_bucket(n, INT_MIN);

        for (const int& x : nums)
        {
            int idx = (x - min) / bucket_size;
            min_bucket[idx] = std::min(x, min_bucket[idx]);
            max_bucket[idx] = std::max(x, max_bucket[idx]);
        }


        int max_gap  = bucket_size;   // Maximum gap is ALWAYS >= bucket_size
        int previous = max_bucket[0]; // We always have 0th Bucket

        for (int i = 0; i < n; i++)
        {
            if (min_bucket[i] == INT_MAX)
                continue; // Skip empty bucket

            max_gap = std::max(max_gap, min_bucket[i] - previous);
            previous = max_bucket[i];
        }

        return max_gap;
    }
};
