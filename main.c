/**
  * main.c
  * split the mainframe file into sections determined by context lines
  * Alan.M
  * 0.1
  * 07 septembre 2018
  * gcc -pg -std=c11 -Wall -fmax-errors=10 -Wextra main.c -o zikarto
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* BUFFER_SIZE(count)
 *
 * Reminder about binary prefixes of standardization:
 *  kibi "binary kilo" : 2^10 bytes 		       = 1 024 bytes
 *  mébi "binary méga" : 2^20 bytes = 1 024 kio  = 1 048 576 bytes
 *  gibi "binary giga" : 2^30 bytes = 1 024 Mio  = 1 073 741 824 bytes
 */
#define BUFFER_SIZE (1024)

/* INFILE(filename)
 * Name of the input file to process
 *
 * Will need to be replaced by a parameter passed on the command
 * line to the program.
 */
#define INFILE ("zosfile.txt")

/**
 * int main (void)
 * Program entry.
 *
 * EXIT_SUCCESS - Ending program without error.
 * EXIT_FAILURE - Error handling at end of program.
 */
int main ()
{
    FILE *p_infile = NULL;
    char *p_buffer = NULL;
    size_t readbytes = 0;

    // Allocate the buffer used for reading the input file
    p_buffer = malloc (BUFFER_SIZE);
    if (p_buffer == NULL)
    {
        fprintf (stderr, "Fatal: failed to allocate %d bytes.\n", BUFFER_SIZE);
        return EXIT_FAILURE;
    }

    // Initialize with binary zero the buffer acquired above
    memset(p_buffer, 0, BUFFER_SIZE);

    // open input file in read only
    p_infile=fopen (INFILE, "r");
    if (!p_infile)
    {
        fprintf (stderr, "Fatal: failed to open input file %s\n", INFILE);
        return EXIT_FAILURE;
    }

    // Read input file by chunk of 1024 bytes
    fseek(p_infile,0,SEEK_SET);
    printf("Current position: %ld\n", ftell(p_infile));

    do 
    {
        readbytes = fread(p_buffer, sizeof(char), BUFFER_SIZE, p_infile);
        if (readbytes > 0 )
        {
            printf("Read of %ld bytes successful\n", readbytes);
        }
    } while(readbytes > 0);
 
    fclose (p_infile);
    free (p_buffer);

    return EXIT_SUCCESS;
}
