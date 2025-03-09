/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3478) Choose K Elements With Maximum Sum
    ========================================

    ============
    Description:
    ============

    You are given two integer arrays, nums1 and nums2, both of length n, along
    with a positive integer k.

    For each index i from 0 to n - 1, perform the following:

        + Find all indices j where nums1[j] is less than nums1[i].

        + Choose at most k values of nums2[j] at these indices to maximize the
          total sum.

    Return an array answer of size n, where answer[i] represents the result for
    the corresponding index i.

    ======================================================================================
    FUNCTION: vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
    Output: [80,30,0,80,50]
    Explanation:
        For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
        For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
        For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
        For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
        For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.


    --- Example 2 ---
    Input: nums1 = [2,2,2,2], nums2 = [3,1,2,3], k = 1
    Output: [0,0,0,0]
    Explanation:
    Since all elements in nums1 are equal, no indices satisfy the condition nums1[j] < nums1[i] for any i, resulting in 0 for all positions.


    *** Constraints ***
    n == nums1.length == nums2.length
    1 <= n <= 10^5
    1 <= nums1[i], nums2[i] <= 10^6
    1 <= k <= n

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------


    *****************
    *** INTUITION ***
    *****************

    This one requires quite a bit of explanation, but it's really worth
    understanding.

    First, you have to understand what is that you're being asked to do.
    Then, try to think of a Brute-Force.


    Brute-Force:

    For value at i=0, find all values inside nums1 and take all of those
    indices and then take those indices and put them into a Min-Heap of size k.

    Each time there is more than k elements inside a Heap, pop the smallest
    one. That way we make sure to always sum only top k elements.

    Now we need the sum of those k elements present in the Min-Heap. However,
    we don't need to pop them at the end one-by-one and them determine the
    total sum, instead we can keep track of the sum as we are constructing the
    Min-Heap.

    Example:
        nums2 = [30, 40, 70, 20, 10, 30],   k = 3
                  0   1   2   3   4   5

    Let's say we want to determine top k=3 elements from this array.

    Instead of pushing one-by-one and popping after it exceeds k and only then
    popping reamining top k elements while adding all those k, we can add each
    element before we push it and subtract each one we pop once it exceeds k.

    Take a look at this and it'll be clear:
    (Min-Heap as a data-structure only ensures the top one is the smallest, the
     rest of the elements are in no particular order)

        nums2 = [30, 40, 15, 20, 80, 50],   k = 3
                  0   1   2   3   4   5


        i = 0)
            min_heap = {30}             // size = 1
            // *** ADD TO SUM ***
            curr_sum = 30

        i = 1)
            min_heap = {30, 40}         // size = 2
            // *** ADD TO SUM ***
            curr_sum = 70

        i = 2)
            min_heap = {15, 40, 30}     // size = 3
            // *** ADD TO SUM ***
            curr_sum = 85

        i = 3)
            min_heap = {15, 30, 40, 20} // size = 4, which is greater than k=3
            // *** ADD TO SUM ***
            curr_sum = 105
            // *** POP ***
            // *** SUBTRACT THE SMALLEST FROM SUM ***
            min_heap = {20, 40, 30}     // size = 3
            curr_sum = 90

        i = 4)
            min_heap = {20, 40, 30, 80} // size = 4, which is greater than k=3
            // *** ADD TO SUM ***
            curr_sum = 170
            // *** POP ***
            // *** SUBTRACT THE SMALLEST FROM SUM ***
            min_heap = {30, 40, 80}     // size = 3
            curr_sum = 150

        i = 5)
            min_heap = {30, 40, 80, 50} // size = 4, which is greater than k=3
            // *** ADD TO SUM ***
            curr_sum = 200
            min_heap = {40, 80, 50}     // size = 3
            curr_sum = 170


    This way we know that the top k=3 elements' sum is 170 without needing to
    pop last k remaining elements to determine that.

    Once this is out of the way, let's determine the Time Complexity of this
    Brute-Force:

        To obtain all indices for the current value in nums1 we need O(N) Time.
        Since we're doing this for each value in nums1, and there are N of them
        that means the Time Complexity of this part is O(N^2).

        Now you have to go through all those obtained indices and get the sum
        of the top-k elements, which takes O(N * logk)

        Since that is done O(N) times, total Time Complexity would be:
        O(N^2 * logk)

        Since at the worst case: k == N, it's O(N^2 * logN)


    Now, let's ask ourselves--Is there any repeated work here?
    If there is, then we certainly can reduce Time Complexity.


    Let's consider this:
        nums1 = [ 4,  2,  1,  5,  3],
        nums2 = [10, 20, 30, 40, 50], k = 2


    In the Brute Force way, we obtain all indices of elements that are less
    than 4, and at the end we do the same but for indices of elements that are
    less than 5.

    So is there any repeated work?

    Well, what if instead of 4 and 5, it was 4 and 57, in that case, even
    though there is repeated work of obtaining indices of elements that are
    less than 4 and INCLUDING 4, the remaining elements need to be obtained
    manually it seems.

    But that's because we had a big gap, what if we sort it?
    But if we sort it, we'll lose indices of each value in nums1, therefore we
    need to construct pairs of {value, original_idx}.

        nums1 = [ 4,  2,  1,  5,  3],
        nums2 = [10, 20, 30, 40, 50], k = 2

        sorted_nums1 = [ {1,2}, {2,1}, {3,4}, {4,0}, {5,3} ]
                           0      1      2      3      4

    Now even if instead of 5 we had 57, obtaining other indices wouldn't
    require going through X additional elements, instead we know that there is
    ONLY ONE indice that we need to include for 57, which is 0(index of 4).

    So for value 5, need to use all the indices that 4 used + additional one
    which is 4's index itself.

    That way if we group them and sort them, we can process them one-by-one and
    thus reduce the Time Complexity by a factor of N, which leaves us with:

        O(N * logn)


    I'll simulate our "Example 1" and I'm sure you'll get it.


    ****************
    *** APPROACH ***
    ****************

    1) Create pairs of {value, original_index} from nums1 and sort it.

        sorted_nums1 = [ {1,2}, {2,1}, {3,4}, {4,0}, {5,3} ]
                           0      1      2      3      4


    2) Add nums2 element of the first smaller element that the current one.
       (This is the optimization. For our value 5, we add index of element 4
        and push nums2[index of element 4]. Why 4? Because 4 is the last value
        that we DIDN'T include in out Min-Heap)

       Add to the "sum".
       If it exceeds k, pop minimum one and subtract it from the "sum".

       Store "sum" at result[curr_original_index].

    ******************
    *** SIMULATION ***
    ******************


        nums1 = [ 4,  2,  1,  5,  3],
        nums2 = [10, 20, 30, 40, 50], k = 2

        sorted_nums1 = [ {1,2}, {2,1}, {3,4}, {4,0}, {5,3} ]
                           0      1      2      3      4


        i = 0)  // original_index = 2
            min_heap = {}
            sum = 0;

            result[original_index] = 0; // sum == 0



        i = 1)  // original_index = 1
            min_heap = {30}
            sum = 30

            result[original_index] = 30; // sum == 30



        i = 2)  // original_index = 4
            min_heap = {20, 30}
            sum = 50

            result[original_index] = 50; // sum == 50


        i = 3)  // original_index = 0
            min_heap = {20, 30, 50}
            sum = 100

            *** min_heap.size() is GREATER than k ***
            // subract smallest from "sum"
            // pop

            min_heap = {30, 50}
            sum = 80

            result[original_index] = 80; // sum == 80


        i = 4)  // original_index = 3
            min_heap = {10, 50, 30}
            sum = 90

            *** min_heap.size() is GREATER than k ***
            // subract smallest from "sum"
            // pop

            min_heap = {30, 50}
            sum = 80

            result[original_index] = 80; // sum == 80


    And we just return "result".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.50% */

/* Time  Complexity: O(N * logN + N * logk) ---> O(N * logN) */
/* Space Complexity: O(N)                                    */
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k)
    {
        const int N = nums1.size();
        vector<long long> result(N, 0);

        vector<pair<int, int>> val_and_orig_idx;
        for (int i = 0; i < N; i++)
            val_and_orig_idx.push_back( {nums1[i], i} );

        /* Sort */
        sort(val_and_orig_idx.begin(), val_and_orig_idx.end());

        // Min-Heap to track largest 'k' elements from nums2
        priority_queue<int, vector<int>, greater<int>> min_heap;

        long long sum = 0;
        int j = 0; // Pointer to track valid elements in heap

        for (int i = 0; i < N; i++)
        {
            // Original index of nums1[i]
            int curr_orig_idx = val_and_orig_idx[i].second;

            // Add valid elements from nums2 to min-heap
            while (j < i)
            {
                int prev_orig_idx = val_and_orig_idx[j].second;

                // Stop if the current element in nums1 is not strictly greater
                if (val_and_orig_idx[i].first <= val_and_orig_idx[j].first)
                    break;

                min_heap.push(nums2[prev_orig_idx]);
                sum += nums2[prev_orig_idx];

                // If heap exceeds size k, remove the smallest element
                if (min_heap.size() > k)
                {
                    sum -= min_heap.top();
                    min_heap.pop();
                }

                // Increment
                j++;
            }

            result[curr_orig_idx] = sum; // Store the sum for the current index
        }

        return result;
    }
};
