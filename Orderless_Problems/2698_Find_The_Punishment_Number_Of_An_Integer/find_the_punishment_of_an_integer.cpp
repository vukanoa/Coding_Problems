/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2698) Find the Punishment of an Integer
    =======================================

    ============
    Description:
    ============


    Given a positive integer n, return the punishment number of n.

    The punishment number of n is defined as the sum of the squares of all
    integers i such that:

        1 <= i <= n

        The decimal representation of i * i can be partitioned into contiguous
        substrings such that the sum of the integer values of these substrings
        equals i.

    ======================================
    FUNCTION: int punishmentNumber(int n);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 182
    Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
    - 1 since 1 * 1 = 1
    - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
    - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
    Hence, the punishment number of 10 is 1 + 81 + 100 = 182

    --- Example 2 ---
    Input: n = 37
    Output: 1478
    Explanation: There are exactly 4 integers i in the range [1, 37] that satisfy the conditions in the statement:
    - 1 since 1 * 1 = 1.
    - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 + 1.
    - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 + 0.
    - 36 since 36 * 36 = 1296 and 1296 can be partitioned into 1 + 29 + 6.
    Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478


    *** Constraints ***
    1 <= n <= 1000

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization. While this is a "classic Memoization problem", you
    should NOT learn Memoization on this proble.

    Check other Memoization problems, learn it and them come back to read the
    code of this one.

*/

/* Time  Beats: 9.07% */
/* Space Beats: 7.81% */

/*
    Time  Complexity: O(N * 2^(log10(N)))

    We iterate through n integers only once. For each integer, we recursively
    traverse all the possible ways to split the number. The number of recursion
    calls is dependent on how many times we have to partition a number, n. This
    is proportional to the number of digits in the squared number, which can be
    calculated as log10(n^2), or simply log10(n).

    At each digit, we are given the option to either break a partition or
    continue adding to the partition, giving us 2 options at each digit. The
    number of times we have to make this decision to exhaust all possible
    options is proportional to the number of digits in the squared number.
    As a result, this leads to a time complexity for the recursive function of
    O(2^(log10(n))).

    Since we iterate through this process n times, we multiply this time
    complexity by a factor of n. This leads to an overall time complexity of
    O(n⋅2^(log10(n))).

*/
/*
    Space Complexity: O(N * log10(N) + log10(N))

    The space complexity is determined by the memo array and recursion stack.

    The depth of the recursion stack is proportional to the current integer.
    In the worst case, a recursive call can continue until each digit is
    explored individually in a partition.

    As a result, the maximum size of the stack is proportional to the number of
    digits in the squared number, which can be calculated as log10(n^2).
    This leads to a time complexity for the recursive stack of O(log10(n^2)),
    which can be simplified to O(log10(n)).

    As for the memo array, its size equals the number of digits that can be
    explored, multiplied by the number of potential values for n, to store all
    possible permutations. As a result, this creates a space complexity of
    O(n * log10(n)).

    Combining these data structures, the overall space complexity of the
    solution is O(n * log10(n) + log10(n))

*/
class Solution {
public:
    int punishmentNumber(int n)
    {
        int punishment_num = 0;

        // Iterate through numbers in range [1, n]
        for (int curr_num = 1; curr_num <= n; curr_num++)
        {
            int square_num = curr_num * curr_num;
            string string_num = to_string(square_num);

            vector<vector<int>> memo(string_num.size(), vector<int>(curr_num + 1, -1));

            if (find_partitions(0, 0, string_num, curr_num, memo))
                punishment_num += square_num;
        }

        return punishment_num;
    }

private:
    bool find_partitions(int start_idx, int sum, string string_num, int target, vector<vector<int>>& memo)
    {
        if (start_idx == string_num.size())
            return sum == target;

        if (sum > target)
            return false;

        if (memo[start_idx][sum] != -1)
            return memo[start_idx][sum];

        bool partition_found = false;

        for (int curr_idx = start_idx; curr_idx < string_num.size(); curr_idx++)
        {
            string curr_str = string_num.substr(start_idx, curr_idx - start_idx + 1);
            int addend = stoi(curr_str);

            if ( ! partition_found)
                partition_found = find_partitions(curr_idx + 1, sum + addend, string_num, target, memo);

            if (partition_found == true)
                return true;
        }

        return memo[start_idx][sum] = partition_found;
    }
};
