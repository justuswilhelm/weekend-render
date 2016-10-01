.PHONY: all
CXXFLAGS=-Wall -Wextra -Werror -std=c++14 -c
LD=ld
all: graphic.ppm

graphic.ppm: main
	./$^ > $@

main: main.o vec3.o ray.o
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f main *.o graphic.ppm
