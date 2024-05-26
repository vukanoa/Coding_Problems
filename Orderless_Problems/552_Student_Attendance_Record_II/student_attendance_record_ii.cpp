#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =================================
    552) Student Attendance Record II
    =================================

    ============
    Description:
    ============

    An attendance record for a student can be represented as a string where
    each character signifies whether the student was absent, late, or present
    on that day. The record only contains the following three characters:

        'A': Absent.
        'L': Late.
        'P': Present.

    Any student is eligible for an attendance award if they meet both of the
    following criteria:

        The student was absent ('A') for strictly fewer than 2 days total.
        The student was never late ('L') for 3 or more consecutive days.

    Given an integer n, return the number of possible attendance records of
    length n that make a student eligible for an attendance award. The answer
    may be very large, so return it modulo 109 + 7.

    =================================
    FUNCTION: int checkRecord(int n);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 8
    Explanation: There are 8 records with length 2 that are eligible for an
    award: "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL" Only "AA" is not
    eligible because there are 2 absences (there need to be fewer than 2).


    --- Example 2 ---
    Input: n = 1
    Output: 3


    --- Example 3 ---
    Input: n = 10101
    Output: 183236316


    *** Constraints ***
    1 <= n <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    Okay, so first thing that come up in my mind is just recursion and this
    approach is quite simple.

        + We will start from the empty string and each time we will choose
          which character to add.

        + We don't want to pass the string into the function because all we
          interested in is just how many consecutive "L" we have so far and how
          many "A" already in the string.

        + We want to call recursion with this rules
            + If we reached the end of the string we want to return result
              (this string is eligable because of steps I describe below)

            + On every recursion we will call recursion with every of three
              characters but only if this string will be eligable after we add
              this new character (So, if there's already 1 "A" we can't add
              another of if there's already 2 consecutive "L" we can't add
              another)

            + We will find the sum of all callings and return it

        + This is sufficient to write code for this approach but there's some
          interesting things I want to mention:

            + Recursion without memoization will give TLE because we
            recalculate many states wich we've seen already. As was said every
            state is defined only by 3 parameters: cur_ind, count_a, count_l

            + I have no idea why but tmp[cur_ind][count_a][count_l] is much
              faster than tmp[cur_ind][count_l][count_a].

            + If you don't take the mod on this step: total: int = (with_a_next
              + with_l_next + with_p_next) % MOD you will get MLE error.

*/

/* Time  Beats: 19.25% */
/* Space Beats: 38.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursion_with_Memoization {
public:
    static const int MOD = 1000000007;

    int checkRecord(int n)
    {
        std::vector<std::vector<std::vector<int>>> tmp(n, std::vector<std::vector<int>>(2, std::vector<int>(3, -1)));
        return check_all_records(0, 0, 0, n, tmp);
    }

private:
    int check_all_records(int curr_ind,
                          int count_a,
                          int count_l,
                          int n,
                          std::vector<std::vector<std::vector<int>>>& tmp)
    {
        if (curr_ind == n)
            return 1;

        if (tmp[curr_ind][count_a][count_l] != -1)
            return tmp[curr_ind][count_a][count_l];

        int with_a_next = (count_a == 0) ? check_all_records(curr_ind + 1, count_a + 1, 0, n, tmp) : 0;
        int with_l_next = (count_l == 2) ? 0 : check_all_records(curr_ind + 1, count_a, count_l + 1, n, tmp);
        int with_p_next = check_all_records(curr_ind + 1, count_a, 0, n, tmp);

        int total = ((with_a_next + with_l_next) % MOD + with_p_next) % MOD;

        tmp[curr_ind][count_a][count_l] = total;
        return total;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    After my recursive solution was accepted I thinked about whether there's
    more optimized approach and here is is - Dynamic Programming (DP)

        + As was said every state is defined only by count_a, count_l and
          cur_ind.

        + But what we can see that for cur_ind we always check in memo for
          cur_ind - 1 so on step when we calculated all states for cur_ind=3 we
          don't care about others cur_ind which are lower.

        + So let's say we have step with cur_ind=n how we will calculate states
          for it knowing all states for cur_ind=n-1?

            + We want to iterate trough every legal combination from
              cur_ind=n-1 of count_a and count_l so (0, 0), (0, 1), (0, 2) and
              (1, 0), (1, 1), (1, 2) and for every this state we want to try to
              add "A", "P" and "L" if this possible and add this result to the
              state with cur_ind=n

            + On every adding we want to add modulo by MOD to avoid MLE
              (described above)

            + On every iteration we copy current state to previous and reset it

        + After we calculated dp n times our result is stored in dp_last so we
          just need to sum up every possible state and return the result

*/

/* Time  Beats: 10.86% */
/* Space Beats: 22.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Dynamic_Programming {
public:
    int checkRecord(int n)
    {
        const int MOD = 1000000007;

        std::vector<std::vector<int>> dp_last   (2, std::vector<int>(3, 0)); // previous state
        std::vector<std::vector<int>> dp_current(2, std::vector<int>(3, 0)); // current  state

        dp_last[0][0] = 1; // empty string

        for (int i = 0; i < n; i++)
        {
            for (int count_a = 0; count_a < 2; count_a++)
            {
                for (int count_l = 0; count_l < 3; count_l++)
                {
                    // choose "P"
                    dp_current[count_a][0] = (dp_current[count_a][0] + dp_last[count_a][count_l]) % MOD;

                    // choose "A"
                    if (count_a == 0)
                        dp_current[count_a + 1][0] = (dp_current[count_a + 1][0] + dp_last[count_a][count_l]) % MOD;

                    // Choose "L"
                    if (count_l < 2)
                        dp_current[count_a][count_l + 1] = (dp_current[count_a][count_l + 1] + dp_last[count_a][count_l]) % MOD;
                }
            }

            dp_last = dp_current; // Reference current to previous
            dp_current = vector<vector<int>>(2, vector<int>(3, 0)); // make new current
        }

        // Sum up the counts for all combinations of length 'n' with different count_a and count_l
        int result = 0;
        for (int count_a = 0; count_a < 2; count_a++)
        {
            for (int count_l = 0; count_l < 3; count_l++)
                result = (result + dp_last[count_a][count_l]) % MOD;
        }

        return result;
    }
};
