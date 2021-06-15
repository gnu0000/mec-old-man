/*
 *
 * man.c
 * Thursday, 8/11/1994.
 *
 */

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GnuArg.h>
#include <GnuFile.h>
#include <GnuStr.h>

char sz[1024];

void Usage (void)
   {
   printf ("  USAGE: MAN [/ManFile=manfile] topic topic ...\n");
   printf ("          wildcards ok for topic.\n\n");
   printf ("ENV VAR: MANFILE=manfile (full filespec)\n");
   exit (0);
   }

finish this
BOOL Match (PSZ pszList, PSZ pszWild)
   {
   StrGetWord (&pszList, szWord, " \t", ",\n", )




   if (!strchr (pszList, ','))
      return StrMatches (pszList, pszWild, FALSE);





    if (!StrMatches (sz+2, p1, FALSE)) // not right section

   }


int main (int argc, char *argv[])
   {
   PSZ    p1;
   USHORT i;
   FILE   *fp;
   BOOL   bRead;
   BOOL   bList;

   if (ArgBuildBlk ("? *^ManFile% *^List"))
      return printf ("%s", ArgGetErr ());

   if (ArgFillBlk (argv))
      return printf  ("%s", ArgGetErr ());

   if (p1 = getenv ("MANFILE"))
      {
      sprintf (sz, "/ManFile=%s", p1);
      ArgFillBlk2 (sz);
      }

   bList = ArgIs ("List");

   if (ArgIs ("?") || !(ArgIs (NULL) || bList))
      Usage ();

   if (!ArgIs ("ManFile"))
      return printf ("ManFile must be specified on cmd line or in MANFILE env var.");

   if (!(fp = fopen (ArgGet ("ManFile", 0), "rt")))
      return printf ("Cannot open ManFile: %s", ArgGet ("ManFile", 0));


   for (i=0; (p1 = ArgGet (NULL, i)) || (!i && bList); i++)
      {
      rewind (fp);
      bRead = TRUE;

      while (TRUE)
         {
         if (bRead && (FilReadLine (fp, sz, "", 1024) == 0xFFFF))
            break;
         bRead = TRUE;

         if (*sz != '#')                    // not a section header line
            continue;

         StrClip (sz+2, " \t");

         if (bList && !p1) // Non specific listing
            {
            printf ("%s\n", sz+2);
            continue;
            }

         if (!Match (sz+2, p1))            // incorrect section
            continue;

         if (bList)       // Qualified listing
            {
            printf ("%s\n", sz+2);
            continue;
            }

         printf ("====== %s ======\n", sz+2);
         while (FilReadLine (fp, sz, "", 1024) != 0xFFFF)
            {
            if (*sz == '#')                // end of this section
               break;
            printf ("%s\n", sz);
            }
         printf ("\n", sz);
         bRead = FALSE;
         }
      }
   fclose (fp);
   return 0;
   }

