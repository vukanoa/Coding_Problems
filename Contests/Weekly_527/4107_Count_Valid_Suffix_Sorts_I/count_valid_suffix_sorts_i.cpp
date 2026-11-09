/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    4107) Count Valid Suffix Sorts I
    ================================

    ============
    Description:
    ============

    You are given two integer arrays nums and target, both of length n.

    For each index i, consider sorting the suffix nums[i..n - 1] of the
    original array in non-increasing order.

    Return the number of indices i for which the resulting array is equal to
    target.

    A subarray is a contiguous non-empty sequence of elements within an array.

    A suffix of an array is a subarray that begins at any index and extends to
    the end of the array.

    ==================================================================
    FUNCTION: int countSuffix(vector<int>& nums, vector<int>& target);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3], target = [3,2,1]
    Output: 1
    Explanation:
        i = 0: The resulting array is [3, 2, 1], which equals target.
        i = 1: The resulting array is [1, 3, 2].
        i = 2: The resulting array is [1, 2, 3].
    Only i = 0 is valid, so the answer is 1.

    --- Example 2 ---
    Input: nums = [1,5,6,4,6], target = [1,5,6,6,4]
    Output: 2
    Explanation:
    Choosing either i = 2 or i = 3 results in [1, 5, 6, 6, 4]. No other index
    produces target. Therefore, the answer is 2.

    --- Example 3 ---
    Input: nums = [7,6,8], target = [8,6,7]
    Output: 0
    Explanation:
    Sorting the suffix starting at indices 0, 1, and 2 produces [8, 7, 6], [7,
    8, 6], and [7, 6, 8], respectively. None equals target, so the answer is 0.


    *** Constraints ***
    1 <= n == nums.length == target.length <= 10^5
    1 <= nums[i], target[i] <= 10

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, since the suffix of nums[i..N-1] needs to be sorted in
    NON-INCREASING (i.e. decreasing with, 0 or more, consecutive EQUAL
    elements), the target[i..N-1] must already be in NON-INCREASING order,
    otherwise it'll never be possible since we're not allowed to "touch" the
    target array.

    So the very first thing is finding the leftmost index 'i' in target array
    for which it is true that, starting from that index, the remaining elements
    until the end of the array are in NON-INCREASING order.

    We do that like this:

            while (i >= 0)
            {
                ...
                
                if (i > 0 && target[i-1] < target[i])
                    break;
                
                // Decrement
                --i;
            }

    (Notice that 'i' end up being -1, so we'll take care of that below)

    Now that we have this "leftmost possible start of suffixes", we must check
    whether ALL of the elements from nums[0..i-1] are EXACTLY THE SAME and IN
    THE SAME ORDER as elements from target[0..i-1].

    Why do we need to check that?

    Because we're allowed to sort ONLY the suffix part, therefore the "prefix
    parts" (i.e. [0..i-1] from both arrays) must already be exactly the same.

    If "prefix parts" are NOT the same for LARGER suffixes, then they'll
    certainly NOT be able to be the same when we increase the length of the
    "prefix parts".

    Example:

        nums = [4, 7, 2, 7, 9, 5, 8, 6]
        targ = [4, 7, 9, 7, 9, 8, 6, 5]
                0  1  2  3  4  5  6  7

    'i' would end up being at index 4. Therefore, ALL of the "prefix parts"(i.e. [0..3] from both array) MUST be exactly the same and in the same order.

    Since we see that is NOT true, then we can immediately return 0.

    Why?

    Because if "prefix parts" [0..3] of boths arrays are NOT the same and in
    the same order, then they CERTAINLY will not be able to be the same and in
    exact same order if we add the next elements.

    That is:

            nums = [4, 7, 2]
            targ = [4, 7, 9]
                    0  1  2

        // They're NOT the same. What about if we add another element?



            nums = [4, 7, 2, 7]
            targ = [4, 7, 9, 7]
                    0  1  2  3

        // STILL not the same! And never will be no matter how much
        // we extend the "prefix part" of each array.



    Okay, but how do we actually check whether the suffixes are the same?

    We don't need to sort each suffix of nums and then compare, that would be
    too slow. It's enough that the "frequency map" of the suffix part in nums
    and suffix part in target are the same.

    But if we compare N suffixes with N elements, that would be O(N^2), that is
    unacceptable.

    So how do we overcome this?

    We will find whether some suffix from [x..N-1] is having the exact same
    "frequency map" while we're trying to find our 'i', i.e. our leftmost index
    from which all the elements in target are in NON-INCREASGIN order.

    How are we going to do that?

    Since we're moving our 'i' pointer backwards, starting from N-1, we're
    going to keep a frequency map called "freq". Inside the "freq" each time
    some target[i] element appears, we're going to INCREMENT the frequency for
    that element in freq. Similarly, each time some nums[i] elements appears,
    we're now going to DECREMENT the frequency for that element.

    Frequencies ARE allowed to be negative. This is unusual, but its handy
    here.

    Anytime a frequency of some number gets to 0, we're going to REMOVE it from
    the map. This is VERY important.

    We're certain that the frequency maps of both suffix parts are the same IF
    AND ONLY IF frequency map is EMPTY, because we know that each elements from
    nums has "canceled" each element from target and vice versa.

    We will "mark" possible_from[i] if frequency map was empty at that point
    while going backwards.

    Now we simply check whether the "prefix parts" are the same and if its
    possible_from[i].

    If it is: ++result;

    Now we extend each prefix part, but if they're NOT the same we IMMEDIATELY
    stop. Remember how we've realized that if prefix parts are not the same,
    then extending them CERTAINLY won't fix that?

    That is also used here.

    As long as extending of the "prefix parts" is possible we also check the
    next 'i' until we get to N.

*/

/* Time  Beats: 30.44% */
/* Space Beats: 89.96% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countSuffix(vector<int>& nums, vector<int>& target)
    {
        const int N = nums.size();
        int result = 0;

        unordered_map<int,int> freq;
        int diff_sum = 0;

        vector<int> possible_from(N, false);

        int i = N-1;
        while (i >= 0)
        {
            ++freq[target[i]];
            --freq[nums[i]];

            if (freq[target[i]] == 0) freq.erase(target[i]);
            if (freq[nums[i]]   == 0) freq.erase(nums[i]);

            if (freq.empty())
                possible_from[i] = true;

            if (i > 0 && target[i-1] < target[i])
                break;
            
            // Decrement
            --i;
        }

        /* Check whether the smallest "prefix parts" are the same */
        for (int j = 0; j < i; j++)
        {
            if (nums[j] != target[j])
                return 0;
        }

        /* As long as "prefix parts" are the same */
        for (int suffix_start = max(0, i); suffix_start < N; suffix_start++)
        {
            if (possible_from[suffix_start])
                ++result;

            /* Try extending "prefix parts" */
            if (nums[suffix_start] != target[suffix_start])
                break;
        }

        return result;
    }
};
