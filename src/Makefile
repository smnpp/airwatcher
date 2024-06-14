CC = g++
CFLAGS = -I./Data -I./Services -std=c++17 -Wall
LDFLAGS =
OBJDIR = obj

# Define source files
DATA_SOURCES = $(wildcard Data/*.cpp)
SERVICE_SOURCES = $(wildcard Services/*.cpp)
INTERFACE_SOURCES = $(wildcard Interface/*.cpp)

# Define object files
DATA_OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(DATA_SOURCES))
SERVICE_OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SERVICE_SOURCES))
INTERFACE_OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(INTERFACE_SOURCES))

# All object files
OBJECTS = $(DATA_OBJECTS) $(SERVICE_OBJECTS) $(INTERFACE_OBJECTS)

# Pattern rule for object files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Main executable
AirWatcher: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Clean the build
clean:
	rm -rf $(OBJDIR)/* main