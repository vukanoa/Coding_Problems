#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2779) Maximum Beauty of an Array After Applying Operation
    =========================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums and a non-negative integer k.

    In one operation, you can do the following:

    Choose an index i that hasn't been chosen before from the range [0,
    nums.length - 1]. Replace nums[i] with any integer from the range:

        [nums[i] - k, nums[i] + k].

    The beauty of the array is the length of the longest subsequence consisting
    of equal elements.

    Return the maximum possible beauty of the array nums after applying the
    operation any number of times.

    A subsequence of an array is a new array generated from the original array
    by deleting some elements (possibly none) without changing the order of the
    remaining elements.

    =====
    Note: Note that you can apply the operation to each index only once.
    =====

    ======================================================
    FUNCTION: int maximumBeauty(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,6,1,2], k = 2
    Output: 3
    Explanation: In this example, we apply the following operations:
    - Choose index 1, replace it with 4 (from range [4,8]), nums = [4,4,1,2].
    - Choose index 3, replace it with 4 (from range [0,4]), nums = [4,4,1,4].
    After the applied operations, the beauty of the array nums is 3
    (subsequence consisting of indices 0, 1, and 3). It can be proven that 3 is
    the maximum possible length we can achieve.


    --- Example 2 ---
    Input: nums = [1,1,1,1], k = 10
    Output: 4
    Explanation: In this example we don't have to apply any operations.
    The beauty of the array nums is 4 (whole array).


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i], k <= 10^5

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Solution to this problem is most certainly much easier than you would
    imagine, however, it's not that easy to come up with it. It's not inuitive.

    After reading the problem, one of the first thing you would probably try is
    for each element in vector "nums", try to put every number from:

        [nums[i] - k, nums[i] + k]

    in a "frequency counter" HashMap.

    Example:
        nums = [1,2,3],  k = 2

        elem = 1:   [-1, 3]
            umap[-1]++;
            umap[0]++;
            umap[1]++;
            umap[2]++;
            umap[3]++;

        elem = 2:   [0, 4]
            umap[0]++;
            umap[1]++;
            umap[2]++;
            umap[3]++;
            umap[4]++;

        elem = 3:   [1, 5]
            umap[1]++;
            umap[2]++;
            umap[3]++;
            umap[4]++;
            umap[5]++;

    And then take the one element that occurs most amount of time and return
    its frequency as a result.

    This works, but is very inefficient.
    Why?

    Because in the Constraints of this problem it is written:

        1 <= nums.length <= 10^5
        0 <= nums[i], k <= 10^5

    Which means that for every element(that is O(N)) we need to go through all
    the elements in the range. But the range for each element is 2*k.

    Why?
    Because in range [nums[i] - k, num[i] + k] there are 2*k different elements

    That means that for every element we would have to scan the entire 2*k
    range, but we also know that in the worst case:

        k == nums.size() == 10^5

    Which means that 2*k is 2*N or just O(N). That further means the overall
    Time Complexity would be O(N * N) which is O(N^2).

    You would get a TLE(Time Limit Exceeded) on LeetCode.


    So how can we optimize this?
    Upon reviewing this Solution you will quickly find out that it's impossible
    to improve this Solution and that you have to come up with a completely
    different idea.

    So what is the idea?
    Here is the part that makes this Solution difficult to come up with, even
    if the Solution itself is incredibly easy.

    When reading a problem, they told us this piece of information:

        "The beauty of the array is the length of the longest SUBSEQUENCE
         consisting of equal elements."

    They've also told us what is SUBSEQUNCE:

        "A subsequence of an array is a new array generated from the original
         array by deleting some elements (possibly none) without changing the
         order of the remaining elements."

    This piece of information is probably what drove you away from the correct
    approach.

    In "Subsequence" kind-of problems, we must NOT sort or re-order in any way,
    shape or form.

    However, that is not ALWAYS true. That is true "only" for most subsequence
    problems.

    In this Problem, as you've tried yourself with a Brute-Force, you could
    see that the order is not really important, right?

    We only cared about the number that appear in most ranges. Even though the
    "longest subsequence" is what we were looking for, we didn't tweak our
    approach to suit general subsequence problems in any way.

    That should tell you that the order does NOT matter. This is very
    un-intuitive for "subsequence" problems, but bear with me.

    Consider this example:
        nums = [4, 1, 6]     k = 2,    Let's draw them on the X-axis:
                |  |  | 
----------------   |  |
|  -----------------  | 
|  |   ----------------
|  |   |
|  |   v
|  |   6:                   <===========>
|  - > 1:    <===========>
-----> 4:             <===========>
             |--|--X--|--|--X--|--X--|--|--|
            -1  0  1  2  3  4  5  6  7  8  9


    However, if we re-ordered the input like this: 

        nums = [1, 4, 6]     k = 2

    And draw it again:
       6:                   <===========>
       4:             <===========>
       1:    <===========>
             |--|--X--|--|--X--|--X--|--|--|
            -1  0  1  2  3  4  5  6  7  8  9

    Would anything change?

    We'll the order did change of the drawing, but the answer would still be
    the same. There are no more than 2 numbers, in any range, that appear more
    than twice, thus that is the answer.

    However, when you look at this sorted "picture", does anything comes to
    mind?

    If you have a FIXED part to the left and FIXED part to the right and
    therefore that range itself is FIXED, and it's FIXED for all the other
    elements as well, does anything comes to mind now?

    Yes, it's Sliding Window!

    Now the problem becomes trivial. It's the most fundamental Sliding Window
    approach.

    (If you aren't familiar with "Sliding Window" technique, check-out problems
     such as: 
        1. Best Time to Buy and Sell a Stock
        2. Longest Substring Without Repeating Characters
        3. Longest Repeating Character Replacement       
    )

    If you are indeed familiar with this technique, the code down below is
    trivial and self-explanatory. The most fundamental Sliding Window problem.

*/

/* Time  Beats: 58.31% */
/* Space Beats: 94.06% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k)
    {
        const int N = nums.size();        
        int result = 1;

        /* Sort */
        sort(nums.begin(), nums.end()); // O(n * logn)

        /* Sliding Window */
        int left  = 0;
        int right = 1;
        while (right < N)
        {
            while (left < right && nums[left] + k < nums[right] - k)
                left++;
                
            result = max(result, right - left + 1);

            // Increment
            right++;
        }

        return result;
    }
};
