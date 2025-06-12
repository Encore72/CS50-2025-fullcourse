#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("How tall is the pyramid? \n");
        if (height <= 0)
        {
            printf("You must introduce a whole number and a value greater than 0. \n");
        }
    }
    while (height <= 0);

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < height; col++)
        {
            if (col < height - row - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
