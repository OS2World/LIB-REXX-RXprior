#----------------------------------------------------------------------
# Makefile for rxprior.dll
#----------------------------------------------------------------------

COPTS = /C+ /W3 /Q+ /Gd- /Ge- /Gm+ /Ti+ /O-
LOPTS = /ST:20000 /NOLOGO /DEBUG

OBJS  = rxprior.obj
LIBS  = os2386 rexx

.c.obj:
   icc $(COPTS) /Fo$@ $<

rxprior.dll : $(OBJS)
   link386 $(LOPTS) $(OBJS),$@,nul,$(LIBS),rxprior.def;

