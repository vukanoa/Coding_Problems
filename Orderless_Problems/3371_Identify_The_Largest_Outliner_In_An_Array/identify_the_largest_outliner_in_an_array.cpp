/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3371) Identify the Largest Outliner in an Array
    ===============================================

    ============
    Description:
    ============

    You are given an integer array nums. This array contains n elements, where
    exactly n - 2 elements are special numbers. One of the remaining two
    elements is the sum of these special numbers, and the other is an outlier.

    An outlier is defined as a number that is neither one of the original
    special numbers nor the element representing the sum of those numbers.

    Note that special numbers, the sum element, and the outlier must have
    distinct indices, but may share the same value.

    Return the largest potential outlier in nums.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,5,10]
    Output: 10
    Explanation:
    The special numbers could be 2 and 3, thus making their sum 5 and the outlier 10.

    --- Example 2 ---
    Input: nums = [-2,-1,-3,-6,4]
    Output: 4
    Explanation:
    The special numbers could be -2, -1, and -3, thus making their sum -6 and the outlier 4.

    --- Example 3 ---
    Input: nums = [1,1,1,1,1,5,5]
    Output: 5
    Explanation:
    The special numbers could be 1, 1, 1, 1, and 1, thus making their sum 5 and the other 5 as the outlier.


    *** Constraints ***
    3 <= nums.length <= 10^5
    -1000 <= nums[i] <= 1000
    The input is generated such that at least one potential outlier exists in nums.

*/

#include <climits>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is way more easy than you think, however you absolutely MUST observe
    one thing. If you notice that one small fact, then the problem because
    trivially easy. At least for a MEDIUM problem.

    First of all, how would a Brute-Force Solution even work?
    Let's consider "Example 1":

        nums = [2,3,5,10]
        Output: 10

    Let's consider each element as an outliner.

        nums = [2,3,5,10]
                ^
                |
              Outliner (potential)

    And each one of the rest of the elements as either in "special numbers" or
    is "sum" itself.
    Maybe there's even a combination where it can be "sum" in one combination
    and "special number" in other.

    Maybe we could improve this part by having a total_sum already calculated.

        total_sum = 20

    So when working with n-1 elements(n elements - one outliner) There are n-2
    possibilities we need to check:

    Each and every one of the remaining elements should be checked if that is
    the "sum". If it is, then all the other are "special elements".

    Since we already have total_sum, we can subtract current potential
    "outliner" from it:

        total_sum - outliner = 20 - 2 = 18

    Okay, the sum of REMAINING elements is 18. Now we can try to see, for each
    of the remaining elements, if that's the "sum".

    How are we going to do that?
    In this case, when "potential outliner" is 2, we start by checking if 3 is
    the "sum".

    How are we doing that?
    We subtract 3 from the current sum(total_sum - outliner).
    If the result is eqaul to 3, then 3 is indeed a "sum". If not, we try the
    next element as a potential "sum".

    However, this would mean our Solution would be O(n^2), which is inefficient
    and we would get a TLE(Time Limi Exceeded) on LeetCode.


    So that would be a Brute-Force. However, if you notice this SMALL thing in
    this Brute-Force approach, the problem becomes trivial.

    This is the "thing" you should notice:

        Let's call (total_sum - outliner) a "curr_sum".

        This is the situation we're in:

            nums = [2,3,5,10]
                    ^ ~~~~~~~
                    |   |
                    |   ---------- curr_sum = 18
                    |
                  Outliner (potential)


        For any of the elements in the "remaining part", in order to be
        "proclaimed" a "sum", this must be true:

            curr_sum - potential_sum = potential_sum

        Right?

        Do you see it now?

        Since:
            curr_sum - ANY_NUMBER should be that same ANY_NUMBER for us to
            "proclaim" this ANY_NUMBER a "sum", we can simply try to find:

                curr_sum / 2

            Out of "remaining elements", except this ANY_NUMBER

        That further means, that instead of trying every single one of the
        "remaining elements" as a "potential sum", which would make our Solution
        a O(n^2), what we can do instead is try to see if there is a:

            curr_sum / 2

        element in "remaining elements".

        Since we ONLY need to see if some number is PRESENT, do you see what we
        can do?

        Yes, HashSet. However, you'd quickly realize a HashSet is not the best
        choice since it's only telling us if it is present or not, much better
        choice is a HashMap since duplicate values are permitted.

    Now, all you have to do is compute a "sum_without" vector which will hold
    a total_sum - current_element as the value in each position.

    Also we'll create a Frequency Map from our "nums".

    Now all we have to do is iterate through all of the elements in "nums" and
    check for each element if it can be an outliner.

    How can we know that?

    First, we must decrement CURRENT value from the HashMap, because it could
    be the case that curr_sum / 2 is equal to the CURRENT value. However if we
    only have one, then we're not allowed to say we've found it since that
    element cann't be used as a "sum" because we're currently using it as an
    "outliner".

    (Read this again and it'll make sense. Read it slowly)

    So:
        if (curr_sum / 2 is PRESENT in HashMap)
            take the maximum out of "result" and current element as an outliner


    That's it.

*/

/* Time  Beats: 66.41% */
/* Space Beats: 32.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int getLargestOutlier(vector<int>& nums)
    {
        const int n = nums.size();
        int result = INT_MIN;

        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        unordered_map<int,int> umap_nums;

        vector<int> sum_without(n, 0);
        for (int i = 0; i < n; i++)
        {
            umap_nums[nums[i]]++;
            sum_without[i] = total_sum - nums[i];
        }

        for (int i = 0; i < n; i++)
        {
            if (sum_without[i] & 1) // Odd / 2 will certainly not be the answer
                continue;

            umap_nums[nums[i]]--;

            int target = sum_without[i] / 2;

            if (umap_nums.find(target) != umap_nums.end() && umap_nums[target] > 0)
                result = max(result, nums[i]);

            umap_nums[nums[i]]++;
        }

        return result;
    }
};
