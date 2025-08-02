CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/morphology

OBJS = $(SRCDIR)/main.o $(SRCDIR)/io_utils.o $(SRCDIR)/morphology.o

all: $(TARGET)

$(BINDIR)/morphology: $(OBJS)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR) $(SRCDIR)/*.o
