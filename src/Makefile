PROGRAM := illu
OBJS := model.o scanner.o tokenizer.o environment.o main.o

CXX ?= clang++
CXXFLAGS += -Wall -Werror -O2 -std=c++11
#INCLUDES := include/
RE2C := re2c
#LIBS := ""

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -ledit $(OBJS) -o $(PROGRAM)

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

scanner.o: scanner.cpp
scanner.cpp: scanner.re
	$(RE2C) -o $@ $<

.PHONY: clean clean-without-program
clean:
	$(RM) $(OBJS)  scanner.cpp $(PROGRAM)

clean-without-program:
	$(RM) $(OBJS) scanner.cpp
