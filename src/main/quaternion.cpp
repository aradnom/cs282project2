#include "simphys/mat33.h"
#include "simphys/quaternion.h"
#include <math.h>

using namespace std;

namespace simphys {

  Quaternion::Quaternion () : w( 0 ), x( 0 ), y( 0 ), z( 0 ) {}

	Quaternion::Quaternion ( const vec3 other ) : w( 0 ), x( other.getX() ), y( other.getY() ), z( other.getZ() ), normalized( false ) {}

	Quaternion::Quaternion ( const float w, const float x, const float y, const float z ) : w( w ), x( x ), y( y ), z( z ), normalized( false ) {}

	// Getters and setters

	// Get real component of quaternion
    float Quaternion::getW() const {
    	return w;
    }

    // Get imaginary components
    float Quaternion::getX() const {
    	return x;
    }

    float Quaternion::getY() const {
    	return y;
    }

    float Quaternion::getZ() const {
    	return z;
    }

    bool Quaternion::getNormalized () const {
    	return normalized;
    }

    // Set real component
    void Quaternion::setW( float w ) {
    	this->w = w;
    }

    // Set imaginary components
    void Quaternion::setX( float x ) {
    	this->x = x;
    }

    void Quaternion::setY( float y ) {
    	this->y = y;
    }

    void Quaternion::setZ( float z ) {
    	this->z = z;
    }

	// Return norm of the quaternion
	float Quaternion::norm () const {

		return sqrt( w * w + x * x + y * y + z * z );

	}

	// Convert quaternion to a unit quaternion
	void Quaternion::normalize () {

		float norm = this->norm();

		w /= norm;
		x /= norm;
		y /= norm;
		z /= norm; 

		normalized = true;

	}

	// Return rotation matrix representing quaternion
	mat33 Quaternion::getMatrix () const {
		float _w, _x, _y, _z;

		// Get a normalized copy of this quaternion before converting.
		// Will check if this quaternion is normalized before proceeding.
		if ( !this->normalized ) {
			Quaternion n( w, x, y, z );
			n.normalize();

			_w = n.getW();
			_x = n.getX();
			_y = n.getY();
			_z = n.getZ();
		} else {
			_w = w;
			_x = x;
			_y = y;
			_z = z;
		}		

		mat33 matrix;

		matrix( 0, 0 ) = ( _w * _w ) + ( _x * _x ) - ( _y * _y ) - ( _z * _z );
		matrix( 0, 1 ) = ( 2 * _x * _y ) - ( 2 * _w * _z );
		matrix( 0, 2 ) = ( 2 * _x * _z ) + ( 2 * _w * _y );

		matrix( 1, 0 ) = ( 2 * _x * _y ) + ( 2 * _w * _z );
		matrix( 1, 1 ) = ( _w * _w ) - ( _x * _x ) + ( _y * _y ) - ( _z * _z );
		matrix( 1, 2 ) = ( 2 * _y * _z ) - ( 2 * _w * _x );

		matrix( 2, 0 ) = ( 2 * _x * _z ) - ( 2 * _w * _y );
		matrix( 2, 1 ) = ( 2 * _y * _z ) + ( 2 * _w * _x );
		matrix( 2, 2 ) = ( _w * _w ) - ( _x * _x ) - ( _y * _y ) + ( _z * _z );

		return matrix;

	}

	// Add the elements of two quaternions
	Quaternion Quaternion::operator + ( const Quaternion& other ) {

		return Quaternion( w + other.getW(), x + other.getX(), y + other.getY(), z + other.getZ() );

	}

	// Multiply two quaternions
	Quaternion Quaternion::operator * ( const Quaternion& other ) {

		// Grab the other properties so we're not hitting these a million times
		float w2 = other.getW();
		float x2 = other.getX();
		float y2 = other.getY();
		float z2 = other.getZ();

		return Quaternion( 
			( w * w2 ) - ( x * x2 ) - ( y * y2 ) - ( z * z2 ),
			( w * x2 ) + ( x * w2 ) + ( y * z2 ) - ( z * y2 ),
			( w * y2 ) - ( x * z2 ) + ( y * w2 ) + ( z * x2 ),
			( w * z2 ) + ( x * y2 ) - ( y * x2 ) + ( z * w2 )
		);

	}

	Quaternion operator * ( const float s, const Quaternion& q ) {
		return Quaternion(
			q.getW() * s,
			q.getX() * s,
			q.getY() * s,
			q.getZ() * s
		);
	}
}