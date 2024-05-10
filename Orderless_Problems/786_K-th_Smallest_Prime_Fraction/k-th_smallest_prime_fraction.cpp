#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    786) K-th Smallest Prime Fraction
    =================================

    ============
    Description:
    ============

    You are given a sorted integer array arr containing 1 and prime numbers,
    where all the integers of arr are unique. You are also given an integer k.

    For every i and j where 0 <= i < j < arr.length, we consider the fraction
    arr[i] / arr[j].

    Return the kth smallest fraction considered. Return your answer as an array
    of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

    ---------------
    -- Follow Up --
    ---------------

    Can you solve the problem with better than O(n2) complexity?


    ========================================================================
    FUNCTION: vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,5], k = 3
    Output: [2,5]
    Explanation: The fractions to be considered in sorted order are:
    1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
    The third fraction is 2/5.

    --- Example 2 ---
    Input: arr = [1,7], k = 1
    Output: [1,7]


    *** Constraints ***
    2 <= arr.length <= 1000
    1 <= arr[i] <= 3 * 10^4
    arr[0] == 1
    arr[i] is a prime number for i > 0.
    All the numbers of arr are unique and sorted in strictly increasing order.
    1 <= k <= arr.length * (arr.length - 1) / 2

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a Brute Force Solution. It works, but it VERY inefficient. I wanted
    to include this one in the current file as well so that we can see the
    gradation of improvement.

*/

/* Time  Beats: 6.78% */
/* Space Beats: 5.22% */

/* Time  Complexity: O(n^2 * logk) */
/* Space Complexity: O(n^2) */
class Solution_Inefficient {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();

        std::priority_queue<std::pair<double, std::vector<int>>,
                            std::vector<std::pair<double, std::vector<int>>>,
                            std::greater<std::pair<double, std::vector<int>>>> min_heap;


        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
                min_heap.push( {1.0 * arr[i] / arr[j], {arr[i], arr[j]} } );
        }

        std::vector<int> result;
        for (int i = 0; i < k; i++)
        {
            result = min_heap.top().second;
            min_heap.pop();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar idea as above, but Time Complexity is reduced to O(n^2), however
    this is still considered a Brute Force Solution.

*/

/* Time  Beats: 10.26% */
/* Space Beats:  6.77% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(k) */
class Solution_Better_But_Still_Inefficient {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();
        std::priority_queue<std::pair<double, std::vector<int>>> max_heap;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                max_heap.push( {1.0 * arr[i] / arr[j], {arr[i], arr[j]} } );

                if(max_heap.size() > k)
                    max_heap.pop();
            }
        }

        std::vector<int> result = max_heap.top().second;
        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.91% */
/* Space Beats: 92.65% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        const int N = arr.size();
        std::vector<int> result;

        double left  = 0;
        double right = 1;
        double mid;

        while (left <= right)
        {
            mid = left + (right - left) / 2;

            int j = 1; // Current denominator index

            int total = 0;
            double max_fraction = 0;

            int numerator_idx   = 0;
            int denominator_idx = 0;

            for (int i = 0; i < N; i++)
            {
                while (j < N && 1.0*arr[i] / arr[j] >= mid)
                    j++;

                total += N - j;

                if (j < N && max_fraction < 1.0*arr[i] / arr[j])
                {
                    max_fraction = 1.0*arr[i] / arr[j];

                    numerator_idx   = i;
                    denominator_idx = j;
                }
            }

            if (total == k)
            {
                result = {arr[numerator_idx], arr[denominator_idx]};
                break;
            }

            if (total > k)
                right = mid;
            else
                left = mid;
        }

        return result;
    }
};
