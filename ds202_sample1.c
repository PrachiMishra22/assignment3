#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <divsufsort.h>

int main()
{
  // intput data
   FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("sequences.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	int state = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		/* Delete trailing newline */
		if (line[read - 1] == '\n')
			line[read - 1] = 0;
		/* Handle comment lines*/
		if (line[0] == '>') {
			if (state == 1)
				printf("\n");
			printf("%s: ", line+1);
			state = 1;
		} else {
			/* Print everything else */
			printf("%s", line);
		}
	}
	printf("\n");
   int n = strlen(line);
  printf("The length of whole genome is %d",n);
  int i, j;

  // allocate
  int *SA = (int *)malloc(n * sizeof(int));
  time_t beginSA, endSA,beginlCP,endlcp ;
    time(&beginSA);

  // sort
  divsufsort((unsigned char *)line, SA, n);

  // output
  for (i = 0; i < n; ++i)
  {
    printf("SA[%2d] = %2d: ", i, SA[i]);
    for (j = SA[i]; j < n; ++j)
    {
      printf("%c", line[j]);
    }
    printf("$\n");
  }
  time(&endSA);
    time_t elapsedSA = endSA - beginSA;
      printf("Time elapsed for computing and printing the SA array is %ld seconds.\n ",elapsedSA);
  // Inverse suffix array

  // allocate
  time(&beginlCP);
  int *INSA = (int *)malloc(n * sizeof(int));

  // constructing the inverse suffix array

  for (i = 0; i < n; ++i)
  {
    INSA[SA[i]] = i;
  }
  // printing inverse suffix array
  for (i = 0; i < n; ++i)
  {
    printf("INSA[%2d] = %2d: ", i, INSA[i]);

    printf("$\n");
  }
  // allocate space to LCP array
  int *LCPArray = (int *)malloc((n - 1) * sizeof(int));

  // calculating LCParray

  int k = 0;
  int suffix = 0;                       // T0
  int FirstSUffix_Index = INSA[suffix]; // location of T0;
  int PreviousSuffix = SA[FirstSUffix_Index - 1];

  for (int i = 0; i < n; ++i)
  {
    if (PreviousSuffix + i <= n && suffix + i <= n)
    {
      if (line[PreviousSuffix + i] == line[suffix + i])
      {
        k = k + 1;
      }
    }
  }
  printf("The Initial value of k is %d", k);
  LCPArray[FirstSUffix_Index] = k;
  int lcp;
  for (int i = 1; i < n; ++i) /// To travel through all element of suffix array
  {
    suffix = i;

    int SUffix_Index = INSA[suffix];

    int PreviousSuffixxx = SA[SUffix_Index - 1];
    if (k - 1 < 0)
    {
      lcp = 0;
    }
    else
    {
      lcp = k - 1;
    }

    for (int j = lcp; j < n; ++j) // To compare characters in a pair of suffixes

    {

      if (PreviousSuffixxx + j < n && suffix + j < n)
      {
        if (line[PreviousSuffixxx + j] == line[suffix + j])
        {
          lcp = lcp + 1;
        }
      }
      else
      {
        break;
      }
    }
    LCPArray[SUffix_Index] = lcp;
    k = lcp;
  }
  // Printing LCP array
  for (int i = 1; i < n; ++i)
  {
    printf("LCP[%d] = %d: ", i, LCPArray[i]);

    printf("$\n");
  }

  time(&endlcp);
  time_t elapsedlcp = endlcp - beginlCP;
  printf("Time elapsed for computing and printing the LCP array is %ld seconds.\n ", elapsedlcp);
  // Length of the longest repeat
  int max = LCPArray[1];
  int longestRepeat;
  for (int p = 1; p < n; ++p)
  {
    if (LCPArray[p] > max)
    {
      max = LCPArray[p];
      longestRepeat = p;
    }
  }

  printf("Length of the longest repeat is %d\n", max);
  printf("Starting positions of the longest repeat in input text is %d, %d\n", SA[longestRepeat], SA[longestRepeat - 1]);

  // deallocate
  free(SA);

  return 0;
}
