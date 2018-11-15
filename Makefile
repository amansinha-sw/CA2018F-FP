CXX = nvcc
TARGET = intervalJoin

all: intervalJoin.cu
	$(CXX) $< -o $(TARGET)

.PHONY: clean run

clean:
	rm -f $(TARGET) 

run:
	./$(TARGET)
