#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
# define MAX_ATTEMPTS 6

void generateWord(char* word);
void initGuessedWord(char* guessedWord, char* word);
int checkInput(char* guessedWord, char* guessedLetters, char* word, int wrong_attempts);
void printGuessedWord(char* guessedWord);

int main() {
	printf("======HANGMAN GAME======\n");
    char word[50], guessedWord[50], guessedLetters[50];
    int wrong_attempts = 0;

	initGuessedWord(guessedWord, word);
    printGuessedWord(guessedWord);
    generateWord(word);
    wrong_attempts = checkInput(guessedWord, guessedLetters, word, wrong_attempts);

    return 0;
}

void generateWord(char* word) {
    FILE *fptr;
    char arrWords[200][50];
    int size = 0, index;
    
    srand(time(NULL));
    
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
    strcspn(word, "\n");     
}

void initGuessedWord(char* guessedWord, char* word) {
    int i;
    int len = strlen(word); 
    for (i = 0; i < len; i++) {
        guessedWord[i] = '_';
        printf("%c ", guessedWord[i]);
    }
    guessedWord[len] = '\0';
}

int checkInput(char* guessedWord, char* guessedLetters, char* word, int wrong_attempts) {
	char guess = guessedLetters[strlen(guessedLetters) - 1];
    char* ptr = word;
    int i;

    printf("Make a guess: ");
    scanf(" %c", &guess);
    while (strchr(guessedLetters, guess)) {
        printf("You already guessed that letter - Try again: ");
        scanf(" %c", &guess);
    }

    while (ptr = strchr(word, guess)) {
        i = ptr - word;
        guessedWord[i] = guess;
    }
    if (ptr == NULL) wrong_attempts++;
    printGuessedWord(guessedWord);
    return wrong_attempts;
}

void printGuessedWord(char* guessedWord) {
    int i;
    for (i = 0; i < strlen(guessedWord); i++) {
        printf("%c", guessedWord);
    }
}