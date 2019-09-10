# Convex-Hull-Algorithms
Algortihms to solve the Convex Hull problem:



1.)Jarivs March:
In computational geometry, the gift wrapping algorithm is an algorithm for computing the convex hull of a given set of points the algorithm is also known as Jarvis march, named after R. A. Jarvis, who published it in 1973; it has O(nh) time complexity, where n is the number of points and h is the number of points on the convex hull. Its real-life performance compared with other convex hull algorithms is favorable when n is small or h is expected to be very small with respect to n. In general cases, the algorithm is outperformed many algortihms and also by the following algorithms.

2.)Graham's Scan:
Graham's scan is a method of finding the convex hull of a finite set of points in the plane with time complexity O(n log n). The algorithm finds all vertices of the convex hull ordered along its boundary. It uses a stack to detect and remove concavities in the boundary efficiently.

3.) KirkPatrick-Seidel:
The Kirkpatrick–Seidel algorithm, called by its authors "the ultimate planar convex hull algorithm", is an algorithm for computing the convex hull of a set of points in the plane, with O(nlog h) time complexity, where n is the number of input points and h is the number of points on the hull. Thus, the algorithm is output-sensitive: its running time depends on both the input size and the output size. Another output-sensitive algorithm, the gift wrapping algorithm, was known much earlier, but the Kirkpatrick–Seidel algorithm has an asymptotic running time that is significantly smaller and that always improves on the O(nlog n) bounds of non-output-sensitive algorithms. The Kirkpatrick–Seidel algorithm is named after its inventors, David G. Kirkpatrick and Raimund Seidel. Although the algorithm is asymptotically optimal, it is not very practical for moderate-sized problems.
