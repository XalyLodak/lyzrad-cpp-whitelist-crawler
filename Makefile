# Makefile simple et robuste
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
LIBS := -lmysqlcppconn
SRCDIR := src
OBJDIR := bin/obj
BINARY := bin/rcon_client
DEBDIR := lyzrad-rcon
DEBPKG := lyzrad-rcon.deb
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all debug release clean dirs deb

all: release

release: CXXFLAGS += -O2
release: $(BINARY)

debug: CXXFLAGS += -g -O0
debug: $(BINARY)

$(BINARY): $(OBJS)
	@echo "Linking -> $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | dirs
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(dir $(BINARY))

deb: release
	@echo "Building .deb package..."
	@mkdir -p $(DEBDIR)/DEBIAN
	@mkdir -p $(DEBDIR)/usr/bin
	@cp $(BINARY) $(DEBDIR)/usr/bin/lyzrad-rcon
	@cp control $(DEBDIR)/DEBIAN/control
	@dpkg-deb --build $(DEBDIR) $(DEBPKG)
	@echo "Package créé : $(DEBPKG)"

clean:
	@echo "Cleaning..."
	@rm -rf bin/*
	@rm -rf $(DEBDIR)
	@rm -f $(DEBPKG)
	@rm -rf *.deb