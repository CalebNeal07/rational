CC=g++
CPP_VERSION=c++17

build/%.o: src/%.cpp
	@mkdir -p build
	@$(CC) -MM -MT $@ $< > build/$*.d
	$(CC) -c -o $@ $< -std=$(CPP_VERSION)

build/test: build/test.o build/rational.o
	$(CC) -o $@ $^ -std=$(CPP_VERSION)

-include build/*.d

.PHONY: test all clean

test: build/test
	./build/test

clean:
	rm -rf build
