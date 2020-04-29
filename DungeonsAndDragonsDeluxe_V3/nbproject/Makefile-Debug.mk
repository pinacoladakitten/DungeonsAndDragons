#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Classes/Actor.o \
	${OBJECTDIR}/Classes/Enemies.o \
	${OBJECTDIR}/Classes/GameSys.o \
	${OBJECTDIR}/Classes/Player.o \
	${OBJECTDIR}/Classes/World.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dungeonsanddragonsdeluxe_v3.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dungeonsanddragonsdeluxe_v3.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dungeonsanddragonsdeluxe_v3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Classes/Actor.o: Classes/Actor.cpp
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/Actor.o Classes/Actor.cpp

${OBJECTDIR}/Classes/Enemies.o: Classes/Enemies.cpp
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/Enemies.o Classes/Enemies.cpp

${OBJECTDIR}/Classes/GameSys.o: Classes/GameSys.cpp
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/GameSys.o Classes/GameSys.cpp

${OBJECTDIR}/Classes/Player.o: Classes/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/Player.o Classes/Player.cpp

${OBJECTDIR}/Classes/World.o: Classes/World.cpp
	${MKDIR} -p ${OBJECTDIR}/Classes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Classes/World.o Classes/World.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
