#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec3.h"

namespace simphys {
  
  class Quaternion {
  private:
    float w;
    float x;
    float y;
    float z;

  public:
    Quaternion() 
      : w{0.0f}
    , x{0.0f}
    , y{0.0f}
    , z{0.0f} { }

    Quaternion ( const vec3 other ) : w( 0 ), x( other.getX() ), y( other.getY() ), z( other.getZ() ) {}

    Quaternion(float w_, float x_, float y_, float z_)
      : w{w_}
    , x{x_}
    , y{y_}
    , z{z_} { }

    // TODO - OTHER MEMBER FUNCTIONS AS APPROPRIATE
    void setX(float n) { x = n; }
    void setY(float n) { y = n; }
    void setZ(float n) { z = n; }
    void setW(float n) { w = n; };
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getW() const { return w; }

    // get the norm of this quaternion.
    float norm() const;
    
    // destructively update this quaternion so that its norm is 1.
    void normalize();

    /*
      Copy assignment operator.
    */
    Quaternion& operator=(const Quaternion& other);

    Quaternion operator + ( const Quaternion& other );

    Quaternion operator * ( const Quaternion& other );
  };

  inline simphys::Quaternion operator * ( const float s, const simphys::Quaternion& q ) {
    return simphys::Quaternion(
      q.getW() * s,
      q.getX() * s,
      q.getY() * s,
      q.getZ() * s
    );
  }

} // namespace simphys


#endif // QUATERNION_H
