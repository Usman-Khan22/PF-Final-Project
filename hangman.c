#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_ATTEMPTS 6

void generateWord(char* word, int choice);
void initGuessedWord(char* guessedWord, char* word);
void printGuessedWord(char* guessedWord);
void addGuess(char* guessedLetters, char guess);
char checkInput(char* guessedLetters);
void logic(char* word, char guess, char* guessedWord, int* wrongattempts);
void giveHint(int choice);
void drawHangman(int wrong_attempts);

int main() {
    char word[50], guessedWord[50], guessedLetters[50] = {'\0'};
    char guess, again[50];
    int wrong_attempts = 0, choice, i;
    srand(time(NULL));
    

    
    do {
        wrong_attempts = 0;
        guessedLetters[0] = '\0';
        printf("=========- HANGMAN -=========\n\n");
        printf("Welcome to The Hangman Game.\n\n");
        printf("Please press Enter to continue...");
    
        getchar(); 
    
        system("cls"); 

        printf("=========- HANGMAN -=========\n\n");

        printf("enter a number between 1-3: ");
        scanf("%d", &choice);
        while (choice < 1 || choice > 3){
            printf("INVALID NUMBER - Please enter a number between 1-3: ");
            scanf("%d", &choice);
        }
        generateWord(word, choice);
        initGuessedWord(guessedWord, word);
	    giveHint(choice);
        drawHangman(wrong_attempts);
        printGuessedWord(guessedWord);

    

        while (1) {
    	
            guess = checkInput(guessedLetters);

            system("cls");

            printf("=========- HANGMAN -=========\n\n");
            giveHint(choice);

            logic(word, guess, guessedWord, &wrong_attempts);
            drawHangman(wrong_attempts);

            if (strcmp(guessedWord, word) == 0) {
                printGuessedWord(guessedWord);
                printf("\nCongratulations! You win\n");
                break;
            }

            if (wrong_attempts == MAX_ATTEMPTS) {
                printf("\nOOPS! You lost\n");
                break;
            }
        
            printGuessedWord(guessedWord);
        }

        printf("The word was: %s\n", word);
        printf("-------------------\n");
	    printf("---Game Over---\n");
        printf("====================\n\n");
        printf("Do you want to play again?: ");
        scanf("%s", again);
        for (i = 0; i < strlen(again); i++) again[i] = tolower(again[i]);
        system("cls");
        while (getchar() != '\n'); 
    } while (strcmp(again, "yes") == 0);
    return 0;
}

void generateWord(char* word, int choice) {
    FILE *file;
    char arrWords[200][50];
    int size = 0, index;
    
    if (choice == 1) file = fopen("progLang.txt", "r");
    if (choice == 2) file = fopen("countries.txt", "r");
    if (choice == 3) file = fopen("space.txt", "r");
    
    if (file == NULL) {
    	printf("error in opening file\n");
   		word[0] = '\0';
    	return;
	}
	
    while (fgets(arrWords[size], sizeof(arrWords[size]), file)) {
    	size++;
	}
	
    fclose(file);

    index = rand() % size;
    strcpy(word, arrWords[index]);
    word[strcspn(word, "\n")] = '\0';     
}

void initGuessedWord(char* guessedWord, char* word) {
    int i;
    int len = strlen(word); 
    for (i = 0; i < len; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[len] = '\0';
}

void printGuessedWord(char* guessedWord) {
    int i;
    printf("word: ");
    for (i = 0; i < strlen(guessedWord); i++) {
        printf("%c ", guessedWord[i]);
    }
    printf("\n\n");
}

void addGuess(char* guessedLetters, char guess) {
    int len = strlen(guessedLetters);
    guessedLetters[len] = toupper(guess);
    guessedLetters[len + 1] = '\0';
}


char checkInput(char* guessedLetters) {
	char guess;

    printf("Make a guess: ");
    scanf(" %c", &guess);
    while (!isalpha(guess)) {
        printf("INVALID INPUT (A-Z only) - Try again: ");
        scanf(" %c", &guess);
    }

    guess = toupper(guess);
    while (strchr(guessedLetters, guess)) {
        printf("You already guessed that letter - Try again: ");
        scanf(" %c", &guess);
    }

    while (!isalpha(guess)) {
        printf("INVALID INPUT (A-Z only) - Try again: ");
        scanf(" %c", &guess);
    }

    guess = toupper(guess);

    addGuess(guessedLetters, guess);

    return guess;
}

void logic(char* word, char guess, char* guessedWord, int* wrong_attempts) {
    int i, found = 0;
    

    for (i = 0; word[i] != '\0'; i++){
        if (word[i] == guess) {
            guessedWord[i] = guess;
            found = 1;
        }
    }
    if (found == 0) {
        (*wrong_attempts)++;
        printf("-------------\n");
        printf("oops! wrong guess\n");
        printf("%d chances left\n", MAX_ATTEMPTS - (*wrong_attempts));
        printf("-------------\n");
    }
    else {
        printf("-------------\n");
        printf("You Guessed right\n");
        printf("-------------\n");
    }
    
}

void giveHint(int choice) {
    if (choice == 1) printf("HINT: IT IS A PROGRAMMING LANGUAGE\n");
    else if (choice == 2) printf("HINT: IT IS A COUNTRY\n");
    else if (choice == 3) printf("HINT: IT IS A CELESTIAL BODY\n");
}

void drawHangman(int wrong_attempts) {
    switch (wrong_attempts) {
        case 0:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 1:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 2:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 3:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t /|   |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 4:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t /|\\  |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 5:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t /|\\  |\n");
            printf("\t\t\t /    |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;

        case 6:
            printf("\t\t\t  +---+\n");
            printf("\t\t\t  |   |\n");
            printf("\t\t\t  O   |\n");
            printf("\t\t\t /|\\  |\n");
            printf("\t\t\t / \\  |\n");
            printf("\t\t\t      |\n");
            printf("\t\t\t=========\n");
            break;
    }
}