CC 				:= g++
SRCDIR 		:= src
BUILDDIR 	:= build
BIN 			:= bin
TARGET 		:= bin/jvm

SRCEXT    := cpp
SOURCES   := $(wildcard $(SRCDIR)/*.$(SRCEXT)) $(wildcard $(SRCDIR)/operands/*.$(SRCEXT))
OBJECTS   := $(subst $(SRCDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

CFLAGS := -g -Wall

$(TARGET): $(OBJECTS) | $(BIN)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR) $(BUILDDIR)/operands
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

$(BIN):
	mkdir $@

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
