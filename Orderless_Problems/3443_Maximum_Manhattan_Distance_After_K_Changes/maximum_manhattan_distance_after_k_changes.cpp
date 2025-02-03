/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3443) Maximum Manhattan Distance After K Changes
    ================================================

    ============
    Description:
    ============

    You are given a string s consisting of the characters 'N', 'S', 'E', 'W',
    where s[i] indicates movements in an infinite grid:

        'N' : Move north by 1 unit.
        'S' : Move south by 1 unit.
        'E' : Move east by 1 unit.
        'W' : Move west by 1 unit.

    Initially, you are at the origin (0, 0). You can change at most k
    characters to any of the four directions.

    Find the maximum Manhattan distance from the origin that can be achieved at
    any time while performing the movements in order.

    The Manhattan Distance between two cells:

        (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|. 

    ===========================================
    FUNCTION: int maxDistance(string s, int k); 
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "NWSE", k = 1
    Output: 3
    Explanation:
    Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
    +--------------+---------------+-----------------+-----------------+
    |   Movement   | Position(x,y) | Manhattan dist  |   Maximum       |
    +--------------+---------------+-----------------+-----------------+
    | s[0] == 'N'  |   ( 0, 1)     | 0 + 1 = 1       |    1            |
    +--------------+---------------+-----------------+-----------------+
    | s[1] == 'W'  |   (-1, 1)     | 1 + 1 = 2       |    2            |
    +--------------+---------------+-----------------+-----------------+
    | s[2] == 'S'  |   (-1, 2)     | 1 + 2 = 3       |    3            |
    +--------------+---------------+-----------------+-----------------+
    | s[3] == 'E'  |   ( 0, 2)     | 0 + 2 = 2       |    3            |
    +--------------+---------------+-----------------+-----------------+
    The maximum Manhattan distance from the origin that can be achieved is 3.
    Hence, 3 is the output.


    --- Example 2 ---
    Input: s = "NSWWEW", k = 3
    Output: 6
    Explanation:
    Change s[1] from 'S' to 'N', and s[4] from 'E' to 'W'.
    The string s becomes "NNWWWW". The maximum Manhattan distance from the
    origin that can be achieved is 6. Hence, 6 is the output.


    *** Constraints ***
    1 <= s.length <= 10^5
    0 <= k <= s.length
    s consists of only 'N', 'S', 'E', and 'W'.

*/

#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    (I advise you to read this whole Explanation(IDEA), until the very end.
     It is boring and difficult, but once you get through all of it carefully,
     you'll come to appreciate both the IDEA and the elegant Implementation)

    The code looks deceptively easy. It seems as this problem is not that hard
    to do.

    I would argue the exact opposite. It is not easy by any means to notice
    some of the key things that are absolutely necessary for you to come up
    with an approach like this.

    I'm going to walk you through my thought process, including the approach
    that DOESN'T work.

    At first I thougth we can treat:
        1) 'N' & 'S', and
        2) 'E' & 'W'

    separately.

    I thought, whenever there are a bunch of 'N's and 'S's, we should take the
    one that appears less and then convert that to the opposite.

    For example:

        'NNSNNSS' k = 2

    Since there are 4 'N' and 3 'S' characters, we should try to convert as
    many 'S' characters as possible to 'N' characters.

    Had we tried the opposite, i.e. convert as many 'N' to 'S', we would NOT
    maxxed out our manhattan distance from the origin.

        Side note: notice that manhattan distance from the origin is literally:
        abs(x) + abs(y)


    In this example if we've changed:
        min(k, frequence_of_less_frequent_directions),

    in this case min(k=2, freq=3) // Because 'S' appears less than 'N' & it's 3
    Therefore, we're allowed to change 2 out of 3 'S' to 'N'.

    That way we'd have:

        'NNNNNNS'

    Those are 6 'N's and 1 'S'.

    If we tried to change 'N' to 'S' instead, we'd have min(k=2, freq=4),
    meaning we'd change 'N' to 'S'.

    We'd have this:

        'SSSNNSS'

    Those are 2 'N's and 5 'S's.

    But it turns out, this cannot be done like this.
    Why?

    Because they've told us this:
        "Find the maximum Manhattan distance from the origin that can be
         achieved AT ANY TIME while performing the movements in order."


    "At any time" is absolutely CRUCIAL.
    

    Consider the Example 1:

        s = "NWSE",  k = 1

    Had we handled 'N' & 'S' separaterly from 'E' & 'W', we'd have a problem.
    At first, we'd count the occurrences of all directions:

        freq = [1, 1, 1, 1]
                N  S  E  W

    Since there are the same amount of 'N' and 'S' characters, we can change
    either of those.
    Let's say we've decided to change 'S' to 'N'.

    However, we must be mindful of our 'k' variable. We cannot change more than
    k directions.

    Therefore, we're going to change min(k=1, freq=1) 'S' characaters to 'N'.
    (Even if k was bigger than 1, we cannot change more 'S's than we have)

        s = "N W S E"
             0 1 2 3

    Had we done that, we'd have a correct result.
    We'd have this:

        s = 'N W N E"
             0 1 2 3
    
    Once we went up on index 2, our Manhattan distance would be 3, which is
    indeed the maximum AT ANY TIME and therefore it is the correct result.


    However, there's a huge problem with this one that doesn't seem very
    obvious.

    Since we're treating 'N' & 'S' and 'E' & 'W' completely separately, then
    we could also try to change 'W' to 'E' first and then change 'S' to 'N' if
    our k allows it.

    Had we done that, for our same example:

        s = "N W S E",  k = 1
             0 1 2 3

    We'd have this:

        s = 'N E S E"
             0 1 2 3

    Going through these, you'll realize that the biggest Manhattan distance
    AT ANY TIME is 2. Which is INCORRECT! It should be 3.

    So how's that possible?


    The order of letter MATTERS! It MATTERS!

        s = "NWSE"   --->    s = "NESE"  // would NOT    work.
        s = "NWSE"   --->    s = "NEES"  // would INDEED work.

    This drastically complicates this problem.

    Now, the fact below is the key observation that is non-trivial. You cannot
    do it without this, yet it is not very intuitive, especially if you're not
    very familiar with these "direction" type of problems.

    Fact:

        Since we're processing elements in a string that is 0-based,
        MAXIMUM MANHATTAN DISTANCE AT ANY GIVEN INDEX IS: INDEX + 1.

    Maximum Manhattan distance at any index, or "max_reachable" in short.

    This is not intuitive...
    But, think about it:

             0 1 2
        s = "N N N"
        s = "N N W"
        s = "N N E"
        s = "S S S"
        s = 'S S W"
        s = "S S E"
        etc.

    At index 2, it's IMPOSSIBLE to have bigger Manhattan Distance than 2+1 = 3.

    If you're not convinced, try to think of a bigger Manhattan Distance with
    only 3 letters. It's IMPOSSIBLE.


    That was the first key observation that is absolutely necessary.
    Second one is that when you--for example--convert k number of 'S' to 'N',
    you don't extend the Manhattan distance by k, BUT BY: 2 * k.

    Why?

    Think of it like this:

        'E W E'
         0 1 2

    You'd go EAST and now x = 1.
    You'd go WEST and now x = 0.
    You'd go EAST and now x = 1.


    But if we had:

        'E E E'
         0 1 2

    You'd go EAST and now x = 1.
    You'd go EAST and now x = 2.
    You'd go EAST and now x = 3.
        

    Not only did you not go back, you actually went in the OPPOSITE direction.
    That is a difference of size 2.


        'E W E'               'E E E'
         0 1 2                 0 1 2

         =                     ===
         1                       3


    Now we need to be careful and combine these two key observations:
        1) Maximal Manhattan distance at index idx is: idx+1.

        2) When you convert k letters, the Manhattan distance is NOT extended
           by k, but by: 2 * k.


    Now, there's one more peace that is also mind-bending at first.

    First, be careful when reading. I'm almost certain most of you overlooked
    this part of the Description:

        "Initially, you are at the origin (0, 0). You can change AT MOST K
         characters to any of the four directions."

    This means that you don't have to change ANYTHING if you don't want.
    Example:

        s = "NNN", k = 2

    Why would we change anything when we're going to have maximal Manhattan
    distance already?

    That's why we don't.


    Now, here comes the mind-bending part.

    Since we KNOW that there CANNOT be a greater Manhattan Distance than idx+1,
    what we're going to do is assume our change is ALWAYS going to increase the
    Manhattan distance.

    Now--hear me out--this is REALLY confusing, but this is the absolute crux.

    Imagine that we had an example like this:

        s = "N W S N", k = 2
             0 1 2 3

    Let's iterate through s index-by-index:

        0) curr = "N"
                   0

            Maximum possible Manhattan Distance at index 0 is: 0+1 = 1.

            Let's try to convert as many letters as we can and pretend as if
            those are necessarily extending our current Manhattan Distance.

            In this case:
                changed_letters = min(k=2, curr_letters=1)

            Therefore, we're allowed to change only 1. But, remember that when
            we're changing a letter, we're extending the Manhattan distance not
            by k, but by 2 * k.

            In this case, that'd be: 1 + 2 * changed_letters
                                     ^   ~~~~~~~~~~~~~~~~~~~
                                  ___|            |
                                  |             size of the extension
                               current
                              Manhattan
                              distance


            So the Manhattan distance at this index 0 would be 3.
            Hmm. But didn't we say maximum Manhattan Distance at idx is: idx+1?

            Yes, therefore we take the MINIMUM out of:
                (max_reachable, curr_manhattan_distance + 2 * changed_letters)


            But there's another thing. I know, I know, it's too much, but
            watch this.

            We don't have to take the min out of (k=2, curr_letters=1), instead
            we can ALWAYS extend the current Manhattan distance by 2 * k.

            Why?
            Because, at the end of this iteration, we're always going to take
            the MINIMUM out of: 
                (max_reachable, curr_manhattan_distance + 2 * changed_letters)


            That means that at this idx=0, max_reachable is 1, but our
            current_manhattan_distance + 2 * k = 3.

            We take the MINIMUM out of those because we CANNOT have bigger
            Manhattan distance than max_reachable, but we also cannot have
            bigger than current_manhattan_distance + 2 * k.

            That's why we do this:

                result = max(result, min(max_reachable, manhattan_dist + 2*k));
                
            (Side note: An example where curr_manhattan_distance + 2 * k is
                        LESS than max_reachable

                        s = "E W E W", k = 1
                             0 1 2 3

                        Here, max_reachable is 4, but
                        current_manhattan_distance + 2 * k <==> 0 + 2 * 1 = 2

                        That's why we always take the minimum.
            )



        1) curr = "N W"
                   0 1

            Current Manhattan distance is 2.
            Maximum reachable at idx=1 is: idx+1 = 2.

            We're trying to extend this by 2 * k even if it's already maxxed
            out.

            After extension: curr_manhattan_distance + 2 * k <==> 2 + 2 * 2 = 6

            However 6 is BIGGER than than max_reachable, therefore we take
            max_reachable.


        2) curr = "N W S"
                   0 1 2

            Current Manhattan distance is 1.
            Maximum reachable at idx=2 is: idx+1 = 3.

            We're trying to extend this by 2 * k even if it's already maxxed
            out.

            After extension: curr_manhattan_distance + 2 * k <==> 1 + 2 * 2 = 5

            However 5 is BIGGER than than max_reachable, therefore we take
            max_reachable.


        3) curr = "N W S E"
                   0 1 2 3

            Current Manhattan distance is 0.
            Maximum reachable at idx=2 is: idx+1 = 4.

            We're trying to extend this by 2 * k even if it's already maxxed
            out.

            After extension: curr_manhattan_distance + 2 * k <==> 0 + 2 * 2 = 4

            Since max_reachable is equal to the size AFTER extension, we take
            max_reachable as our result here as well.


    At any given point, maximal Manhattan distance was 4. That's what we return
    and that's what's corect.

    This is a VERY difficult one, don't get discouraged!

*/

/* Time  Beats: 63.64% */
/* Space Beats: 18.18% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxDistance(string s, int k)
    {
        const int N = s.length();
        int result = 0;

        int x = 0;
        int y = 0;

        for (int idx = 0; idx < N; idx++)
        {
            if (s[idx] =='N') y++;
            if (s[idx] =='S') y--;
            if (s[idx] =='E') x++;
            if (s[idx] =='W') x--;

            int manhattan_dist = abs(x) + abs(y); // Curr Manhattan Dist.
            int max_reachable  = idx + 1; // Curr max possible Manhattan Dist.

            result = max(result, min(max_reachable, manhattan_dist + 2*k));
        }

        return result;
    }
};
