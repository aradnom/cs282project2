#include "simphys/quaternion.h"
#include <math.h>

// TODO - provide necessary implementation

// get the norm of this quaternion.
float simphys::Quaternion::norm() const
   {
    float val = sqrt(pow(w,2)+pow(x,2)+pow(y,2)+pow(z,2));

    return val > 0 ? val : 0;

   }
void simphys::Quaternion::normalize() {
  float norm = this->norm();

  w /= norm;
  x /= norm;
  y /= norm;
  z /= norm;  
}

simphys::Quaternion& simphys::Quaternion::operator=(const Quaternion& other) {
  
  if (this == &other) {
    return *this;
  }

  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;

  return *this;
}

// Add the elements of two quaternions
simphys::Quaternion simphys::Quaternion::operator + ( const Quaternion& other ) {

  return Quaternion( w + other.getW(), x + other.getX(), y + other.getY(), z + other.getZ() );

}

// Multiply two quaternions
simphys::Quaternion simphys::Quaternion::operator * ( const Quaternion& other ) {

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


