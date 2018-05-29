CPPFLAGS = -Wall -fno-diagnostics-show-caret -fdiagnostics-color=always -D_GNU_SOURCE=1 -D_REENTRANT -g
#LIBS = -lSDL -lSDL_gfx
LIBS = -L/mingw32/lib -lmingw32 -lSDLmain -lSDL -lSDL_gfx -mwindows 

all: program.exe

%.o : %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
	
program.exe : Program.o Particle.o Neutron.o Proton.o Photon.o Vec3.o SDLDriver.o
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm -f *.o program.exe