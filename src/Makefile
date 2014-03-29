PROGRAM := rpn
SRCS := model.cpp lexer.cpp main.cpp
OBJS := $(subst .cpp,.o,$(SRCS))

CXX := clang++

CXXFLAGS := -Wall -W -O2 -std=c++11
#INCLUDES := include/
RE2C := re2c
#LIBS := ""

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

lexer.o: lexer.cpp
lexer.cpp: lexer.re
	$(RE2C) -o $@ $<

clean:
	$(RM) $(OBJS) $(PROGRAM)

clean-without-program:
	$(RM) $(OBJS) lexer.cpp
