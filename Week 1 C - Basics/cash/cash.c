#include <cs50.h>
#include <stdio.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int change_owed(void);
int amount_of_coins(int changeOwed);

int main(void)
{

    int changeOwed = change_owed();
    int coins = amount_of_coins(changeOwed);
    printf("%i\n", coins);
}

int amount_of_coins(int changeOwed)
{
    int amountOfCoins = 0;

    if (changeOwed >= QUARTER)
    {
        amountOfCoins += changeOwed / QUARTER;
        changeOwed = changeOwed % QUARTER;
    }

    if (changeOwed >= DIME)
    {
        amountOfCoins += changeOwed / DIME;
        changeOwed = changeOwed % DIME;
    }

    if (changeOwed >= NICKEL)
    {
        amountOfCoins += changeOwed / NICKEL;
        changeOwed = changeOwed % NICKEL;
    }

    if (changeOwed >= PENNY)
    {
        amountOfCoins += changeOwed / PENNY;
        changeOwed = changeOwed % PENNY;
    }

    return amountOfCoins;
}

int change_owed(void)
{

    int changeOwed;

    do
    {
        changeOwed = get_int("change_owed: \n");
        if (changeOwed <= 0)
        {
            printf("You can't owe 0 or less. \n");
        }
    }
    while (changeOwed <= 0);
    return changeOwed;
}
