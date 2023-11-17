CXX = clang
CXXFLAGS = -Wall

.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f client server

client:
	$(CXX) $(CXXFLAGS) -o client client.c funcs.c

server:
	$(CXX) $(CXXFLAGS) -o server server.c funcs.c

all:
	rm -f client server
	$(CXX) $(CXXFLAGS) -o client client.c funcs.c
	$(CXX) $(CXXFLAGS) -o server server.c funcs.c
