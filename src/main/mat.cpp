#include <iostream>
#include <vector>
#include "simphys/mat.h"

using namespace std;

namespace simphys {	

	mat::mat ( int rows, int columns ) {
		vector<float> newRow;

		for ( int j = 0; j < columns; j++ )
			newRow.push_back( 0.0f );

		for ( int i = 0; i < rows; i++ )
			matrix.push_back( newRow );				
	}
	
	void mat::transpose () {
		int i = 0;

		auto swap = [&] ( int r, int c ) { float tmp = matrix[r][c]; matrix[r][c] = matrix[c][r]; matrix[c][r] = tmp; };
		
		for ( ; i < ( (int)matrix.size() - 1); i++ )	
			for ( int j = ( i + 1 ); j < (int)matrix.size(); j++ )	
				swap( i, j );	
	}

	void mat::print () {
		for ( auto & col : matrix ) {
		  	for ( auto & row : col )
				cout << row << " ";
			cout << "\n";	  
		}
	}

	int mat::getSize () {
		return (int)matrix.size();
	}

	// Overloaded operators for this matrix

	float & mat::operator () ( const unsigned int row, const unsigned int col ) {
		if ( row <= matrix.size() && col <= matrix.size() )
			return matrix[row][col];
	}
}

