/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define booleans */
typedef short bool;
#define true 1
#define false 0

/* True if desired in the password, false if not */
bool uppercase_letters = false;
bool lowercase_letters = false;
bool symbols = false;
bool digits = false;

/* Characters */
char uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char digit[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char symbol[4] = {'~', '@', '#', '&'};

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* Convert the passed character into lowercase */
char
upper_to_lower (char ch) 
{
  return  ch + 32;
}

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* Generate and print a random string with the desired characteristics */
void
generate (int length)
{

  /* Calculate how many possible characters there are */
  int num_options = 0;
  if(uppercase_letters)
  {
    num_options += 26;
  }
  if(lowercase_letters)
  {
    num_options += 26;
  }
  if(digits)
  {
    num_options += 10;
  }
  if(symbols)
  {
    num_options += 4;
  }

  /* Character array for the possible characters */
  char options[num_options];

  /* Determine the possible characters */
  int i = 0;
  int i_2 = 0;
  if(uppercase_letters)
  {
    while(i < 26)
    {
      options[i_2] = uppercase[i];
      i ++;
      i_2 ++;
    }
  }
  i = 0;
  if(lowercase_letters)
  {
    while(i < 26)
    {
      options[i_2] = upper_to_lower(uppercase[i]);
      i ++;
      i_2 ++;
    }
  }
  i = 0;
  if(digits)
  {
    while(i < 10)
    {
      options[i_2] = digit[i];
      i ++;
      i_2 ++;
    }
  }
  i = 0;
  if(symbols)
  {
    while(i < 4)
    {
      options[i_2] = symbol[i];
      i ++;
      i_2 ++;
    }
  }

  /* Character array for the resulting string */
  char buffer[length + 1];
  buffer[length] = '\0';

  /* Set the seed for the random number generator */
  srand(time(NULL));

  /* Generate the string */
  i = 0;
  while (i < length)
  {
    buffer[i] = options[rand() % num_options];
    i ++;
  }

  printf("%s\n", buffer);

} 

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* Scan arguments */
void
scanargs(char *s)
{

  /* Scan through arguments to determine what ASCII characters are desired */
  while (*s != '\0' && *s != ' ')
  {

    switch (*s ++)
  	{

    	/* Use uppercase letters in the password */
      case 'u':
        uppercase_letters = true;
        break;

      /* Use lowercase letters in the password */
      case 'l':
        lowercase_letters = true;
        break;

      /* Use symbols in the password */
      case 's':
        symbols = true;
        break;

      /* Use digits in the password */
      case 'd':
        digits = true;
        break;

      /* Use all possible characters in the password */
      case 'a':
        uppercase_letters = true;
  			lowercase_letters = true;
  			symbols = true;
  			digits = true;
        break;

      /* Print instructions */
      case 'h':
          printf("At least one of the following arguments must be passed, "
            "more than one may be passed:\n"
            "'-u' will select possible characters from uppercase letters (A, B, C ... Z)\n"
            "'-l' will select possible characters from lowercase letters (a, b, c ... z)\n"
            "'-s' will select possible characters from symbols (~, @, #, &)\n"
            "'-d' will select possible characters from digits (0, 1, 2 ... 9)\n"
            "'-a' will select possible characters from all of the above\n"
            "'-h' will print this help message\n"
            "The final argument must be a number representing the desired password length.\n");
        break;

    }

  }

}

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* Ensure correct input */
bool
error_checking (char *ch)
{

  /* Ensure that the final argument is a number */
  char *tmp_pointer = ch;
  bool number_found = true;
  while(*tmp_pointer != '\0')
  {
    if(*tmp_pointer < 48 || *tmp_pointer > 57)
    {
      printf("The final argument must be a number representing the desired password length.\n"
        "Please pass argument '-h' for instructions.\n");
      exit(0);
    }
    tmp_pointer ++;
  }

  /* Ensure that the user has selected at least one type of character to include
     in the password */
  if(!uppercase_letters && !lowercase_letters && !symbols && !digits)
  {
    printf("You must select at least one type of character to include in your password.\n"
      "Please pass argument '-h' for instructions.\n");
    exit(0);
  }

}

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

int
main (int num_args, char **args)
{

	/* No arguments presented, exit */
  if(num_args == 1)
  {
		printf("No arguments passed.\nPlease pass argument '-h' for instructions.\n");
		exit(0);
  }

  /* Parse arguments to determine what ASCII characters to use,
  	 then ensure correct input and generate a password with selected
     characters as options */
  while (num_args > 1)
  {

    num_args --, args ++;
    if (**args == '-')
    {
      scanargs(*args);
    }

  }

  error_checking(*args);

  /* At the final argument,
   argument is a number,
   user has selected at least one type of character
   generate the password */
  int time_1 = time(NULL);
  int time_2 = time(NULL);
  while(1)
  {
    if(time_1 != time_2)
    {
      time_2 = time(NULL);
      generate(atoi(*args));
    }
    time_1 = time(NULL);
  }

  exit(0);

}

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */
