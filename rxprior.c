/*------------------------------------------------------------------
 * rxprior.c : external rexx function to set priority
 *------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCL_BASE
#include <os2.h>

#define INCL_REXXSAA
#include <rexxsaa.h>

/*------------------------------------------------------------------
 * prototypes for rexx functions, to make sure we declared everything
 * correctly
 *------------------------------------------------------------------*/

RexxFunctionHandler SysSetPriority;
RexxFunctionHandler SysGetPriority;

#pragma linkage(SysSetPriority, system)
#pragma linkage(SysGetPriority, system)

/*------------------------------------------------------------------
 * this function is called when user invokes SysGetPriority() in REXX
 *
 * expects no parameters
 *------------------------------------------------------------------*/
ULONG APIENTRY SysGetPriority(
   PUCHAR     pszName,
   ULONG      ulArgc,
   PRXSTRING  prxArgv,
   PSZ        pszQueueName,
   PRXSTRING  prxRet
   )
   {
   PPIB   ppib;
   PTIB   ptib;
   APIRET rc;

   /*---------------------------------------------------------------
    * call DosGetInfoBlocks()
    *---------------------------------------------------------------*/
   rc = DosGetInfoBlocks(&ptib,&ppib);

   /*---------------------------------------------------------------
    * put priority in return code
    *---------------------------------------------------------------*/
   sprintf(prxRet->strptr,"%08.8lx",ptib->tib_ptib2->tib2_ulpri);
   prxRet->strlength = strlen(prxRet->strptr);

   return 0;
   }

/*------------------------------------------------------------------
 * this function is called when user invokes SysSetPriority() in REXX
 *
 * expects the following parameters
 *    1 - number between -31 and 31, the delta of the priority to set
 *    2 - optional class: "NOCHANGE", "IDLETIME", "REGULAR",
 *                        "TIMECRITICAL", "FOREGROUNDSERVER"
 *    3 - option scope: "PROCESS", "PROCESSTREE", "THREAD"
 *
 *------------------------------------------------------------------*/
ULONG APIENTRY SysSetPriority(
   PUCHAR     pszName,
   ULONG      ulArgc,
   PRXSTRING  prxArgv,
   PSZ        pszQueueName,
   PRXSTRING  prxRet
   )
   {
   APIRET     rc;
   PSZ        pszDelta;
   PSZ        pszClass;
   PSZ        pszScope;
   ULONG      ulScope;
   ULONG      ulClass;
   LONG       lDelta;

   /*---------------------------------------------------------------
    * make sure there are 1, 2 or 3 parameters
    *---------------------------------------------------------------*/
   if ((ulArgc < 1) || (ulArgc > 3))
      return 40;

   /*---------------------------------------------------------------
    * apply default parameters
    *---------------------------------------------------------------*/
   if (RXVALIDSTRING(prxArgv[0]))
      pszDelta = prxArgv[0].strptr;
   else
      pszDelta = "0";

   if ((ulArgc >= 2) && RXVALIDSTRING(prxArgv[1]))
      pszClass = prxArgv[1].strptr;
   else
      pszClass = "NOCHANGE";

   if ((ulArgc >= 3) && RXVALIDSTRING(prxArgv[2]))
      pszScope = prxArgv[2].strptr;
   else
      pszScope = "PROCESS";

   /*---------------------------------------------------------------
    * convert delta to a number
    *---------------------------------------------------------------*/
   lDelta = strtol(pszDelta,NULL,10);

   /*---------------------------------------------------------------
    * convert class to a pre-defined constant
    *---------------------------------------------------------------*/
   if      (!stricmp(pszClass, "NOCHANGE"))
      ulClass =           PRTYC_NOCHANGE;

   else if (!stricmp(pszClass, "IDLETIME"))
      ulClass =           PRTYC_IDLETIME;

   else if (!stricmp(pszClass, "REGULAR"))
      ulClass =           PRTYC_REGULAR;

   else if (!stricmp(pszClass, "TIMECRITICAL"))
      ulClass =           PRTYC_TIMECRITICAL;

   else if (!stricmp(pszClass, "FOREGROUNDSERVER"))
      ulClass =           PRTYC_FOREGROUNDSERVER;

   else
      ulClass = PRTYC_NOCHANGE;

   /*---------------------------------------------------------------
    * convert scope to a pre-defined constant
    *---------------------------------------------------------------*/
   if      (!stricmp(pszScope, "PROCESS"))
      ulScope =           PRTYS_PROCESS;

   else if (!stricmp(pszScope, "PROCESSTREE"))
      ulScope =           PRTYS_PROCESSTREE;

   else if (!stricmp(pszScope, "THREAD"))
      ulScope =           PRTYS_THREAD;

   else
      ulScope = PRTYS_PROCESS;

   /*---------------------------------------------------------------
    * call the DosSetPriority() function
    *---------------------------------------------------------------*/
   rc = DosSetPriority(ulScope,ulClass,lDelta,0);

   /*---------------------------------------------------------------
    * set return value
    *---------------------------------------------------------------*/
   sprintf(prxRet->strptr,"%ld",rc);
   prxRet->strlength = strlen(prxRet->strptr);

   return 0;
   }

