from cs50 import get_int

while True:
    pyramyd_height = get_int("How tall is the pyramid? ")
    if pyramyd_height >= 1 and pyramyd_height <= 8:
        break
    print("You must introduce a number between 1 and 8")


for row in range(pyramyd_height):
    for col in range(pyramyd_height - row - 1):
        print(" ", end="")
    for col in range(row + 1):
        print("#", end="")
    print("  ", end="")
    for col in range(row + 1):
        print("#", end="")
    print()

