#ifndef MAT_H
#define MAT_H

#include <vector>
#include <iostream>

namespace simphys {

	class mat {

	protected:

		std::vector<std::vector<float > > matrix;
		void multiply();		

	public:

		// Constructors
		mat( int rows, int columns );

		// Functions
		void transpose();
		void print();
		int getSize();		

		// Operators		
		float & operator () ( const unsigned int row, const unsigned int col );	
	
	};	

	// Templated * operator for multiplying any size matrices

	template <class M>
	M operator * ( M & first, M & second ) {
		M result;

		auto sumRow = [&] (int r, int c) { 
			float tmp = 0;
			for ( int k = 0; k < (int)first.getSize(); k++ )
				tmp += first( k, r ) * second( k, c );	
			return tmp;
		};		

		for ( int i = 0; i < (int)first.getSize(); i++ )
			for ( int j = 0; j < (int)second.getSize(); j++ )
				result( i, j ) = sumRow( i, j );
		
		return result;
	}
}

#endif
