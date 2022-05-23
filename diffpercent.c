#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )  {
    FILE      *fp1, *fp2;
    int       i = 0;
    float     result = 0;
    long  int fsize1 = 0, fsize2 = 0, match = 0, minfilesize = 0, maxfilesize = 0;

    if (argc != 3)
    {
       printf("I'm sorry but I need two filenames to work.\n");
       printf("Usage: diffpercent filename1 filename2\n");
       printf("Shows a percentage difference between the data of two files.\n");
       exit (3);
    }

    fp1  = fopen(argv [1], "rb");
    if  (fp1 == NULL)
    {
       fprintf(stderr, "I'm sorry but I can't open first input file.\n");
       exit (3);
    }

    fp2 = fopen(argv [2], "rb");
    if (fp2 == NULL)
    {

       fprintf(stderr, "I'm sorry but I can't open second input file.\n");
       exit (3);

    }

    if (fseek(fp1, 0, SEEK_END) != 0)

    {

       fprintf(stderr, "I can't move the file pointer. Sorry but I prefer to give up!\n");
       exit (2);

    }


    if (fseek(fp2, 0, SEEK_END) != 0)

    {

       fprintf(stderr, "I can't move the file pointer. Sorry but I prefer to give up!\n");
       exit (2);

    }

    // Seeks to end of file to get the file size

    fsize1 = ftell(fp1);
    fsize2 = ftell(fp2);

    if (fsize1 > fsize2) { minfilesize = fsize2; maxfilesize = fsize1; } else { minfilesize = fsize1; maxfilesize = fsize2; }

   // same as rewind(file);

    if (fseek(fp1, 0, SEEK_SET) != 0)
    {

       fprintf(stderr, "I can't move the file pointer. Sorry but I prefer to give up!\n");
       exit (2);

    }

    if (fseek(fp2, 0, SEEK_SET != 0))
    {

      fprintf(stderr, "I can't move the file pointer. Sorry but I prefer to give up!\n");
      exit (2);
    }

    // Allocate memory to contain the whole file:
    // add one more byte for the NULL character to
    // terminate the memory string.

    char *buffer1 = malloc(minfilesize + 1);
    char *buffer2 = malloc(minfilesize + 1);

    if (buffer1 == NULL || buffer2 == NULL)
    {
       fprintf(stderr, "I can't allocate memory for the task I have to acomplish. Sorry but I prefer to give up!\n");
       exit (1);
    }

    fread(buffer1, minfilesize, 1, fp1);

    if (ferror (fp1))
    {
       fprintf(stderr, "I can't read the first file. Sorry but I prefer to give up!\n");
       exit (2);
    }

    fread(buffer2, minfilesize, 1, fp2);

    if (ferror (fp2))
    {
       fprintf(stderr, "I can't read the second file. Sorry but I prefer to give up!\n");
       exit (2);
    }

   // Null-terminated string

   buffer1 [fsize1 + 1] = 0;
   buffer2 [fsize2 + 1] = 0;

   for (i = 0; i < minfilesize; i++ )
   {
       if (buffer1 [i] != buffer2 [i]) match = match + 1;
   }

   result = (float)match / (float)maxfilesize * 100;

   printf("%s %s %.2lf\n", argv [1], argv [2], result);

   fclose(fp1);
   fclose(fp2);

   free (buffer1);
   free (buffer2);

   return EXIT_SUCCESS;
