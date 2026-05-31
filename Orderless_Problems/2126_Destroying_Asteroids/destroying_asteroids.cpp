/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2126) Destroying Asteroids
    ===========================

    ============
    Description:
    ============

    You are given an integer mass, which represents the original mass of a
    planet. You are further given an integer array asteroids, where
    asteroids[i] is the mass of the ith asteroid.

    You can arrange for the planet to collide with the asteroids in any
    arbitrary order. If the mass of the planet is greater than or equal to the
    mass of the asteroid, the asteroid is destroyed and the planet gains the
    mass of the asteroid. Otherwise, the planet is destroyed.

    Return true if all asteroids can be destroyed. Otherwise, return false.

    ===================================================================
    FUNCTION: bool asteroidsDestroyed(int mass, vector<int> asteroids);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mass = 10, asteroids = [3,9,19,5,21]
    Output: true
    Explanation: One way to order the asteroids is [9,19,5,3,21]:
    - The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
    - The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
    - The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
    - The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
    - The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
    All asteroids are destroyed.

    --- Example 2 ---
    Input: mass = 5, asteroids = [4,9,23,4]
    Output: false
    Explanation: 
    The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
    After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
    This is less than 23, so a collision would not destroy the last asteroid.


    *** Constraints ***
    1 <= mass <= 10^5
    1 <= asteroids.length <= 10^5
    1 <= asteroids[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 89.98% */
/* Space Beats: 81.61% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++'s Intro Sort
class Solution_Sorting {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids)
    {
        const int N = asteroids.size();

        /* Sort in ASCENDING order */
        sort(asteroids.begin(), asteroids.end());

        unsigned long long planet = 1ULL * mass;

        for (int i = 0; i < N; i++)
        {
            if (planet < asteroids[i])
                return false;

            planet += asteroids[i];
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

/* Time  Beats: 100.00% */
/* Space Beats:   8.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Counting_Sort {
public:
    static bool asteroidsDestroyed(int mass, vector<int>& asteroids)
    {
        static constexpr int MAX_ASTEROID_MASS = 1e5;

        unsigned freq[MAX_ASTEROID_MASS + 1] = {0};

        unsigned max_asteroid = 0;
        for (const unsigned& asteroid_mass: asteroids)
        {
            freq[asteroid_mass]++;
            max_asteroid = max(max_asteroid, asteroid_mass);
        }

        unsigned long long planet = 1ULL * mass;

        for (int curr_asteroid = 1; curr_asteroid <= max_asteroid; curr_asteroid++)
        {
            if (freq[curr_asteroid] == 0)
                continue;

            if (planet < curr_asteroid)
                return false;

            planet += 1ULL * curr_asteroid * freq[curr_asteroid];

            freq[curr_asteroid] = 0; // Used all the asteroids with this mass
        }

        return true;
    }
};
