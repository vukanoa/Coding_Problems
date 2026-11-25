/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    593) Valid Square
    ===========================

    ============
    Description:
    ============

    Given the coordinates of four points in 2D space p1, p2, p3 and p4, return
    true if the four points construct a square.

    The coordinate of a point pi is represented as [xi, yi]. The input is not
    given in any order.

    A valid square has four equal sides with positive length and four equal
    angles (90-degree angles).

    ===============================================================================================
    FUNCTION: bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
    Output: true

    --- Example 2 ---
    Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
    Output: false

    --- Example 3 ---
    Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
    Output: true


    *** Constraints ***
    p1.length == p2.length == p3.length == p4.length == 2
    -10^4 <= xi, yi <= 10^4

*/

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 1.54% */
/* Space Beats: 6.43% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:

    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        vector<vector<int>> p = {p1, p2, p3, p4};

        return check_all_permutations(p, 0);
    }

private:
    double dist(vector<int>& p1, vector<int>& p2)
    {
        return (p2[1] - p1[1]) * (p2[1] - p1[1]) +
               (p2[0] - p1[0]) * (p2[0] - p1[0]);
    }

    bool check(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        return dist(p1, p2) > 0 &&
               dist(p1, p2) == dist(p2, p3) &&
               dist(p2, p3) == dist(p3, p4) &&
               dist(p3, p4) == dist(p1, p4) &&
               dist(p1, p3) == dist(p2, p4);
    }

    void swap(vector<vector<int>>& p, int x, int y)
    {
        vector<int> tmp = p[x];
        p[x] = p[y];
        p[y] = tmp;
    }

    bool check_all_permutations(vector<vector<int>>& p, int l)
    {
        if (l == 4)
        {
            if (p[0] == p[1] ||
                p[1] == p[2] ||
                p[2] == p[3] ||
                p[3] == p[0] ||
                p[0] == p[2] ||
                p[1] == p[3])
            {
                return false;
            }

            return check(p[0], p[1], p[2], p[3]);
        }
        else
        {
            bool result = false;

            for (int i = l; i < 4; i++)
            {
                swap(p, l, i);

                result |= check_all_permutations(p, l + 1);

                swap(p, l, i);

                if (result)
                    return true;
            }

            return result;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.50% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        vector<vector<int> > p{p1, p2, p3, p4};

        sort(p.begin(), p.end());

        return dist(p[0], p[1]) != 0                &&
               dist(p[0], p[1]) == dist(p[1], p[3]) &&
               dist(p[1], p[3]) == dist(p[3], p[2]) &&
               dist(p[3], p[2]) == dist(p[2], p[0]) &&
               dist(p[0], p[3]) == dist(p[1], p[2]);
    }

private:
    double dist(vector<int>& p1, vector<int>& p2)
    {
        return (p2[1] - p1[1]) * (p2[1] - p1[1]) +
               (p2[0] - p1[0]) * (p2[0] - p1[0]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.59% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        return check(p1, p2, p3, p4) || check(p1, p3, p2, p4) || check(p1, p2, p4, p3);
    }

private:
    double dist(vector<int>& p1, vector<int>& p2)
    {
        return (p2[1] - p1[1]) * (p2[1] - p1[1]) +
               (p2[0] - p1[0]) * (p2[0] - p1[0]);
    }

    bool check(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        return dist(p1, p2) > 0             &&
               dist(p1, p3) > 0             &&
               dist(p1, p2) == dist(p2, p3) &&
               dist(p2, p3) == dist(p3, p4) &&
               dist(p3, p4) == dist(p4, p1) &&
               dist(p1, p3) == dist(p2, p4);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.06% */
/* Space Beats: 22.88% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        // keep points in an array to be able to get them by index
        vector<vector<int>> points = {p1, p2, p3, p4};
        set<double> lengths;
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = i+1; j < 4; j++)
            {
                double curr = dist(points[i], points[j]);

                // if distance is zero -- we got a duplicated point
                if (curr == 0)
                    return false;

                lengths.insert(curr);
            }
        }

        // We are supposed to end with ONLY TWO different lengths:
        // 1) The sides and
        // 2) The diagonals
        return lengths.size() == 2;
    }

private:
    double dist(vector<int>& p1, vector<int>& p2)
    {
        return sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) +
                    (p2[1] - p1[1]) * (p2[1] - p1[1]));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.52% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_5 {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
        vector<int> d = {dist(p1, p2),
                         dist(p1, p3),
                         dist(p1, p4),
                         dist(p2, p3),
                         dist(p2, p4),
                         dist(p3, p4)};

        /* Sort */
        sort(d.begin(), d.end());

        return d[0] > 0     &&
               d[0] == d[1] &&
               d[1] == d[2] &&
               d[2] == d[3] &&
               d[4] == d[5];
    }

private:
    int dist(vector<int>& a, vector<int>& b)
    {
        int dx = a[0] - b[0];
        int dy = a[1] - b[1];

        return dx * dx + dy * dy;
    }
};
