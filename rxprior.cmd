/*------------------------------------------------------------------
 * rxprior.cmd : test the external functions in rxprior.dll
 *------------------------------------------------------------------*/

"@echo off"

/*------------------------------------------------------------------
 * load functions
 *------------------------------------------------------------------*/
if RxFuncQuery("SysSetPriority") then
   do
   rc = RxFuncAdd("SysSetPriority","RxPrior","SysSetPriority")
   rc = RxFuncAdd("SysGetPriority","RxPrior","SysGetPriority")
   end

/*------------------------------------------------------------------
 * print the current priority
 *------------------------------------------------------------------*/
say "current priority:" SysGetPriority()

/*------------------------------------------------------------------
 * change the priority a few times, and print info each time
 *------------------------------------------------------------------*/

call Test "-1",  "NOCHANGE"          , "PROCESS"
call Test "-1",  "REGULAR"           , "THREAD"
call Test "-1",  "TIMECRITICAL"      , ""
call Test "-1",  "FOREGROUNDSERVER"  , "GARBAGE"

call Test "0"
call Test "0", "NOCHANGE"
call Test "1", "NOCHANGE"
call Test "2", "NOCHANGE"
call Test "3", "NOCHANGE"

call Test "0", "REGULAR"

exit

/*------------------------------------------------------------------
 * run one test
 *------------------------------------------------------------------*/
Test: procedure expose pid
   delta = arg(1)
   class = arg(2)
   scope = arg(3)

   /*---------------------------------------------------------------
    * call with different # of parameters to test defaulting
    *---------------------------------------------------------------*/
   if      (arg() = 1) then rc = SysSetPriority(delta)
   else if (arg() = 2) then rc = SysSetPriority(delta,class)
   else if (arg() = 3) then rc = SysSetPriority(delta,class,scope)

   if (rc <> 0) then
      say "rc =" rc "from SysSetPriority("delta","class","scope")"

   /*---------------------------------------------------------------
    * get the priority
    *---------------------------------------------------------------*/
   priority = SysGetPriority()

   say "priority =" priority,
       "from SysSetPriority("delta","class","scope")"

   return

