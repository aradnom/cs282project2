#include "simphys/quaternion.h"
#include <math.h>

// TODO - provide necessary implementation

// get the norm of this quaternion.
float simphys::Quaternion::norm() const
   {
    float val = sqrt(pow(w,2)+pow(x,2)+pow(y,2)+pow(z,2));
    if(val>0)
       {
        return val;
       }
    else
       {
        return 0;
       }
   }
void simphys::Quaternion::normalize()
   {
    if(norm()!=1)
       {
        float tempVal = norm();
        tempVal = floor(tempVal * pow(10., 3) + .5) / pow(10., 3);
        if(!(tempVal>=0.0f))
           {
            return;
           }
        setW(w/tempVal);
        setX(x/tempVal);
        setY(y/tempVal);
        setZ(z/tempVal);
        if(!(getW()>0.001f))
          setW(0.001f);
        if(!(getX()>0.001f))
          setX(0.001f);
        if(!(getY()>0.001f))
          setY(0.001f);
        if(!(getZ()>0.001f))
          setZ(0.001f);
       }
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
