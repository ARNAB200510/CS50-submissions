import csv
import sys


def main():
    #TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: <CSV file> <Text file>")
        return

    #TODO: Read database file into a variable
    #Open the file to store the STR pattern in  a list
    test_list = []
    with open(sys.argv[1], "r") as file:
        buf = csv.reader(file)
        test_list = next(buf)
    #Open the file again for matching the database
    with open(sys.argv[1], "r") as file1:
        database = csv.DictReader(file1)
        # TODO: Read DNA sequence file into a variable
        with open(sys.argv[2], "r") as file2:
            seq = file2.read()
            #TODO: Find longest match of each STR in DNA sequence
            #Store the STR pattern in an empty dictionary
            count = {}
            test_list.pop(0)
            for string in test_list:
                count[string] = str(longest_match(seq, string))

            # TODO: Check database for matching profiles
            for elements in database:
                result = elements.pop("name")
                if list(count.values()) == list(elements.values()):
print(f"{result}")
                    return
            print("No match")
    return


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
