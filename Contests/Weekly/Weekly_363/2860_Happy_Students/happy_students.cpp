/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2860) Happy Students
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums of length n where n is the
    total number of students in the class. The class teacher tries to select a
    group of students so that all the students remain happy.

    The ith student will become happy if one of these two conditions is met:

        + The student is selected and the total number of selected students is
          strictly greater than nums[i].

        + The student is not selected and the total number of selected students
          is strictly less than nums[i].

    Return the number of ways to select a group of students so that everyone
    remains happy.

    ===========================================
    FUNCTION: int countWays(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1]
    Output: 2
    Explanation: 
    The two possible ways are:
    The class teacher selects no student.
    The class teacher selects both students to form the group. 
    If the class teacher selects just one student to form a group then the both
    students will not be happy. Therefore, there are only two possible ways.

    --- Example 2 ---
    Input: nums = [6,0,3,3,6,7,2,7]
    Output: 3
    Explanation: 
    The three possible ways are:
    The class teacher selects the student with index = 1 to form the group.
    The class teacher selects the students with index = 1, 2, 3, 6 to form the
    group.
    The class teacher selects all the students to form the group.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] < nums.length

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.78% */
/* Space Beats: 71.30% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // SC of C++'s Intro Sort
class Solution {
public:
    int countWays(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        sort(nums.begin(), nums.end()); // in ASCENDING order

        if (nums[0] >= 1)
            ++result;
        else if (N >= 2 && nums[0] == 0 & nums[1] >= 2)
            ++result;
        else if (N == 1 && nums[0] == 0)
            ++result;
        
        int selected = 1;
        for (int i = 1; i < N; i++)
        {
            ++selected;

            if (selected > nums[i] && (i == N-1 || selected < nums[i+1]))
                ++result;
        }

        return result;
    }
};
