#include "BinaryLog.h" 
#include <assert.h>     /* assert */
#include <string>

BinaryLogOut::BinaryLogOut( const char* format_, const char* file_ ) :
file(file_, std::ofstream::binary),
format( format_ ),
linePos(0)
{
	uint32_t length = format.length();
	file.write( (char*)&length, sizeof(length) );
	file << format;
}

void BinaryLogOut::flush( void )
{
	file.flush();
}

void BinaryLogOut::log(  uint8_t* data, int length )
{
	assert( format.at(linePos) == 'c' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(   int8_t* data, int length )
{
	assert( format.at(linePos) == 'C' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log( uint16_t* data, int length )
{
	assert( format.at(linePos) == 'h' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(  int16_t* data, int length )
{
	assert( format.at(linePos) == 'H' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log( uint32_t* data, int length )
{
	assert( format.at(linePos) == 'i' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(  int32_t* data, int length )
{
	assert( format.at(linePos) == 'I' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log( uint64_t* data, int length )
{
	assert( format.at(linePos) == 'l' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(  int64_t* data, int length )
{
	assert( format.at(linePos) == 'L' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(    float* data, int length )
{
	assert( format.at(linePos) == 'f' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}
void BinaryLogOut::log(   double* data, int length )
{
	assert( format.at(linePos) == 'd' );
	file.write( (char*)data, sizeof(data[0])*length );
	linePos++;
	if ( linePos >= format.length() )
		linePos = 0;
}

void BinaryLogToCsv( const char* fileIn, const char* fileOut )
{
	std::ifstream inFile( fileIn, std::ifstream::binary );
	std::ofstream outFile( fileOut, std::ifstream::out );
	
	// get the length
	uint32_t length;
	inFile.read( (char*)&length, sizeof(length) );
	// get the format
	std::string format("");
	for (int i=0; i<length; i++)
	{
		char c;
		inFile.read( &c, sizeof(c) );
		format.append( &c, 1 );
	}

	// Load in and print out
	int linePos = 0;
	while( !inFile.eof() )
	{
		switch ( format.at(linePos) )
		{
			case 'c':
			{
				uint8_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'C':
			{
				int8_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'h':
			{
				uint16_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'H':
			{
				int16_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'i':
			{
				uint32_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'I':
			{
				int32_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'l':
			{
				uint64_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'L':
			{
				int64_t i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'f':
			{
				float i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
			case 'd':
			{
				double i;
				if ( !inFile.read( (char*)&i, sizeof(i) ).eof() )
					outFile << i;
			}
			break;
		}

		if ( !inFile.eof() && (linePos+1<format.length()) )
			outFile << ",\t";

		if ( ++linePos>=format.length() )
		{
			if ( !inFile.eof() )
				outFile << std::endl;

			linePos = 0;
		}
	}

}