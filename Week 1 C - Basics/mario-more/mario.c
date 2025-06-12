#include <cs50.h>
#include <stdio.h>

#define MIN_HEIGHT 1
#define MAX_HEIGHT 8

int get_height(void);
void pyramid_maker(int height);

int main(void)
{

    int height = get_height();
    pyramid_maker(height);
}

int get_height(void)
{

    int height;

    do
    {
        height = get_int("Introduce a height value from 1 to 8: \n");
        if (!(height >= MIN_HEIGHT && height <= MAX_HEIGHT))
        {
            printf("You must introduce a whole number, and a value from 1 to 8 \n");
        }
    }
    while (!(height >= MIN_HEIGHT && height <= MAX_HEIGHT));
    return height;
}

void pyramid_maker(int height)
{
    for (int row = 0; row < height; row++)
    {
        // spaces
        for (int col = 0; col < height - row - 1; col++)
        {
            printf(" ");
        }

        // left side
        for (int col = 0; col <= row; col++)
        {
            printf("#");
        }
        printf("  ");

        // right side
        for (int col = 0; col <= row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}
