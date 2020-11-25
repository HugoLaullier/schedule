

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

scheduleLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =  -std=c++14 -fopenmp -O2 -g -Wall -fmessage-length=0 -I$(scheduleLIB_PATH)include

OBJS = schedule.o scheduleIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :


#END OF USER MAKEFILE OPTIONS

TARGET =	schedule

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(scheduleLIB_PATH)/libeasea.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp schedule.png schedule.dat schedule.prm schedule.mak Makefile schedule.vcproj schedule.csv schedule.r schedule.plot schedule.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp schedule.png schedule.dat schedule.prm schedule.mak Makefile schedule.vcproj schedule.csv schedule.r schedule.plot schedule.pop
endif

