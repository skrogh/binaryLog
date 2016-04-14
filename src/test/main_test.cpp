#include "BinaryLog.h"

#include <fstream>
#include <cstdint>
#include <iostream>

int main( int argc, char *argv[] )
{
	{
	BinaryLogOut logOut( "IIdd", "test.txt" );
	int i = 1;
	logOut.log( &i, 1 );
	logOut.log( &i, 1 );
	double j = 1;
	logOut.log( &j, 1 );
	logOut.log( &j, 1 );
	}
	BinaryLogToCsv( "test.txt", "test.csv" );
	return 0;
}
