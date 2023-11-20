#include <iostream>
#include <vector>
#include <unordered_set>

/*

    ============
    Description:
    ============

    There are N points on a plane, a numbered from 0 to N-1; the coordinates of
    the K-th point are (X[K], Y[K]). Find any triangle with vertices at three
    of the given points, such that no other point lies inside this triangle
    (and no other points, except vertices, on the boundary of the triangle).

    The triangle must have a positive area.

    Write a function:
    =======================================================
    FUNCTION: int solution(vector<int>& X, vector<int>& Y);
    =======================================================

    that, given two arrays X and Y consisting of N integers each, representing
    points on the plane, returns an array B consisting of exactly three
    integers, such that the points with indices B[0] B[1] and ZB[2] form an
    empty triangle.

    If there is no such triplet, return an empty array instead.

    --- Example 1 ---
    X = [1, 4, 3, 2, 3]
    Y = [4, 3, 1, 1, 2]
    Output: (There are multiple correct answers such as): [0, 1, 4] or [4, 2, 3]
    Explanation:
    The function could return [0, 1, 4], since points 0, 1 and 4 form an empty
    triangle. Answer [0, 1, 2] would be incorrect, since triangle 0, 1, 2
    contains point 4 inside. Answer [0, 1, 3] would be incorrect, since
    trinagle 0, 1, 3 contains point 4 on the boundary. Answer [1, 3, 4] would
    be incorrect, since 1, 3, 4 do not form a triangle with positive area.
    Answer [4, 2, 3] would be considered correct, since points 2, 3, 4 also
    form an empty triangle.


    --- Example 2 ---
    X = [0]
    Y = [0]
    Output: (This is the only possible answer) {} // i.e. an empty vector


    --- Example 3 ---
    X = [0, 1, 2, 4, 4, 5, 6]
    Y = [0, 1, 2, 3, 4, 5, 6]
    Output: (There are multiple correct answers such as): [0, 1, 3] or [2, 3, 4], etc.


    --- Example 3 ---
    X = [0, 1, 3, 0, 0, 2]
    Y = [3, 0, 0, 1, 2, 0]
    Output: (There are multiple correct answers such as): [0, 1, 4] or [1, 3, 5], etc.


    *** Constraints ***
    N is an integer within the range [1 .. 300 000];
    Each element of arrays X and Y is an integer within the range [0 .. 1 000 000 000];
    Given N points are pairwise distinct.

*/

/*
	------------
	--- IDEA ---
	------------

	There are two approaches:

	1. Calculate 3 area from the point P to every two point in the triangle:
		area_1 = P, A, B
		area_2 = P, A, C
		area_3 = P, B, C

		total_area = A, B, C

		if (total_area == area_1 + area_2 + area_3)
			it's INSIDE the triangle or ON the triangle itself
		else
			it's OUTSIDE of the triangle
	


	2. Disastrous formula:
	    w1 = (Ax * (Cy - Ay) + (Py - Ay) * (Cx - Ax) - Px * (Cy - Ay)) / ((By - Ay) * (Cx - Ax) - (Bx - Ax) * (Cy - Ay))

		w2 = (Py - Ay - w1 * (By - Ay)) / (Cy - Ay)


		if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1)
		    Point P is inside triangle ABC
		else
			Point P is OUTSIDE the triangle or ON the triangle itself

*/
struct Point2D{
    int x;
    int y;

    Point2D(int xx, int yy)
        : x(xx), y(yy)
    {}
};

class Solution {
public:
    std::vector<int> solution(std::vector<int>& X, std::vector<int>& Y)
    {
        const int N = X.size();

        std::vector<int> points;
        std::unordered_set<int> used_points;

        for (int i = 0; i < N-2; i++)
        {
            points.push_back(i);
            used_points.insert(i);

            if (backtracking(X, Y, points, used_points, i+1))
                return points;

            points.pop_back();
            used_points.erase(i);
        }

        return {};
    }

private:
    bool backtracking(std::vector<int>& X,
                      std::vector<int>& Y,
                      std::vector<int>& points,
                      std::unordered_set<int>& used_points,
                      int start)
    {
        const int N = X.size();

        if (points.size() == 3)
        {
            Point2D A(X[points[0]], Y[points[0]]);
            Point2D B(X[points[1]], Y[points[1]]);
            Point2D C(X[points[2]], Y[points[2]]);

            if (area_of_triangle(A, B, C) == 0)
                return false;

            for (int i = 0; i < N; i++)
            {
                if (used_points.find(i) != used_points.end()) // used
                    continue;

                Point2D P(X[i], Y[i]);

                if (point_in_triangle(A, B, C, P))
                    return false;
            }

            return true; // We have found an empty-triangle that has Area > 0
        }

        for (int i = start; i < N; i++)
        {
            points.push_back(i);
            used_points.insert(i);

            if (backtracking(X, Y, points, used_points, i+1))
                return true;

            points.pop_back();
            used_points.erase(i);
        }

        return false;
    }

    bool point_in_triangle(Point2D A, Point2D B, Point2D C, Point2D P)
    {
            double s1 = C.y - A.y;
            double s2 = C.x - A.x;
            double s3 = B.y - A.y;
            double s4 = P.y - A.y;

            double w1 = (A.x * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (B.x-A.x) * s1);
            double w2 = (s4- w1 * s3) / s1;

            return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
    }

private:
    double area_of_triangle(Point2D A, Point2D B, Point2D C)
    {
        double area = 0.5 * std::abs(A.x * (B.y - C.y) +
                                     B.x * (C.y - A.y) +
                                     C.x * (A.y - B.y));

        return area;
    }

};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> X = {1, 4, 3, 2, 3};
    // std::vector<int> Y = {4, 3, 1, 1, 2};

    /* Example 2 */
    // std::vector<int> X = {0};
    // std::vector<int> Y = {0};

    /* Example 2 */
    // std::vector<int> X = {0, 1, 2, 4, 4, 5, 6};
    // std::vector<int> Y = {0, 1, 2, 3, 4, 5, 6};

    /* Example 3 */
    std::vector<int> X = {0, 1, 3, 0, 0, 2};
    std::vector<int> Y = {3, 0, 0, 1, 2, 0};


    std::cout << "\n\t==========================";
    std::cout << "\n\t=== NON-EMPTY TRIANGLE ===";
    std::cout << "\n\t==========================\n\n";


    /* Write Input */

    /* Print X */
    bool first = true;
    std::cout << "\n\tX: [";
    for (auto x: X)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";

    /* Print Y */
    first = true;
    std::cout << "\n\tY: [";
    for (auto x: Y)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    std::vector<int> results = sol.solution(X, Y);


    /* Write Output */
    first = true;
    std::cout << "\n\tResult: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
