#include <cs50.h>
#include <stdio.h>

int n = 0;
bool checksum(unsigned long);

int main(void)
{

    unsigned long num = get_long("Number:");

    if (checksum(num))
    {

        if (n == 15 && (num / 10000000000000 == 34 || num / 10000000000000 == 37))
        {
            printf("AMEX\n");
            return 0;
        }
        if (n == 16 && (num / 100000000000000 == 51 || num / 100000000000000 == 52 || num / 100000000000000 == 53 ||
                        num / 100000000000000 == 54 || num / 100000000000000 == 55))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        if ((n == 13 || n == 16) && (num / 1000000000000000 == 4 || num / 1000000000000 == 4))
        {
            printf("VISA\n");
            return 0;
        }
    }

    printf("INVALID\n");
}

bool checksum(unsigned long num)
{
    unsigned long temp = num;
    int sum = 0, digit;

    while (temp != 0)
    {
        digit = temp % 10; // Get the digits

        if (n % 2 != 0) // For odd digits,double and add the product
        {
            digit *= 2;

            if (digit / 10 == 0) // For a single digit number
            {
                sum += digit;
            }

            else // For a double digit number
            {
                while (digit != 0)
                {
                    sum += (digit % 10);
                    digit /= 10;
                }
            }
        }

        else // For even digits add the digits to sum
        {
            sum += digit;
        }

        temp /= 10;
        ++n;
    }

    if (sum % 10 == 0) // The check condition
    {
        return true;
    }

    return false;
}