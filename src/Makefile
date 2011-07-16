CXX = g++
CXXFLAGS = -O2 -Wall -g

SRCS = random.cpp ngram.cpp kaibun.cpp hashtrie.cpp trie.cpp util.cpp log.cpp \
sexp.cpp arraytrie.cpp asciiserializer.cpp dictionary.cpp
OBJS = $(SRCS:%.cpp=%.o)
TESTSRCS = test_kaibun.cpp test_random.cpp test_hashtrie.cpp testmain.cpp \
test_sexp.cpp test_arraytrie.cpp test_asciiserializer.cpp

TESTOBJS = $(TESTSRCS:%.cpp=%.o)

TESTLIBS = /usr/lib/libboost_unit_test_framework-gcc-mt.a

ALLSRCS = $(SRCS) $(TESTSRCS)

.SUFFIXES:
.SUFFIXES: .cpp .o .d

ALL: kaibun, test

.cpp.d:
	$(CXX) -MM $^ > $@

test: $(OBJS) $(TESTOBJS)
	$(CXX)  $(CXXFLAGS) -o $@ $^ $(TESTLIBS)

kaibun: $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) *.o *.d

-include $(ALLSRCS:%.cpp=%.d)
