#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MISTAKES 9

// TODO: Make a proper graphical representation
const static char *stages[] = {
  "9 tries left",
  "8 tries left",
  "7 tries left",
  "5 tries left",
  "4 tries left",
  "3 tries left",
  "2 tries left",
  "1 tries left",
  "0 tries left",
};

// TODO: Choose a random word from a text file
char* get_wordpointer() {
  static char word[] = "motorcycle";
  char *wp = &word[0];
  return wp;
}

void display_hangman(int mistakes) {
  printf("%s\n", stages[mistakes]);
}


void display_word(char* wordp) {
  printf("%s\n", wordp);
}

void obfuscate(char *wp) {
  while(*wp != '\0') {
    *wp = '_';
    wp++;
  }
}

// TODO: Implement this
void get_player_guess() {
}

int main() {
  char *originalwp = get_wordpointer();
  int mistakes = 0;

  // make a copy of the original word and obfuscate it
  char *obfuscatedwp = (char*)malloc(strlen(originalwp)*sizeof(char));
  strcpy(obfuscatedwp, originalwp);
  obfuscate(obfuscatedwp);


  while(mistakes < MAX_MISTAKES) {
    display_hangman(mistakes);
    display_word(obfuscatedwp);
    get_player_guess();
    //TODO: Remove this
    mistakes++;
  }

  return 0;
}
