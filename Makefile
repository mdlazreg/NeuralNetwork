TARGET = NeuralNetwork
CC = g++
CPPFLAGS = -std=c++0x 
SRCs =  Main.cpp Input.cpp NeuralNetwork.cpp DualLayer.cpp

OBJS = $(patsubst %.cpp,obj/%.o,$(SRCs))

.PHONY : all
all: $(TARGET)

$(OBJS): | obj

obj:
	@mkdir -p $@


obj/%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

all: $(TARGET)

clean:
	rm -rf $(TARGET) obj

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS)
