#ifndef PLAYFAIR_H
#define PLAYFAIR_H

void prepare(const char input[], char output[]);
void grid(const char codeword[], char square[6][6]);
bool occurs_before(const char str[], char letter, int pos);
void bigram(char square[6][6], const char inchar1, const char inchar2, char &outchar1, char &outchar2);
int get_row(char square[6][6], char inchar);
int get_col(char square[6][6], char inchar);
void encode(char square [6][6], const char prepared[], char encoded[]);
void decode(char square[6][6], const char encoded[], char decoded[]);
#endif
