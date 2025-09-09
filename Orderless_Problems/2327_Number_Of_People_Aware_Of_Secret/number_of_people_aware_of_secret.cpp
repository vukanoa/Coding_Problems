/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2327) Number of People Aware of Secret
    ======================================

    ============
    Description:
    ============

    On day 1, one person discovers a secret.

    You are given an integer delay, which means that each person will share the
    secret with a new person every day, starting from delay days after
    discovering the secret. You are also given an integer forget, which means
    that each person will forget the secret forget days after discovering it.

    A person cannot share the secret on the same day they forgot it, or on any
    day afterwards.

    Given an integer n, return the number of people who know the secret at the
    end of day n. Since the answer may be very large, return it modulo 10^9 + 7

    ================================================================
    FUNCTION: int peopleAwareOfSecret(int n, int delay, int forget);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, delay = 2, forget = 4
    Output: 5
    Explanation:
    Day 1: Suppose the first person is named A. (1 person)
    Day 2: A is the only person who knows the secret. (1 person)
    Day 3: A shares the secret with a new person, B. (2 people)
    Day 4: A shares the secret with a new person, C. (3 people)
    Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
    Day 6: B shares the secret with E, and C shares the secret with F. (5 people)

    --- Example 2 ---
    Input: n = 4, delay = 1, forget = 3
    Output: 6
    Explanation:
    Day 1: The first person is named A. (1 person)
    Day 2: A shares the secret with B. (2 people)
    Day 3: A and B share the secret with 2 new people, C and D. (4 people)
    Day 4: A forgets the secret. B, C, and D share the secret with 3 new people. (6 people)


    *** Constraints ***
    2 <= n <= 1000
    1 <= delay < forget <= n

*/

#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since N=1000 in the Constraints, that immediately means that O(N^2) is an
    acceptable Time Complexity, therefore we should think in that direction.

    We know for each day, when will that person start to spread the secret and
    when will he/she stop(i.e. he/she would forget).

    That means that the number of NEW people who know secret is the difference
    between absolute difference forget and delay. However since "delay" is
    ALWAYS smaller than "forget", as stated in the Constraints, we do not have
    to worry about that.

    Now, at each day where there are new people who got to know the secret,
    for each of them "create" exactly (forget - delay) new people starting from
    day:
        current_day + delay

    However, since there may be more than one person know got the secret TODAY
    we don't want to repeatedly do each person on a given day, we can simply
    use current amont of people as an increment value starting from day:

        current_day + value

    Since we're allowed to have a O(N^2) Time Complexity, we can see that this
    is exactly a O(N^2) Solution, therefore, this is acceptable.

    At the end we ONLY want to count those who didn't forget.
    Bu how can we know that?

    Simple, people who didn't forget begin at day: (n - forget + 1)
    Start adding people who know from that day onwards, until day 'n'.

    At the end return that sum.

*/

/* Time  Beats: 63.37% */
/* Space Beats: 90.84% */

/* Time  Complexity: O(N^2) */ // Acceptable for Constraints where N=1000
/* Space Complexity: O(N)   */
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget)
    {
        const int MOD = 1e9 + 7;

        int days[1001];
        memset(days, 0x00, sizeof(days));

        days[1] = 1; // Number of people who know secret at day x

        for (int i = 1; i <= n; i++)
        {
            int know_today = days[i];

            if (know_today == 0)
                continue;

            int to   = min(n+1, i + forget);
            int from = min(n+1, i + delay);

            int length = to - from;

            while (length > 0)
            {
                days[from] += know_today;
                days[from] %= MOD;

                from++;
                length--;
            }
        }

        // We only care about from (n - forget + 1) onwards, since that is
        // the number of people who did NOT forget secrets
        long long result = 0LL;
        for (int i = n - forget + 1; i <= n; i++)
        {
            result += days[i];
            result %= MOD;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.43% */
/* Space Beats: 91.58% */

/* Time  Complexity: O(N^2) */ // Acceptable for Constraints where N=1000
/* Space Complexity: O(N)   */
class Solution_Memoization {
private:
    const int MOD = 1e9 + 7;
    int memo[1001];

public:
    int peopleAwareOfSecret(int n, int delay, int forget)
    {
        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(n, delay, forget);
    }

private:
    int solve(int limit, int& delay, int& forget)
    {
        if (memo[limit] != -1)
            return memo[limit];

        long long count = (forget >= limit) ? 1 : 0;

        for (int days_since_learned = delay; days_since_learned < min(forget, limit); days_since_learned++)
        {
            count += solve(limit - days_since_learned, delay, forget);
            count %= MOD;
        }

        return memo[limit] = static_cast<int>(count);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.69% */
/* Space Beats: 68.56% */

/* Time  Complexity: O(N^2) */ // Acceptable for Constraints where N=1000
/* Space Complexity: O(N)   */
class Solution_Bottom_Up {
public:
    int peopleAwareOfSecret(int n, int delay, int forget)
    {
        const int MOD = 1e9 + 7;
        vector<int> dp(n + 1, 0);

        for (int curr_day = 0; curr_day <= n; curr_day++)
            dp[curr_day] = (forget >= curr_day) ? 1 : 0;

        for (int curr_day = 0; curr_day <= n; curr_day++)
        {
            for (int days_since_learned = delay; days_since_learned < min(forget, curr_day); days_since_learned++)
            {
                dp[curr_day] += dp[curr_day - days_since_learned];
                dp[curr_day] %= MOD;
            }
        }

        return dp[n];
    }
};
