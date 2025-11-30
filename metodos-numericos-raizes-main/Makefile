CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGET = main

SOURCES = main.cpp \
          SistemaJatos.cpp \
          Menu.cpp \
          FuncaoJato.cpp \
          Jato.cpp \
          Bisseccao.cpp \
          PosicaoFalsa.cpp \
          NewtonRaphson.cpp \
          Resultado.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all run clean
