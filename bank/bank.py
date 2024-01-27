greeting = input("Greeting: ")

if greeting.split()[0].lower() == "hello":
    print("$0")
elif greeting.split()[0].lower()[0] == "h":
    print("$20")
else:
    print("$100")
