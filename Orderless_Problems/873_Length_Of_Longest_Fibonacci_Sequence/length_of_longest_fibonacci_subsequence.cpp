/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    873) Length of Longest Fibonacci Subsequence
    ============================================

    ============
    Description:
    ============

    A sequence x1, x2, ..., xn is Fibonacci-like if:

        n >= 3
        xi + xi+1 == xi+2 for all i + 2 <= n

    Given a strictly increasing array arr of positive integers forming a
    sequence, return the length of the longest Fibonacci-like subsequence of
    arr. If one does not exist, return 0.

    A subsequence is derived from another sequence arr by deleting any number
    of elements (including none) from arr, without changing the order of the
    remaining elements. For example, [3, 5, 8] is a subsequence of
    [3, 4, 5, 6, 7, 8].

    ====================================================
    FUNCTION: int lenLongestFibSubseq(vector<int>& arr);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,4,5,6,7,8]
    Output: 5
    Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].

    --- Example 2 ---
    Input: arr = [1,3,7,11,12,14,18]
    Output: 3
    Explanation: The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].


    *** Constraints ***
    3 <= arr.length <= 1000
    1 <= arr[i] < arr[i + 1] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you haven't solved famous "Longest Increasing Subsequence", i.e. "LIS",
    then you don't have a chance of solving this one.

    Especially if you haven't solved "LIS" using "Stable Sort technique" that
    solves it in O(N * logN) instead of O(N^2).

    This one, as you can see below, has a Time Complexity of O(N^2 * logN),
    therefore if you haven't solved "LIS" using "Stable Sort technique', don't
    even try to solve this one.

    Go and look at that problem and that specific Solution, try to understand
    it and then come back to try and decipher this.

*/

/* Time  Beats: 83.33% */
/* Space Beats: 45.30% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(N^2)        */
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr)
    {
        const int N = arr.size();
        int result = 0;

        vector<vector<int>> fibonacci_matrix;

        for (int i = 2; i < N; i++)
        {
            for (int j = i-1; j >= 1; j--)
            {
                int target = arr[i] - arr[j];

                if (target > arr[j-1])
                {
                    for (int x = 0; x < fibonacci_matrix.size(); x++)
                    {
                        int size = fibonacci_matrix[x].size();

                        int second_to_last = fibonacci_matrix[x][size-2];
                        int last           = fibonacci_matrix[x][size-1];

                        if (second_to_last + last == arr[i])
                        {
                            fibonacci_matrix[x].push_back(arr[i]);
                            result = max(result, size + 1);
                        }
                    }

                    break;
                }
                else
                {
                    auto it = lower_bound(arr.begin(), arr.begin() + j, target);
                    if (it != (arr.begin() + j) && target == *it) // Found
                    {
                        vector<int> new_fib = {*it, arr[j], arr[i]};
                        fibonacci_matrix.push_back(new_fib);

                        result = max(result, 3);
                    }
                }
            }
        }

        /****************************************************/
        /* All Fibonacci subsequences for the current Input */
        /****************************************************/
        // for (int x = 0; x < fibonacci_matrix.size(); x++)
        // {
        //     cout << "{";
        //     for (int i = 0; i < fibonacci_matrix[x].size(); i++)
        //         cout << fibonacci_matrix[x][i] << " ";
        //     cout << "}\n";
        // }

        return result;
    }
};
