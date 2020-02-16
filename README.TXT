----------------------------------------------------------------------

   You are hereby granted a royalty-free license to use, modify,
   distribute, copy and create derivative works of the (name
   of code or module or program), subject to the following terms
   and conditions.  The (program, code whatever) is provided AS IS
   with no warranty of any kind. No support of any kind will be
   provided by the author or IBM Corporation.  The use of this
   code is at your own risk and the risk of your licensees.
   You are not granted any right to use any trademark or trade name
   of IBM in connection with the use or distribution of this (program
   or code name) or any version or modification thereof. The
   author and IBM do not warrant that this code does not infringe the
   intellectual property rights of any third party.

----------------------------------------------------------------------

This package contains the source for the rxPrior function package for
OS/2, as described in the article "Extending REXX with External
Functions" in the OS/2 Developer Magazine, January/February 1994, pg.
73, by Andrei Malacinski and Patrick Mueller.  Patrick can be reached
via the Internet at pmuellr@vnet.ibm.com.

The package is made up of five files:
   README      - this file
   rxprior.lst - packing list
   rxprior.c   - the C source
   rxprior.mak - the make file
   rxprior.def - the .def file
   rxprior.cmd - a REXX program to test the function package

To build the rxprior.dll file, invoke make on the rxprior.mak
file.  After building the .dll, you can run the rxprior.cmd test
program.

The sample code implements two functions:  SysGetPriority() and
SysSetPriority().  These functions are used to query and set the
priority of the currently process.

SysGetPriority()
   This function expects no parameters.  It returns an 8-digit hex
   string that indicates the priority of the current process.  The
   function returns the priority from a field in the info blocks
   structure returned by the DosGetInfoBlocks() function.

SysSetPriority(delta,class,scope)
   This function expects the delta parameter to be a number from -31 to
   31, the class parameter to be one of the strings "NOCHANGE", IDLETIME",
   "REGULAR", "TIMECRITICAL", or "FOREGROUNDSERVER",  and the scope
   parameter to be one of the strings "PROCESS", "PROCESSTREE" or
   "THREAD".  The parameters correspond to the values expected by
   the DosSetPriority() function.  The external function calls this
   function and returns the return code from that function.  The
   delta parameter must be passed in, but the other two are optional.
   Missing or incorrect parameters cause default values to be used.

The RxPrior.cmd file tests the external functions by calling
SysSetPriority() a number of times with different parameters.  After
each call to SysSetPriority(), SysGetPriority() is called to determine
what the priority was set to.  The resulting value is printed as output
from the program.

