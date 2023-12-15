#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    649) Dota2 Senate
    ===========================

    ============
    Description:
    ============

    In the world of Dota2, there are two parties: the Radiant and the Dire.

    The Dota2 senate consists of senators coming from two parties. Now the
    Senate wants to decide on a change in the Dota2 game. The voting for this
    change is a round-based procedure. In each round, each senator can exercise
    one of the two rights:

        Ban one senator's right: A senator can make another senator lose all
        his rights in this and all the following rounds.  Announce the victory:
        If this senator found the senators who still have rights to vote are
        all from the same party, he can announce the victory and decide on the
        change in the game.

    Given a string senate representing each senator's party belonging. The
    character 'R' and 'D' represent the Radiant party and the Dire party. Then
    if there are n senators, the size of the given string will be n.

    The round-based procedure starts from the first senator to the last senator
    in the given order. This procedure will last until the end of voting. All
    the senators who have lost their rights will be skipped during the
    procedure.

    Suppose every senator is smart enough and will play the best strategy for
    his own party. Predict which party will finally announce the victory and
    change the Dota2 game. The output should be "Radiant" or "Dire".

    ====================================================
    FUNCTION: string predictPartyVictory(string senate);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: senate = "RD"
    Output: "Radiant"
    Explanation:
    The first senator comes from Radiant and he can just ban the next senator's
    right in round 1.  And the second senator can't exercise any rights anymore
    since his right has been banned.  And in round 2, the first senator can
    just announce the victory since he is the only guy in the senate who can
    vote.


    --- Example 2 ---
    Input: senate = "RDD"
    Output: "Dire"
    Explanation:
    The first senator comes from Radiant and he can just ban the next senator's
    right in round 1.  And the second senator can't exercise any rights anymore
    since his right has been banned.  And the third senator comes from Dire and
    he can ban the first senator's right in round 1.  And in round 2, the third
    senator can just announce the victory since he is the only guy in the
    senate who can vote.


    *** Constraints ***
    n == senate.length
    1 <= n <= 10^4
    senate[i] is either 'R' or 'D'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Naive, intuitive approach.

*/

/* Time  Beats: 12.25% */
/* Space Beats:  5.23% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Naive {
public:
    std::string predictPartyVictory(std::string senate)
    {
        int num_rad = 0;
        int num_dir = 0;

        for (char& party : senate)
        {
            if (party == 'R')
                num_rad++;
            else
                num_dir++;
        }

        int ban_rad = 0;
        int ban_dir = 0;

        std::unordered_set<int> uset;
        for (;;)
        {
            for (int i = 0; i < senate.length(); i++)
            {
                if (uset.count(i))
                    continue;

                if (ban_rad > 0 && senate[i] == 'R')
                {
                    ban_rad--;
                    num_rad--;
                    uset.insert(i);
                    continue;
                }
                else if (ban_dir > 0 && senate[i] == 'D')
                {
                    ban_dir--;
                    num_dir--;
                    uset.insert(i);
                    continue;
                }

                if (senate[i] == 'R' && num_dir == 0)
                    return "Radiant";
                else if (senate[i] == 'D' && num_rad == 0)
                    return "Dire";

                if (senate[i] == 'R')
                    ban_dir++;
                else
                    ban_rad++;
            }
        }

        return "Radiant"; // Or "Dire" it's irrelevant
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We will use a two queue approach.
    Recall, each senator has a position to exercise their right.

    The ones to the left have an earlier turn than the ones to the right.
    radiants is queue that holds all positions of active senators in "Radiant"
    dires    is queue that holds all positions of active senators in "Dire".

    Active being that they still have the right to vote.
    Our queue will be ordered so that the senators with earlier voting power
    come first (to the left, front, of the queue).

    To goal is to have the earliest senator of each queue fight each other to
    see who gets to eliminate the other depending on their position.

    Obviously, the one with the earlier position will win.
    The loser is removed from the queue since they are no longer active.

    The winner will go to the end of the queue for the next round.
    We keep doing this until one queue is empty which means there are no more
    senators on the team.


    Let's look at an example:

    senate = "R D D R D R R D R"
              0 1 2 3 4 5 6 7 8

    First, let's insert each senator into their respective queues
    Each are uniquely identified by their indexes

    Queues:
        radians: [0, 4, 6, 7, 9]
                  ^
                  |
                front
                  |
                  v
        dires:   [1, 2, 3, 5, 8]


    We will use the size of the senate n = 10 as an index to increment our
    senate positions as the rounds go on.


    Queues: n = 10
        radians: [0, 4, 6, 7, 9]
                  ^
                  |
                front  (Fight!)
                  |
                  v
        dires:   [1, 2, 3, 5, 8]

        Since radiant's senator has a lower index, it beats the dires' senator.

        Dires' senator is eliminated while radiant's senator moves onto the
        next round by going to the end of the queue with its next index 10, in
        this case.


    Queues: n = 11  <-- n is incremented since each senator gets a unique index
        radians: [4, 6, 7, 9, 10]
                  ^
                  |
                front  (Fight!)
                  |
                  v
        dires:   [2, 3, 5, 8]

        This time dire's senator wins so radiant's senator is eliminated and
        dire's senator goes to the end of the queue with index 11 now.

    Queues: n = 12
        radians: [6, 7, 9, 10]
                  ^
                  |
                front  (Fight!)
                  |
                  v
        dires:   [2, 3, 5, 8, 11]

    ...
    ...
    ...

    Queues: n = 16
        radians: [15]
                  ^
                  |
                front  (Fight!)
                  |
                  v
        dires:   [12, 13, 14]

        After this fight, dir wins and radiant's queue become empty.
        Thus we know dires must be winners!

*/

/* Time  Beats: 85.16% */
/* Space Beats: 31.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string predictPartyVictory(std::string senate)
    {
        std::queue<int> radiants;
        std::queue<int> dires;

        int n = senate.length();
        for (int i = 0; i < n; i++)
        {
            if (senate[i] == 'R')
                radiants.push(i);
            else
                dires.push(i);
        }

        while (!radiants.empty() && !dires.empty())
        {
            if (radiants.front() < dires.front())
                radiants.push(n++);
            else
                dires.push(n++);

            dires.pop();
            radiants.pop();
        }

        return dires.empty() ? "Radiant" : "Dire";
    }
};
