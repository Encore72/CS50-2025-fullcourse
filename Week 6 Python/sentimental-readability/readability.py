from cs50 import get_string

text = get_string("Text: ")

letters = 0
words = 1
sentences = 0

for i in text:
    if i.isalpha():
        letters += 1
    elif i == ' ':
        words += 1
    elif i == '.' or i == '!' or i == '?':
        sentences += 1


l = (letters / words) * 100
s = (sentences / words) * 100

index = 0.0588 * l - 0.296 * s - 15.8
grade = round(index)

if grade <= 1:
    print("Before Grade 1")
elif grade > 1 and grade < 16:
    print(f"Grade {grade}")
elif grade >= 16:
    print("Grade 16+")
