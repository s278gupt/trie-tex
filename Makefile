CXX=c++
CXXFLAGS=-std=c++14 -Wall -Werror -g -MMD
EXEC=triex
OBJECTS=main.o node.o trie.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean