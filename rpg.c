/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Define booleans */
typedef short bool;
#define true 1
#define false 0

/* True if desired in the password, false if not */
bool uppercase_letters = false;
bool lowercase_letters = false;
bool symbols = false;
bool digits = false;

/* True if on the final argument, false if not */
bool on_final_arg = false;

/* True if user wants to use a custom seed, false if not */
bool custom_seed = false;

/* Seed for random number generator */
unsigned int seed;

/* Characters */
char uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char lowercase[26];
char digit[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char symbol[4] = {'~', '@', '#', '&'};

/* Error messages */
char *final_arg =
"The final argument must be a number representing the desired password length.\n"
"Please pass argument '-h' for instructions.\n";
char *no_args =
"No arguments passed.\nPlease pass argument '-h' for instructions.\n";
char *no_chars_selected =
"You must select at least one type of character to "
"include in your password.\nPlease pass argument '-h' for instructions.\n";
char *no_seed =
"The argument following '-c' must be your custom seed (as an integer).\n"
"Please pass argument '-h' for instructions.\n";

/* Help message */
char *help_message = 
"At least one of the following arguments must be passed, "
"more than one may be passed:\n"
"'-u' will select possible characters from uppercase letters (A, B, C ... Z)\n"
"'-l' will select possible characters from lowercase letters (a, b, c ... z)\n"
"'-s' will select possible characters from symbols (~, @, #, &)\n"
"'-d' will select possible characters from digits (0, 1, 2 ... 9)\n"
"'-a' will select possible characters from all of the above\n"
"'-c' will allow the user to specify a seed for random number generation "
"and will attempt to use the following argument as the seed\n"
"'-h' will print this help message\n"
"The final argument must be a number representing the desired password length.\n";

/* Function prototypes */
bool is_number (char *);

/* ***************************************************************** */
/* GENERATOR                                                         */
/* ***************************************************************** */

/* Generate and print a random string with the desired characteristics */
void
generate (int length)
{

  /* Calculate how many possible characters there are */
  int num_options = 0;
  if(uppercase_letters)
    num_options += 26;
  if(lowercase_letters)
    num_options += 26;
  if(digits)
    num_options += 10;
  if(symbols)
    num_options += 4;

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
  if(lowercase_letters)
  {
		i = 0;
    while(i < 26)
    {
      options[i_2] = lowercase[i];
      i ++;
      i_2 ++;
    }
  }
  if(digits)
  {
		i = 0;
    while(i < 10)
    {
      options[i_2] = digit[i];
      i ++;
      i_2 ++;
    }
  }
  if(symbols)
  {
		i = 0;
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
  if(!custom_seed)
    seed = time(NULL);
  srand(seed);

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
/* ARGUMENT SCANNER                                                  */
/* ***************************************************************** */

/* Scan arguments */
void
scan_argument (char *str)
{

  /* Scan through arguments to determine what ASCII characters are desired */
  while (*str != '\0' && *str != ' ')
  {
    switch (*str ++)
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

      /* Use a custom seed */
			case 'c':
				custom_seed = true;
				str ++;
        while(*str == ' ')
          str ++;
        char* end;
				if(is_number(str))
          seed = strtoul(str, &end, 10);
        else
        {
          printf("%s", no_seed);
          exit(0);
        }
        while(*str != ' ' && *str != '\0')
          str ++;
        if(on_final_arg)
        {
          printf("%s", final_arg);
          exit(0);
        }
				break;

      /* Print instructions */
      case 'h':
        printf("%s", help_message);
        exit(0);
        break;

    }
  }

}

/* ***************************************************************** */
/* ERROR CHECKER                                                     */
/* ***************************************************************** */

/* Ensure that the passed argument is a number */
bool
is_number (char *str)
{

  char *tmp_pointer = str;
  while(*tmp_pointer != '\0' && *tmp_pointer != ' ')
  {
    if(*tmp_pointer < 48 || *tmp_pointer > 57)
    {
			return false;
    }
    tmp_pointer ++;
  }
	return true;

}

/* Ensure correct input */
void
error_checking (char *str)
{

  /* Ensure that the final argument is a number, exit and print an error if not */
	if(!is_number(str))
  {
    printf("%s", final_arg);
    exit(0);
  }

  /* Ensure that the user has selected at least one type of character to include
     in the password, exit and print an error if not */
  if(!uppercase_letters && !lowercase_letters && !symbols && !digits)
  {
    printf("%s", no_chars_selected);
    exit(0);
  }

}

/* ***************************************************************** */
/* MAIN & SETUP                                                      */
/* ***************************************************************** */

/* Convert the passed character to lowercase */
char
upper_to_lower (char ch) 
{
  return  ch + 32;
}

/* Fill up the lowercase array with converted uppercase letters */
void
fill_lowercase_array ()
{

	int i = 0;
  while(i < 26)
  {
    lowercase[i] = upper_to_lower(uppercase[i]);
    i ++;
  }

}
 

int
main (int num_args, char **args)
{

	/* No arguments presented, exit */
  if(num_args == 1)
  {
		printf("%s", no_args);
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
      scan_argument(*args);
    }
  }

	/* args is now pointing to the final argument */
  on_final_arg = true;
	/* Check for problems */
  error_checking(*args);
	/* Fill the array of lowercase letters */
	fill_lowercase_array();
  /* At the final argument,
   argument is a number,
   user has selected at least one type of character
   generate the password */
  generate(atoi(*args));

	/* Done */
  exit(0);

}

/* ***************************************************************** */
/*                                                                   */
/* ***************************************************************** */

