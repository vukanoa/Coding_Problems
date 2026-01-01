/*
    ============
    === EASY ===
    ============

    ===========================
    1) Two Sum
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums and an integer target, return indices of
    the two numbers such that they add up to target.

    You may assume that each input would have exactly one solution, and you may
    not use the same element twice.

    =====
    Node: You can return the answer in any order.
    =====

    ======================================================================
    FUNCTION: std::vector<int> twoSum(std::vector<int>& nums, int target);
    ======================================================================


    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input : nums = [2, 7, 11, 15], target = 9
    Output: [0, 1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1]

    --- Example 2 ---
    Input : nums = [3, 2, 4], target = 6
    Output: [1, 2]

    --- Example 3 ---
    Input : nums = [3, 3], target = 6
    Output: [0, 1]

    *** Constraints ***
    2 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target  <= 10^9
    Only one valid answer exists

*/

#include <vector>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simply map all of the values to its indices and then check if the
    difference between the current element and target is present in the map
    "indces".

    If it is, return {indices[diff], i}.



    NOTE:
    Average time of "lookup" and "insertion" in unordered_map and unordered_set
    is O(1).

    However, the worst-case scenario is O(N), but since that happens rarely, we
    can consider it O(1), that's why we say it's Amortized O(1).

    There are multiple ways of resolving "Hash collisions", but here are two:

    // C++ uses the first option, i.e. "Separate chaining"
    1. Separate chaining: each bucket holds a linked list (or similar) of
                          colliding elements. Extra memory is used for the
                          nodes. Lookup traverses the chain.

    2. Open addressing: all elements are stored directly in the table. When a
                        collision occurs, the algorithm probes other slots
                        (linear, quadratic, or double hashing) until an empty
                        slot is found. No extra linked nodes are allocated.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Two_Pass {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        const int N = nums.size();

        unordered_map<int, int> indices; // {number, index}

        // O(N) (entire block)
        for (int i = 0; i < N; i++)
            indices.insert( {nums[i], i} ); // O(1) Amortized due to occassional rehashes

        // O(N) (enire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            int diff = target - nums[i];

            if (indices.find(diff) != indices.end()) // O(1) Average-case
                return {indices[diff], i};

            indices.insert( {nums[i], i} ); // O(1) Amortized due to occassional rehashes
        }

        return {}; // Unreachable because there will ALWAYS be a VALID answer
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of putting everything in HashMap(unordered) from the outset, we can
    do so on-demand, thus creating a One-Pass Solution.

    The Overall Time Complexity stays the same, however, the "wall-time clock"
    is improved.

    
    The idea is to always check if the different is present. If it is NOT, only
    then insert current element.

    Since we're told that the valid answer ALWAYS exists, we'll, at some point,
    stumble upon on it.

    Once we do, we'll immediately return the result.

*/

/* Time  Complexity: O(N) */ // One-Pass
/* Space Complexity: O(N) */
class Solution_One_Pass {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        const int N = nums.size();

        unordered_map<int, int> seen;
        // O(N) (enire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            if (seen.find(target - nums[i]) != seen.end()) // O(1) Average-case
                return {seen[target - nums[i]], i};

            seen.insert( {nums[i], i} ); // O(1) Amortized due to occassional rehashes
        }

        return {}; // Unreachable because there will ALWAYS be a VALID answer
    }
};
