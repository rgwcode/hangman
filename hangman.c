#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MISTAKES 9
#define WORDS_FILE "words.txt"
#define LONGEST_WORD 50

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
|  \n\
|  \n\
|",
"\
.-.\n\
| |\n\
| O\n\
|  \n\
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

uint count_lines(FILE *fp) {
  uint lines = 0;
  char c;
  while((c = getc(fp)) != EOF) {
    if(c == '\n')
      lines++;
  }

  fseek(fp,0, SEEK_SET);
  return lines;
}

char* pick_random_word(char** words, uint lines) {
  uint pick = (rand() / (RAND_MAX / (lines - 1)));
  return words[pick];
}

char** get_words_from_file(FILE *fp, uint lines) {
  char **words = malloc(lines * sizeof(char*));
  for (uint i = 0; i < lines; i++) {
    words[i] = malloc(LONGEST_WORD * sizeof(char));
    fscanf(fp, "%s", words[i]);
  }
  return words;
}

void display_hangman(uint mistakes) {
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

int play_again() {
  char c = 0;
  int playagain = 2;

  printf("Do you want to play again?\ny/n: ");
  while(playagain == 2) {
    c = getchar();
    flush();

    switch (c) {
    case 'y':
      playagain = 1;
      break;
    case 'n':
      playagain = 0;
      break;
    default:
      printf("Please answer y or n: ");
    }
  }
  return playagain;
}

int guess(char guessed_char, char word[], char *obfuscated_word) {
  uint hits = 0;
  for(int i = 0; word[i] != '\0'; i++) {
    if(word[i] == guessed_char) {
      obfuscated_word[i] = guessed_char;
      hits++;
    }
  }
  return hits;
}

int main() {
  srand(time(NULL));
  FILE *fp = fopen(WORDS_FILE, "r");

  if(fp == NULL) {
    fprintf(stderr, "Error: cannot open words file.");
    return 1;
  }

  uint lines = count_lines(fp);
  char** words = get_words_from_file(fp, lines);
  fclose(fp);
  int playing = 1;
  while(playing) {
    char *originalwp = pick_random_word(words, lines);
    uint mistakes = 0;

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

    if(mistakes >= MAX_MISTAKES) {
      printf("You lose!\n");
    }
    else {
      printf("You win!\n");
    }
    printf("The word was:\n[%s]\n", originalwp);
    free(obfuscatedwp);
    playing = play_again();
  }
  printf("Thanks for playing!\n");
  return 0;
}
