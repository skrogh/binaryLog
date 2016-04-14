#include "BinaryLog.h"

#include <fstream>
#include <cstdint>
#include <iostream>

int main( int argc, char *argv[] )
{
	BinaryLogToCsv( "/dev/stdin", "/dev/stdout" );
	return 0;
}
