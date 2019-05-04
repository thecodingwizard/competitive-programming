## Convex Hull
1. Sort points by x-value, then y-value

2. Loop through points
   a. Add point
   b. If the first three points form a left-turn, delete the 2nd to last point

3. At the last point, we have found the upper convex hull. Repeat to find the
   lower convex hull, but check for right turns instead of left turns.

## Finding if two line segments intersect
1. Compute cross product of one endpoint of one segment to the endpoints of the
   other two segments. Multiplied together, it should be <= 0.

2. Do the same for the other segment. Each computation determines if the segment's
   endpoints lie on opposite sides of the segment.