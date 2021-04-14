CXX=g++
CXX_FLAGS=-g -DDEBUG
TARGET=test_server
SRC=test.cpp Server.cpp

.PHONY : all clean

all : $(TARGET)

$(TARGET) :
	$(CXX) $(CXX_FLAGS) $(SRC) -o $(@)

clean :
	rm $(TARGET)