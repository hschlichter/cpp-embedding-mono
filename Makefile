CC = clang++
CFLAGS = -std=c++11 -D_THREAD_SAFE -O0 -g
LDFLAGS = -lmono-2.0 -lpthread -framework CoreFoundation -lobjc -liconv
INCLUDE = -I. -I/Library/Frameworks/Mono.framework/Versions/Current/include/mono-2.0
LDINCLUDE = -L/Library/Frameworks/Mono.framework/Versions/Current/lib

OUTFOLDER = ./out

CPP_SRC = main.cpp
CS_SRC = interop.cs\
	hello.cs

# Main build rules.
.PHONY: all
all: $(OUTFOLDER)/hello.dll $(CPP_SRC)
	$(CC) $(CPP_SRC) -o $(OUTFOLDER)/main $(CFLAGS) $(INCLUDE) $(LDINCLUDE) $(LDFLAGS)

# Build C# dll.
$(OUTFOLDER)/hello.dll: $(CS_SRC)
	mcs -t:library -out:$(OUTFOLDER)/hello.dll $(CS_SRC)

# Source folders to compile
$(OUTFOLDER)%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE)

# Clean rules
.PHONY: clean
clean:
	@rm -rfv $(OUTFOLDER)
