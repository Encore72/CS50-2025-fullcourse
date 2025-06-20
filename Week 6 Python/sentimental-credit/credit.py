import re

def main():

    cardNumber = get_valid_card_number()
    if luhn_check(cardNumber):
        print(f"Number: {cardNumber}")
        print(get_card_type(cardNumber))
    else:
        print("INVALID")


def get_valid_card_number():
    # Promt user for a positive card number
    while True:
        cardNumber = input("Card Number: ")
        if re.fullmatch(r"\d{13}|\d{15}|\d{16}", cardNumber):
            return cardNumber
        else:
            print("INVALID")
            break


def luhn_check(cardNumber):
    totalSum = 0
    length = len(cardNumber)

    # this range syntax means range(start -initial value-, stop -final value-, step-increment or decrement-)
    for i in range(length - 1, -1, -1):
        # "i" will allow us to go through the entire card number digit by digit
        digitAnalised = int(cardNumber[i])
        # starting from the right we verify if that digit is even or odd position, if odd we double it
        # e.j. for a length "4" in iteration nº1 i = 3 (because length = 4 - 1) therefore 4-3 = 1 which is odd and will be doubled in value and added to totalSum
        if (length - i) % 2 == 0:
            digitAnalised *= 2
            # if the result of doubling the digit is higher than 9 we substract 9 to respect luhn's law
            # e.j. imagine "15", 15-9 = 6 which is 1+5 which is luhn's law for double digit results on odd numbers
            if digitAnalised > 9:
                digitAnalised -= 9
        totalSum += digitAnalised

    if totalSum % 10 == 0:
        return True
    else:
        return False


def get_card_type(cardNumber):
    length = len(cardNumber)
    firstTwoDigits = int(cardNumber[:2])
    firstDigit = int(cardNumber[0])

    if length == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37):
        return "AMEX"
    elif (length == 13 or length == 16) and firstDigit == 4:
        return "VISA"
    elif length == 16 and (firstTwoDigits >= 51 and firstTwoDigits  <= 55):
        return "MASTERCARD"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
