/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2140) Solving Questions with Brainpower
    =======================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array questions where questions[i] =
    [points_i, brainpower_i].

    The array describes the questions of an exam, where you have to process the
    questions in order (i.e., starting from question 0) and make a decision
    whether to solve or skip each question. Solving question i will earn you
    points_i points but you will be unable to solve each of the next
    brainpower_i questions. If you skip question i, you get to make the
    decision on the next question.

        For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]: If
        question 0 is solved, you will earn 3 points but you will be unable to
        solve questions 1 and 2.  If instead, question 0 is skipped and
        question 1 is solved, you will earn 4 points but you will be unable to
        solve questions 2 and 3.

    Return the maximum points you can earn for the exam.

    ===============================================================
    FUNCTION: long long mostPoints(vector<vector<int>>& questions);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: questions = [[3,2],[4,3],[4,4],[2,5]]
    Output: 5
    Explanation: The maximum points can be earned by solving questions 0 and 3.
    - Solve question 0: Earn 3 points, will be unable to solve the next 2
      questions
    - Unable to solve questions 1 and 2
    - Solve question 3: Earn 2 points Total points earned: 3 + 2 = 5. There is
      no other way to earn 5 or more points.


    --- Example 2 ---
    Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
    Output: 7
    Explanation: The maximum points can be earned by solving questions 1 and 4.
    - Skip question 0
    - Solve question 1: Earn 2 points, will be unable to solve the next 2
      questions
    - Unable to solve questions 2 and 3
    - Solve question 4: Earn 5 points Total points earned: 2 + 5 = 7. There is
      no other way to earn 7 or more points.


    *** Constraints ***
    1 <= questions.length <= 10^5
    questions[i].length == 2
    1 <= points_i, brainpower_i <= 10^5

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This is a textbook example of a 1D Dynamic Programming problem.

    The question you have to ask yourself when wanting to check if the problem
    you're currently solving is the Dynamic Programming problem is this:

    "If I have the answer of this entire example and I prepend(or append)
    another element(pair in this case) to it, will the result of this current
    example help me in any way?"

    Let's see the Example 1:
        questions = [[3,2], [4,3], [4,4], [2,5]]
                       0      1      2      3

    The result of this example is 5. (Solve the 0th question and the 3rd one)

    Let's ask our question again:"If I have the answer of this entire
    example(which we do now, the result is 5) and I prepend another
    element(pair) to it, will the result of this current example(without the
    prepended element), which is 5, help me in any way to solve that new
    example?"


    Old Example:
        questions = [[3,2], [4,3], [4,4], [2,5]]
                       0      1      2      3
    (result = 5)


    Prepend an element to "Old Example":
        questions = [[4,2], [3,2], [4,3], [4,4], [2,5]]
                       0      1      2      3      4

               dp = [  ?  ,   5  ,  ...  , ... ,  ...]]
                       0      1      2      3      4


    "?" - We still haven't computed the result starting from this element

    "5" - The result of the entire array starting from the index 1 to the end.

    "..." - Other computed results from corresponding starting positions to
            the end of the array.


    Let's check if solving subproblems will help us in any way.

    We always have two choices:
        1. Solve the current one (at index 0 in this case)
        2. Skip  the current one (at index 0 in this case)

    1. [Solve the current one]
        If I choose to solve this current one(index 0), then I'm not able to
        solve next "brainpower" questions(the second value in the pair).

        So, If I solve the 0th questions, then I'm unable to solve next 2
        questions i.e. questions at index 1 and question at index 2.

        However I am able to solve questions, again, from index 3 onwards.

        So, will computed, and stored, example from index 3 to the end of the
        array help me solve the current problem?

            Yes, it will!
            Therefore, this is a Dynamic Programming problem.



    2. [Skip the current one]
        If I choose to skip this current one, then the max value I'm able to
        earn is the exact same as solving the previous subproblem, i.e. the
        "Old Example"

        So since if I skip the current one, the max will be the same value as
        for the previous subproblem, therefore this is definitely a Dynamic
        Programming problem.


    So, I should say that the maximum I'm able to earn starting from index 0
    is equal to:

    max(
        solve_current_one
            +
        result_of_the_the_first_subproblem_to_the_right_that_I'm_able_to_solve,

            OR

        0 // Skip the current one
            +
        result_of_the_very_next_subproblem_to_the_right
       )


    However, there's one caveat here. What if:
        result_of_the_the_first_subproblem_to_the_right_that_I'm_able_to_solve
    doesn't exist?

    How can it "not exist"?
    It may not exist because "brainpower" value is greater than or equal to
    the remaining amount of elements to the right.

    Old Example:
        questions = [[3,2], [4,3], [4,4], [2,5]]
                       0      1      2      3


    Let's say that we're trying to solve a question at index 2.
    If we solve that one, then we're unable to solve the next 4 questions,
    however you can clearly see that there is a total of one question to the
    right, in other words - If you choose to solve question at index 2 then
    you're unable to solve any other questions to the right.

    Because of that we must have this condition:
        if ((i + 1 + brainpower) < n)
            dp[i] = std::max<long long>(points + dp[i + 1 + brainpower], dp[i + 1]);
        else
            dp[i] = std::max<long long>(points, dp[i + 1]);

    Also, it's important to note that the result of the very last question, and
    therefore the result of the very last subproblem, will always be the number
    of points it can earn by itself since there are no additional questions to
    the right.

    Therefore, before we start iterating in the for loop, we say:
        dp[n-1] = questions[n-1][0]; // Points

    Since dp[i+1] would be out of bounds.
    i = n-1   ==>  i+1 = n // Index n is out of Bounds

*/

/* Time  Beats: 85.16% */
/* Space Beats: 76.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long mostPoints(std::vector<std::vector<int>>& questions)
    {
        const int n = questions.size();

        vector<long long> dp(n, 0);
        dp[n-1] = questions[n-1][0];

        for (int i = n-2; i >= 0; i--)
        {
            long long  points     = questions[i][0];
            long long  brainpower = questions[i][1];

            /*
                (i + 1 + brainpower) is the closest question to the right that
                we're allowed to solve if we solve the current one.

                Therefore (i + 1 + brainpower < n) means - "Is it possible to
                solve at least one more question if we solve this one?"
            */
            if (i + brainpower + 1 < n)
                dp[i] = max(points + dp[i + brainpower + 1], dp[i+1]);
            else
                dp[i] = max(points, dp[i+1]);
        }

        return dp[0];
    }
};
