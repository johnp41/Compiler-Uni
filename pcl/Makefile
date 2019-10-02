CXX = g++-8
CXXFLAGS = -Wall -Wextra -std=c++11 -g 
C = gcc-8
CFLAGS = -std=c11 -Wall -g
DEPS = my-ast.hpp symbol.h
LLVMFLAGS =`llvm-config-6.0 --cxxflags --ldflags --libs all --system-libs`
default:pcl lib

lib :
	cd edsger_lib; bash libs.sh

lexer.cpp:lexer.l my-ast.hpp my-ast.cpp fix.cpp
	flex -s -o lexer.cpp   lexer.l  


lexer.o: lexer.cpp   parser.hpp   my-ast.cpp symbol.h lexer.hpp my-ast.hpp

parser.hpp parser.cpp: parser.y my-llvm.cpp  my-ast.cpp my-ast.hpp my-ast.cpp symbol.c symbol.h
	bison -dv -o parser.cpp parser.y

parser.o: parser.cpp parser.hpp symbol.c symbol.h sem.cpp sem.o my-llvm.cpp

my-llvm.o: my-llvm.cpp my-llvm.hpp symbol.c symbol.h 
	$(CXX) my-llvm.cpp -c   $(CXXFLAGS) `llvm-config-6.0 --cxxflags` 

pcl: lexer.o parser.o my-ast.o error.o  general.o symbol.o sem.o my-llvm.o fix.o
	$(CXX) $(CXXFLAGS) -o pcl  $^   $(LLVMFLAGS)




#%o: %cpp $(DEPS)

#%o: %c

.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
	$(C) $(CFLAGS) -c $<


clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean:clean
	$(RM) pcl

