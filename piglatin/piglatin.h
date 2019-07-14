#ifndef PIGLATIN_H
#define PIGLATIN_H
#include <iostream>

int findFirstVowel(const char word[]);
void translateWord(const char english[], char piglatin[]);
void swap(char word[], int index);
void translateStream(std::istream& inputStream, std::ostream& outputStream);
#endif
