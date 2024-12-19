def split(n):
    sum1 = 0
    for i in n:
        sum1 = sum1 + int(i)
    return int(sum1)


def validate(num):
    mylist = []
    for digit in str(num):
        mylist.append(digit)
    sum = 0
    for o_digit in mylist[-2::-2]:
        if int(o_digit) * 2 < 10:
            sum = sum + (int(o_digit) * 2)

        else:
            sum = sum + split(str(int(o_digit) * 2))
    for e_digit in mylist[-1::-2]:
        sum += int(e_digit)
    if sum % 10 == 0:
        return True
    return False


##MAIN##
while True:
    num = int(input("Enter card number:"))
    if str(num).isdigit():
        break

##Validate the card
if validate(num):
    LENGTH = len(str(num))
    string = str(num)[:2]
    if LENGTH == 15 and string in ("34", "37"):
        print("AMEX")
        exit()
    elif LENGTH == 16 and string in ("51", "52", "53", "54", "55"):
        print("MASTERCARD")
        exit()
    elif LENGTH in (15, 16) and string[0] == "4":
        print("VISA")
        exit()
    else:
        print("INVALID")
        exit()

else:
    print("INVALID")
    exit()
