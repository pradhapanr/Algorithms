# QuickHull

## An algorithm made to compute the convex hull with a QuickSort style algorithm.

### <b>What is the Convex Hull?</b>

The convex hull of a shape is the smallest convex set that contains it. In this case, our input for this program would be a file that contains coordinates for points that could be plotted on a two dimensional graph.

The convex hull contains the smallest set of points that when lines are drawn between each point to create an outline, would border every other point in the data set.

<img src="https://ars.els-cdn.com/content/image/3-s2.0-B9781785482434500050-f05-07-9781785482434.jpg">

<hr>

### <b>Explanation of the Algorithm</b>

The QuickHull algorithm takes inspiration from QuickSort by using a divide and conquer strategy by choosing an appropriate line segment to seperate the dataset or "hull" into two seperate pieces. Each time, the hull adds the point furthest from this line segment created, and eventually is composed of the furthest out points that encompass every other point in the graph. This is done recursively, with the base case being that there are no further points left past that line segment. 

<img src="https://upload.wikimedia.org/wikipedia/commons/4/42/Animation_depicting_the_quickhull_algorithm.gif">  

<hr>

### <b>Instructions for Execution</b>
A makefile has been provided for execution of the program.
Simply open a terminal inside the QuickHull directory and input the following command to make the QuickHull executable:

````
make all
````

To run the program, a file must be passed in as an argument. An example text file is already in the repository if you would like to see a demo. This is done with the command:

````
./QuickHull points.txt
````

The program output will be all of the points that make up the convex hull for that data set.

