#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
void text_to_binary(const char* text, char* binary);
void binary_to_text(const char* binary, char* text);
void add_error_correction(const char* data, char* corrected);
int decode(const char* received, char* decoded);
int binary_to_value(int bit1, int bit2, int bit3);
int calculate_value(char encoded[7]);
void flip(char encoded[7], int index);
#endif
