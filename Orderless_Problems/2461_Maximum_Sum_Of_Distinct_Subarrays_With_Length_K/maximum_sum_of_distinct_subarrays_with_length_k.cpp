#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    2461) Maximum Sum of Distinct Subarrays With Length K
    =====================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k. Find the maximum
    subarray sum of all the subarrays of nums that meet the following
    conditions:

        + The length of the subarray is k, and

        + All the elements of the subarray are distinct.

    Return the maximum subarray sum of all the subarrays that meet the
    conditions. If no subarray meets the conditions, return 0.

    A subarray is a contiguous non-empty sequence of elements within an array.

    =================================================================
    FUNCTION: long long maximumSubarraySum(vector<int>& nums, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,5,4,2,9,9,9], k = 3
    Output: 15
    Explanation: The subarrays of nums with length 3 are:
    - [1,5,4] which meets the requirements and has a sum of 10.
    - [5,4,2] which meets the requirements and has a sum of 11.
    - [4,2,9] which meets the requirements and has a sum of 15.
    - [2,9,9] which does not meet the requirements because the element 9 is repeated.
    - [9,9,9] which does not meet the requirements because the element 9 is repeated.
    We return 15 because it is the maximum subarray sum of all the subarrays
    that meet the conditions


    --- Example 2 ---
    Input: nums = [4,4,4], k = 3
    Output: 0
    Explanation: The subarrays of nums with length 3 are: - [4,4,4] which does
                 not meet the requirements because the element 4 is repeated.
                 We return 0 because no subarrays meet the conditions.


    *** Constraints ***
    1 <= k <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    We need to choose the maximum subarray that has all DISTINCT elements.
    To achieve that, we can simply use a HashMap.

    If the HashMap's size is equal k, then we know all the elements in it have
    occurred only and exacly once in the current subarray.

    We will, as you imagine, use a "Sliding Window" approach.

    We'll assign both "left" and "right" pointers to point at index 0, at the
    beginning.

    We'll iterate with our "right" pointer, until it becomes == nums.size().

    In each iteration, immediately, we'll insert currently non-existing element
    and set its count(value) to 1 or we will increment the count of an already
    existing element.

    We will also add this current element value to "sum".

    However, we do NOT want to do anything with it until we've established a
    "Sliding Window" of size k, because that's what we're told to do. We ONLY
    care about subarrays of size EXACTLY k. Therefore, until we have a subarray
    of that size, that's all we do in the for-loop.

    Once "right-left+1" becomes EQUAL to k, we know we've established a desired
    length of our subarray.(From that moment on, every right-left+1 will be k)

    In that case we must check if all the elements in it are DISTINCT. Only if
    they ARE DISTINCT we'll take the maximum between "result"(default 0) and
    "sum" of the current subarray of length k.

    How are we going to do that?
    If our HashMap's size is k, then all the elements in it have a
    frequency_count of exactly 1. Think about it and it'll make sense.

    Afterwards, once we've established the SlidingWindow, from that iteration
    onwards, we must start shifting our "left" pointer as well.

    We have to be careful with it. Before we shift our "left" pointer, we must:
        1. Subtract nums[left] from current "sum", and
        2. We must also decrement the frequency_count(value in HashMap) for
           this nums[left] element.

    BUT, this is important, one we DECREMENT the frequency_count for this
    nums[left] element, we MUST check if, AFTER we've decremented, current
    frequency_count is 0.

    If that is the case we MUST(!!!) remove this entry from the HashMap,
    otherwise we wouldn't be sure if all the elements are DISTINCT in the
    following subarrays of size k.

    Once we've done that, we only have to shift our "left" pointer.
    After the for-loop is done, we simply return "result".

    That's it.

*/

/* Time  Beats: 82.14% */
/* Space Beats: 88.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k)
    {
        long long result = 0;

        unordered_map<int, int> umap;
        int left  = 0;
        int right = 0;

        long long sum = 0;
        for (right = 0; right < nums.size(); right++)
        {
            umap[nums[right]]++;
            sum += nums[right];

            if (right - left + 1 < k) // Until the SlidingWindow is established
                continue;

            if (umap.size() == k)
                result = max(result, sum);

            sum -= nums[left];
            umap[nums[left]]--;
            if (umap[nums[left]] == 0)
                umap.erase(nums[left]);

            left++;
        }

        return result;
    }
};
