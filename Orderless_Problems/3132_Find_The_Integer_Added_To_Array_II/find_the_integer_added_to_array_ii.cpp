/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3132) Find the Integer Array to Array II
    ========================================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2.

    From nums1 two elements have been removed, and all other elements have been
    increased (or decreased in the case of negative) by an integer, represented
    by the variable x.

    As a result, nums1 becomes equal to nums2. Two arrays are considered equal
    when they contain the same integers with the same frequencies.

    Return the minimum possible integer x that achieves this equivalence.

    ==========================================================================
    FUNCTION: int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
    Output: -2
    Explanation:
    After removing elements at indices [0,4] and adding -2, nums1 becomes
    [18,14,10].

    --- Example 2 ---
    Input: nums1 = [3,5,5,3], nums2 = [7,7]
    Output: 2
    Explanation:
    After removing elements at indices [0,3] and adding 2, nums1 becomes [7,7].


    *** Constraints ***
    3 <= nums1.length <= 200
    nums2.length == nums1.length - 2
    0 <= nums1[i], nums2[i] <= 1000
    The test cases are generated in a way that there is an integer x such that
    nums1 can become equal to nums2 by removing two elements and adding x to
    each element of nums1.

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You CANNOT do it using "GCD method". Consider exapmle "3,3,5,5";

*/

/* Time  Beats: 40.80% */
/* Space Beats: 27.59% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        int result = 0;

        vector<pair<int,int>> ignore;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                ignore.push_back( {i, j} );
            }
        }

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        unordered_set<int> uset(nums1.begin(), nums1.end());
        vector<int> uniq(uset.begin(), uset.end());

        sort(uniq.begin(), uniq.end());
        const int SIZEEE = uniq.size();
        int size = min(3, SIZEEE);

        vector<int> potential_x;
        for (int i = 0; i < size; i++)
        {
            potential_x.push_back(nums2[0] - uniq[i]);
        }

        sort(potential_x.begin(), potential_x.end());

        // 3 3 5 5 (Consider this!!!)
        for (const int& x : potential_x)
        {
            for (const auto& skip : ignore)
            {
                int j = 0;
                bool valid = true;

                for (int i = 0; i < N; i++)
                {
                    if (i == skip.first || i == skip.second)
                        continue;


                    if (nums2[j] - nums1[i] != x)
                    {
                        valid = false;
                        break;
                    }
                    else
                    {
                        j++;
                    }
                }

                if (valid)
                    return x;
            }
        }

        return 0; // Unreachable
    }
};
