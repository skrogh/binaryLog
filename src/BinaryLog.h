#pragma once

#include <fstream>
#include <cstdint>
#include <string>

// f: float
// d: double,
// c: unsigned 8 bit int
// C: signed 8 bit int
// h: unsigned 16 bit int
// H: signed 16 bit int
// i: unsigned 32 bit int
// I: signed 32 bit int
// l: unsigned 64 bit int
// L: signed 64 bit int

class BinaryLogOut
{
public:
	BinaryLogOut( const char* format_, const char* file_ );
	void log(  uint8_t* data, int length );
	void log(   int8_t* data, int length );
	void log( uint16_t* data, int length );
	void log(  int16_t* data, int length );
	void log( uint32_t* data, int length );
	void log(  int32_t* data, int length );
	void log( uint64_t* data, int length );
	void log(  int64_t* data, int length );
	void log(    float* data, int length );
	void log(   double* data, int length );
	void flush( void );
	//~BinaryLog();
private:
	std::string format;
	std::ofstream file;
	int linePos;
};

void BinaryLogToCsv( const char* fileIn, const char* fileOut );
