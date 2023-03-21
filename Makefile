COMPILEFLAGS	 = -I"libs\include" -DSFML_STATIC
LINKFLAGS	 = -o main -L"libs\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main

all: preclean compile link clean

compile:
	g++ $(COMPILEFLAGS) -c *.cpp 

link:
	g++ *.o $(LINKFLAGS)

clean:
	del *.o

preclean:
	del *.exe