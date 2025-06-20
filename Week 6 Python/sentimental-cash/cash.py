from cs50 import get_float

QUARTER = 25
DIME = 10
NICKEL = 5
PENNY = 1


def main():

    changeOwed = round(change_owed() * 100)
    coins = amount_of_coints(changeOwed)
    print(coins)


def amount_of_coints(changeOwed):

    amountOfCoins = 0

    # in every iterarion of this for "coin" takes the value of each constant (quarter = 25...)
    # if we were using "for coin in range(4)", then coin would take the values 0, 1, 2, 3
    for coin in [QUARTER, DIME, NICKEL, PENNY]:
        amountOfCoins += changeOwed // coin
        changeOwed %= coin

    return amountOfCoins


def change_owed():
    while True:
        changeOwed = get_float("Change owed: ")
        if changeOwed <= 0:
            print("You can't owe 0 or less")
        else:
            return changeOwed


if __name__ == "__main__":
    main()
