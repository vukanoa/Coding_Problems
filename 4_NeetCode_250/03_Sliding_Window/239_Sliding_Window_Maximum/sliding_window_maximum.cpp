/*
    ============
    === HARD ===
    ============

    ===========================
    239) Sliding Window Maximum
    ===========================

    ============
    Description:
    ============

    You are given an array of integers "nums", there is a sliding window of
    size 'k' which is moving from the very left of the array to the very right.
    You can only see the 'k' numbers in the window. Each time the sliding
    window moves right by one position.

    Return the max sliding window.

    =================================================================
    FUNCTION: vector<int> maxSlidingWindow(vector<int>& nums, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
    Output: [3, 3, 5, 5, 6, 7]
    Window position                     Max
    ---------------                    -----
    [1   3  -1] -3   5   3   6   7        3
     1  [3  -1  -3]  5   3   6   7        3
     1   3 [-1  -3   5]  4   6   7        5
     1   3  -1 [-3   5   4]  6   7        5
     1   3  -1  -3  [5   4   6]  7        6
     1   3  -1  -3   5  [4   6   7]       7

    --- Example 2 ---
    Input:  nums = [1], k = 1
    Output: [1]

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    1 <= k <= nums.length

*/

#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    ====================================
    === Monotonicly DECREASING DEQUE ===
    ====================================

    Here we introduce an interesting data structure. It's a deque with an
    interesting property - the elements in the deque from head to tail are in
    DECREASING order (hence the name monotonic)

    To achieve this property, we modify the push operation so that:

        Before we push an element into the deque, we first pop everything
        smaller than it out of the deque.

    This enforces the DECREASING order.

    The overall Time complexity is O(N). This is because each element in the
    original array can be pushed into and popped out of the deque ONLY ONCE.

    The KEY why this Monotonicly-Decreasing-Deque works is becase we are
    keeping an element inside the structure as long as its INDEX is within the
    valid bounds AND it keeps the MONOTONICLY DECREASING order.

    Why are both important?

    Well, the first one is obvious -- It needs to be within the bounds.
    Second, it needs to be in MONOTONICLY DECREASING order because once the
    elements that are BIGGER than it, are popped due to NOT BEING WITHIN THE
    BOUNDS, it will certainly become the maximum of the next ongoing window.

    (Read this upper paragrpah again, slowly. It is the crux of this solution)

*/

/* Time  Beats: 75.32% */
/* Space Beats: 42.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(k) */ // O(k) EXTRA space, since "result" is not EXTRA
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> result;

        deque<int> mono_decr_deque; // Of INDICES(!!!)

        // O(N) (entire block)
        int i = 0;
        while (i < N)
        {
            /* Pop elements from the FRONT that are OUT OF CURRENT WINDOW */
            while ( ! mono_decr_deque.empty() && mono_decr_deque.front() <= (i - k))
            {
                mono_decr_deque.pop_front(); // O(1)
            }

            /* Pop elements from the BACK that are LESS THAN OR EQUALS to nums[i] */
            /* This KEEPS the "Decreasing" property */
            while ( ! mono_decr_deque.empty() && nums[mono_decr_deque.back()] <= nums[i])
            {
                mono_decr_deque.pop_back(); // O(1)
            }

            // This one is CERTAINLY within the bounds and every element BEFORE
            // it, that is WITHIN THE BOUNDS, is STRICTLY GREATER than it
            mono_decr_deque.push_back(i); // O(1)

            // Start keeping track of the "Max" only after we've gone over the first k elements
            if (i+1 >= k)
                result.push_back(nums[mono_decr_deque.front()]);

            // Increment
            i++;
        }


        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The exact same IDEA as above, however the implementation is different for
    it is done on another occasion.

    I prefer the above one, though it's beneficial to look at both.

*/

/* Time  Beats: 96.33% */
/* Space Beats: 34.97% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(k) */ // O(k) EXTRA space, since "result" is not EXTRA
class Solution_2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> result;

        deque<int> mono_decr_deque; // Of INDICES(!!!)

        for (int i = 0; i < N; i++)
        {
            while ( ! mono_decr_deque.empty() && nums[mono_decr_deque.back()] < nums[i])
                mono_decr_deque.pop_back();

            mono_decr_deque.push_back(i);

            if (i+1 >= k) // Once we've gone over the first k elements
            {
                result.push_back(nums[mono_decr_deque.front()]);

                if (mono_decr_deque.front() == i - k + 1)
                    mono_decr_deque.pop_front();
            }
        }

        return result;
    }
};
