#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    514) Freedom Trail
    ===========================

    ============
    Description:
    ============

    In the video game Fallout 4, the quest "Road to Freedom" requires players
    to reach a metal dial called the "Freedom Trail Ring" and use the dial to
    spell a specific keyword to open the door.

    Given a string ring that represents the code engraved on the outer ring and
    another string key that represents the keyword that needs to be spelled,
    return the minimum number of steps to spell all the characters in the
    keyword.

    Initially, the first character of the ring is aligned at the "12:00"
    direction. You should spell all the characters in key one by one by
    rotating ring clockwise or anticlockwise to make each character of the
    string key aligned at the "12:00" direction and then by pressing the center
    button.

    At the stage of rotating the ring to spell the key character key[i]:

        + You can rotate the ring clockwise or anticlockwise by one place,
          which counts as one step. The final purpose of the rotation is to
          align one of ring's characters at the "12:00" direction, where this
          character must equal key[i].

        + If the character key[i] has been aligned at the "12:00" direction,
          press the center button to spell, which also counts as one step.
          After the pressing, you could begin to spell the next character in
          the key (next stage). Otherwise, you have finished all the spelling.

    =======================================================
    FUNCTION: int findRotateSteps(string ring, string key);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ring = "godding", key = "gd"
    Output: 4
    Explanation:
    For the first key character 'g', since it is already in place, we just need
    1 step to spell this character.
    For the second key character 'd', we need to rotate the ring "godding"
    anticlockwise by two steps to make it become "ddinggo".
    Also, we need 1 more step for spelling.
    So the final output is 4.


    --- Example 2 ---
    Input: ring = "godding", key = "godding"
    Output: 13



    *** Constraints ***
    1 <= ring.length, key.length <= 100
    ring and key consist of only lower case English letters.
    It is guaranteed that key could always be spelled by rotating ring.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.20% */
/* Space Beats: 94.81% */

/* Time  Complexity: O(??) */
/* Space Complexity: O(??) */
class Solution_Memoization {
public:
    int r, k;

    vector<char> pos[26];
    int dp[200][200];

    int findRotateSteps(string& ring, string& key)
    {
        r = ring.size();
        k = key.size();

        compute_pos(ring);
        fill(&(dp[0][0]), &(dp[0][0]) + 40000, INT_MAX);

        int result = INT_MAX;

        for (int j : pos[key[k-1] - 'a'])
            result = min(result, dfs(k-1, j, ring, key));

        return result;
    }

private:
    void compute_pos(string& ring)
    {
        // Build the array for pos[c - 'a']
        for (int i = 0; i < r; i++)
            pos[ring[i]-'a'].push_back(i);
    }

    int dfs(int i, int j, string& ring, string& key)
    {
        if (i == 0) // Base case
        {
            if (key[i] == ring[j])
                return dp[0][j] = min(j, r-j) + 1;

            return dp[0][j] = 1e9+7;
        }

        if (dp[i][j]!=INT_MAX)
            return dp[i][j];

        int result = 1e9 + 7;

        if (key[i] == ring[j])
        {
            for (int prev : pos[key[i-1] - 'a'])
            {
                int step = abs(prev-j);
                step = min(step, r-step);

                // Update the minimum steps
                result = min(result, dfs(i-1, prev, ring, key) + step+1);
            }
        }

        return dp[i][j] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 97.86% */
/* Space Beats: 81.89% */

/* Time  Complexity: O(??) */
/* Space Complexity: O(??) */
class Solution_Bottom_Up {
public:
    int findRotateSteps(string& ring, string& key)
    {
        vector<int> pos[26];
        const int r = ring.size();
        const int k = key.size();

        for (int i = 0; i < r; i++)
            pos[ring[i] - 'a'].push_back(i);

        int dp[2][200];
        fill(dp[0], begin(dp[0]) + r, INT_MAX);

        for (int p : pos[key[0] - 'a'])
            dp[0][p] = min(p, r-p) + 1;

        for (int i = 1; i < k; i++)
        {
            fill(dp[i&1], begin(dp[i&1]) + r, INT_MAX); //Reset the current row

            for (int j: pos[key[i-1] - 'a'])
            {
                for (int p : pos[key[i] - 'a'])
                {
                    int step = abs(p-j);
                    step = min(step, r-step);

                    dp[i&1][p] = min(dp[i&1][p], dp[(i-1)&1][j] + step+1);
                }
            }
        }

        return *min_element(dp[(k-1) & 1], begin(dp[(k-1) & 1]) + r);
    }
};
