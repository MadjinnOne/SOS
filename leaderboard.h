#pragma once

#define MAX_ENTRIES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} LeaderboardEntry;

void lireLeaderboard(const char *filename, LeaderboardEntry *entries, int *numEntries);
void ajouterEntreeLeaderboard(const char *filename, const char *name, int score);
int compare(const void *a, const void *b);
void trierLeaderboard(LeaderboardEntry *entries, int numEntries);
