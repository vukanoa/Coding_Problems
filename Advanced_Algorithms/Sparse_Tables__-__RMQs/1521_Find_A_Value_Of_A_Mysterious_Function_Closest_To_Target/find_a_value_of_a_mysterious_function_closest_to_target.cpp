/*
    ============
    === HARD ===
    ============

    =============================================================
    1521) Find a Value of a Mysterious Function Closest to Target
    =============================================================

    ============
    Description:
    ============

        func(arr, l, r) {
            if (r < l) {
                return -1000000000; // -1e9
            }
            ans = arr[l];
            for (int = l + 1; i <= r; i++) {
                ans = ans & arr[i];
            }
            return ans;
        }

    Winston was given the above mysterious function func. He has an integer
    array arr and an integer target and he wants to find the values l and r
    that make the value |func(arr, l, r) - target| minimum possible.

    Return the minimum possible value of |func(arr, l, r) - target|.

    Notice that func should be called with the values l and r where 0 <= l, r <
    arr.length.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [9,12,3,7,15], target = 5
    Output: 2
    Explanation: Calling func with all the pairs of [l,r] =
                 [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]],
                 Winston got the following results
                 [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7
                 and 3, thus the minimum difference is 2.


    --- Example 2 ---
    Input: arr = [1000000,1000000,1000000], target = 1
    Output: 999999
    Explanation: Winston called the func with all possible values of [l,r] and
                 he always got 1000000, thus the min difference is 999999.


    --- Example 3 ---
    Input: arr = [1,2,4,8,16], target = 0
    Output: 0


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i] <= 10^6
    0 <= target <= 10^7

*/

#include <climits>
#include <cstdlib>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 64.33% */
/* Space Beats: 61.70% */

/* Time  Complexity: O(N * log(MAX_VALUE) * logN) */
/* Space Complexity: O(N * logN)                  */
class Solution {
private:
    vector<vector<int>> table;
    int LOG_N;

public:
    int closestToTarget(vector<int>& arr, int target)
    {
        const int N = arr.size();
        int result = INT_MAX;

        LOG_N = 0;
        while ((1 << LOG_N) <= N)
            ++LOG_N;

        table = vector<vector<int>>(N, vector<int>(LOG_N));
        initialize_sparse_table(arr);

        for (int L = 0; L < N; L++)
        {
            int R = L;

            while (R < N)
            {
                int value = range_and(L, R);

                result = min(result, abs(target - value));

                if (value == 0) // Because AND-ing with 0 ALWAYS gives 0
                    break;

                int low  = R;
                int high = N - 1;

                while (low < high)
                {
                    int mid = low + (high - low + 1) / 2; // Low-leaning mid

                    if (range_and(L, mid) == value)
                        low  = mid;
                    else
                        high = mid - 1;
                }

                R = low + 1;
            }
        }

        return result;
    }

private:
    void initialize_sparse_table(vector<int>& arr)
    {
        const int N = arr.size();

        for (int i = 0; i < N; i++)
            table[i][0] = arr[i];

        for (int power = 1; power < LOG_N; power++)
        {
            for (int i = 0; (i + (1 << power) - 1) < N; i++)
            {
                int half_power = power - 1;

                table[i][power] = table[i                    ][half_power] &
                                  table[i + (1 << half_power)][half_power];
            }
        }
    }

    int range_and(int L, int R)
    {
        int power = 31 - __builtin_clz(R - L + 1);

        return table[L                   ][power] &
               table[R - (1 << power) + 1][power];
    }
};




/*
    ------------
    --- IDEA ---
    ------------


    Observations:

    1. If we start taking AND of elements of any sequence, the AND value will
       either remain the same or decrease.

       Let arr[1], arr[2], arr[3] be the sequence:

           -> a1 = arr[1]
           -> a2 = arr[1] & arr[2]
           -> a3 = arr[1] & arr[2] & arr[3]

       We can say:

           a1 >= a2 >= a3

       because while taking AND we cannot set a bit. Therefore, the AND value
       either remains the same or decreases.


    2. The AND value can decrease at most the number of set bits in arr times,
       i.e. at most max(log(arr)) times.



    3. The number of unique AND values of subarrays starting at any position is
       AT MOST LOG(arr[i]), where arr[i] is the first element of the subarray.



    4. The AND values of subarrays starting at index i can be calculated from
       the AND values of subarrays starting at index i + 1.

       subarray_AND_values[i] contains the AND values of subarrays starting
       from index i.

       For example, let:

           arr[] = [2, 6, 7, 2, 4]

       Subarrays starting at index 4:

           [4]                    -> subarray_AND_values[4] = {4}

       Subarrays starting at index 3:

           [2], [2, 4]            -> subarray_AND_values[3] = {2, 0}

       Subarrays starting at index 2:

           [7], [7, 2], [7, 2, 4]
                                   -> subarray_AND_values[2] = {7, 2, 0}

       AND_table[i, len] is the AND of the subarray starting at index i with
       length len.

       Observe that:

           AND_table[i, 1] = arr[i]
           AND_table[i, 2] = arr[i] & AND_table[i + 1, 1    ]
           AND_table[i, 3] = arr[i] & AND_table[i + 1, 2    ]
           AND_table[i, 4] = arr[i] & AND_table[i + 1, 3    ]
           ...
           AND_table[i, j] = arr[i] & AND_table[i + 1, j - 1]

       Also, AND_table[i + 1, j] is present in subarray_AND_values[i + 1], by
       the definition of subarray_AND_values[i].

       Therefore, subarray_AND_values[i] can be calculated from

           subarray_AND_values[i + 1],

       because the AND values in:

           subarray_AND_values[i    ]

       are simply arr[i] AND-ed with the values in:

           subarray_AND_values[i + 1].



       From Observation (3), we can conclude:

           subarray_AND_values[i].size() <= log(max(arr)) <= 20

       because arr.size() <= 10^6.

*/

/* Time  Beats: 63.45% */
/* Space Beats: 45.32% */

/* Time  Complexity: O(N * log(max(arr))) */
/* Space Complexity: O(N * log(max(arr))) */
class Solution_DP {
public:
    int closestToTarget(vector<int>& arr, int target)
    {
        const int N = arr.size();
        int result = INT_MAX;

        vector<set<int>> AND_table(N);

        /* Calculate unique AND values of subarrays starting at each index */
        AND_table[N - 1].insert(arr[N - 1]);

        for (int L = N-2; L >= 0; L--)
        {
            AND_table[L].insert(arr[L]);

            for (const int& value : AND_table[L + 1])
            {
                AND_table[L].insert(arr[L] & value);
            }
        }

        /* Find the closest AND value to target */
        for (int L = 0; L < N; L++)
        {
            for (int value : AND_table[L])
                result = min(result, abs(value - target));
        }

        return result;
    }
};
