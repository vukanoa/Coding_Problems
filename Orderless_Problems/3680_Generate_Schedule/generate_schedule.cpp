/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3680) Generate Schedule
    ===========================

    ============
    Description:
    ============

    You are given an integer n representing n teams. You are asked to generate
    a schedule such that:

        + Each team plays every other team exactly twice: once at home and once
          away.

        + There is exactly one match per day; the schedule is a list of
          consecutive days and schedule[i] is the match on day i.

        + No team plays on consecutive days.

    Return a 2D integer array schedule, where schedule[i][0] represents the
    home team and schedule[i][1] represents the away team. If multiple
    schedules meet the conditions, return any one of them.

    If no schedule exists that meets the conditions, return an empty array.

    ======================================================
    FUNCTION: vector<vector<int>> generateSchedule(int n);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3
    Output: []
    Explanation:
    Since each team plays every other team exactly twice, a total of 6 matches
    need to be played: [0,1],[0,2],[1,2],[1,0],[2,0],[2,1].
    It's not possible to create a schedule without at least one team playing
    consecutive days.

    --- Example 2 ---
    Input: n = 5
    Output: [[0,1],[2,3],[0,4],[1,2],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[2,0],[3,1],[4,0],[2,1],[4,3],[1,0],[3,2],[4,1],[3,0],[4,2]]
    Explanation:
    Since each team plays every other team exactly twice, a total of 20 matches
    need to be played.
    The output shows one of the schedules that meet the conditions. No team
    plays on consecutive days.


    *** Constraints ***
    2 <= n <= 50

*/

#include <algorithm>
#include <random>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    At first, I thought I can just be greedy -- List all of the matches and
    pick the next match that doesn't have repeating team.

    However, this is unacceptable, even for small Constraints like these.

    But why doesn't this work exactly?

    With two loops where each goes from 0 to n, we'll pick matches with team 0
    much more often at the start and that'll leave us with a bunch of n-1
    team's matches that can't be picked all in consecutive days.


    But this creates a question -- What if all of the matches are EVENLY
    distributed?

    What do you mean "evenly distributed"? How in the world are you going to
    EVENLY distribute them?

    Well, it doesn't have to be truly EVEN, but it needs to be ordered in such
    a way that the searching for the next available match is acceptable.

    Is there a way for us to do that?
    It turns out that for these Constraints, there is -- Shuffle.

    Loop until we find a valid match:
        1. Shuffle the matches and then greedily pick the next valid match
           (i.e. the one match that doesn't have a repeating team).

        2. If we cannot find  a valid next match, then Loop again.

        3. If we have found a valid next match -- Return the schedule



    You may ask yourself about the chances of finding a valid schedule with the
    shuffle-and-greedy approach -- Will it take forever to find a valid
    schedule?


    Let's look at what the Math says:

        + Total number of matches: n * (n-1)

            Since each team has to play every other team twice, it's:
                2 * C(n, 2)

        + Number of matches per team: 2 * (n - 1)

            There are exactly (n-1) opponents and 2 means you play each twice.



    If we divide the total_number_of_matches with number_of_matches_per_team,
    we get: n / 2.


    This means that on average each team has to play a match every n/2 days.

    Therefore, if there are more teams, the matches for each team are more far
    apart, making scheduling the matches much easier.

    This also explains why there's no valid schedule for n <= 4.

*/

/* Time  Beats: 27.57% */
/* Space Beats: 24.09% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<vector<int>> generateSchedule(int n)
    {
        if (n <= 4)
            return {};

        // Generate all matches (directed pairs)
        vector<vector<int>> all_matches;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                all_matches.push_back( {i, j} );
            }
        }

        vector<vector<int>> final_schedule;
        vector<vector<int>> shuffled_matches;
        bool valid_schedule_found = false;

        // Random generator for shuffle
        random_device rd;
        mt19937 rng(rd());

        // Keep shuffling until a valid schedule is found
        while ( ! valid_schedule_found)
        {
            shuffled_matches = all_matches;
            shuffle(shuffled_matches.begin(), shuffled_matches.end(), rng);

            vector<vector<int>> current_schedule;

            for (int match_idx = 0; match_idx < static_cast<int>(all_matches.size()); match_idx++)
            {
                bool match_found = false;

                for (int candidate_idx = 0; candidate_idx < (int)shuffled_matches.size(); candidate_idx++)
                {
                    int player_a = shuffled_matches[candidate_idx][0];
                    int player_b = shuffled_matches[candidate_idx][1];

                    if (current_schedule.empty() ||
                        (player_a != current_schedule.back()[0] &&
                         player_a != current_schedule.back()[1] &&
                         player_b != current_schedule.back()[0] &&
                         player_b != current_schedule.back()[1]))
                    {
                        current_schedule.push_back(shuffled_matches[candidate_idx]);
                        shuffled_matches.erase(shuffled_matches.begin() + candidate_idx);
                        match_found = true;
                        break;
                    }
                }

                if ( ! match_found)
                    break;
            }

            if (static_cast<int>(current_schedule.size()) == static_cast<int>(all_matches.size()))
            {
                final_schedule = current_schedule;
                valid_schedule_found = true;
            }
        }

        return final_schedule;
    }
};
