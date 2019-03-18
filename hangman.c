#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MISTAKES 9
#define WORDS_FILE "words.txt"

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

void flush() {
  while(getchar() != '\n')
    ;
}

int count_lines(FILE *fp) {
  int lines = 0;
  char c;
  while((c = getc(fp)) != EOF) {
    if(c == '\n')
      lines++;
  }
  return lines;
}

// TODO: Choose a random word from a text file
char* get_word() {
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

//TODO: Add check for already guessed characters
char get_player_guess() {
  char c = 0;
  while(c == 0) {
    printf("Take your guess: ");
    c = getchar();
    flush();

    if(!isalpha(c)) {
      printf("Please enter a valid character.\n");
      c = 0;
    }
  }
  return tolower(c);
}

int guess(char guessed_char, char word[], char *obfuscated_word) {
  int hits = 0;
  for(int i = 0; word[i] != '\0'; i++) {
    if(word[i] == guessed_char) {
      obfuscated_word[i] = guessed_char;
      hits++;
    }
  }
  return hits;
}

int main() {
  FILE *fp = fopen(WORDS_FILE, "r");

  if(fp == NULL) {
    fprintf(stderr, "Error: cannot open words file.");
    return 1;
  }



  char *originalwp = get_word();
  int mistakes = 0;

  char *obfuscatedwp = (char*)malloc(strlen(originalwp)*sizeof(char));
  strcpy(obfuscatedwp, originalwp);

  obfuscate(obfuscatedwp);

  while(mistakes < MAX_MISTAKES && (strcmp(originalwp,obfuscatedwp) != 0)) {
    display_word(obfuscatedwp);
    char player_guess = get_player_guess();

    if(guess(player_guess,originalwp, obfuscatedwp) == 0) {
      mistakes++;
    }

    display_hangman(mistakes);
  }

  if(mistakes >= MAX_MISTAKES)
    printf("You lose!\n");
  else
    printf("You win!\n");

  return 0;
}
