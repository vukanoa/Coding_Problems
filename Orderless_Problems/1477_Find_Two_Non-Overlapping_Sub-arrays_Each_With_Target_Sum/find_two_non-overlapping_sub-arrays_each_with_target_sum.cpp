/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    1477) Find Two Non-Overlapping Sub-arrays Each With Target Sum
    ==============================================================

    ============
    Description:
    ============

    You are given an array of integers arr and an integer target.

    You have to find two non-overlapping sub-arrays of arr each with a sum
    equal target. There can be multiple answers so you have to find an answer
    where the sum of the lengths of the two sub-arrays is minimum.

    Return the minimum sum of the lengths of the two required sub-arrays, or
    return -1 if you cannot find such two sub-arrays.

    ============================================================
    FUNCTION: int minSumOfLengths(vector<int>& arr, int target);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [3,2,2,4,3], target = 3
    Output: 2
    Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of
                 their lengths is 2.

    --- Example 2 ---
    Input: arr = [7,3,4,7], target = 7
    Output: 2
    Explanation: Although we have three non-overlapping sub-arrays of sum = 7
                 ([7], [3,4] and [7]), but we will choose the first and third
                 sub-arrays as the sum of their lengths is 2.

    --- Example 3 ---
    Input: arr = [4,3,2,6,2,3,4], target = 6
    Output: -1
    Explanation: We have only one sub-array of sum = 6.


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i] <= 1000
    1 <= target <= 10^8

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---  (Explanation by "eunice", not my own)
    ------------


    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    |  3  |  4  |  3  |  2  |  1  |  3  |  1  |  3  |  6  |  1  |      N = 10
    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
       0     1     2     3     4     5     6     7     8     9   

    In 2D array, finding these subarrays is simply a matter of moving forward
    or downward:

        + If the current sum is less than k, we move forward to include the
          next prefix sum.

        + If the current sum is greater than k, we move down to the next row,
          effectively removing the leftmost element from the subarray.


                        Running prefix_sum [i ... n-1]

        +-----+#####+     +     +     +     +     +     +     +     +
        |  3  #  7  # 10  | 12  | 13  | 16  | 17  | 20  | 26  | 27  |
        +-----+#####+#####+~~~~~+     +     +     +     +     +     +
              |  4  #  7  #  9  | 10  | 13  | 14  | 17  | 23  | 24  |
              +-----+#####+-----+-----+-----+     +     +     +     +
                    |  3  |  5  |  6  |  9  | 10  | 13  | 19  | 20  |
                    +     +-----+-----+-----+#####+-----+     +     +
                          |  2  |  3  |  6  #  7  # 10  | 16  | 17  |
                          +     +     +-----+#####+-----+     +     +
                                |  1  |  4  |  5  |  8  | 14  | 15  |
                                +     +     +     +#####+-----+     +
                                      |  3  |  4  #  7  # 13  | 14  |
                                      +     +     +#####+-----+     +
                                            |  1  |  4  | 10  | 11  |
                                            +     +     +-----+     +
                                                  |  3  |  9  | 10  |
                                                  +     +-----+#####+
                                                        |  6  #  7  #
                                                        +-----+#####+
                                                              |  1  |
                                                              +     +

    Whenever we find an element equal to target, this corresponds to a subarray
    with:
        
        sum == "target"



    Given the left and right pointers "start" and "end", its corresponding
    length is simply:

        curr_subarray_len = end − start + 1


        +-----+-----=     +     +     +     +     +     +     +     +
        |  3  |  7  | 10    12    13    16    17    20    26    27   
        +-----+-----+-----+     +     +     +     +     +     +     +
              |  4  |  7  |  9    10    13    14    17    23    24   
              +-----+-----+     +     +     +     +     +     +     +
                       3     5     6     9    10    13    19    20   
                    +     +-----+-----+-----+-----+     +     +     +
                          |  2  |  3  |  6  |  7  | 10    16    17   
                          +-----+-----+-----+-----+     +     +     +
                                   1     4     5     8    14    15   
                                +     +-----+-----+-----+     +     +
                                      |  3  |  4  |  7  | 13    14   
                                      +-----+-----+-----+     +     +
                                               1     4    10    11   
                                            +     +     +     +     +
                                                     3     9    10   
                                                  +     +-----+-----+
                                                        |  6  |  7  |
                                                        +-----+-----+
                                                                 1   
                                                              +     +

    We want the two smallest lengths, but it is not that simple, since the two
    subarrays must also be non–overlapping.



    Avoiding Overlap

    Here, we are at index end=7, where:

        The curr_subarray_len = 3 
        The leftmost index of the current subarray is start = 5.
        To prevent overlap, the previous subarrays MUST end BEFORE index 5.


    We check the min length among all subarrays that end BEFORE the left index
    i=5, then add it to the current length.

    Essentially, this box contains the non–overlapping subarrays as seen before
    start:
                                                        |                   
                                                        |start  end
                                                        |  |     |
                                                        |  |     |
                                                        |  v     v
           0     1     2     3     4     5     6     7  |  8     9   
                                                        |
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     +     +
        @  3  |  7  | 10    12    13    16    17    20  @ 26    27   
        @-----+-----+-----+     +     +     +     +     @     +     +
        @     |  4  |  7  |  9    10    13    14    17  @ 23    24   
        @     +-----+-----+     +     +     +     +     @     +     +
        @              3     5     6     9    10    13  @ 19    20   
        @           +     +-----+-----+-----+-----+     @     +     +
        @                 |  2  |  3  |  6  |  7  | 10  @ 16    17   
        @                 +-----+-----+-----+-----+     @     +     +
        @                          1     4     5     8  @ 14    15   
        @                       +     +-----+-----+-----@     +     +
        @                             |  3  |  4  |  7  @ 13    14   
        @                             +-----+-----+-----@     +     +
        @                                      1     4  @ 10    11   
        @                                   +     +     @     +     +
        @            dp[7] = 2                       3  @  9    10   
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----+-----+
                                                        |  6  |  7  |
                                                        +-----+-----+
                                                        |        1   
                                                        |     +     +
                                                        |
                                                        |


    We can cache the minimum length of subarrays found in this area as we slide
    the array:

        + For every current subarray arr[start ... end], we pair its length
          with the minimum length cached BEFORE index start.

        + The minimum sum is our final answer.


    For Space Optimization: Since we only need the min length found so far in
                            the area to the left, the entire dp array can be
                            replaced with a single variable.
*/

/* Time  Beats: 81.70% */
/* Space Beats: 67.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target)
    {
        const int N = arr.size();
        int result  = INT_MAX;

        vector<int> dp(N, INT_MAX);

        int start = 0;
        int sum   = 0;

        for (int end = 0; end < N; end++)
        {
            sum += arr[end];

            while (sum > target)
            {
                sum -= arr[start];
                ++start;
            }

            if (sum == target)
            {
                int curr_subarray_len = end - start + 1;

                if (start > 0 && dp[start - 1] != INT_MAX)
                    result = min(result, curr_subarray_len + dp[start - 1]);

                dp[end] = curr_subarray_len;
            }

            if (end > 0)
                dp[end] = min(dp[end], dp[end - 1]);
        }

        return result == INT_MAX ? -1 : result;
    }
};
