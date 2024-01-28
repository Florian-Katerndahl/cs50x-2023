def main():
    text = input("Text: ")

    index = coleman_liau(text)
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def coleman_liau(text):
    word_count = len(text.split())
    sentence_count = len(text.split("!?."))

    letter_count = 0
    for letter in text:
        if letter.isalpha():
            letter_count += 1

    avg_letters = letter_count / word_count * 100.0
    avg_sentences = sentence_count / word_count * 100.0

    print(word_count, sentence_count, letter_count, avg_letters, avg_sentences)

    return round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)


main()
