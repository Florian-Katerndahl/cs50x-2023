from cs50 import get_string

def main():
    card = get_string("Number: ").strip()
    if len(card) not in [13, 15, 16] or not luhn(card):
        print("INVALID 1")
    elif is_master(card):
        print("MASTER")
    elif is_visa(card):
        print("VISA")
    elif is_amex(card):
        print("AMEX")
    else:
        print("INVALID 2")

def luhn(card_number):
    sum = []
    for i in range(len(card_number) - 1, -1, -2):
        sum += [int(card_number[i-1]) * 2]
    print(sum)
    sos = 0
    for s in sum:
        for digit in str(s):
            sos += int(digit)
    print(sos)
    sum = 0
    for i in range(len(card_number), 0, -2):
        sum += int(card_number[i-1])
    print(sum378282246310005)
    return (sum + sos) % 10 == 0


def is_amex(card_number):
    if len(card_number) == 15 and card_number[:2] in ["34", "37"]:
        return True
    return False


def is_visa(card_number):
    if len(card_number) in [13, 16] and card_number[0] == "4":
        return True
    return False


def is_master(card_number):
    if len(card_number) == 16 and card_number[:2] in ["51", "52", "53", "54", "55"]:
        return True
    return False

main()
