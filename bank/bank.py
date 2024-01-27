greeting = input("Greeting: ")
first_word = greeting.split()[0].lower()

if first_word == "hello":
    print("$0")
elif first_word[0] == "h":
    print("$20")
else:
    print("$100")
