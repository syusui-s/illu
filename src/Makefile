PROGRAM := stap
SRCS := model.cpp scanner.cpp tokenizer.cpp main.cpp
OBJS := $(subst .cpp,.o,$(SRCS))

CXX := clang++

CXXFLAGS := -Wall -Werror -O2 -std=c++11
#INCLUDES := include/
RE2C := re2c
#LIBS := ""

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

scanner.o: scanner.cpp
scanner.cpp: scanner.re
	$(RE2C) -o $@ $<

clean:
	$(RM) $(OBJS)  scanner.cpp $(PROGRAM)

clean-without-program:
	$(RM) $(OBJS) scanner.cpp
