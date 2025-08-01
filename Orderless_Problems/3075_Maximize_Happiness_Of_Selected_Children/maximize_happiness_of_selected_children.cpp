/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3075) Maximize Happiness of Selected Children
    =============================================

    ============
    Description:
    ============

    You are given an array happiness of length n, and a positive integer k.

    There are n children standing in a queue, where the ith child has happiness
    value happiness[i]. You want to select k children from these n children in
    k turns.

    In each turn, when you select a child, the happiness value of all the
    children that have not been selected till now decreases by 1. Note that the
    happiness value cannot become negative and gets decremented only if it is
    positive.

    Return the maximum sum of the happiness values of the selected children you
    can achieve by selecting k children.

    =======================================================================
    FUNCTION: long long maximumHappinessSum(vector<int>& happiness, int k);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: happiness = [1,2,3], k = 2
    Output: 4
    Explanation: We can pick 2 children in the following way:
    - Pick the child with the happiness value == 3. The happiness value of the
      remaining children becomes [0,1].
    - Pick the child with the happiness value == 1. The happiness value of the
      remaining child becomes [0]. Note that the happiness value cannot become
      less than 0.
    The sum of the happiness values of the selected children is 3 + 1 = 4.


    --- Example 2 ---
    Input: happiness = [1,1,1,1], k = 2
    Output: 1
    Explanation: We can pick 2 children in the following way:
    - Pick any child with the happiness value == 1. The happiness value of the
      remaining children becomes [0,0,0].
    - Pick the child with the happiness value == 0. The happiness value of the
      remaining child becomes [0,0].
    The sum of the happiness values of the selected children is 1 + 0 = 1.


    --- Example 3 ---
    Input: happiness = [2,3,4,5], k = 1
    Output: 5
    Explanation: We can pick 1 child in the following way:
    - Pick the child with the happiness value == 5. The happiness value of the
      remaining children becomes [1,2,3].
    The sum of the happiness values of the selected children is 5.


    *** Constraints ***
    1 <= n == happiness.length <= 2 * 10^5
    1 <= happiness[i] <= 10^8
    1 <= k <= n

*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem should be marked as EASY.

    Heapify vector "happiness" and then just pop first k elements. However,
    there is only one caveat.

    Since we have to pop top k elements, each time we pop we should subtract
    the number of the turn it was popped at.

    For example:
        happiness = [1, 2, 3, 4, 5], k=3

    Turn 0: 5
    Turn 1: 4
    Turn 2: 3

    Therefore, our end result is going to be:
        result += (5 - 0) + (4 - 1) + (3 - 2) = 9


    In a nutshell, this line is the crux of this problem:

            result += happy - i > 0 ? happy - i : 0;

*/

/* Time  Beats: 87.60% */
/* Space Beats: 11.63% */

/* Time  Complexity: O(n + k*logn) */
/* Space Complexity: O(n) */
class Solution_Heap {
public:
    long long maximumHappinessSum(std::vector<int>& happiness, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        long long result = 0;

        // O(n)
        priority_queue<int> max_heap(happiness.begin(), happiness.end());

        // O(k * logn)
        for (int i = 0; i < k; i++)
        {
            int happy = max_heap.top();
            max_heap.pop(); // O(log n)

            result += happy - i > 0 ? happy - i : 0;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Insted of using a Heap, we are sorting the vector "happiness".

    The rest of the Solution is exactly the same as above.

*/

/* Time  Beats: 99.85% */
/* Space Beats: 60.15% */

/* Time  Complexity: O(k + n * logn)  */
/* Space Complexity: O(n) or O(1) */ // Depending on the sorting algorihtm
class Solution_Sorting {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        long long result = 0;

        // O(n * logn)
        std::sort(happiness.begin(), happiness.end(), std::greater<int>());

        for (int i = 0; i < k; i++)
            result += happiness[i] - i > 0 ? happiness[i] - i : 0;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another Sorting Solution, but implemented differently. It's good to see
    both.

*/

/* Time  Beats: 83.09% */
/* Space Beats: 91.10% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // LogN because of Introsort's TC
class Solution_Sorting_2 {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k)
    {
        const int N = happiness.size();
        long long result = 0;

        /* Sort */
        sort(happiness.begin(), happiness.end());

        long long decrement = 0;

        while (k-- > 0)
        {
            result += max(0LL, happiness.back() - decrement);
            happiness.pop_back();
            decrement++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of Heap or some standard sorting algorithm, we are using:
    Partial Sort.

    What is "Partial Sort"?

    As the name suggests, it only partially sorts array/vector.

    In our Solution:
    std::partial_sort(happiness.begin(), happiness.begin() + k, happiness.end(), greater<int>());

    It sorts only first K elements in descending order, meaning the 0-th
    element is the greatest.

    After first k elements, from 0 to k-1, the rest is unsorted.

    The rest of the Solution is exactly the same as two Solutions above.

*/

/* Time  Beats: 67.75% */
/* Space Beats: 60.15% */

/* Time  Complexity: O(k + k * logn) */
/* Space Complexity: O(1) */
class Solution_Partial_Sort {
public:
    long long maximumHappinessSum(std::vector<int>& happiness, int k)
    {
        long long result = 0;

        // O(n * logk)
        std::partial_sort(happiness.begin(), happiness.begin() + k, happiness.end(), greater<int>());

        for (int i = 0; i < k; i++)
            result += happiness[i] - i > 0 ? happiness[i] - i : 0;

        return result;
    }
};
