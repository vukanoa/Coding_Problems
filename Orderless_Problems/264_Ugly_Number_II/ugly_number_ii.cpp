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

#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.01% */
/* Space Beats: 25.51% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Set {
public:
    int nthUglyNumber(int n) 
    {
        set<long> ugly_numbers_set;
        ugly_numbers_set.insert(1);

        long current_ugly = 1;
        for (int i = 0; i < n; i++) 
        {
            current_ugly = *ugly_numbers_set.begin();
            ugly_numbers_set.erase(ugly_numbers_set.begin());

            ugly_numbers_set.insert(current_ugly * 2);
            ugly_numbers_set.insert(current_ugly * 3);
            ugly_numbers_set.insert(current_ugly * 5);
        }

        return static_cast<int>(current_ugly);
    }
};




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
class Solution_Heap {
public:
    int nthUglyNumber(int n)
    {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.94% */
/* Space Beats: 42.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Efficient {
public:
    int nthUglyNumber(int n)
    {
        vector<int> nums = {1};

        int i2 = 0;
        int i3 = 0;
        int i5 = 0;

        for (int i = 0; i < n; i++)
        {
            int next_num = min( {nums[i2] * 2, nums[i3] * 3, nums[i5] * 5} );
            nums.push_back(next_num);

            if (next_num == nums[i2] * 2)
                i2++;

            if (next_num == nums[i3] * 3)
                i3++;

            if (next_num == nums[i5] * 5)
                i5++;
        }

        return nums[n-1];
    }
};
