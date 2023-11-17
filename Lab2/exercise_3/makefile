CXX = clang
CXXFLAGS = -Wall

.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f client server

client:
	$(CXX) $(CXXFLAGS) -o client client.c fifo-write.c fifo-read.c funcs.c

server:
	$(CXX) $(CXXFLAGS) -o server server.c fifo-write.c fifo-read.c funcs.c
