from cs50 import get_string

def main():
    print(luhn("4003600000000014"))

def luhn(card_number):
    sum = 0
    for i in range(len(card_number) - 1, -1, -2):
        sum += int(card_number[i-1]) * 2
    print(sum)

    sos = 0
    for digit in str(sum):
        sos += int(digit)
    print(sos)

    sum = 0
    for i in range(len(card_number), 0, -2):
        sum += int(card_number[i-1])
    print(sum)

    return (sum + sos) % 10

main()
