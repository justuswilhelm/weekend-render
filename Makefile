.PHONY: all clean format
CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -c
LD=ld
OBJS=main.o vec3.o ray.o sphere.o hitable_list.o
all: graphic.ppm

graphic.ppm: main
	time ./$^ > $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f main *.o graphic.ppm

format:
	clang-format -i *.cpp *.h
