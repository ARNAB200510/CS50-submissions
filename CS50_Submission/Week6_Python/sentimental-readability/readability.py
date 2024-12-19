# MAIN#
def main():
    # TAKE INPUT FROM THE USER#
    paragraph = input("Enter the paragraph please:")
    # count the number of words now
    word = word_count(paragraph)
    # Count the number of letters in the paragraph
    letter = letter_count(paragraph) * (100 / word)
    # SENTENCES
    sentence = sentence_count(paragraph) * (100 / word)
    # INDEX
    index = round(0.0588 * letter - 0.296 * sentence - 15.8)
    if index >= 16:
        print("Grade 16+")

    elif index <= 1:
        print("Before Grade 1")
    elif 1 < index < 16:
        print(f"Grade {index}")


def letter_count(para):
    count = 0
    for letter in para:
        if "a" <= letter <= "z" or "A" <= letter <= "Z":
            count += 1
    return count


def word_count(para):
    words = para.split()
    return len(words)


def sentence_count(para):
    s_count = 0
    for letter in para:
        if letter in ["?", "!", "."]:
            s_count += 1
    return s_count

