#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

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