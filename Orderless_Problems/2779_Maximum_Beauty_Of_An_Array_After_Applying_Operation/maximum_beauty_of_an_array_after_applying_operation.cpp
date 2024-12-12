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




/*
    ------------
    --- IDEA ---
    ------------

    This one is even more optimal than the above O(N * logN) Solution.
    This one runs in only O(N) Time.

    The idea is using "Prefix Sum" on ranges. This is something you must know
    beforehand in order to come up with a Solution that uses it.

    So, what is the idea?

    When you have N ranges, in an unsorted, way, how can we find out what is
    the length of one or more numbers that are overlapping in most amount of
    difference ranges?

    Let's draw it:
        nums = [4,6,1,2]
                0 1 2 3 // indices


        2:       <===========>
        1:    <===========>
        6:                   <===========>
        4:             <===========>
              |--|--X--|--|--X--|--X--|--|--|
             -1  0  1  2  3  4  5  6  7  8  9


    How can we determine that?

    First thing that we must notice - All the elements in "nums" are >= 0.
    That means that no matter the value of k, if the left range surpasses the
    zero(or is at zero itself), we can consider that as an overlap.

    Why?
    Consider left ranges of this Input:
        nums = [0, 1, 2, 3, 7]    k = 4

        7:                          <LLLLLLLLLLL_RRRRRRRRRRR>
        3:             <LLLLLLLLLLL_RRRRRRRRRRR>
        2:          <LLLLLLLLLLL_RRRRRRRRRRR>
        1:       <LLLLLLLLLLL_RRRRRRRRRRR>
        0:    <LLLLLLLLLLL_RRRRRRRRRRR>
              |--|--|--|--X--X--X--X--|--|--|--X
             -4 -3 -2 -1  0  1  2  3  4  5  6  7


    This is not obvious at a first glance, but read this carefully:

    Since any element in "nums" is 0 or greater than 0, any "left range" that
    surpasses zero(goes negative) or ends at zero are going to be considred
    overlapping.

    Read that again.

    Why is it like that?
    Consider this:

        3:             <LLLLLLLLLLL_RRRRRRRRRRR>
        0:    <LLLLLLLLLLL_RRRRRRRRRRR>
              |--|--|--|--X--X--X--X--|--|--|--X
             -4 -3 -2 -1  0  1  2  3  4  5  6  7

    Since Xs are place only >= 0, any range to the left overlaps. Think about
    it:

        Starting at X=0, Left range is [-4, 0]
        Starting at X=3, Left range is [-1, 3]

    We do NOT care which NUMBERS are overlapping, we ONLY care IF ANY number
    from the left portion of these two ranges overlaps or not.

    Read it again. This is the crux.

    We care about "IF ANY number overlaps" because that is what we are asked
    to find out and return.
    We are NOT asked to return THE NUMBER that overlaps in most of these
    ranges, we are aksed to return BIGGEST FREQUENCY of ANY number in these
    ranges.

    For example if some number 4 appears in 7 out of 9 ranges, we need to
    return 7 and NOT 4.

    We do NOT care what is that number, we care about its FREQUENCY!

    Therefore, because all elements in "nums" are >= 0, if any "left part" of
    any range ends at zero or suprasses zero, we are counting as if its end is
    at zero. All of such ranges will be counted as if they end at 0.


    Let's continue with the rest of this approach, but this was VERY important
    to understand.

    Let's draw ranges again:

        nums = [4,6,1,2]
                0 1 2 3 // indices


        2:       <===========>
        1:    <===========>
        6:                   <===========>
        4:             <===========>
              |--|--X--|--|--X--|--X--|--|--|
             -1  0  1  2  3  4  5  6  7  8  9

    Instead of sorting and then using a "Sliding Window" technique and thus
    have a Time Complexity of O(n), we can do something more optimal.

    We are going to create a new vector "prefix_sum" that is going to be of
    size:
        2 * (10^5 + 1)

    Why this size?

    10^5 is the  maximum possible value for k.
    10^5 is also maximum possible value for nums[i]

    Thus the rightmost possible range would be: 10^5 + 10^5 which is 2 * 10^5
    However, because indexing starts at 0, we need to 1.

    But, that would be: 2 * 10^5 + 1, which wouldn't include the left part of
    this maximum possible range.

    10^5 is the maximum possible value for k.
    0    is the minimum possible value for nums[i]

    Thus, the leftmost possible range would be: 0 - 10^5 = -10^5
    But that would mean the total range is:

        [-10^5 ... 2*10^5]

    But, didn't we explain up above that we do NOT need part of the range that
    is LESS than 0?

    Therefore, the range will:
        begin at index: 0 and
        end   at index: 2 * (10^5 + 1)


    Let's continue with prefix_sum approach.

    We begin at index 0 where all the ranges that end at 0 or surpass the zero
    to the left(that are going to negative side) and the all we do is this:

        If any range BEGINS at current index, we include those(there can be
        more than one, obviously).

        However, if the current index is ONE index AFTER the upper bound of
        some range, then we subtract one because numbers from that range are
        no longer overlapping with the current index.

    This is a VERY powerful technique, but you need to spend time thinking
    about it until it becomes natural.

    Let's dry run our example:

        nums = [4,6,1,2]
                0 1 2 3 // indices


        2:       <===========>
        1:    <===========>
        6:                   <===========>
        4:             <===========>
              |--|--X--|--|--X--|--X--|--|--|
             -1  0  1  2  3  4  5  6  7  8  9



        2:      +1          -1
        1:      +1       -1
        6:                  +1          -1
        4:            +1          -1

                [2  0  1  0  0 -1  0 -1  0 -1   0                ...  0]
                 0  1  2  3  4  5  6  7  8  9  10 ...           2*(10^5 + 1)

        (Remember that negative ranges are considred to end at zero)

        i=0
        res=2  // current max

        i=1
        res=2

        i=2
        res=3  // current max

        i=3
        res=3

        i=4
        res=3

        i=5
        res=2

        i=6
        res=2

        i=7
        res=1

        i=8
        res=1

        i=9
        res=0

        i=10
        res=0

        ... // The result won't change any more because no more ranges begin or
            // end at any further range untli the end.


    Final result = 3

    Try reading this last part and look at this picture and at one point it
    will click, I promise.

    Once it clicks, now you have a new tool for your toolbox!

*/

/* Time  Beats: 28.70% */
/* Space Beats:  5.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Prefix_Sum {
public:
    int maximumBeauty(vector<int>& nums, int k)
    {
        const int n = nums.size();
        vector<int> prefix_sum(2 * (1e5 + 1), 0);

        for (int i = 0; i < n; i++)
        {
            int start_range = nums[i] - k;
            int end_range   = nums[i] + k;

            if (start_range <= 0) // Because:  0 <= nums[i], k < 10^5
                prefix_sum[0]++;
            else
                prefix_sum[start_range]++;

            // Because at this index current range NO LONGER is able to be
            // counted. The range ends
            prefix_sum[end_range + 1]--;
        }

        int max_beauty = 0;

        for (int i = 1; i < prefix_sum.size(); i++)
        {
            prefix_sum[i] += prefix_sum[i - 1];
            max_beauty = max(max_beauty, prefix_sum[i]);
        }

        return max_beauty;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    This is an additional Optimization, but on the above "Prefix Sum" approach.

    Instead of allocating (2 *(10^5 + 1)) elements and going through it, we
    know that there is no point in iterating through elements BEFORE the
    minimum element and AFTER the maximum element.

    Let's look at the previous example:

        nums = [4,6,1,2]
                0 1 2 3 // indices


        2:       <===========>
        1:    <===========>
        6:                   <===========>
        4:             <===========>
              |--|--X--|--|--X--|--X--|--|--|
             -1  0  1  2  3  4  5  6  7  8  9



        2:      +1          -1
        1:      +1       -1
        6:                  +1          -1
        4:            +1          -1

                [2  0  1  0  0 -1  0 -1  0 -1   0                ...  0]
                 0  1  2  3  4  5  6  7  8  9  10 ...           2*(10^5 + 1)

        (Remember that negative ranges are considred to end at zero)

        Since minimum element is 1, we can use the same trick we used to NOT
        write negative values.

        Why?
        Because, as we've said for the zero, we do NOT care WHICH NUMBER is
        repeating in most amount of different ranges, rather we only care about
        the AMOUNT OF RANGES in which ANY number is repeating.

        Thus, as we've already seen:

            nums = [0, 1, 2, 3, 7]    k = 4

            7:                          <LLLLLLLLLLL_RRRRRRRRRRR>
            3:             <LLLLLLLLLLL_RRRRRRRRRRR>
            2:          <LLLLLLLLLLL_RRRRRRRRRRR>
            1:       <LLLLLLLLLLL_RRRRRRRRRRR>
            0:    <LLLLLLLLLLL_RRRRRRRRRRR>
                  |--|--|--|--X--X--X--X--|--|--|--X
                 -4 -3 -2 -1  0  1  2  3  4  5  6  7

        If ANY range goes NEGATIVE(surpasses zero), we will count as if that
        range ends at 0. We don't care which NUMBER they overlap on, we only
        care that they overlap.

        (This is confusing if you are reading it for the first time, but bear
        with me)


        However, we don't need to "cut off" at 0, we can do THE SAME thing, but
        "cut off" at minimum element in "nums".

        Why?
        Since we know there AREN'T any element to the left of that minimum
        element, we also know that any range that surpasses it can be counted
        as if it ends at that minimum element. Absolutely equivalent "trick" as
        the one we've used for the zero.

        However, this way we can improve Space efficiency.

        We could also do the same thing, but for the MAXIMUM element.
        Simply look at the our first example:

        nums = [4,6,1,2]
                0 1 2 3 // indices


        2:       <===========>
        1:    <===========>
        6:                   <===========>
        4:             <===========>
              |--|--X--|--|--X--|--X--|--|--|
             -1  0  1  2  3  4  5  6  7  8  9



        2:      +1          -1
        1:      +1       -1
        6:                  +1          -1
        4:            +1          -1

                [2  0  1  0  0 -1  0 -1  0 -1   0                ...  0]
                 0  1  2  3  4  5  6  7  8  9  10 ...           2*(10^5 + 1)


        After the maximum value "6", the total result can only DECREASE, which
        means that we ALREADY have the "maximum beauty". We don't need to
        iterate through all those 0s all the way up to index: 2 * (10^5 + 1).


    This way we've reduced Space Complexity from O(n) down to O(1).

*/

/* Time  Beats: 88.83% */
/* Space Beats: 39.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Prefix_Sum_Another {
public:
    int maximumBeauty(vector<int>& nums, int k)
    {
        int min_elem = *min_element(nums.begin(), nums.end()) - k;
        int max_elem = *max_element(nums.begin(), nums.end()) + k;

        const int ELEMENTS_IN_RANGE = max_elem - min_elem + 1;

        vector<int> prefix_sum(ELEMENTS_IN_RANGE + 1, 0);

        for (int num : nums)
        {
            prefix_sum[num - k - min_elem]++;
            prefix_sum[num + k + 1 - min_elem]--;
        }

        int max_beauty = 0;
        int result = 0;

        for (int i = 0; i < ELEMENTS_IN_RANGE; ++i)
        {
            max_beauty += prefix_sum[i];
            result = max(result, max_beauty);
        }

        return result;
    }
};
