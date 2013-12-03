# Makefile Unit Tests and Behavior Tree Files

GCC        = g++ -g -O0 -Wall -Wextra 
MKDEPS     = g++ -MM -std=gnu++0x
VALGRIND   = valgrind --leak-check=full --show-reachable=yes

MKFILE     = Makefile

SOURCES    = BehaviorTree.cpp Blackboard.cpp BTreeTests.cpp
OBJECTS    = ${SOURCES:.cpp=.o}

HEADERS = IBehaviorTree.h

EXECBIN    = TestBT.out

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS} 
	${GCC} -o ${EXECBIN} ${OBJECTS}

%.o : %.cpp
	${GCC} -c $<

clean :
	- rm ${OBJECTS}

spotless : clean
	- rm ${EXECBIN}

