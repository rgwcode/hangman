#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MISTAKES 9

const static char *stages[] = {"\
   \n\
   \n\
   \n\
   \n\
   ",
"\
   .\n\
   |\n\
   |\n\
   |\n\
   |",
  "\
   .-.\n\
   |\n\
   |\n\
   |\n\
   |",
  "\
   .-.\n\
   | |\n\
   |\n\
   |\n\
   |",
  "\
   .-.\n\
   | |\n\
   | O\n\
   |\n\
   |",
  "\
   .-.\n\
   | |\n\
   | O\n\
   | |\n\
   |",
  "\
   .-.\n\
   | |\n\
   | O\n\
   |-|\n\
   |",
  "\
   .-.\n\
   | |\n\
   | O\n\
   |-|-\n\
   |",
  "\
   .-.\n\
   | |\n\
   | O\n\
   |-|-\n\
   |/",
  "\
   .-.\n\
   | |\n\
   | O\n\
   |-|-\n\
   |/ \\",
};

// TODO: Choose a random word from a text file
char* get_wordpointer() {
  static char word[] = "motorcycle";
  char *wp = &word[0];
  return wp;
}

void display_hangman(int mistakes) {
  printf("\
--------------\n\
%s\n\
--------------\n", stages[mistakes]);
}

void display_word(char* wordp) {
  printf("[%s]\n", wordp);
}

void obfuscate(char *wp) {
  while(*wp != '\0') {
    *wp = '_';
    wp++;
  }
}

// TODO: Implement this
char get_player_guess() {
  printf("Take your guess: ");
  getchar();
  // Get input
  printf("\n");
  return 'x';
}

int guess(char guess, char *word) {
  return 1;
}


int main() {
  char *originalwp = get_wordpointer();
  int mistakes = 0;

  // make a copy of the original word and obfuscate it
  char *obfuscatedwp = (char*)malloc(strlen(originalwp)*sizeof(char));
  strcpy(obfuscatedwp, originalwp);
  obfuscate(obfuscatedwp);


  while(mistakes < MAX_MISTAKES) {
    display_word(obfuscatedwp);
    char player_guess = get_player_guess();
    mistakes = mistakes + guess(player_guess, obfuscatedwp);
    display_hangman(mistakes);
  }

  return 0;
}
