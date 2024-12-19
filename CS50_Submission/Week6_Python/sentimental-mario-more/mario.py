size = 0
while not ( 1 <= size <= 8):
    try:
        size = int (input ("Number of rows please!"))
    except ValueError:
        continue
i  = 0
while (i < size ):
    #Print the spaces first
    spaces = 0
    while (spaces < size - i - 1):
        print(" ",end = "")
        spaces = spaces + 1

    #Print the left pyramid
    j = 0
    while (j < i + 1):
        print("#",end = "")
        j = j + 1

    #Print spaces
    print (2 * " ",end = "")
    #The right pyramid
    j2 = 0
    while (j2 < i + 1):
        print ("#",end  ="")
        j2  = j2 + 1
    print ("")
    i = i + 1

