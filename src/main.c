#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "memhog.h"

int
main (int const argc, char const *const argv[])
{
  size_t size = 0;
  if (argc < 2)
    {
      size = get_total_system_memory ();
    }
  else
    {
      char *endptr = NULL;

      errno = 0;
      size = (size_t)strtoull (argv[1], &endptr, 0);

      if (errno != 0 || endptr == NULL || *endptr != '\0')
        {
          fprintf (stderr, "Invalid argument: %s\n", argv[1]);
          fflush (stderr);

          return EXIT_FAILURE;
        }
    }

  printf ("Allocating %zu bytes of memory...", size);
  fflush (stdout);

  uint8_t *const memory = hog_memory (size);
  if (memory == NULL)
    {
      printf ("\n");
      fprintf (stderr, "Failed to allocate %zu bytes of memory.\n", size);

      fflush (stdout);
      fflush (stderr);

      return EXIT_FAILURE;
    }

  printf ("Done.\n");
  printf ("Press Enter to release memory and exit...");
  fflush (stdout);

  getchar ();
  free (memory);

  return EXIT_SUCCESS;
}
