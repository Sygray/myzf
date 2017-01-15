CXX = g++
TARGET = main
LIBS = -lcurl -lcrypto
INCLUDES = -I/usr/local/Cellar/boost/1.63.0/include -I/usr/local/Cellar/openssl/1.0.2j/include/
SRCDIR = ./
OBJDIR = ./
SRCS := $(shell find $(SRCDIR)*.cpp)
OBJS := $(SRCS:.cpp=.o) 

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $^ -o $@ $(LIBS) $(INCLUDES)

clean:
	rm $(TARGET) $(OBJS)
