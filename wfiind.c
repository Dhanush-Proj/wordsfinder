#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 4096
#define MAX_LEN 256

typedef struct {
    char text[MAX_LEN];
    int score;
} Item;

Item items[MAX_ITEMS];
int item_count = 0;

int fuzzy_match(const char *pattern, const char *str) {
    int score = 0;
    int pi = 0;
    for (int si = 0; str[si] && pattern[pi]; si++) {
        if (tolower(str[si]) == tolower(pattern[pi])) {
            score += 5; 
            if (si > 0 && tolower(str[si-1]) == tolower(pattern[pi-1]))
                score += 2; 
            pi++;
        } else {
            score -= 1;
        }
    }
    if (pattern[pi] != '\0')
        return -9999; 
    return score;
}

int compare_items(const void *a, const void *b) {
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;
    return ib->score - ia->score; 
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <query> <file>\n", argv[0]);
        // fprintf(stderr, "Example: %s cat /usr/share/dict/words\n", argv[0]);
        return 1;
    }

    const char *query = argv[1];
    const char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, sizeof(buffer), fp) && item_count < MAX_ITEMS) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(items[item_count].text, buffer, MAX_LEN);
        item_count++;
    }
    fclose(fp);

    
    for (int i = 0; i < item_count; i++)
        items[i].score = fuzzy_match(query, items[i].text);


    qsort(items, item_count, sizeof(Item), compare_items);

    int shown = 0;
    for (int i = 0; i < item_count && shown < 10; i++) {
        if (items[i].score > -9999) {
            printf("%s\n", items[i].text);
            shown++;
        }
    }

    return 0;
}
