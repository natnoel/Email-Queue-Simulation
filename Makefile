#CSCI203 Assignment 2
SRCS = PoissonDist.cpp Mail.cpp EmailQueue.cpp ServerResources.cpp MainA2.cpp
HDRS = PoissonDist.h Mail.h EmailQueue.h ServerResources.h
PROJ = Assignment2

CC = g++
OBJS = $(SRCS:.cpp=.o)
APP = $(PROJ).exe
CFLAGS = -c -g -Wall -I/opt/local/include
ifeq (,$(findstring CYGWIN,$(shell uname)))
  LDFLAGS = -L/opt/local/lib
else
  LDFLAGS = -L/opt/local/lib -enable-auto-import
endif
LIBS = -lcppunit -ldl

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(APP) $(LIBS)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(APP)
