#include <iostream>
#include <vector>
#include <deque>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    658) Find K Closest Elements
    ============================

    ============
    Description:
    ============

    Given a sorted integer array arr, two integers k and x, return the k
    closest integers to x in the array. The result should also be sorted in
    ascending order.

    An integer a is closer to x than an integer b if:
        |a - x| < |b - x|, or
        |a - x| == |b - x| and a < b


    ==========================================================================
    FUNCTION: vector<int> findClosestElements(vector<int>& arr, int k, int x);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,4,5], k = 4, x = 3
    Output: [1,2,3,4]

    --- Example 2 ---
    Input: arr = [1,2,3,4,5], k = 4, x = -1
    Output: [1,2,3,4]


    *** Constraints ***
    1 <= k <= arr.length
    1 <= arr.length <= 10^4
    arr is sorted in ascending order.
    -10^4 <= arr[i], x <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic Sliding Window technique.

*/

/* Time  Beats: 95.34% */
/* Space Beats: 17.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution_Sliding_Window {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        std::deque<int> deque;
        for (int i = 0; i < arr.size(); i++)
        {
            deque.push_back(arr[i]);

            if (i - k >= 0)
            {
                if (std::abs(deque.front() - x) <= std::abs(deque.back() - x))
                    deque.pop_back();
                else
                    deque.pop_front();
            }
        }

        std::vector<int> results(deque.begin(), deque.end());

        return results;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

   Note that, you SHOULD NOT compare the absolute value of:
       abs(x - A[mid]) and abs(A[mid + k] - x).

   It fails at cases like arr = [1,1,2,2,2,2,2,3,3], x = 3, k = 3

*/

/* Time  Beats: 98.93% */
/* Space Beats: 26.20% */

/* Time  Complexity: O(log(N - K)) */
/* Space Complexity: O(K) */
class Solution_Binary_Search {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        int left  = 0;
        int right = arr.size() - k;

        while (left < right)
        {
            int mid = (left + right) / 2;

            if (x - arr[mid] > arr[mid + k] - x)
                left = mid + 1;
            else
                right = mid;
        }

        return std::vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
