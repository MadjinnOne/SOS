#include "leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Comparaison pour le tri décroissant
int compare(const void *a, const void *b) {
    LeaderboardEntry *entryA = (LeaderboardEntry *)a;
    LeaderboardEntry *entryB = (LeaderboardEntry *)b;
    return entryB->score - entryA->score;
}

void trierLeaderboard(LeaderboardEntry *entries, int numEntries) {
    qsort(entries, numEntries, sizeof(LeaderboardEntry), compare);
}

void lireLeaderboard(const char *filename, LeaderboardEntry *entries, int *numEntries) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        *numEntries = 0;
        return;
    }

    int i = 0;
    while (i < MAX_ENTRIES && fscanf(file, "%49s %d", entries[i].name, &entries[i].score) == 2) {
        i++;
    }

    *numEntries = i;

    fclose(file);
}

void ajouterEntreeLeaderboard(const char *filename, const char *name, int score) {
    LeaderboardEntry entries[MAX_ENTRIES];
    int numEntries;

    lireLeaderboard(filename, entries, &numEntries);

    int insertIndex = -1;
    for (int i = 0; i < numEntries; i++) {
        if (score > entries[i].score) {
            insertIndex = i;
            break;
        }
    }

    if (insertIndex != -1) {
        for (int i = MAX_ENTRIES - 1; i > insertIndex; i--) {
            entries[i] = entries[i - 1];
        }
        strncpy(entries[insertIndex].name, name, MAX_NAME_LENGTH);
        entries[insertIndex].score = score;

        if (numEntries < MAX_ENTRIES) {
            numEntries++;
        }
    } else if (numEntries < MAX_ENTRIES) {
        strncpy(entries[numEntries].name, name, MAX_NAME_LENGTH);
        entries[numEntries].score = score;
        numEntries++;
    } else {
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < numEntries; i++) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
}
