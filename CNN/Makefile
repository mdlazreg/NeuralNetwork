TARGET = CNN
CC = g++
CPPFLAGS = -std=c++0x 
SRCs =  InputImage.cpp ConvNeuralNetwork.cpp Layer.cpp ConvolutionLayer.cpp FullyConnectedLayer.cpp PoolingLayer.cpp
LocalSrc = Main.cpp
LocalOBJS = $(patsubst %.cpp,obj1/%.o,$(LocalSrc))
OBJS = $(patsubst %.cpp,obj2/%.o,$(SRCs))
.PHONY : all
all: $(TARGET)

$(OBJS): | obj

obj:
	@echo $(OBJS) $(LocalOBJS)
	@mkdir -p obj1 obj2 


obj2/%.o: ../%.cpp
	$(CC) -I. -I.. -c $(CPPFLAGS) $< -o $@


obj1/%.o: %.cpp
	$(CC) -I. -I.. -c $(CPPFLAGS) $< -o $@


clean:
	rm -rf $(TARGET) obj1 obj2

$(TARGET): $(OBJS) $(LocalOBJS)
	@echo $(OBJS) $(LocalOBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LocalOBJS)
