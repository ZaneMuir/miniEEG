CXX = gcc
CFLAGS = -Wall -Wconversion -O3 -fPIC
SHVER = 2
OS = $(shell uname)

lib-test: test-suite
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,miniEEG.so.$(SHVER)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,miniEEG.so.$(SHVER)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} miniEEGIO_test.o -o libminiEEG_test.so.$(SHVER)
test-suite: miniEEGIO_test.c
	$(CXX) $(CFLAGS) -c miniEEGIO_test.c

all: writer
lib: miniEEG.o
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,libminiEEG.so.$(SHVER)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,libminiEEG.so.$(SHVER)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} miniEEG.o -o libminiEEG.so.$(SHVER)
writer: miniEEGWriter.c miniEEG.o
	$(CXX) $(CFLAGS) -c miniEEGWriter.c miniEEG.o -o writer -lm
miniEEG.o: miniEEG.c miniEEG.h
	$(CXX) $(CFLAGS) -c miniEEG.c

clean:
	rm -f *~ miniEEGIO_test.o libminiEEG_test.so.$(SHVER) miniEEGWriter.o miniEEG.o libminiEEG.so.$(SHVER) writer