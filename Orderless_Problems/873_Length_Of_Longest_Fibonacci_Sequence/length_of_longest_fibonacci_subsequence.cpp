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

#include <unordered_map>
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




/*
    ------------
    --- IDEA ---
    ------------

    Example 1:
        arr = {1,2,3,4,5,6,7,8}

          |  0  1  2  3  4  5  6  7
        --+--------------------------
        0 |  -  2  2  2  2  2  2  2
        1 |  -  -  3  2  2  2  2  2
        2 |  -  -  -  3  4  2  2  2
        3 |  -  -  -  -  3  3  4  2
        4 |  -  -  -  -  -  3  3  5
        5 |  -  -  -  -  -  -  3  3
        6 |  -  -  -  -  -  -  -  3
        7 |  -  -  -  -  -  -  -  -

    What does, say, dp[2][4] represent?

    It represents the LENGTH of the Fibonacci subsequence that ENDS at indices
    2 and 4, i.e. it ends with elements 3 and 5, respectively.

    In this case, it would be: {1,2,3,5}
                                0 1 2 4

    We don't actually care about the previous elements, we only care about the
    last two elements, since those two are going to be used to form the next
    number and thus extend the subsequence.

    Now read the code and look at the table above and you'll get it. It's not
    easy to come up with this, but if you notice some repeated work and
    ESPECIALLY if you notice that the Constraints are small, you almost
    certainly can make this table and probably can perform Dynamic Programming.

*/

/* Time  Beats: 29.48% */
/* Space Beats: 21.37% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_DP {
public:
    int lenLongestFibSubseq(vector<int>& arr)
    {
        const int N = arr.size();
        int result = 0;

        // dp[prev][curr] stores len of Fib. seq. ending at indices: prev, curr
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Map each value to its index for O(1) lookup
        unordered_map<int, int> val_to_idx;

        for (int curr = 0; curr < arr.size(); curr++)
        {
            val_to_idx[arr[curr]] = curr; // Map it

            for (int prev = 0; prev < curr; prev++)
            {
                // Find if there exists a previous number to form Fib. seq.
                int target_val = arr[curr] - arr[prev];

                int target_idx = -1;
                if (val_to_idx.find(target_val) != val_to_idx.end())
                    target_idx = val_to_idx[target_val];

                // Update dp if valid Fibonacci sequence possible
                // target_val < arr[prev] ensures strictly increasing sequence
                if (target_idx != -1 && target_val < arr[prev])
                    dp[prev][curr] = dp[target_idx][prev] + 1;
                else
                    dp[prev][curr] = 2;

                result = max(result, dp[prev][curr]);
            }
        }

        return result > 2 ? result : 0;
    }
};
