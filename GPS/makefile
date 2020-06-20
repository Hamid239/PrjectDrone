JL_SHARE :=/mnt/s/projectDrone/julia/usr/share/julia
CFLAGS   += $(shell $(JL_SHARE)/julia-config.jl --cflags)
CXXFLAGS += $(shell $(JL_SHARE)/julia-config.jl --cflags)
LDFLAGS  += $(shell $(JL_SHARE)/julia-config.jl --ldflags)
LDLIBS   += $(shell $(JL_SHARE)/julia-config.jl --ldlibs)
print-%  : ; @echo $* = $($*)
CC := gcc
CXX := g++

.PHONY: all
all: testing

main: testing.c makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o test testing.c

.PHONY: clean
clean:
	$(RM) main
	
	
