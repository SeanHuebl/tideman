#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int win, int lose);
bool check_edge(int node);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate over each candidate and see if the vote name is in the list
    for (int i = 0; i < candidate_count; i++)
    {
        // If name is on list
        if (strcmp(candidates[i], name) == 0)
        {
            // Update ranks array with rank vote and return true
            ranks[rank] = i;
            return true;
        }
    }
    // If name is not part of voter list return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Set ranks to a new array where index = candidate number and value = ranking
    int places[candidate_count];
    for (int n = 0; n < candidate_count; n++)
    {

        places[ranks[n]] = n;
    }

    // For each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // For each candidate compare ranks of candidate i vs candidate j
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate i is higher rank than j, update value at [i][j]
            if (places[i] < places[j])
            {
                preferences[i][j]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] != 0)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count ++;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int victory_strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        victory_strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    for (int i = 0, temp = 0; i < pair_count - 1; i++)
    {
        if (victory_strength[i] < victory_strength[i + 1])
        {
            pair pair_temp;
            temp = victory_strength[i];
            pair_temp = pairs[i];

            victory_strength[i] = victory_strength[i + 1];
            pairs[i] = pairs[i + 1];

            victory_strength[i + 1] = temp;
            pairs[i + 1] = pair_temp;
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                // If candidate i has a connection to the left of it, break out of loop
                if (check_edge(i) == true)
                {
                    break;
                }

                // If candidate has no connection to the left, it is a winner
                else
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }

    return;
}

bool check_cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }

    else
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (locked[end][i])
            {
                if (check_cycle(start, i))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Function to look to left of input node to see if something is connected to it
bool check_edge(int node)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][node])
        {
            return true;
        }
    }
    
    return false;
}