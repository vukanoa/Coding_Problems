#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ============================================
    1700) Number of Students Unable to Eat Lunch
    ============================================

    ============
    Description:
    ============

    The school cafeteria offers circular and square sandwiches at lunch break,
    referred to by numbers 0 and 1 respectively. All students stand in a queue.
    Each student either prefers square or circular sandwiches.

    The number of sandwiches in the cafeteria is equal to the number of
    students. The sandwiches are placed in a stack. At each step:

        + If the student at the front of the queue prefers the sandwich on the
          top of the stack, they will take it and leave the queue.

        + Otherwise, they will leave it and go to the queue's end.

    This continues until none of the queue students want to take the top
    sandwich and are thus unable to eat.

    You are given two integer arrays students and sandwiches where
    sandwiches[i] is the type of the i-th sandwich in the stack (i = 0 is the
    top of the stack) and students[j] is the preference of the j-th student in
    the initial queue (j = 0 is the front of the queue). Return the number of
    students that are unable to eat.

    ============================================================================
    FUNCTION: int countStudents(vector<int>& students, vector<int>& sandwiches);  
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
    Output: 0 
    Explanation:
    - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
    - Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
    - Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
    - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
    - Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
    - Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
    - Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
    - Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
    Hence all students are able to eat.


    --- Example 2 ---
    Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
    Output: 3


    *** Constraints ***
    1 <= students.length, sandwiches.length <= 100
    students.length == sandwiches.length
    sandwiches[i] is 0 or 1.
    students[i] is 0 or 1.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  5.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int N = students.size();
        unordered_set<int> uset;

        int top    = 0;
        int curr   = 0;
        int unable = 0;

        for(;;)
        {
            if (students[curr] == sandwiches[top])
            {
                uset.insert(curr);
                top++;
                unable = 0; // Reset
            }
            else
                unable++;
            
            if (uset.size() == N)
                break;
            
            if (unable == (N - uset.size()))
                return unable;

            int next = (curr + 1) % N;
            while (uset.count(next))
                next = (next + 1) % N;
            
            curr = next;
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int N = students.size();

        int have_not_eaten = N;

        unordered_map<int, int> count_preferences;
        for (const int& prefer_type : students)
            count_preferences[prefer_type]++;

        for (const int& top_type : sandwiches)
        {
            if (count_preferences[top_type] > 0)
            {
                count_preferences[top_type]--;
                have_not_eaten--;
            }
            else
                break;
        }

        return have_not_eaten;
    }
};
