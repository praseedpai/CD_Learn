// fourth_a.cpp
// g++ -c -o fourth_a.o fourth_a.cpp
// link with fourth.cpp ( see the heading for how to do it)
long myabs( long a ) {
   if ( a < 0 ) { a = -a; }
   return a;
}
// eof fourth_a.cpp