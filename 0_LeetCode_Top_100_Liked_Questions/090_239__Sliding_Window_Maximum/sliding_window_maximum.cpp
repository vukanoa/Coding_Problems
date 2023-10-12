#include <iostream>
#include <vector>
#include <deque>

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



/*
    ------------
    --- IDEA ---
    ------------

    Let's start with:


    ============================
    === Brute Force Solution ===
    ============================

    We can write a nested loop, the outer loop goes through each window and
    the inner loop finds the max within the window. This is O(N^2) time
    complexity. Since at worst k == n. If k was always smaller than n, it would
    be O(n * k).

    To optimize on brute force, we can either reduce outer or inner loop
    complexity. Since we have toe examine each element at least once(there's no
    way to find the maximum if we don't know what the values are), there is not
    much we can do for outer loop. So we have to work on the inner loop.

    *** Preserving inner elements maximum ***
    Currently, to get the max of the sliding window, we look at each element in
    the window and compare them. Analogous to sliding window sum problem (given
    an array and a window size, return the sum of each window), when a window
    slides, only two elements change - the leftmost gets removed and a new
    element gets added to the right.

    Everything in the middle(let's call them "inner elements") is unchanged,
    and the maximum element among these inner elements are unchanged as well.
    They key to reducing inner loop complexity is to persist the maximum of
    the inner elements as we slide the window. Ideally, we want to be able to
    access the maximum element in less than O(n) time and updating it in less
    than O(n) time.


    =======================
    === Monotonic Deque ===
    =======================

    Here we introduce an interesting data structure. It's a deque with an
    interesting property - the elements in the deque from head to tail are in
    decreasing order (hence the name monotonic)

    To achieve this property, we modify the push operation so that:
        Before we push an element into the deque, we first pop everything
        smaller than it out of the deque.

    This enfroces the decreasing order.

    The overall time complexity is O(N). This is because each element in the
    original array can be pushed into and popped out of the deque only once.

    Which indicates that both "push" and "pop" operations are performed in O(1)

    The key why monotonic deque works is it stores both magnitude and position
    information. From head to tail, the elements get smaller and further to the
    right of the array.

    Consider this Example:
        [1, 3, -1, -3, 5, 3, 6, 7], k = 4;


    We start pushing nums[deque.front()] into "results" once (r + 1 becomes  k)
    i.e.:
        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; However "right" pointer is always incrementing.



    Also that's when we start incrementing our left pointer.



    0)          l
                r
        nums = [1] 3  -1  -3  5  3  6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 0
           ------------------------
             ^
             |
             ------ back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    1)
                l  r
        nums = [1  3] -1  -3  5  3  6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 1
           ------------------------
             ^
             |
             ------ back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    2)
                l      r
        nums = [1  3  -1] -3  5  3  6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 1 | 2
           ------------------------
                 ^
                 |
                 --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    3)
                l          r
        nums = [1  3  -1  -3] 5  3  6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 1 | 2 | 3
           ------------------------
                     ^
                     |
                     --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    4)
                   l          r
        nums =  1 [3  -1  -3  5] 3  6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 4
           ------------------------
             ^
             |
             --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    5)
                       l         r
        nums =  1  3 [-1  -3  5  3] 6  7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 4 | 5
           ------------------------
                 ^
                 |
                 --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    6)
                           l        r
        nums =  1  3  -1 [-3  5  3  6] 7
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 6
           ------------------------
             ^
             |
             --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    7)
                              l        r
        nums =  1  3  -1  -3 [5  3  6  7]
                0  1   2   3  4  5  6  7

        Deque: (It stores INDICES, not values)

    front ----
             |
             v
           ------------------------
           | 7
           ------------------------
             ^
             |
             --- back

        if (r + 1 >= k)
            results.push_back(nums[deque.back()]);
            left++;

        right++; We always increment "right" pointer.




    ==================
    === End Result ===
    ==================

        Resuls = {3, 5, 5, 6, 7};

*/

/* Time  Beats: 97.53% */
/* Space Beats: 46.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */  // It is said that k can be equal to n, so O(n)
class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
    {
        std::vector<int> results;
        std::deque<int>  deque;   // Stores indices

        int left  = 0;
        int right = 0;
        while (right < nums.size())
        {
            while (!deque.empty() && nums[deque.back()] < nums[right])
                deque.pop_back();

            deque.push_back(right);

            /* Remove leftmost element if it's outside the window */
            if (left > deque.front()) // deque.front() is an INDEX!
                deque.pop_front();

            /* If window has 'k' elements, add front of the deque to results */
            if (right + 1 >= k)
            {
                results.push_back(nums[deque.front()]);
                left++;
            }

            right++;
        }

        return results;
    }
};


int
main()
{
    Solution      sol;

    /* Example 1 */
    // std::vector<int> nums {1, 3, -1, -3, 5, 3, 6, 7};
    // int k = 3;

    /* Example 2 */
    // std::vector<int> nums {1};
    // int k = 1;

    /* Example 3 */
    std::vector<int> nums {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 4;


    std::cout << "\n\t==============================";
    std::cout << "\n\t=== SLIDING WINDOW MAXIMUM ===";
    std::cout << "\n\t==============================\n";


    /* Write Input */
    std::cout << "\n\tK: " << k;
    bool first = true;
    std::cout << "\n\tArray:  [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    std::vector<int> output = sol.maxSlidingWindow(nums, k);


    /* Write Output */
    first = true;
    std::cout << "\n\tOutput: [";
    for (auto x: output)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
