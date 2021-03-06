#ifndef RIGID_BODY_H
#define RIGID_BODY_H

// TODO - provide appropriate headers
#include "simphys/quaternion.h"
#include "simphys/vec3.h"
#include "simphys/mat33.h"

#include <chrono>

typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

namespace simphys {

  // TODO - provide necessary forward declarations

  class RigidBody {
    // TODO - declare member variables and functions
    private:
       // size values
       float radius;
       float mass;
       float invMass;

       // current position
       vec3 pos;

       // current velocity
       vec3 vel;

       // current acceleration
       vec3 acc;

       // current angular velocity
       vec3 angvel;

       // current angular acceleration
       vec3 angacc;

       //array for holding intertia tensor
       float inertiaTensor[9];//stored within is actually the inverse of the intertia tensor

       mat33 inverseTensor;

       // accumulated force for the current time step
       vec3 accumulatedForces;

       vec3 accumulatedTorques;

       // Damping parameter 
       float damping;
    public:
       // current orientation
       Quaternion orientation;


       RigidBody() {
         radius=1;
         pos.setX(0.0f);
         pos.setY(0.0f);
         pos.setZ(0.0f);
         accumulatedForces.setX(0.0f);
         accumulatedForces.setY(0.0f);
         accumulatedForces.setZ(0.0f);
         accumulatedTorques.setX(0.0f);
         accumulatedTorques.setY(0.0f);
         accumulatedTorques.setZ(0.0f);
         vel.setX(0.0f);
         vel.setY(0.0f);
         vel.setZ(0.0f);
         acc.setX(0.0f);
         acc.setY(0.0f);
         acc.setZ(0.0f);
         angvel.setX(0.0f);
         angvel.setY(0.0f);
         angvel.setZ(0.0f);
         angacc.setX(0.0f);
         angacc.setY(0.0f);
         angacc.setZ(0.0f);
         orientation.setX(0.0f);
         orientation.setY(0.0f);
         orientation.setZ(0.0f);
         orientation.setW(1.0f); // This is "neutral"         
         damping=0.999f;
         mass=1.0f;
         invMass=1.0f;
         inverseTensor( 0, 0 ) = 2.5f; // Inverse values
         inverseTensor( 1, 1 ) = 2.5f;
         inverseTensor( 2, 2 ) = 2.5f;

       }
    
    // setters
    void setPosition(const vec3& newPos);
    void setVelocity(const vec3& newVel);
    void setAngVelocity( const vec3& newVel );
    void setAcceleration(const vec3& newAcc);
    void setAngAcceleration( const vec3& newAcc );
    void setDamping(float d);
    void setMass(float m);

    // getters
    vec3 getPosition() const;
    Quaternion* getOrientation();
    vec3 getVelocity() const;
    vec3 getAngVelocity() const;
    vec3 getAcceleration() const;
    vec3 getAngAcceleration() const;
    float getDamping() const;
    float getMass() const;    

       // Update the position and velocity of this rigid body.
       void integrate(fseconds duration);

       // Update the position and velocity of this rigid body.
       void integrateO(fseconds duration);
    
       // clear the force accumulation vector
       void clearForces();

    // Apply a force to this rigid body
    void applyForce(const vec3& force);

    // Apply a torque to this rigid body at the given point
    void applyTorque( const vec3 &point, const vec3& force );
  };

  // TODO - provide necessary non-member functions.

}


#endif // RIGID_BODY_H
