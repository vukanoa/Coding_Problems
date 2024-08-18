#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    264) Ugly Number II
    ===========================

    ============
    Description:
    ============

    An ugly number is a positive integer whose prime factors are limited to 2,
    3, and 5.

    Given an integer n, return the nth ugly number.

    ===================================
    FUNCTION: int nthUglyNumber(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 12
    Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first
                 10 ugly numbers.


    --- Example 2 ---
    Input: n = 1
    Output: 1
    Explanation: 1 has no prime factors, therefore all of its prime factors are
                 limited to 2, 3, and 5.


    *** Constraints ***
    1 <= n <= 1690

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.60% */
/* Space Beats: 19.29% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int nthUglyNumber(int n)
    {
        // Use a min-heap (priority queue with greater<int>)
        priority_queue<int, vector<int>, greater<int>> min_heap;
        min_heap.push(1);

        unordered_set<int> visited;
        visited.insert(1);
        const vector<int> factors = {2, 3, 5};

        for (int i = 0; i < n; i++)
        {
            int num = min_heap.top();
            min_heap.pop();

            if (i == n-1)
                return num;

            for (const int& factor : factors)
            {
                long long new_num = (long long)num * factor;

                if (new_num <= INT_MAX && visited.find(new_num) == visited.end()) // Check for overflow and duplicates
                {
                    visited.insert(new_num);
                    min_heap.push(new_num);
                }
            }
        }

        return -1; // This will never get executed
    }
};
