/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    2145) Count the Hidden Sequences
    ================================

    ============
    Description:
    ============

    You are given a 0-indexed array of n integers differences, which describes
    the differences between each pair of consecutive integers of a hidden
    sequence of length (n + 1). More formally, call the hidden sequence hidden,
    then we have that differences[i] = hidden[i + 1] - hidden[i].

    You are further given two integers lower and upper that describe the
    inclusive range of values [lower, upper] that the hidden sequence can
    contain.

        For example, given differences = [1, -3, 4], lower = 1, upper = 6, the
        hidden sequence is a sequence of length 4 whose elements are in between
        1 and 6 (inclusive).
            [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.

            [5, 6, 3, 7] is not possible since it contains an element greater
                         than 6.

            [1, 2, 3, 4] is not possible since the differences are not correct.

    Return the number of possible hidden sequences there are. If there are no
    possible sequences, return 0.

    =============================================================================
    FUNCTION: int numberOfArrays(vector<int>& differences, int lower, int upper);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: differences = [1,-3,4], lower = 1, upper = 6
    Output: 2
    Explanation: The possible hidden sequences are:
    - [3, 4, 1, 5]
    - [4, 5, 2, 6]
    Thus, we return 2.

    --- Example 2 ---
    Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
    Output: 4
    Explanation: The possible hidden sequences are:
    - [-3, 0, -4, 1, 2, 0]
    - [-2, 1, -3, 2, 3, 1]
    - [-1, 2, -2, 3, 4, 2]
    - [0, 3, -1, 4, 5, 3]
    Thus, we return 4.

    --- Example 3 ---
    Input: differences = [4,-7,2], lower = 3, upper = 6
    Output: 0
    Explanation: There are no possible hidden sequences. Thus, we return 0.


    *** Constraints ***
    n == differences.length
    1 <= n <= 10^5
    -10^5 <= differences[i] <= 10^5
    -10^5 <= lower <= upper <= 10^5

*/

#include <climits>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one is not very difficult.

    Since we need to make ALL of the differences "fit" within [lower, upper]
    that just means: Try to find the biggest difference between the lowest
    point at any time and highest point at any time.

    That the "diff" will be: highest_point - lower_point

    Then see how many of these "diff" can you fit in [lower, upper]

    Example:
        Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5

    Let's see it on the y-axis of the coordinate system:

        ^
      7 |
      6 |
      5 |           X
      4 |        X
      3 |  X           X
      2 |
      1 |
      0 ---1--2--3--4--5-- -------------------------->
     -1 |     X
     -2 |
     -3 |
     -4 |
        V


    So,
        1) The lowest  point(if we start at 0) is -1
        2) The highest point(if we start at 0) is +4


    That means the diff is +4 - (-1) = +4 + 1 = +5

    However, our [lower, upper] is [-4, 5]

    Since our range is of size: +5 - (-4) + 1 = +5 + 4 + 1 = 10
    But why "+1"?

    Because imagine the the "diff"(difference between highest and lowest point)
    is 3 and that the range between [lower, upper] is also 3.

    Does that mean we cannot fit it at all?
    No. Obviously we CAN fit it ONCE.

    Therefore, that ONE is additional and that's why we add "+1".


    Now if the range range(i.e. (upper - lower + 1)) is LESS than "diff", then
    that means we CANNOT fit it in not even once, therefore we return 0.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper)
    {
        const int N = differences.size();

        long long maxx = 0;
        long long minn = 0;

        long long point = 0;
        for (int i = 0; i < N; i++)
        {
            point += differences[i];

            maxx = max(maxx, point);
            minn = min(minn, point);
        }

        int diff   = maxx - minn;
        int bounds = upper - lower + 1;

        return (bounds < diff) ? 0 : bounds - diff;
    }
};
