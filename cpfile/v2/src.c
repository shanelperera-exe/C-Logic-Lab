#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Seed the random number generator
    int mood = rand() % 2;  // Randomly choose 0 or 1

    printf("Checking if your computer is in a good mood today...\n");
    
    if (mood) {
        printf("🎉 Your computer is happy! Everything should work fine today. 🎉\n");
    } else {
        printf("💀 Uh-oh! Your computer woke up on the wrong side of the motherboard. Expect bugs. 💀\n");
    }

    return 0;
}