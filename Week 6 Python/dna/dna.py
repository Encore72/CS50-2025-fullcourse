import csv
import sys


def main():

    # TODO: Check for command-line usage
    # need 3 because dna.py counts as an argument
    if len(sys.argv) != 3:
        print("Invalid. You must provide 2 arguments.")
        sys.exit(1)

    # TODO: Read database file into a variable

    # create an empty list
    database_of_suspects = []
    # we open large.csv or small.csv to read them
    with open(sys.argv[1], "r") as database_file:
        # reads the first row as headers from .csv and creates a dictionary with "name: xxx and str_pattern_count: yyy" as keys,
        csv_reader = csv.DictReader(database_file)
        # then on each iteration reads the name of the suspect and every str pattern count {"name": Alice", "AGATC": "2"...}
        for row in csv_reader:
            # and adds each row to database_of_suspects as a dictionary (one per suspect)
            database_of_suspects.append(row) # e.j. this will contain {"name": Alice", "AGATC": "2"... "name": "Bob", "AGATC": "4"...}

    # TODO: Read DNA sequence file into a variable

    # we open x.txt (dna sequence sample) and save it into dna_sequence_sample
    with open(sys.argv[2], "r") as dna_file:
        dna_sequence_sample = dna_file.read() # e.j. this will contain for 1.txt = AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATT...


    # TODO: Find longest match of each STR in DNA sequence

    # obtain every STR pattern except "name" and store it in a list
    str_patterns = list(database_of_suspects[0].keys()) # gets ["name", "AGATC", "AATG", "TATC"...]
    str_patterns.remove("name") # updates to ["AGATC", "AATG", "TATC"...]

    # create dict to store the highest counts of each STR pattern
    sample_str_counts = {} # e.j. this will store {"AGATC": 3, "AATG": 7...}

    # for every str pattern in str patterns call longest_match and check how many times that str pattern appears in the dna_sequence_sample and stores that value it in the "sample_str_counts" dictionary
    for str_pattern in str_patterns:
        sample_str_counts[str_pattern] = longest_match(dna_sequence_sample, str_pattern) # e.j. longest_match(AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATT..., "AGATC")

    # TODO: Check database for matching profiles

    # compare DNA sample with each suspect in the database
    for suspect in database_of_suspects: # e.j. 1st loop we are checking "Alice"
        matching_str_pattern = 0
        # check each STR type
        for str_pattern in str_patterns:
            # convert suspect's STR count from string (csv stores in strings) to int to be able to compare
            if int(suspect[str_pattern]) == sample_str_counts[str_pattern]: # e.j. 1st loop is --- (Alice[AGATC] = 2) == (sample_str_counts[AGATC] = 3) 2 != 3 so no match
                matching_str_pattern += 1

        # if all STR counts match, we found the suspect
        if matching_str_pattern == len(str_patterns): # this will check that all str patterns in the sample have been matched with the str patterns of the dna of the suspect
            print(suspect["name"]) # we print the value stored in the name key
            return

    # If we get here no suspect matches all STR counts
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
