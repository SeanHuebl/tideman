# Tideman
## This Project Is Homework From Harvard's CS50 Class. Per Their Academic Honesty Policy You Are NOT Allowed To Use This code As A Submission For Your Homework!

Project: Tideman | Language: C

For this homework assignment, we had an option of an easier or a harder problem. I chose the harder option. The homework was to implement a Tideman style election.This assignment is one that I am very proud of, as it was definately one of the hardest problems I have faced in my coding journey so far. 
It was my first time working with 2D arrays, as well as custom data structs, and navigating directed graphs.It took me quite a long time to wrap my head around the problem, but when I finally solved it I felt like I could accomplish anything with code!

Implementation of a Tideman style election in C



The assignment was as follows:

Complete the implementation of tideman.c in such a way that it simulates a Tideman election.

Complete the vote function.
The function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate, then you should update the ranks array to indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)

Recall that ranks[i] here represents the user’s ith preference.
The function should return true if the rank was successfully recorded, and false otherwise (if, for instance, name is not the name of one of the candidates).
You may assume that no two candidates will have the same name.

Complete the record_preferences function.
The function is called once for each voter, and takes as argument the ranks array, (recall that ranks[i] is the voter’s ith preference, where ranks[0] is the first preference).
The function should update the global preferences array to add the current voter’s preferences. Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.
You may assume that every voter will rank each of the candidates.

Complete the add_pairs function.
The function should add all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
The function should update the global variable pair_count to be the number of pairs of candidates. (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).

Complete the sort_pairs function.
The function should sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.

Complete the lock_pairs function.
The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.

Complete the print_winner function.
The function should print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.

