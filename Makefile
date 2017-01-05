TARGET = NeuralNetwork
CC = g++
CPPFLAGS = -std=c++0x 
OBJS =  Main.o Input.o NeuralNetwork.o NeuralLayer.o

.PHONY : all
all: $(TARGET)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)
$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS)
