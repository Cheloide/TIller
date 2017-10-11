CC =  c++
DEBUG = -g -D DEBUG
LFLAGS = -Wall
CFLAGS = -Wall -c

EXECUTABLENAME = tiler
OBJPATH = obj
BINPATH = bin
DEBUGPATH = debug
SOURCEPATH = src
PKGCONFIGCFLAGS = `pkg-config --cflags keybinder-3.0 gtk+-3.0 libwnck-3.0 glib-2.0 yaml-cpp`
PKGCONFIGLIBS = `pkg-config --libs gtk+-3.0 libwnck-3.0 glib-2.0 keybinder-3.0 yaml-cpp`
DECLARE = -D WNCK_COMPILATION -D WNCK_I_KNOW_THIS_IS_UNSTABLE

clean:
	rm -rf $(OBJPATH)/* $(BINPATH)/* $(DEBUGPATH)/*

##BIN

build: compile
	$(CC) $(LFLAGS) $(PKGCONFIGCFLAGS) $(OBJPATH)/* -o $(BINPATH)/$(EXECUTABLENAME) $(PKGCONFIGLIBS)

compile: clean main.o config.o config.o layoutmanager.o

main.o: $(SOURCEPATH)/main.cpp
	$(CC) $(CFLAGS) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/main.cpp -o $(OBJPATH)/main.o

config.o: $(SOURCEPATH)/config.h $(SOURCEPATH)/config.cpp
	$(CC) $(CFLAGS) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/config.cpp -o $(OBJPATH)/main.o

layout.o:: $(SOURCEPATH)/layoutmanager.h $(SOURCEPATH)/layoutmanager.cpp
	$(CC) $(CFLAGS) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/layoutmanager.cpp -o $(OBJPATH)/main.o


##DEBUG

debug: clean debug-compile 
	$(CC) $(LFLAGS) $(DEBUG) $(PKGCONFIGCFLAGS) $(OBJPATH)/* -o $(DEBUGPATH)/$(EXECUTABLENAME) $(PKGCONFIGLIBS) $(DECLARE)

debug-compile: debug-main.o debug-keybind.o debug-config.o debug-layoutmanager.o

debug-main.o: $(SOURCEPATH)/main.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/main.cpp -o $(OBJPATH)/main.o $(DECLARE)

debug-config.o: $(SOURCEPATH)/config.h $(SOURCEPATH)/config.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/config.cpp -o $(OBJPATH)/config.o $(DECLARE)

debug-layoutmanager.o:: $(SOURCEPATH)/layoutmanager.h $(SOURCEPATH)/layoutmanager.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/layoutmanager.cpp -o $(OBJPATH)/layoutmanager.o $(DECLARE)

debug-keybind.o:: $(SOURCEPATH)/keybind.h $(SOURCEPATH)/keybind.cpp
	$(CC) $(CFLAGS) $(DEBUG) $(PKGCONFIGCFLAGS) $(SOURCEPATH)/keybind.cpp -o $(OBJPATH)/keybind.o $(DECLARE)