/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3447) Assign Elements to Groups with Constraints
    ================================================

    ============
    Description:
    ============

    You are given an integer array groups, where groups[i] represents the size
    of the ith group. You are also given an integer array elements.

    Your task is to assign one element to each group based on the following
    rules:

        + An element j can be assigned to a group i if groups[i] is divisible
          by elements[j].

        + If there are multiple elements that can be assigned, assign the
          element with the smallest index j.

        + If no element satisfies the condition for a group, assign -1 to that
          group.

    Return an integer array assigned, where assigned[i] is the index of the
    element chosen for group i, or -1 if no suitable element exists.

    =====
    Note: An element may be assigned to more than one group.
    =====

    =================================================================================
    FUNCTION: vector<int> assignElements(vector<int>& groups, vector<int>& elements);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: groups = [8,4,3,2,4], elements = [4,2]
    Output: [0,0,-1,1,0]
    Explanation:
        elements[0] = 4 is assigned to groups 0, 1, and 4.
        elements[1] = 2 is assigned to group 3.
        Group 2 cannot be assigned any element.


    --- Example 2 ---
    Input: groups = [2,3,5,7], elements = [5,3,3]
    Output: [-1,1,0,-1]
    Explanation:
        elements[1] = 3 is assigned to group 1.
        elements[0] = 5 is assigned to group 2.
        Groups 0 and 3 cannot be assigned any element.


    --- Example 3 ---
    Input: groups = [10,21,30,41], elements = [2,1]
    Output: [0,1,0,1]
    Explanation:
    elements[0] = 2 is assigned to the groups with even values, and
    elements[1] = 1 is assigned to the groups with odd values.


    *** Constraints ***
    1 <= groups.length <= 10^5
    1 <= elements.length <= 10^5
    1 <= groups[i] <= 10^5
    1 <= elements[i] <= 10^5

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one requires a bit of Math, but it's not too bad. It's definitely good
    to know this stuff.

    The first thing that comes to mind would, probably, be:"A Brute Force?".
    But no, we cannot do that given the Constraints.

    It would take O(N * M) which is way too inefficient given the Constraints.


    The next thing that surely won't hurt and is almost as obvious, is to
    create a HashMap {element : index} because it is allowed to have multiple
    instances of the same element in more than one index.

    We're told we ALWAYS need the divisor of group that has the SMALLEST INDEX.
    Since that is the case, we should create a map of every UNIQUE element from
    "elements" as a key, and the value should be the smallest index at which it
    appears in "elements".

    Example:
        groups = [8,7,2,9,13], elements = [2,1,2,2,3,7,10,7,3,3]
                                           0 1 2 3 4 5  6 7 8 9

    Our HashMap "elem_to_idx" should look like this:


             Hash Map
        |  Key  :  Value |
        +----------------+
        |   2   :    0   | // Leftmost position of  2 is at index 0
        +----------------+
        |   7   :    5   | // Leftmost position of  7 is at index 5
        +----------------+
        |   1   :    2   | // The only position of  1 is at index 2
        +----------------+
        |  10   :    6   | // The only position of 10 is at index 6
        +----------------+
        |   3   :    4   | // Leftmost position of  3 is at index 4
        +----------------+


    Okay, but how is that going to help us?

    I want you to be aware of this fact:

        When you divide an element "elem" with X you get Y.
        But, it's also true that if you divide element "elem" with Y you get X.

        (if and only if "elem" is divisible by X(and Y obviously))

    In other words:

        elem = 15

        15 / 3 = 5
        15 / 5 = 3

    This seems trivial, but this is literally going to solve the problem.
    If 15 is divisible by 3, then 15 is ALSO divisible by its QUOTIENT(i.e. 5).

    So, if: 15 % 3 == 0, then we don't have to check if: 15 % 5 == 0, because
    it certainly is.


    But let's understand what makes the Brute Force approach so inefficient.
    Of course, it's O(N * M) Time Complexity, but let's understand what we are
    doing there.

        groups = [8,7,2,9,13], elements = [2,1,2,2,3,7,10,7,3,3]
                                           0 1 2 3 4 5  6 7 8 9


    Let's use our HashMap here since that'd be an Optimization even if we could
    use a Brute Force.

        Our HashMap "elem_to_idx" should look like this:

             Hash Map
        |  Key  :  Value |
        +----------------+
        |   2   :    0   | // Leftmost position of  2 is at index 0
        +----------------+
        |   7   :    5   | // Leftmost position of  7 is at index 5
        +----------------+
        |   1   :    2   | // The only position of  1 is at index 2
        +----------------+
        |  10   :    6   | // The only position of 10 is at index 6
        +----------------+
        |   3   :    4   | // Leftmost position of  3 is at index 4
        +----------------+


    groups = [8,7,2,9,13],
              i

    We are iterating through "groups" starting at i=0.

    i = 0)
        curr_group = 8

        For curr_group=8, we would be going through ALL of the UNIQUE elements
        in the Map.
        Sure, we understand that's inefficient but WHY is it inefficient?

        It's inefficient because some numbers CAN NEVER be divisors of our
        curr_group = 8.

        But what can we do about it?

        What are ALL the divisors of 8?
        They are:
            1) 1
            2) 2
            3) 4
            4) 8

        So no matter how many elements are in HashMap "elem_to_idx", there are
        always EXACTLY 4 possible divisors of 8.

        So then, that means, if we had a million of UNIQUE elements in our
        HashMap "elem_to_idx", we would be going through ALL of them instead of
        checking only these 4.


    Let's say that our curr_group is 15.
    What are all of its divisors?
    They are:
        1) 1
        2) 3
        3) 5

    But if for 8 we have 4 divisors(1,2,4,8) and for 15 only 3(1,3,5), then...
    How can we obtain that information?

    Once we have curr_group = 8 or curr_group = 15, how can we know what are
    the divisors of any given number?

    Well, we don't out of the bat, we have to iterate. But this is the crux,
    we are going to consider only elements that have its squares LESS THAN OR
    EQUAL to curr_group.

    This seems COMPLETELY unintuitive. Why would we do that? And how does
    someone figure that out?

    Let's reason our way through. First, let's refresh our memory with one of
    the observations we've made:

        When you divide an element "elem" with X you get Y.
        But, it's also true that if you divide element "elem" with Y you get X.

        (if and only if "elem" is divisible by X(and Y obviously))


        elem = 15

        15 / 3 = 5
        15 / 5 = 3

    This is CRUCIAL, even if it doesn't seem that way.
    Why would this be crucial?

    It's crucial because we DON'T have to iterate all the way up to 5 in order
    to check if 5 is a divisor of 15 and if 5 is present in our "elem_to_idx"
    HashMap.

    Then... How can we know if 5 is a divisor of 15 if we don't iterate all the
    way up to it?

    BECAUSE WE'LL HAVE 5 AS THE QUOTIENT OF DIVISION WITH AN ELEMENT <= 5.
    (It's LESS THAN OR EQUAL TO because for some curr_group such as 25, we
     can't have 5 as a product unless we divide curr_group with 5, but for
     most of the numbers we will)

    Next, but how do we know how much should we iterate for any number?
    It has to do with the thing we've just explained right above this question.

    For every potential divisor, we'll check up to TWO elements in our
    "elem_to_idx" HashMap.

    The first one is going to be the divisor itself, but the second one is
    going to be the quotient of the curr_group and current divisor.

    As we've already given an example:

        elem = 15
        divisor = 3;

        if (elem % divisor == 0) // elem is DIVISIBLE by divisor
        {
            if (elem_to_idx.count(divisor)) // and it DOES exists in HashMap
                idx = min(idx, elem_to_idx[divisor]);  // Take the smallest idx

            quotient = elem / divisor;
            if (elem_to_idx.count(quotient)) // if QUOTIENT exists in HashMap
                idx = min(idx, elem_to_idx[quotient]); // Take the smallest idx
        }


    BUT HOW DO WE KNOW WHAT IS THE UPPER BOUND?!?!?!

        Let's consider the same curr_group = 15.


        divisor = 1)

            idx = INT_MAX; // We could also put N, since that is Out-Of-Bounds
                           // and higher than all indices in our "elements".

            if (elem % 1 == 0)
            {
                We'll potentially check if two elements are present in HashMap:
                    1) divisor
                    2) quotient

                If "divisor" is present in HashMap:
                    idx = min(idx, elem_to_idx[divisor])

                If "quotient" is present is HashMap:
                    idx = min(idx, elem_to_idx[quotient];
            }

            That's why we've put idx=INT_MAX.

            If elem is NOT divisible by divisor    OR
               "divisor"  is NOT present in HashMap OR
               "quotient" is NOT present int HashMap

               then idx will remain equal to INT_MAX. In that case we should
               put -1 as a final result for this group.

            Otherwise, put the index at variable "idx" that we've obtained in
            this iteration.


    But, I still haven't answered the question:
        "BUT HOW DO WE KNOW WHAT IS THE UPPER BOUND?!?!?!"

    When divisor is 1, then we'll check two elements in HashMap:
        1) 1
        2) 15, because curr_group=15 / 1 = 15

    When divisor is 2, then we'll check two elements in HashMap:
        1) 2
        2) 7, because curr_group=15 / 2 = 7 (INTEGER DIVISION)

    When divisor is 3, then we'll check two elements in HashMap:
        1) 3
        2) 5, because curr_group=15 / 3 = 5


    And then, we'll stop.
    BUT WHYYYYYYY!?!?!? WHY WOULD WE STOP HERE?!?

    Because we don't have to check the presence of the same element twice.
    Let me explain.

    It's important to get this:

        (Only if curr_group is DIVISIBLE by a divisor)

                    (divisor)  (quotient)
        curr_group / SMALLER = LARGER
        curr_group / LARGER  = SMALLER
        curr_group / EQUAL   = EQUAL

        If we divide 15 by 3, we'd get 5. But we don't have to divide 15 by 5,
        because we'd get 3 and then check those two because they were already
        processed.

    Okay.. But what about 4? Why didn't we consider 4 as our potential divisor?
    Because 4 * 4 is GREATER than curr_group=15.

    It sounds confusing, let's reason slowly.
    Don't forget this:


                     (divisor) = (quotient)
        curr_group /  SMALLER  = LARGER
        curr_group /  LARGER   = SMALLER

    But also, realize this:

       (divisor)  (quotient)
        SMALLER * LARGER    = curr_group
           3    *    5      =   15


    But, here comes the mind-bending part:

       (divisor)  (quotient)
        EQUAL   *  EQUAL    = EQUAL_SQUARED
          4     *   4       = 4^2 (which is 16)


    However, we are going to consider 1, 2 and 3 as divisor because:

       (divisor)  (quotient)
        SMALLER * LARGER    <= curr_group=15
           1    *   15      <= 15
           2    *    7      <= 15
           3    *    5      <= 15

           4    *    4      >  15  // This will not do it

    "Okay", you may say, "But why don't we continue? Sure 4 * 4 is greater tahn
     15 and 4 isn't a divisor, but if we continue 5 will be. Who knows if there
     are more divisors out there, but we've decided to stop".

     The answer is, as I've already said:

        BECAUSE WE DON'T HAVE TO CHECK THE PRESENCE OF SAME ELEMENT TWICE.


     1 ensures that 15 is also checked.
     2 ensures that  7 is also checked.
     3 ensures that  5 is also checked.

     Once we find out that some X * X is GREATER than curr_group, after that
     THE DIVISOR IS THE ONE THAT IS GOING TO BE SMALLER AND QUOTIENT IS THE ONE
     THAT IS GOING TO BE LARGER.


                We had:
                   (divisor)  (quotient)
                    SMALLER * LARGER    <= curr_group=15
      ------------- 1    *   15      <= 15
      | ----------- 2    *    7 XXX  <= 15     // 15 is NOT divisible by 2
      | | --------- 3    *    5      <= 15
      | | |
      | | |
      | | |
      | | |
      | | |     But now we'd have:
      | | |        (divisor)  (quotient)
      | | |         LARGER  * SMALLER   <= curr_group=15
      | | |------->   5     *   3       <= 15      // Already processed
      | |
      | |--------->   6     *   2 XXX   <= 15      // 15 is NOT divisible by 6
      | |--------->   7     *   2 XXX   <= 15      // 15 is NOT divisible by 7
      |
      |----------->   8     *   1       <= 15      // 15 is NOT divisible by 8
      |----------->   9     *   1 XXX   <= 15      // 15 is NOT divisible by 9
      |----------->  10     *   1 XXX   <= 15      // 15 is NOT divisible by 10
      |----------->  11     *   1 XXX   <= 15      // 15 is NOT divisible by 11
      |----------->  12     *   1 XXX   <= 15      // 15 is NOT divisible by 12
      |----------->  13     *   1 XXX   <= 15      // 15 is NOT divisible by 13
      |----------->  14     *   1 XXX   <= 15      // 15 is NOT divisible by 14
      |----------->  15     *   1 XXX   <= 15      // Already processed


      But keep in mind that:

                     (divisor) = (quotient)
        curr_group /  SMALLER  = LARGER
        curr_group /  LARGER   = SMALLER


      Therefore, once the first case where X * X is greater than curr_group is
      the case after which we'd start to get either:
        1) qoutients that were ALREADY processed
        2) curr_group is NOT divisible by divisor

     That means we've ALREADY PROCESSED ALL POTENTIAL DIVISORS by trying only
     divisors which when squared are LESS THAN OR EQUAL TO curr_group.

     That way we've reduced a Time Complexity from O(N * M) to (M * sqrt(G)),
     where 'G' is the max value in groups.



     Also, here's an example where X * X is curr_group:
     curr_group = 25

        divisor = 1, quotient = 25
        divisor = 2, XXX            // Not divisible
        divisor = 3, quotient = 9
        divisor = 4, XXX            // Not divisible
        divisor = 5, quotient = 5

     T herefore, we'd only iterate sqrt(curr_group) times.
     The bigger the number, the bigger saving of time it is.


     It's not intuitive, but once you know it, it's not too bad.

*/

/* Time  Beats: 60.48% */
/* Space Beats: 57.48% */

/* Time  Complexity: O(N + M + M * sqrt(G)) */ // G <==> max value in groups
/* Space Complexity: O(N)                   */
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements)
    {
        vector<int> result;

        unordered_map<int,int> elem_to_idx;
        for (int i = 0; i < elements.size(); i++)
        {
            if (elem_to_idx.count(elements[i]) == 0) // Doesn't exist
                elem_to_idx[elements[i]] = i;
        }

        for (int i = 0; i < groups.size(); i++)
            check(groups[i], elem_to_idx, result);

        return result;
    }

private:
    void check(int group, unordered_map<int,int>& elem_to_idx, vector<int>& result)
    {
        int idx = INT_MAX; // Or 'N', just some high Out-of-Bounds index

        for (int divisor = 1; divisor*divisor <= group; divisor++)
        {
            if (group % divisor == 0) // If it's DIVISIBLE
            {
                int quotient = group / divisor;

                if (elem_to_idx.count(divisor))
                    idx = min(idx, elem_to_idx[divisor]);

                if (elem_to_idx.count(quotient))
                    idx = min(idx, elem_to_idx[quotient]);
            }
        }

        if (idx != INT_MAX)
            result.push_back(idx);
        else
            result.push_back(-1);
    }
};
