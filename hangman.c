#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
# define MAX_ATTEMPTS 6

void generateWord(char* word);
void initGuessedWord(char* guessedWord, char* word);

int main() {
	printf("======HANGMAN GAME======\n");
    char word[50], guessedWord[50], guessedLetters[50];
    int attempts = 0;
	initGuessedWord(guessedWord, word);
    generateWord(word);
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

void checkInput(char* guessedWord, char* guessedLetters, char* word, int* attempts) {
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
    if (ptr == NULL) attempts++;
} 