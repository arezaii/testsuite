############################################################################
#
#  Program:         ScaLAPACK
#
#  Module:          SLmake.inc
#
#  Purpose:         Top-level Definitions
#
#  Creation date:   February 15, 2000
#
#  Modified:        October 13, 2011
#
#  Send bug reports, comments or suggestions to scalapack@cs.utk.edu
#
############################################################################
#
#  C preprocessor definitions:  set CDEFS to one of the following:
#
#     -DNoChange (fortran subprogram names are lower case without any suffix)
#     -DUpCase   (fortran subprogram names are upper case without any suffix)
#     -DAdd_     (fortran subprogram names are lower case with "_" appended)

CDEFS         = -DAdd_

#
#  The fortran and C compilers, loaders, and their flags
#

FC            = $(TEST_FTN_MPI) #mpif90
CC            = $(TEST_CC_MPI) #mpicc 
NOOPT         = -O0
FCFLAGS       = -O3
CCFLAGS       = -O3
FCLOADER      = $(FC)
CCLOADER      = $(CC)
FCLOADFLAGS   = $(FCFLAGS)
CCLOADFLAGS   = $(CCFLAGS)

#
#  The archiver and the flag(s) to use when building archive (library)
#  Also the ranlib routine.  If your system has no ranlib, set RANLIB = echo
#

ARCH          = ar
ARCHFLAGS     = cr
RANLIB        = ranlib

#
#  The name of the ScaLAPACK library to be created
#

SCALAPACKLIBSO  = -lscalapack #libscalapack.a

#
#  BLAS, LAPACK (and possibly other) libraries needed for linking test programs
#

#BLASLIB       = -lblas
#LAPACKLIB     = -llapack
LIBS          = -L$(NETLIB_SCALAPACK_LIB_PATH) $(LAPACKLIB) $(BLASLIB) $(SCALAPACKLIBSO)
