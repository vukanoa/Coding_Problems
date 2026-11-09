/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    4026) Maximum Gap Between Stations
    ==================================

    ============
    Description:
    ============

    You are given two strings skill and station of lengths n and m, respectively.

    skill[i] represents the skill of worker i, and station[j] represents the
    skill supported by station j.

    You must assign every worker to a distinct station. Let ji be the index of
    the station assigned to worker i. A valid assignment must satisfy:

        + station[ji] == skill[i] for every 0 <= i < n.

        + The assigned station indices must be strictly increasing in worker
          order, meaning j0 < j1 < ... < jn - 1.

    The gap of an assignment is the maximum difference between the station
    indices assigned to two consecutive workers. In other words, it is max(ji -
    ji - 1) over all 1 <= i < n.

    If there is only one worker, the gap is 0.

    Return the maximum possible gap among all valid assignments. It is
    guaranteed that at least one valid assignment exists.

    =======================================================
    FUNCTION: int maximumGap(string skill, string station);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: skill = "aa", station = "aaaa"
    Output: 3
    Explanation:
        The two workers must be assigned to two different 'a' stations.
        Assigning them to stations [0, 3] gives a gap of 3.

    --- Example 2 ---
    Input: skill = "xyz", station = "xyzz"
    Output: 2
    Explanation:
        Assign worker 0 to station j = 0, and worker 1 to station j = 1.
        To maximize the gap, assign worker 2 to station j = 3.
        This gives the assignment [0, 1, 3] with gaps [1, 2], so the gap is 2.

    --- Example 3 ---
    Input: skill = "cbc", station = "cbcdbc"
    Output: 4
    Explanation:
        Assign worker 0 to station j = 0, and worker 1 to station j = 1.
        To maximize the gap, assign worker 2 to station j = 5.
        This gives the assignment [0, 1, 5] with gaps [1, 4], so the gap is 4.


    *** Constraints ***
    skill.length == n
    station.length == m
    1 <= n <= m <= 10^5
    skill and station consist of lowercase English letters.
    It is guaranteed that a valid assignment exists for every worker.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The key here is to realize that if there are, say, 4 'c' characters in our
    input string skill, then since each worker has to be assigned a station
    index that is GREATER that ALL of the previous workers, we realize that
    for each worker there is an earliest and latest possible indices it can
    occupy.

    Let's look at an example:

        skill = "cbcaabcbc"               station = "caaabbccacbcacxcgcfcvc"
                 012345678                           ^     ^^ ^ ^ ^ ^ ^ ^ ^ 
                 ^ ^   ^ ^                           |     || | | | | | | |
                 | |   | |                           |     || | | | | | | |
                 |_|_ _|_|                           |__ __||_|_|_|_|_|_|_|
                     |                                  | 
               ______|                          ________|
              |                                |
    There are 4 'c' characters, but there are 10 stations of character 'c'.


    Indices of stations for character 'c' are: {0,6,7,9,11,13,15,17,19,21}

    It's VERY important NOT to forget that each worker needs to be assigned a
    station with a GREATER index than ALL of the workers before.

    So, since there are 4 'c' characters, the EARLIEST station index that the
    first 'c' character {ie. 0th 'c') can be assigned to is 0th station.

        "cccc"    {0,6,7,9,11,13,15,17,19,21}
         0123      ^
         ^         |
         |_________|

    But what is the LATEST?
    Can we simply assign the (station_index = 21) to it?

    NO!!!
    Why not?

    Because if we do that, then the REMAINING 3 'c' characters will NOT be
    assigned ANY station since they MUST have GREATER station indices than the
    'c' characters that come before them.

    So if we immeditely take the greatest station idx for 'c' character, then
    none of the remaining 'c' characters will be able to have a station.

    So that's forbidden.
    So, what do we do?

    We have to determine the LATEST station index for each 'c' character (and
    other characters within their own set of station indices).

    What is the LATEST index that the first 'c' character (i.e. 0th 'c') can be
    assigned at?

    It's the:

        last_c_station_idx - remaining_c_characters_after_this_one


    Since we're currently dealing with the FIRST (i.e. 0th 'c') character:

        "cccc"    {0,6,7,9,11,13,15,17,19,21}
         0123      0 1 2 3  4  5  6  7  8  9
         ^
         |


    and there are 3 REMAINING 'c' characters, then the LATEST POSSIBLE station
    index for this 0th 'c' character is:
    
        (9 - remaining_c_characters) <==> (9 - 3) = 6
           ________|               _________________|
          |||                     |
          vvv                     v
        "cccc"    {0,6,7,9,11,13,15,17,19,21}
         0123      0 1 2 3  4  5  6  7  8  9


    Once we do that for EVERY of the N skills, we simply start at index 1 and
    check whether the current gap is the maximum one.

    Current gap would be: Take the LATEST POSSIBLE of current skill and the
                          EARLIEST POSSIBLE of the previous skill. 

*/

class Solution {
public:
    int maximumGap(string skill, string station)
    {
        const int N = skill.size();
        const int M = station.size();
        int result = 0;

        vector<int> earliest(N); // Earliest station for worker [0..N-1]
        vector<int> latest(N);   // Latest   station for worker [0..N-1]

        /* Assign EARLIEST possible STATION for every worker */
        int j = 0;
        for (int i = 0; i < N; i++)
        {
            while (station[j] != skill[i])
                j++;

            earliest[i] = j;
            j++;
        }

        /* Assign LATEST possible STATION for every worker */
        j = M-1;
        for (int i = N-1; i >= 0; i--)
        {
            while (station[j] != skill[i])
                j--;

            latest[i] = j;
            j--;
        }

        /* Take the MAXIMUM POSSIBLE gap */
        for (int i = 1; i < N; i++)
            result = max(result, latest[i] - earliest[i-1]);

        return result;
    }
};
