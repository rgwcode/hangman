#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MISTAKES 9

const static char *stages[] = {"\
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
Hang 'em high.\n\
%s\n\
--------------\n", stages[mistakes]);
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
