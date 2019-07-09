#include "wordlist.h"

struct wordlist *suggest(const char *word, bool (*is_word)(const char *));

