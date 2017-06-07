CC=g++
BIN=MiddleBox ThroughputTest
#TestAll
FLAGS=-Wall -g -fpermissive -std=c++0x
RM=-rm -f
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
OBJ_PURE=$(filter-out MiddleBox.o ThroughputTest.o, $(OBJ))

#thrift
THRIFT_LINK=-lthrift
THRIFT_LIB=-L/usr/local/lib

#openssl
OPENSSL_LINK=-lcrypto

#caravel
CARAVEL_LINK=-lcaravel
CARAVEL_LIB=-L../Caravel
CARAVEL_INC=-I../Caravel

#combine the inc & lib
INC=$(CARAVEL_INC) $(OPENSSL_INC) $(THRIFT_INC)
LIB=$(CARAVEL_LINK) $(CARAVEL_LIB) $(OPENSSL_LINK) $(THRIFT_LINK) $(THRIFT_LIB)


all: $(BIN)

%.d: %.cpp
	$(CC) -MM $(FLAGS) $(INC) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(FLAGS) $(INC) $< -o $@

MiddleBox:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(OBJ_PURE) $(LIB)

ThroughputTest:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(OBJ_PURE) $(LIB)

clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) $(BIN)

-include $(SRC:.cpp=.d)
