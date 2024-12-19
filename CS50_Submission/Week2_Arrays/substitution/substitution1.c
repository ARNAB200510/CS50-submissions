#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc,char *argv[]) //argv is one array and argv[1] is the character array inputed
{
    char alpha[] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', '\0' };

    if( argc != 2 )
    {
        printf( " Key!\n" );
        exit( 1 );
    }

    if( strlen(argv[1]) != 26  ) //not using argv because it is a 2D array
    {
        printf( "Key must contain 26 characters\n" );
        exit( 1 );
    }

    for( int i = 0 ; i<26 ; i++ )
    {
         int j = i + 1;

        if( isalpha( argv[1][i] ) == 0 )
        {
            printf( "The key must contain alphabets only\n" );
            exit( 1 );
        }

        while( j < 26 )
        {
            if ( i == 25 )
            {
                break;
            }

            if ( argv[1][ j ] == argv[1][ i ] )
            {
                printf( "The elements of the key should be unique\n" );
                exit( 1 );
            }
            j++;
        }

    }

    char strin[ 50 ];
    printf( "Plaintext:" );
    int i  =  0;
    char c;
    for ( ; (c = getchar()) != '\n' ;i++ )
    {
        strin [ i ] = c;
    }
    strin[ i ] ='\0';
    printf( "Ciphertext:" );

    for ( int z = 0 ; strin[ z ] != '\0' ;z++ )
    {
        char op = strin[z],med ;
        int index=0,track = 0;
        if ( op == ',' || op == '.' ||  op == '!' )
        {
            printf( "%c", op );
            continue;
        }

        if( isupper( op ) )
        {
            track = -1;
        }

        for( int u = 0 ; u < 26 ; u++ )
        {
             if( alpha[ u ] == tolower( op )  )
            {
                 index = u;
                 break;

            }

        }
        med = argv[1][ index ];

        if ( track == -1 )
        {
            printf( "%c",toupper( argv[1][ index ] ) );
        }

        else
        {
            printf( "%c",tolower( argv[ 1 ][ index ] ) );
        }



     }
     printf( "\n" );



 }