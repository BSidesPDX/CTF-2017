#include "highscore.h"
#define fhighscore "/tmp/highscore.save"

bool eraseHighScore()
{
    size_t res = remove(fhighscore);
    return (res == 1);
}

bool setHighScore(int maxTile, int highscore)
{
    if (maxTile > highscore)
    {
        FILE* f = fopen(fhighscore, "w");
        char buffer[2048] = {0};
        int key;
        int count = 0;

        if (f == NULL) return false;
        size_t res = fwrite(&maxTile, sizeof(maxTile), 1, f);

        printf("\n\nWhat is your name?\n");
        do
        {
            key=getkey();
            buffer[count] = key;
            count ++;
        } while (key != '\n' && count < 2048-1);

        buffer[count] = '\0';

        printf("New highscore!");
        printf(" %d belongs to - ", maxTile);
        printf(buffer);
        res = fwrite(buffer, sizeof(buffer), 1, f);
            key=getkey();
        fclose(f);
        return (res == 1);
    }
    return false;
}

int loadHighScore(char **playerName)
{
    int highscore;
    FILE* f = fopen(fhighscore, "r");
    if (f == NULL) return false;
    size_t res = fread(&highscore, sizeof(highscore), 1, f);
    if (!res)
        return 0;

   *playerName = (char *) malloc(100);

    if (*playerName == NULL)
    {
        free(*playerName);
        return 0;
    }

    res = fread(*playerName, sizeof(playerName), 1, f);
    fclose(f);

    if (res == 1)
        return highscore;
    else
        return 0;
}
