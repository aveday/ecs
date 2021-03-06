CXX := g++
CPPFLAGS := -Wall -Wextra -std=c++14
BIN := test
LDFLAGS := -lm -lglfw -lGL -lGLU -lGLEW
RM:= rm -rf

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=obj/%.o)

all: $(BIN)

clean:
	@echo Cleaning...
	@$(RM) obj dep $(BIN)

$(BIN): $(OBJS)
	@echo Linking executable $(BIN)
	@$(CXX) $(LDFLAGS) $(OBJS) -o $@

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir -p dep/$(*D) obj/$(*D)
	@$(CXX) $(CPPFLAGS) -I. -Isrc -MMD -MP -MF dep/$*.d -c -o $@ $<

-include $(OBJS:obj/%.o=dep/%.d)

.PHONY: all clean

