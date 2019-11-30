CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = myprogram
OBJECTS = main.o Game.o Command.o TextDisplay.o Player.o Board.o BlockFiles/IBlock.o BlockFiles/JBlock.o BlockFiles/LBlock.o BlockFiles/OBlock.o BlockFiles/SBlock.o BlockFiles/StarBlock.o BlockFiles/ZBlock.o BlockFiles/TBlock.o Block.o Cell.o  Level.o LevelZero.o LevelOne.o LevelTwo.o LevelThree.o LevelFour.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
