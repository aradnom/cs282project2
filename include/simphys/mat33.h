#ifndef MAT33_H
#define MAT33_H

#include <iostream>
#include <vector>
#include "vec3.h"
#include "mat.h"

namespace simphys {

	class mat33 : public mat {
	public:
		// Constructor(s)
		mat33() : mat( 3, 3 ) {};	
	};	

	// Overloaded * for vector multiplication, only function unique to the child classes

	inline vec3 operator * ( mat33 & matrix, const vec3 & vector ) {
		std::vector<float> tmp, result( 3, 0.0f );
		tmp.push_back( vector.getX() );
		tmp.push_back( vector.getY() );
		tmp.push_back( vector.getZ() );

		for ( int i = 0; i < matrix.getSize(); i++ )
			for ( int j = 0; j < matrix.getSize(); j++ )
				result[i] += matrix( i, j ) * tmp[j];		

		return vec3( result[0], result[1], result[2] );
	}
}

#endif
