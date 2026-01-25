/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    853) Car Fleet
    ===========================

    ============
    Description:
    ============

    There are n cars going to the same destination along a one-lane road. The
    destination is target miles away.

    You are given two integer array position and speed, both of length n, where
    position[i] is the position of the ith car and speed[i] is the speed of the
    ith car (in miles per hour).

    A car can never pass another car ahead of it, but it can catch up to it and
    drive bumper to bumper at the same speed. The faster car will slow down to
    match the slower car's speed. The distance between these two cars is
    ignored (i.e., they are assumed to have the same position).

    A car fleet is some non-empty set of cars driving at the same position and
    same speed. Note that a single car is also a car fleet.

    If a car catches up to a car fleet right at the destination point, it will
    still be considered as one car fleet.

    Return the number of car fleets that will arrive at the destination.

    ==============================================================================
    FUNCTION: int carFleet(int target, vector<int>& position, vector<int>& speed);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
    Output: 3
    Explanation:
    The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting
    each other at 12.  The car starting at 0 does not catch up to any other
    car, so it is a fleet by itself.  The cars starting at 5 (speed 1) and 3
    (speed 3) become a fleet, meeting each other at 6. The fleet moves at speed
    1 until it reaches target.  Note that no other cars meet these fleets
    before the destination, so the answer is 3.


    --- Example 2 ---
    Input: target = 10, position = [3], speed = [3]
    Output: 1
    Explanation: There is only one car, hence there is only one fleet.


    --- Example 3 ---
    Input: target = 100, position = [0,2,4], speed = [4,2,1]
    Output: 1
    Explanation:
    The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting
    each other at 4. The fleet moves at speed 2.  Then, the fleet (speed 2) and
    the car starting at 4 (speed 1) become one fleet, meeting each other at 6.
    The fleet moves at speed 1 until it reaches target.


    *** Constraints ***
    n == position.length == speed.length
    1 <= n <= 10^5
    0 < target <= 10^6
    0 <= position[i] < target
    All the values of position are unique.
    0 < speed[i] <= 10^6

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's important to read the problem correctly.
        1. There is a ONE-LANE road! That's super important!

        2. A car can NEVER pass another car ahead of it.(Because it's a
           ONE-LANE road), but it can catch up to it, and drive bumper to
           bumper at the same speed.

    Imagine that we have 2 cars:

    speed:   20          10
            #### ->      #### ->

    Of course the faster one(one that is moving 20 miles/hour) is going to
    catch up to the slower one, but since they are in the same road, even when
    the left one(faster one) do catch up, that faster one is just going to be
    traveling right next to the slower one.

    The slower one was traveling at 10, once the faster one "catches up", its
    speed(of the faster one) is going to be reduced to 10 because it cannot
    pass the one that's ahead of it.


    speed:   10  10
            ####-#### ->
            ~~~~~~~~~~
               ^
               |
               -------------- One Car Fleet

    If cars are next-to-each-other, i.e. a Car Fleet, then they are assumed to
    have the same exact position. Even though, technically, one is behind the
    other, they are considered to have the same position.

    That's also mentioned in:
        "The distance between these two cars is ignored (i.e., they are assumed
        to have the same position)."

    Also, a single car, can be considered a Car Fleet.

    Also you may wonder - What if the car catches up at the moment they arrive
    at the destination?

    They've also mentioned that:
        "If a car catches up to a car fleet right at the destination point, it
        will still be considered as one car fleet."


    Consider the very first Example they gave to us:

    Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
    Output: 3

    Initially there are 5 Car Fleets, but when they actually arrive at the
    destination(which in this case is at position 12), the number of Car Fleets
    is 3.

    Let's represent position and speed as a pair, just for the ease of reading:

    {position, speed} = [{3, 3}, {5, 2}, {7, 1}];
    target = 10

    You can think of these pairs as linear equations. You will quickly see that
    they intersect at some point(in this example).

    (Position)
    ^         ^                         It's impossible to draw but, here,
    |        /                          {3, 3} is correctly represented.
 10 -       /                           (at time 0 it will be at position 0,
  9 -      /                             at time 1 it will be at position 6                         
  8 -     /                              at time 2 it will be at position 12,
  7 -    /                               etc.)                                 
  6 -   /
  5 -  /                                Now you have to imagine or draw in an
    | /                                 notebook or some software how the rest
  3 -/                                  is going to look like.                
    |
    |
    -----,----,----,----,----,--> (Time)
         1    2    3    4    5

    What does the intersection tell us? That from that point onward, those two
    cars, which intersected, are going to become a Car Fleet, and they will
    continue to move at the speed of the "right"(slower) one.

    Look at: {3, 3} and {7, 1} first.
    (Those are {position, speed} and not coordinates on the coordinate system)

    They will definitely intersect - Where?
    They will intersect at around 2 seconds. However, we must look at {5, 2} as
    well since it's possible that there are some cars between those two and it
    is possible that some previous car is going to "catch up" to the one in
    front of it and therefore will decrease the speed of the one in front of it
    and then that car won't be able to intersect even though it is shown on a
    coordinate system.

    Once the first car catches up some car in front, then that faster car now
    has to be drawn with a bit less steep slope because it is moving at a
    slower pace.

    It's VERY important that you draw this in order, i.e. in order in which
    cars make the fleet because it may be that the "left" car won't ever
    reach the "right" car(the one in front of it), however it can happen that
    the "right" car reaches its "right" car(the one in front of it) and then
    because of that it decreases the speed to move at a pace of the "caught up"
    one, therefore making it possible that the very first car in this story,
    will indeed, actually, "catch up" the "right" (one in front of it).

    Consider this example:
    target = 15

    {position, speed}:
    {2, 4}, {5, 8}, {10, 1}

    speed:        4           8                   1
                 ####->      ####->              ####->               @
    Position:    2           5                   10                  15
 --------------> 222233334444555566667777888899990000-              Destination
 |
 |
 |  ================================================================
 -- Note: I've used 4 spaces between the digits that denote position
 |  ================================================================
 |
 |  Once one Unit of time passes(let's say one second, or one hour), we are
 |  going to be in this situation:
 |
 |  speed:                        4              1    1
 |                               ####->         ####-####->           @
 |  Position:                    6                   11              15
 ------------->  222233334444555566667777888899990000-              Destination


    So you can see that, at the beginning, it seemed as if the very first car,
    the one with the initial speed of 4, is never going to "catch up" with the
    one in front of it(with the initial speed of 8 and position 5).

    However, since that car was very fast, it first "caught" its front(the car
    with the initial speed of 1 and position 10) and therefore has to decrease
    the speed from 8 all the way down to 1 since it became a Car Fleet with its
    front(speed 1).
    They met at position 11.

    Now the very first car still moves at speed 4, but the Car Fleet in front
    of it moves only at speed 1.

    Now it does like like it's possible that the very first car will actually
    "catch up" with the one in front of it.



    So let's go back to the very first example:

    {position, speed} = [{3, 3}, {5, 2}, {7, 1}];
    target = 10

    speed:            3       2       1
                     ####->  ####->  ####->       @
    Position:        3       5       7           10 <- Destination
 --------------> 222233334444555566667777888899990000
 |
 |
 |  ================================================================
 -- Note: I've used 4 spaces between the digits that denote position
    ================================================================

    Also note that I've drawn these cars in sorted order because that's the
    only thing that makes sense. Wouldn't we want to go through cars in sorted
    order? Of course we would, because the relative order of the cars is never
    gonna change.

    For any to cars, how do we know if they are going to intersect(collide)
    before they reach the destination?
    Try to think about this, it's the crux of this Solution.

    It may go through your mind to calculate the intersection point of some
    two cars, however there is an easier way.

    Let's look from the back - What time(in Units of time) is the last car
    going to reach the destination. Remember that the last(the most right one)
    car is NEVER going to slow down. It's impossible to "catch up" and thus
    decrease its speed because there are no cars in front of it, so that makes
    it easy for us to calculate at what time(in Units of time) will the very
    last car reach the destination.

    Since we're able to calculate that, now we can calculate the one before it
    as well - At what time(in Units of time) will the 2nd to last car reach the
    destination?

    ************************
    *** This is the Crux ***
    ************************
    If we calculate that the "2nd to last" car will reach the destination
    BEFORE the one in front of it, OR AT THE SAME TIME(because they've said so
    in the Description of the Problem), then that means that they became a Car
    Fleet!

    They became a Car Fleet somewhere in the middle between the very last one
    and the destination point, inclusive: [position of the last, destination]

    Note that they cannot collide before the position of the very last one.
    If they were on the same position, they would already be considered a Car
    Fleet.

    However they can, indeed, meet at the position of the very last one since
    the speed of the front car can be 0.


    Let's calculate to see if they are going to intersect before the
    destination point.

    {position, speed} = [{3, 3}, {5, 2}, {7, 1}];
    target = 10

    speed:            3       2       1
                     ####->  ####->  ####->       @
    Position:        3       5       7           10 <- Destination
 --------------> 222233334444555566667777888899990000
 |
 |
 |  ================================================================
 -- Note: I've used 4 spaces between the digits that denote position
    ================================================================

    How are we going to calculate at which Time they'll reach the Destination?
    It's:
        (destination - initial_position) / speed;

    Last   one will reach the Destination at: (10-7)/1 = 3
    middle one will reach the Destination at: (10-5)/2 = 2.5

    So since the middle one, the "left" one, is going to reach the destination
    before the one in front of it, then that must mean that they will intersect
    before reaching the destination. Now we know they will be a one Car Fleet.

    So we can, kind of, "delete" one of the two in this new Car Fleet and
    continue calculating for the rest. However, which one of these two should
    we "delete"?

    We'll always going to keep the one that comes ahead, i.e. we'll "delete"
    the one that comes before, the "left" one since we're told that once faster
    one "catches up", it starts to move at the speed of the "caught one", i.e.
    the one that is in the front.

    So we can just remove the left one.

    This is why we didn't calculate the first two cars, since it would be
    harder to know if they'll collide or not because it's possible for the
    2nd one to slow down at some point and then let the first one "catch up".

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    That was the purpose of the one example above. Of this one:
    target = 15

    {position, speed}:
    {2, 4}, {5, 8}, {10, 1}

    speed:        4           8                   1
                ####->       ####->              ####->               @
    Position:    2           5                   10                  15
 --------------> 222233334444555566667777888899990000-              Destination
 |
 |
 |  ================================================================
 -- Note: I've used 4 spaces between the digits that denote position
 |  ================================================================
 |
 |  Once one Unit of time passes(let's say one second, or one hour), we are
 |  going to be in this situation:
 |
 |  speed:                        4              1    1
 |                               ####->         ####-####->           @
 |  Position:                    6                   11              15
 ------------->  222233334444555566667777888899990000-              Destination

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    So that's why we have to go from the back and calculate these.

    Now let's continue with our original Example 1. We were here:

    {position, speed} = [{3, 3}, {5, 2}, {7, 1}];
    target = 10

    speed:            3       2       1
                     ####->  ####->  ####->       @
    Position:        3       5       7           10 <- Destination
                 222233334444555566667777888899990000

    And now after calculating that the last one and the middle one are going to
    make a Car Fleet, we're at this state:

    speed:                        3      1    1
                                 ####-> ####-#### @
    Position:                    6           9   10 <- Destination
                 222233334444555566667777888899990000


    Now we're left with only 2 Cat Fleets. The first one consists of a single
    car and the second Car Fleet consists of two cars.

    Let's calculate at which point they'll reach the destination:

    1st(left  one): (10 - 6) / 3 = 1.33333

    2nd(right one): (10 - 9) / 1 = 1


    The part where we go through the cars is O(n), however because we have to
    sort the Input, that makes the overall Time Complexity: O(n * logn).

    As for Space Complexity we're going to have: O(n) since we are going to be
    using a Stack and we're going to make a vector of pairs.


    So here's how we are going to implement this:

    We will make an Empty Stack at first and we'll go through the cars in
    reverse order, as we've already concluded, and add the very last car to the
    Stack(that is empty at this point).

    Now continue traversing and pushing to the stack. Every time we have more
    than 1 car on the Stack, we calculate if they will collide and then if they
    do, we just pop the car on the top(the one we're "traversing" right now).

    And what we'll end up return is the number of Car Fleets that exists at the
    end of the entire Algorithm which we can get easily because we just take
    the size of the Stack and that will tell us how many Car Fleets we actually
    have.

    In this case, it's just going to be a single one.


    Let's do a quick Simulation for Example 1:

    {position, speed} = [{3, 3}, {5, 2}, {7, 1}];
    target = 10


    1.
        ---------------------
        | Empty
        ---------------------



    2.
        ---------------------
        | {7, 1}
        ---------------------

        speed:            3       2       1
                         ####->  ####->  ####->       @
        Position:        3       5       7           10 <- Destination
                     222233334444555566667777888899990000



    3.
                                  More than 1 car
        ---------------------    (calculate if collide)    ------------------
        | {7, 1} | {5, 2}       ------------------------>  | {7, 1}
        ---------------------     they collide - Pop       ------------------

        speed:                        3      1    1
                                     ####-> ####-#### @
        Position:                    6           9   10 <- Destination
                     222233334444555566667777888899990000



    4.
                                  More than 1 car
        ---------------------    (calculate if collide)    ------------------
        | {7, 1} | {3, 3}       ------------------------>  | {7, 1} | {3, 3}
        ---------------------     they DON'T collide       ------------------



    At the end:
        return stack.size();
*/

/* Time  Beats: 63.78% */
/* Space Beats: 52.60% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed)
    {
        const int N = position.size();
        vector<pair<int, int>> combined;

        for (int i = 0; i < N; i++)
            combined.push_back( {position[i], speed[i]} );

        // Sort in DESCENDING order
        sort(combined.rbegin(), combined.rend());

        vector<double> stack;
        for (auto& [curr_position, curr_speed] : combined)
        {
            stack.push_back(1.0 * (target - curr_position) / curr_speed);

            if (stack.size() >= 2 && stack[stack.size() - 1] <= stack[stack.size() - 2])
                stack.pop_back();
        }

        return stack.size();
    }
};
