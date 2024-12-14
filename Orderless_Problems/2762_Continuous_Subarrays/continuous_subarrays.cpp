/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2762) Continuous Subarrays
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. A subarray of nums is called
   continuous if:

        + Let i, i + 1, ..., j be the indices in the subarray. Then, for each
          pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.

    Return the total number of continuous subarrays.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ===========================================================
    FUNCTION: long long continuousSubarrays(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,4,2,4]
    Output: 8
    Explanation:
    Continuous subarray of size 1: [5], [4], [2], [4].
    Continuous subarray of size 2: [5,4], [4,2], [2,4].
    Continuous subarray of size 3: [4,2,4].
    Thereare no subarrys of size 4.
    Total continuous subarrays = 4 + 3 + 1 = 8.
    It can be shown that there are no more continuous subarrays.

    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: 6
    Explanation:
    Continuous subarray of size 1: [1], [2], [3].
    Continuous subarray of size 2: [1,2], [2,3].
    Continuous subarray of size 3: [1,2,3].
    Total continuous subarrays = 3 + 2 + 1 = 6.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a "Sliding Window" approach, but it has one VERY important "trick"
    that you must now, otherwise you wouldn't even try "Sliding Window". You
    wouldn't think basic "Sliding Window" can help us with this.

    Let's say that, somehow, you had all the continuous subarrays from [L, R-1]
    (Ignore difference of 2 between each pair for now)

                0 1 2 3 4 5 6 7 8 9
        nums = [7,5,6,7,8,9,4,5,6,7]
                L       R

    Imagine that we had ALL the continuous non-empty subarrays from [L, R-1],
    inclusively. What would they be? And how much of them are there?

        size 1: {7}, {5}, {6}, {7}
        size 2: {7,5}, {5,6}, {6,7}
        size 3: {7,5,6}, {5,6,7}
        size 4: {7,5,6,7}

        So there are: 4 + 3 + 2 + 1 = 10

    But now consider this, this is the absolute CRUX of this "trick":

    If we now want to consider the element at index R as well, how many, would
    there be?

        size 1: {7}, {5}, {6}, {7}, {8}
        size 2: {7,5}, {5,6}, {6,7}, {7,8}
        size 3: {7,5,6}, {5,6,7}, {6,7,8}
        size 4: {7,5,6,7}, {5,6,7,8}
        size 5: {7,5,6,7,8}

        That's a total of: 5 + 4 + 3 + 2 + 1 = 15

    Hold on a second! Once R was less by one(i.e. 3), there where 10 subarrays,
    and now there are 15.

    So what is the difference? How many NEW ONES would we have if we extended
    previous window?
    We would have 5 more than before.

    Now consider this mindblowing fact:

        Earlier:
            L was 0
            R was 3

            and we had 10


        Now:
            L is 0
            R is 4

            and we have 15

        The difference is 5.


    Therefore if we wanted to add current element and then add ONLY subarrays
    that we have NOT counted in previous window(i.e. only subarrays that have
    this new element in it), ALL we have to do is this:

        R - L + 1

    That's the difference. That's how many new subarrays are there in total.
    This would work even if L is, for example, 3 and R is 9. It always works.

    This is VERY unintuitive to me and if you didn't see this before, it is
    almost impossible to come up with this Solution.

*/

/* Time  Beats: 79.04% */
/* Space Beats: 79.83% */

/*
    Time  Complexity: O(n)

    O(n * logk) ~ O(n)

    The outer loop iterates through the array once with the right pointer,
    taking O(n) operations. For each element, we perform map operations
    (insertion, deletion, finding min/max) which take O(logk) time, where k is
    the size of the map. Since we maintain a window where the max - min <= 2,
    the size of the sorted map k is bounded by 3 (as elements can only differ
    by 0, 1, or 2). Therefore, logk is effectively constant, making the overall
    time complexity O(n).

    (This is important to understand!)

*/
/*
    Space Complexity: O(n)

    The sorted map stores elements within the current window. Since the
    difference between any two elements in a valid window cannot exceed 2, the
    maximum number of unique elements (k) possible in the map at any time is 3.
    Therefore, the space complexity is constant, O(1)

*/
class Solution_Sliding_Window_TreeMap {
public:
    long long continuousSubarrays(vector<int>& nums)
    {
        const int n = nums.size();
        long long count = 0; // Total count of valid subarrays

        // Map to maintain sorted frequency map of current window
        map<int, int> map;

        int left  = 0;
        int right = 0;

        while (right < n)
        {
            map[nums[right]]++;

            // While window violates the condition |nums[i] - nums[j]| <= 2
            // Shrink window from left
            while (map.rbegin()->first - map.begin()->first > 2)
            {
                // Remove leftmost element from frequency map
                map[nums[left]]--;

                if (map[nums[left]] == 0)
                    map.erase(nums[left]);

                left++;
            }

            // Add count of all valid subarrays ending at right
            count += right - left + 1;
            right++;
        }

        return count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is the same IDEA as above, however, instead of using a "Red-black map"
    we use MinHeap and MaxHeap.

*/

/* Time  Beats: 10.18% */
/* Space Beats: 44.26% */

/* Time  Complexity: O(n) */ // Same reasons as above
/* Space Complexity: O(1) */ // Same reasons as above
class Solution_Sliding_Window_Heap {
public:
    long long continuousSubarrays(vector<int>& nums)
    {
        int left  = 0;
        int right = 0;
        long long count = 0;

        // Min and max heaps storing indices, sorted by nums[index] values
        priority_queue<int,
                       vector<int>,
                       function<bool(int, int)>> min_heap([&nums](int a, int b) { return nums[a] > nums[b]; });

        priority_queue<int,
                       vector<int>,
                       function<bool(int, int)>> max_heap([&nums](int a, int b) { return nums[a] < nums[b]; });


        while (right < nums.size())
        {
            // Add current index to both heaps
            min_heap.push(right);
            max_heap.push(right);

            // While window violates |nums[i] - nums[j]| ≤ 2 condition
            // Shrink window from left and remove outdated indices
            while (left < right && nums[max_heap.top()] - nums[min_heap.top()] > 2)
            {
                left++;

                // Remove indices that are now outside window
                while ( ! max_heap.empty() && max_heap.top() < left)
                    max_heap.pop();

                while ( ! min_heap.empty() && min_heap.top() < left)
                    min_heap.pop();
            }

            // Add count of all valid subarrays ending at right
            count += right - left + 1;
            right++;
        }

        return count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent IDEA as two above, however here we use two DEQUES to do this.

*/

/* Time  Beats: 81.64% */
/* Space Beats: 47.34% */

/* Time  Complexity: O(n) */ // Same reasons as above
/* Space Complexity: O(1) */ // Same reasons as above
class Solution_Sliding_Window_Deque {
public:
    long long continuousSubarrays(vector<int>& nums)
    {
        const int n = nums.size();

        // Monotonic deque to track maximum and minimum elements
        deque<int> monotonic_decreasing;
        deque<int> monotonic_increasing;

        int left  = 0;
        int right = 0;
        long long count = 0;

        while (right < n)
        {
            // Maintain decreasing monotonic deque for maximum values
            while (!monotonic_decreasing.empty() && nums[monotonic_decreasing.back()] < nums[right])
                monotonic_decreasing.pop_back();

            monotonic_decreasing.push_back(right);

            // Maintain increasing monotonic deque for minimum values
            while (!monotonic_increasing.empty() && nums[monotonic_increasing.back()] > nums[right])
                monotonic_increasing.pop_back();

            monotonic_increasing.push_back(right);

            // Shrink window if max-min difference exceeds 2
            while ( ! monotonic_decreasing.empty() &&
                    ! monotonic_increasing.empty() &&
                    nums[monotonic_decreasing.front()] - nums[monotonic_increasing.front()] > 2)
            {
                // Move left pointer past the element that breaks the condition
                if (monotonic_decreasing.front() < monotonic_increasing.front())
                {
                    left = monotonic_decreasing.front() + 1;
                    monotonic_decreasing.pop_front();
                }
                else
                {
                    left = monotonic_increasing.front() + 1;
                    monotonic_increasing.pop_front();
                }
            }

            // Add count of all valid subarrays ending at current right pointer
            count += right - left + 1;

            // Increment
            right++;
        }

        return count;
    }
};
