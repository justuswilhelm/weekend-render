.PHONY: all clean format
CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -c -O3
OBJS=main.o vec3.o ray.o sphere.o hitable_list.o camera.o
all: graphic.ppm

graphic.ppm: main
	time ./$^ > $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f main *.o graphic.ppm *.h.gch

format:
	clang-format -i *.cpp *.h
