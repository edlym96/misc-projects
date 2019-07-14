/* you may assume a maximum word length of 512 characters*/
#define MAX_LENGTH 512

/* insert your function prototypes here */
int frequency(const char* target);

int edit_distance(const char* a, const char* b);
int get_distance(const char* a, const char* b, int i, int j);
int max(int i, int j);
int min(int i, int j);
int indicator(const char a, const char b);
bool spell_correct(const char* word, char* fixed);
