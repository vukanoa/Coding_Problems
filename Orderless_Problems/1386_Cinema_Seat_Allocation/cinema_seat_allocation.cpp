/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    1386) Cinema Seat Allocation
    ============================

    ============
    Description:
    ============

    A cinema has n rows of seats, numbered from 1 to n. Each row has 10 seats,
    numbered from 1 to 10.

    You are given a 2D integer array reservedSeats, where reservedSeats[i] =
    [rowi, seati] means that seat seati in row rowi is already reserved.

    A four-person group must be assigned to four seats in the same row. The
    group can be seated in one of the following seat blocks:

        seats 2, 3, 4, 5
        seats 4, 5, 6, 7
        seats 6, 7, 8, 9

    A block can be used only if none of its seats are reserved. Each seat can
    be assigned to at most one group.

    Return an integer denoting the maximum number of four-person groups that
    can be assigned.

    =============================================================================
    FUNCTION: int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
    Output: 4
    Explanation: The figure above shows an optimal allocation of four groups.
                 Seats marked in blue are already reserved, and each set of
                 four contiguous seats marked in orange is assigned to one
                 group.

    --- Example 2 ---
    Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
    Output: 2

    --- Example 3 ---
    Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
    Output: 4


    *** Constraints ***
    1 <= n <= 10^9
    1 <= reservedSeats.length <= min(10 * n, 10^4)
    reservedSeats[i] == [rowi, seati]
    1 <= rowi <= n
    1 <= seati <= 10
    All reservedSeats[i] are distinct.

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.06% */
/* Space Beats: 93.41% */

/* Time  Complexity: O(M * logM) */
/* Space Complexity: O(logM)     */ // Space of C++'s Intro Sort
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats)
    {
        const int M = reservedSeats.size();
        int result = 0;

        int left  = 0;
        int right = 0;

        int prev_row = 0;

        /* SOrt in ASCENDING order */
        sort(reservedSeats.begin(), reservedSeats.end());

        bool reserved_seats[11] = {false};
        while (right < M)
        {
            // Count rows with NO reservations
            result += 2 * (reservedSeats[right][0] - prev_row - 1);

            prev_row = reservedSeats[right][0];

            // Mark all reserved seats in the current row
            while (right < M && reservedSeats[left][0] == reservedSeats[right][0])
            {
                reserved_seats[reservedSeats[right][1]] = true;
                right++;
            }

            const bool seats_2_to_5 = check(reserved_seats, 2, 5);
            const bool seats_4_to_7 = check(reserved_seats, 4, 7);
            const bool seats_6_to_9 = check(reserved_seats, 6, 9);

            if (seats_2_to_5 && seats_6_to_9)
                result += 2;
            else if (seats_2_to_5 || seats_4_to_7 || seats_6_to_9)
                result++;

            left = right;

            // Reset for the next row
            fill(reserved_seats, reserved_seats + 11, false);
        }

        // Remaining rows are completely empty
        result += 2 * (n - prev_row);

        return result;
    }

private:
    bool check(bool* reserved_seat, int left, int right)
    {
        for (int i = left; i <= right; i++)
        {
            if (reserved_seat[i])
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 80.74% */
/* Space Beats: 78.38% */

/* Time  Complexity: O(M) */
/* Space Complexity: O(M) */
class Solution_Bitset {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats)
    {
        const int M = reservedSeats.size();

        int left   = 0b11110000;
        int middle = 0b11000011;
        int right  = 0b00001111;

        unordered_map<int, int> occupied;

        for (const vector<int>& entry : reservedSeats)
        {
            const int& row  = entry[0];
            const int& seat = entry[1];

            if (seat >= 2 && seat <= 9)
                occupied[row] |= (1 << (seat - 2));
        }

        int result = (n - occupied.size()) * 2;

        for (auto& [row, bitmask] : occupied)
        {
            if (((bitmask | left)   == left)   ||
                ((bitmask | middle) == middle) ||
                ((bitmask | right)  == right))
            {
                ++result;
            }
        }

        return result;
    }
};
