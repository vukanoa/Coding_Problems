#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1094) Car Pooling
    ===========================

    ============
    Description:
    ============

    There is a car with capacity empty seats. The vehicle only drives east
    (i.e., it cannot turn around and drive west).

    You are given the integer capacity and an array trips where trips[i] =
    [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi
    passengers and the locations to pick them up and drop them off are fromi
    and toi respectively. The locations are given as the number of kilometers
    due east from the car's initial location.

    Return true if it is possible to pick up and drop off all passengers for
    all the given trips, or false otherwise.

    ====================================================================
    FUNCTION: bool carPooling(vector<vector<int>>& trips, int capacity);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: trips = [[2,1,5],[3,3,7]], capacity = 4
    Output: false

    --- Example 2 ---
    Input: trips = [[2,1,5],[3,3,7]], capacity = 5
    Output: true


    *** Constraints ***
    1 <= trips.length <= 1000
    trips[i].length == 3
    1 <= numPassengersi <= 100
    0 <= fromi < toi <= 1000
    1 <= capacity <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    First of all, it's logical that we'd want to have "trips" sorted in
    ascending order by second value(index 1, i.e. "from" values).

    Why is that logical?

    Because they did NOT say "trips" are already in sorted order by any of the
    fields, therefore since we want to take passengers as we go, we must have
    them in sorted order by "from" values.

    Otherwise, if we had not done that, then we could first take passengers at
    station("from", i.e. x kilometers from the starting point) 7, but not yet
    have passengers that we were waiting at station 3.

    Look at the road:

                4 waitings passengers

                      |
                      |                2 waitings passengers
                      |                    |
                      v                    v

    0                 3                    7                                 ?
    <-----------------|--------------------|--------------------------------->
    WEST                                                                  EAST


    Imagine if we took those 2 passengers, waiting at "station" 7, first.
    That wouldn't make any sense.

    If a car goes strictly from the East to the West, then how is it possible
    to first take those 2 waiting passengers at station 7, than those 4 at
    "station" 3?

    It's not. It's absurd.

    Precisely because of that we MUST sort in ASCENDING order by the
    second(index 1) value.


    Imagine we had this input:
        trips = [[2,1,4],[9,0,3],[8,5,6],[3,3,7]]
                    ^       ^       ^       ^
                    |       |       |       |
                    ---- --------------------
                        |
    After sorting by second value(index 1), we'll have this:

        trips = [[9,0,3],[2,1,4],[3,3,7],[8,5,6]]

-------------------------------------------------------------------------------
    Only now can we begin thinking about the real Solution.

    Let's say:
        capacity = 11

    1. [9,0,7]

        The first trip we'll "hit" when going from West to East is:
            [9,0,7]

        Remember:
        index[0] - Number of passengers
        index[1] - from (starting "station", i.e. in kilometers from beginning)
        index[2] - to   (ending   "station", i.e. in kilometers from beginning)

        So, we take first trip's passengers:
        capacity = capacity - 9 ==> capacity = 11 - 9 ==> capacity = 2

        We also must somehow memorize when to drop these 9 passengers.
        We are going to do that by pushing a pair of values to a minimum heap.

        min_heap.push( {to, Number_of_passengers} )

        Now our min_heap looks like this:
            min_heap = [ {3,9} ];

        As you can see, we'll push a pair of (to, Number_of_passengers) because
        we want a Minimum Heap to be "balancing" itself based on an "ending
        station"(i.e. "to", i.e. index[2]), since we want to know the EARLIEST
        "station" to the East at which we must drop off passengers.


    2. [2,1,4]

        Then we get to the next trip:
            [2,1,4]

        Before taking this trip's passengers, we, first, have to check if
        before this trip's second value(index 1), we've "surpassed" some
        "ending stations" that we've put in our min_heap.

        Remember how we've put a pair {to, Number_of_passengers} in a Heap?
        "Number_of_passengers are now, "Number_of_passengers_to_drop_off",
        since we got them in our car at the moment.

        Therefore, before taking new passengers in this next trip, we first
        must check if before arriving at THIS TRIP's "starting station"(i.e.
        "from"), we were supposed to drop off some passengers.

        Since in our Heap, we only have: [ {3,9} ], meaning - EARLIEST station
        at which we must drop off passengers is station 3.

        Currently, since we see that this trip's "starting station"(i.e.
        "from") is equal 1, then that means we still don't have to drop off any
        passengers in our car.

        We can proceed to check if we can put all of the passengers at current
        trip's "station" to our car.

        Currently:
            capacity = 2

        This trip's "Number_of_passengers" is 2.


        If (capacity < Number_of_passengers)
            Then we MUST return "false"

        However, the upper condition is NOT true, therefore, we can take all
        passengers, i.e. all 2, i.e. both passengers.

        Then we update our capacity:
            capacity = capacity - Number_of_passengers ==> capacity = 2 - 2 = 0

        And we must push {to, Number_of_passengers} to our min_heap:
            min_heap = [ {3,9}, {4,2},];



    3. [3,3,7]

        Then we proceed to 3rd trip(i.e. trips at index 2):
            [3,3,7]

        Again, first, we must check if before this "stating station"(i.e.
        "from") equal 3, we had some "ending stations" in our min_heap.

        If we had, then that means we've had to drop off passengers whose
        "ending stations" are <= 3.

        Our min_heap looks like this:
            min_heap = [ {3,9}, {4,2} ];
                           ^
                           |
                          top

        min_heap.top() <==> {3,9}

        Clarification:
            min_heap.top().first  --> "ending station"(i.e. "to")
            min_heap.top().second --> "Number_of_passengers"


        Since min_heap.top().first <= 3(current trip's "starting
        station"("from") )
        then we must drop 9 passengers that are assosiated with
        "ending station 3".

        Therefore:
            capacity += min_heap.top().second;
            min_heap.pop().


        However, there doesn't have to be, at max, one station before the
        current one at which we had to drop off passengers.

        There can be either:
            None, one or even multiple "stations"
        at which we had to drop off passengers before this "starting station"
        we're currently on. ("starting station 3" in this case)

        Therefore:
            capacity += Number_of_passengers ==> capacity += 9 ==> capacity = 9


        Now our min_heap looks like this:
            min_heap = [ {4,2} ];

        Since min_heap.top().first is NOT <= from, we can proceed to check if
        there are enough seats to take all current's 3 passengers at this
        "starting station 3".

        Currently:
            capacity = 9

        if (capacity < current_trip_number_of_passengers)
            // we would return false

        However, since this condition is NOT true, we can decrement current
        trip's number of passengers from the capacity.

        capactiy = capacity - 3 ==> capacity = 9 - 3 ==> capacity = 6

        And we must push {"to", current_trip_number_of_passengers} to min_heap.

        Now our min_heap looks like this:
            min_heap = [ {4,2} {7,3} ];


    4.  [8,5,6]

        And last trip
        [8,5,6]
           ^
           |
           |
          from

        We check if before "starting station 5" there were some "ending
        stations" along the way.

        Now our min_heap looks like this:
            min_heap = [ {4,2} {7,3} ];

        We check that by:
            while (!min_heap.empty() && min_heap.top().first <= from)
            {
                capacity -= min_heap.top().second;
                min_heap.pop();
            }

        "ending station 4" was before current trip's "starting station",
        therefore we had to drop off passengers assosiated with that "ending
        station".

        As min_heap.top().second value says, we had to drop 2 passengers.

        Therefore:
            capacity = capacity + 2 ==> capacity = 6 + 2 ==> capacity = 8

        Now our min_heap looks like this:
            min_heap = [ {7,3} ];

        if (capacity < current_trip_number_of_passengers)
            // we would return false

        However, since this condition is NOT true, we can decrement current
        trip's number of passengers from the capacity.

        capactiy = capacity - 8 ==> capacity = 8 - 8 ==> capacity = 0

        And we must push {"to", current_trip_number_of_passengers} to min_heap.

        Now our min_heap looks like this:
            min_heap = [ {4,2} {8,6} ];

        Since there are no more trips and we haven't returned "false" at any
        point, we can conclude that we are indeed able to pick up and drop off
        all of the passengers in all of these trips in this sequence.

        Hence, we return true.

*/

/* Time  Beats: 99.48% */
/* Space Beats: 60.01% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity)
    {
        // O(n * logn)
        // Sort by index 1's value(second element out of 3) in ASCENDING order
        std::sort(trips.begin(), trips.end(), [](const std::vector<int>& a,
                                                 const std::vector<int>& b)
                                                {
                                                    return a[1] < b[1];
                                                });

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> min_heap;

        // O(n * logk)
        for (std::vector<int>& trip : trips)
        {
            int to_take_passengers = trip[0];
            int from = trip[1];
            int to = trip[2];

            /*
                min_heap.top().first <==> Earliest destination from some trip
                                          that already started(its passengers
                                          are currently in the car)
            */
            while (!min_heap.empty() && min_heap.top().first <= from)
            {
                int to_drop_passengers = min_heap.top().second;
                min_heap.pop(); // O(logk)

                capacity += to_drop_passengers;
            }

            if (capacity < to_take_passengers)
                return false;

            capacity -= to_take_passengers;
            min_heap.push( {to, to_take_passengers} ); // O(logk)
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a similar approach to a last Solution in this file(I've explained
    that one before this one, that's why I'm referring it from here).

    The point is that at a given "station" we can have multiple "takings" or
    "drop offs"(or both, of course, but that is implicit in logical OR).

    Therefore, we need a HashMap where we can have "stations" as keys and all
    the different values associated with that key, hence a MultiMap.

    (We could use a basic Map(aka "TreeMap" in other languages)), however then
    we'd have to use a vector as values and then we'd have to iteratore over
    that as well.

    To prevent multiple indendation, we're going to be using a MultiMap here.

    As I've said, we can "take" and/or "drop off" passengers at any "station"
    and we can do that multiple times per "action"(i.e. "take" or "drop off").

    However, our capacity CANNOT be below zero AFTER WE'RE DONE WITH PROCESSING
    SOME STATION.


    Example:

        trips = [[0,-4], [2,-2], [4,-5], [5,-1], [7,-2], [7,4], [7,5], [9,1]]
        capacity = 13

             MultiMap
        |  Key  :  Value |
        +----------------+
        |   0   :   -4   |
        +----------------+
        |   2   :   -2   |
        +----------------+
        |   4   :   -5   |
        +----------------+
        |   5   :   -1   |
        +----------------+
        |   7   :   -3   |
        +----------------+
        |   7   :   +4   |
        +----------------+
        |   7   :   +5   |
        +----------------+
        |   9   :   +1   |
        +----------------+
        |   9   :   +2   |
        +----------------+
        |  11   :   +3   |
        +----------------+


                        Initial capacity: 13

        Station  0  -->   capacity += -4       // capacity = 9

        Station  2  -->   capacity += -2       // capacity = 7

        Station  4  -->   capacity += -5       // capacity = 2

        Station  5  -->   capacity += -1       // capacity = 1

        Station  7  -->   capacity += -3       // capacity = -2
        Station  7  -->   capacity += +4       // capacity = 2
        Station  7  -->   capacity += +5       // capacity = 7

        Station  9  -->   capacity += +1       // capacity = 8
        Station  9  -->   capacity += +2       // capacity = 10

        Station 11  -->   capacity += +3       // capacity = 13



    Notice two importants things:
        1. Keys are sorted in ASCENDING order BY THE KEY, however, they are NOT
           by any means sorted by the values as well! Values appear next to
           keys in order in which they were inserted to the MultiMap!
           That is VERY imporant to notice.


        2. capacity CAN be less than zero ONLY while there are unprocessed
           passengers FOR THAT STATION.

           Look at "Station 7", it takes on 3 passengers and capacity becomes:
               -2
           however, since there are more passengers to take on and/or drop off
           then we must NOT return false immediately.

           But, if we process the last key-value pair for that key(station) and
           our capacity is LESS than 0, then and only then do we return false
           immediately!

           This line in the code, down below, is crucial:

               if(capacity < 0 && iter->first != iter_next->first)
                   return false;

*/

/* Time  Beats: 55.99% */
/* Space Beats: 20.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(m) */
class Solution_Multimap {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity)
    {
        std::multimap<int, int> multi_map;

        for(int i = 0; i < trips.size(); i++)
        {
            int num_passengers = trips[i][0];
            multi_map.insert( {trips[i][1], -num_passengers} ); // From
            multi_map.insert( {trips[i][2],  num_passengers} ); // To
        }

        for (auto iter = multi_map.begin(); iter != multi_map.end(); iter++)
        {
            capacity += iter->second;

            auto iter_next = iter;
            ++iter_next;

            // The main part comes here because for a particular interval we
            // have to check until the next value is not same
            if(capacity < 0 && iter->first != iter_next->first)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since the upper bound of trips.length is 1001, we can initialize an array
    on the Stack of size 1001 with 0 values as their default.

    Then, the only thing we have to do is use it as a "hash map". We have to
    add all the passegers for a given "from" station and we have to subtract
    all of the passengers from a given "to" station.


    Example:
        trips = [[9,0,3],[2,1,4],[3,3,7],[8,5,6]]

    the "stops" or rather "stations" we are going to add and subtract values in
    are:

         |  |     |  |  |  |  |
         v  v     v  v  v  v  v
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ..., 0]
         0  1  2  3  4  5  6  7  8  9      1000

    These pointed slots are the ONLY "stations" at which we have take to drop
    off passengers.

    Since all of the other slots(i.e. "stations") are 0, they will not
    interfere with our calculations.

    This is how our array will look after processing every "trip" one by one:

    Before:

        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ..., 0]
         0  1  2  3  4  5  6  7  8  9      1000


    1. [9, 0, 3]
           |  |_____
         __|       |
         |         |
         v         v
        [9, 0, 0, -9, 0, 0, 0, 0, 0, 0, ..., 0]
         0  1  2   3  4  5  6  7  8  9      1000



    2. [2, 1, 4]
           |  |_________
           |_          |
            |          |
            v          v
        [9, 2, 0, -9, -2, 0, 0, 0, 0, 0, ..., 0]
         0  1  2   3   4  5  6  7  8  9      1000



    3. [3, 3, 7]
           |  |___________________
           |________             |
                   |             |
                   v             v
        [9, 2, 0, -6, -2, 0, 0, -3, 0, 0, ..., 0]
         0  1  2   3   4  5  6   7  8  9      1000



    4. [8, 5, 6]
           |  |________________
           |_______________   |
                          |   |
                          v   v
        [9, 2, 0, -6, -2, 8, -8, -3, 0, 0, ..., 0]
         0  1  2   3   4  5   6   7  8  9      1000


                        Initial capacity: 11

    capacity -= 9                         // capacity = 2
    capacity -= 2                         // capacity = 0
    capacity -= 0                         // capacity = 0
    capacity -= -6 ==> capacity += 6      // capacity = 6
    capacity -= -2 ==> capacity += 2      // capacity = 8
    capacity -= 8                         // capacity = 0
    capacity -= -8 ==> capacity += 8      // capacity = 8
    capacity -= -3 ==> capacity += 3      // capacity = 11



    Out capacity must NOT get below the zero at any point. If it happens to get
    below zero, we immediately return false.

    Otherwise we've been able to take and dropp off every passenger using our
    car with given capacity.


    As you can see, our capacity wasn't below zero at any point, therefore we
    can return true.

*/

/* Time  Beats: 78.33% */
/* Space Beats: 60.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(m) */
class Solution_Multimap_Thousand_and_One_Stops {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity)
    {
        int stops[1001] = {};

        for (auto& trip : trips)
        {
            stops[trip[1]] += trip[0]; // Take people in car at "From" station
            stops[trip[2]] -= trip[0]; // take people in car at "To"   station
        }

        for (int i = 0; capacity >= 0 && i < 1001; i++)
            capacity -= stops[i];

        return capacity >= 0;
    }
};
