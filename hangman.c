#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_ATTEMPTS 6

void generateWord(char* word);
void initGuessedWord(char* guessedWord, char* word);
void printGuessedWord(char* guessedWord);
void addGuess(char* guessedLetters, char guess);
char checkInput(char* guessedLetters, char* word);
int logic(char* word, char guess, char* guessedWord);
void drawHangman(int wrong_attempts);

int main() {
    char word[50], guessedWord[50], guessedLetters[50] = {'\0'};
    char guess;
    int wrong_attempts = 0;
    srand(time(NULL));

    generateWord(word);
    initGuessedWord(guessedWord, word);
    
    printf("=========- HANGMAN -=========\n");
    printf("Welcome to The Hangman Game.\n\n");
    printf("Please press Enter to continue...");
    
    getchar(); 
    
    system("cls"); 

    printf("=========- HANGMAN -=========\n\n");
    drawHangman(wrong_attempts);
    printGuessedWord(guessedWord);

    while (1) {
    	
        guess = checkInput(guessedLetters, word);

        system("cls");

        printf("=========- HANGMAN -=========\n\n");

        wrong_attempts = logic(word, guess, guessedWord);
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
    return 0;
}

void generateWord(char* word) {
    FILE *fptr;
    char arrWords[200][50];
    int size = 0, index;
    
    
    fptr = fopen("words.txt", "r");
    
    if (fptr == NULL) {
    	printf("error in opening file\n");
        word[0] = '\0';
    	return;
	}
	
    while (fgets(arrWords[size], sizeof(arrWords[size]), fptr)) {
    	size++;
	}
	
    fclose(fptr);
    
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
    guessedLetters[len] = guess;
    guessedLetters[len + 1] = '\0';
}


char checkInput(char* guessedLetters, char* word) {
	char guess;
    int i, found = 0;

    printf("Make a guess: ");
    scanf(" %c", &guess);
    guess = toupper(guess);
    while (strchr(guessedLetters, guess)) {
        printf("You already guessed that letter - Try again: ");
        scanf(" %c", &guess);
    }
    addGuess(guessedLetters, guess);

    return guess;
}

int logic(char* word, char guess, char* guessedWord) {
    int i, found = 0;
    static int wrong_attempts = 0;

    for (i = 0; word[i] != '\0'; i++){
        if (word[i] == guess) {
            guessedWord[i] = guess;
            found = 1;
        }
    }
    if (found == 0) {
        printf("-------------\n");
        printf("oops! wrong guess\n");
        printf("%d chances left\n", MAX_ATTEMPTS - 1 - wrong_attempts);
        printf("-------------\n");
        wrong_attempts++;
    }
    else {
        printf("-------------\n");
        printf("You Guessed right\n");
        printf("-------------\n");
    }
    
    return wrong_attempts;
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