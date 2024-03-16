#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    2542) Maximum Subsequence Score
    ===============================

    ============
    Description:
    ============

    You are given two 0-indexed integer arrays nums1 and nums2 of equal length
    n and a positive integer k. You must choose a subsequence of indices from
    nums1 of length k.

    For chosen indices i0, i1, ..., ik - 1, your score is defined as:

        The sum of the selected elements from nums1 multiplied with the minimum
        of the selected elements from nums2.  It can defined simply as:
        (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] ,
        nums2[i1], ... ,nums2[ik - 1]).

    Return the maximum possible score.

    A subsequence of indices of an array is a set that can be derived from the
    set {0, 1, ..., n-1} by deleting some or no elements.

    ============================================================================
    FUNCTION: long long maxScore(vector<int>& nums1, vector<int>& nums2, int k);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
    Output: 12
    Explanation:
    The four possible subsequence scores are:
    - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
    - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6.
    - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12.
    - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
    Therefore, we return the max score, which is 12.


    --- Example 2 ---
    Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
    Output: 30
    Explanation:
    Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the
    maximum possible score.


    *** Constraints ***
    n == nums1.length == nums2.length
    1 <= n <= 10^5
    0 <= nums1[i], nums2[j] <= 10^5
    1 <= k <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    This seems as a DP problem, but it's not.

    ===========================================
    == In a nutsheel, this is the algorithm: ==
    ===========================================

    1. Push all nums1 and nums2 elements in pairs in vector<pair<int, int>>.

    2. Sort that vector by values of nums2.
         - We have two options:
             a) push elements in vector of pairs in order {nums2, nums1} and
                then just use a basic sort like this:
                    sort(pairs.begin(), pairs.end())

             b) push elements in vecor of pairs in a "normal" order, i.e.
                {nums1, nums}, but then use a "comparator" for a sort to
                make sure elements are sorted by nums2 and not by nums1.

    3. Push elements(nums1s) in min_heap

    4. Keep the running total of nums1s so far.

    5. Once min_heap.size() becomes > k, pop from the heap.

    6. If the min_heap.size() == k, then:
         result = std::max(result, n1_sum * curr_nums2);




    Example where it seems impossible to work, but actually still works with
    this code:

    nums1 = [2, 7, 3, 1]
    nums2 = {7, 6, 5, 4]
    k = 3

    Once we're on the last one, at that point min_heap.size() becomes greater
    than k and then we pop the minimum element form the nums1, i.e. the one
    on the top of the min_heap(that's why we're using the min_heap).

    So once we pop the "1" from the heap, that means we cannot use 4 as n2,
    right?

    However, this still seems to work.
    Why?

    Because it is guaranteed that if it happens that the minimum element in
    heap is the one that has the the least value up until this point form the
    nums2, we are guaranteed not to get the new maximum.

    In other words, it would be THE SAME product as in the previous iteration.

        1. sum = 2 + 7 + 3 = 12
           min_heap = {2, 7, 3}  // Where 2 is the TOP of the min_heap(size 3)

           result = std::max(0, 12 * 5) = 60


        2. sum = 2 + 7 + 3 + 1
           min_heap = {1, 2, 7, 3} // min_heap.size() > k --> we must pop

           min_heap.pop(); // We will pop '1' and 1's corresponding nums2 elem.
                              is the lowest multiplication value(4).

           min_heap = {2, 7, 3}; // As in the previous iteration

           However, since 4(multiplications value from nums2) isn't bound to
           any of the remaining elements in min_heap, then we'd have this:

               result = std::max(60, 12 * 4) = std::max(60, 48) = 60

           As you can see - NOTHING will change since we've done that same
           calculation in the previous iteratation, however we've used a
           GREATER "multiplication value". We've used 5, since we've sorted
           the vector of pairs and 5 was in the order.

           Now if the new lowest "multiplication value" is NOT BOUND to any
           element since we've popped it, then we are SURE that it won't change
           our result for the worse.


    Consider this example again.

    Once we get to index=2, we'll have:
        n1_sum = 7
        n2_min = 5

    So it's:
        7 * 5 = 35

    Now we increment index to 3 and we add nums[3] to n1_sum.
        n1_sum = 8

    However since now min_heap.size() is 4, which is > k=3, then we have to
    pop one element from the min_heap and subtract that popped value from
    n1_sum.

    In this case we're going to pop 1, so n1_sum becomes 7 again.

    However, since now min_heap.size() is equal to k, we, again, calculate
    the maximum:
        result = std::max(result, n1_sum * n2);

    n2 here is 4, which is the minimum from nums2 up to this point in the
    sorted array, however we aren't allowed to use this.

    However, we're sure that it won't be greater than the previous result
    because the previous result had THE SAME n1_sum, but a GREATER n2 value.
    We used to multiply it by n2=5 and now we're trying to multiply it by 4.

    That's why we don't have to worry about that and this still works even if
    it seems that it should not.

*/

/* Time  Beats: 78.95% */
/* Space Beats: 65.97% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
private:
    struct sort_comparator
    {
        bool operator()(const std::pair<int, int>& left, const std::pair<int, int>& right)
        {
            return left.second > right.second;
        }
    };

public:
    long long maxScore(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        std::vector<std::pair<int, int>> pairs;

        for (int i = 0; i < nums1.size(); i++)
            pairs.push_back( {nums1[i], nums2[i]} );

        std::sort(pairs.begin(), pairs.end(), sort_comparator());

        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
        long long n1_sum = 0;
        long long result = 0;

        for (auto& entry : pairs)
        {
            int n1 = entry.first;
            int n2 = entry.second;

            n1_sum += n1;
            min_heap.push(n1);

            if (min_heap.size() > k)
            {
                n1_sum -= min_heap.top();
                min_heap.pop();
            }

            if (min_heap.size() == k)
                result = std::max(result, n1_sum * n2);
        }

        return result;
    }
};
