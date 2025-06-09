/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    3577) Count the Number of Computer Unlocking Permutations
    =========================================================

    ============
    Description:
    ============

    You are given an array complexity of length n.

    There are n locked computers in a room with labels from 0 to n - 1, each
    with its own unique password. The password of the computer i has a
    complexity complexity[i].

    The password for the computer labeled 0 is already decrypted and serves as
    the root. All other computers must be unlocked using it or another
    previously unlocked computer, following this information:

        You can decrypt the password for the computer i using the password for
        computer j, where j is any integer less than i with a lower complexity.
        (i.e. j < i and complexity[j] < complexity[i]) To decrypt the password
        for computer i, you must have already unlocked a computer j such that j
            < i and complexity[j] < complexity[i].

    Find the number of permutations of [0, 1, 2, ..., (n - 1)] that represent a
    valid order in which the computers can be unlocked, starting from computer
    0 as the only initially unlocked one.

    Since the answer may be large, return it modulo 109 + 7.

    =====
    Note: that the password for the computer with label 0 is decrypted, and not
          the computer with the first position in the permutation.
    =====

    =========================================================
    FUNCTION: int countPermutations(vector<int>& complexity);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: complexity = [1,2,3]
    Output: 2
    Explanation:
    The valid permutations are:
        [0, 1, 2]
            Unlock computer 0 first with root password.
            Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
            Unlock computer 2 with password of computer 1 since complexity[1] < complexity[2].
        [0, 2, 1]
            Unlock computer 0 first with root password.
            Unlock computer 2 with password of computer 0 since complexity[0] < complexity[2].
            Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].


    --- Example 2 ---
    Input: complexity = [3,3,3,4,4,4]
    Output: 0
    Explanation:
    There are no possible permutations which can unlock all computers.


    *** Constraints ***
    2 <= complexity.length <= 10^5
    1 <= complexity[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is easy ONLY IF YOU NOTICE the following:

    Since the password at 0th index is the one that is already decrypted, then
    if that element is not THE SMALLEST element in the entire array, then you
    won't be able to decrypt all of them, therefore you return 0.

    Examples:

        [4, 1, 3, 2, 5, 7, 8]
         ^
         |
      decrypted already


    Question: How are you going to unlock 1, 2 and 3?
    You won't. It's impossible. Therefore you return 0.


    However, if at the 0th index is indeed the smallest value:

        [1, 2, 4, 3, 5, 7, 8]
         ^
         |
      decrypted already


    You can decrypt ALL of them, irrespective of the order in which you do so.


    Remember the Description of the problem:
        To decrypt the password for computer i, you must have already unlocked
        a computer j such that j < i and complexity[j] < complexity[i].


    since j == 0 and complexity[j] is the SMALLEST, then that means we can
    unlock ALL THE OTHER IRRESPECTIVE OF THE ORDER.


    Therefore, correct orders are all the permutations of the last N-1
    elements.


    It's as simple as that, but you have to notice this.

*/

/* Time  Beats: 27.27% */
/* Space Beats:  9.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    vector<long long> memo;
    const int MOD = 1e9 + 7;

public:
    int countPermutations(vector<int>& complexity)
    {
        const int N = complexity.size();
        memo.assign(N, -1);

        int smallest_value = complexity[0];
        for (int i = 1; i < N; i++)
        {
            if (complexity[i] <= smallest_value)
                return 0;
        }

        return factorial(N-1) % MOD;
    }

private:
    long long factorial(int n)
    {
        if (n == 0 || n == 1)
            return 1;

        if (memo[n] != -1)
            return memo[n];

        memo[n] = (n * factorial(n - 1)) % MOD;

        return memo[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's equivalent to the above Solution, however here we don't actually need
    to use Memoization to calculate Factorials, in this problem we can simply
    multiply all the elements' indices from [1, n-1].

    It's important to see this explicitly like this so that you're aware of it
    even if it seem trivial and obvious.

    It's a much more concise and straightforward way to implement it and it's
    much faster for implementation, however it is good that you're able to
    write Memoization version of factorial calculation.


    Also, with this approach, we're saving N space, which is indeed better.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Optimized {
private:
    const int MOD = 1e9 + 7;

public:
    int countPermutations(vector<int>& complexity)
    {
        const int N = complexity.size();
        long long result = 1;

        for (int i = 1; i < N; i++)
        {
            if (complexity[i] <= complexity[0])
                return 0;

            result *= i;
            result %= MOD;
        }

        return result;
    }
};
