CXXFLAGS =	-Wall
TARGET =	Walki
$(TARGET):	
	$(CXX) Walki.cpp -o $(TARGET) 

all:	$(TARGET)

clean:
	rm -f $(TARGET)
