#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int generateRandomNumber(int min, int max);
// Structure to hold player information
struct Player {
    char name[50];
    int score;
};
int generateRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void saveScore(struct Player *player) {
    FILE *file = fopen("scores.txt", "a");
    if (file == NULL) {
        printf("Unable to open the score file.\n");
        return;
    }

    fprintf(file, "%s %d\n", player->name, player->score);
    fclose(file);
}

void displayHighScore() {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("No high scores found.\n");
        return;
    }

    printf("High Scores:\n");
    printf("------------\n");

    struct Player player;
    while (fscanf(file, "%s %d", player.name, &player.score) != EOF) {
        printf("Player: %s\tScore: %d\n", player.name, player.score);
    }
    fclose(file);
}


int main(){
    struct Player *player;
    player = (struct Player *)malloc(sizeof(struct Player));

    printf("Welcome to the Number Guessing Game!\n");
    printf("Enter your name: ");
    scanf("%s", player->name);

    printf("Hello, %s! Let's play!\n", player->name);

    int randomNumber, guess;
    int attempts = 0;
    srand(time(0));
    randomNumber = generateRandomNumber(1, 100);

    printf("I'm thinking of a number between 1 and 100. Can you guess it?\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        if (guess > randomNumber) {
            printf("Too high! Try again.\n");
        } else if (guess < randomNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("Congratulations, %s! You guessed the number %d in %d attempts!\n", player->name, randomNumber, attempts);
            player->score = attempts;
            saveScore(player);
        }
    } while (guess != randomNumber);

    printf("Your best score is %d attempts.\n", player->score);

    int option;
    printf("Options:\n");
    printf("1. Check scores\n");
    printf("2. Play Again\n");
    printf("3.Quit\n");
    printf("Select an option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            displayHighScore();
            break;
        case 2: main();
               break;
        case 3:
            printf("Thanks for playing!\n");
            break;
        default:
            printf("Invalid option. Exiting...\n");
            break;
    }

    free(player);

    return 0;

}

