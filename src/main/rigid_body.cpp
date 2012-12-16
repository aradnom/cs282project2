#include "simphys/rigid_body.h"
#include "simphys/vec3.h"
#include "simphys/mat33.h"
#include <iostream>
#include <memory>
#include <chrono>

typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

// TODO - implement rigid body code here.

using namespace std;

namespace simphys {
  using std::shared_ptr;

  void RigidBody::setPosition(const vec3& newPos) {
    pos.setX(newPos.getX());
    pos.setY(newPos.getY());
    pos.setZ(newPos.getZ());
  }

  void RigidBody::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void RigidBody::setAngVelocity(const vec3& newVel) {
    angvel = newVel;
  }

  void RigidBody::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void RigidBody::setAngAcceleration(const vec3& newAcc) {
    angacc = newAcc;
  }

  void RigidBody::setDamping(float d) {
    damping = d;
  }

  void RigidBody::setMass(float m) {
    // TODO - decide if this is reasonable. Error handling?
    invMass = 1.0f / mass; //1 = mass
  }

  vec3 RigidBody::getPosition() const {
    vec3 tempVec;
    tempVec.setX(pos.getX());
    tempVec.setY(pos.getY());
    tempVec.setZ(pos.getZ());
    return tempVec;
  }

  Quaternion* RigidBody::getOrientation() {
    return &orientation;
  }

  vec3 RigidBody::getVelocity() const {
    return vel;
  }

  vec3 RigidBody::getAngVelocity() const {
    return angvel;
  }
  
  vec3 RigidBody::getAcceleration() const {
    return acc;
  }

  vec3 RigidBody::getAngAcceleration() const {
    return angacc;
  }

  float RigidBody::getDamping() const {
    return damping;
  }
  
  float RigidBody::getMass() const {
    return 1.0f / invMass;
  }
  

  void RigidBody::integrate(fseconds duration) {

    // update position using Euler integration

    //pos = pos + duration.count() * vel;

    //Position based on Velocity Verlet
    vec3 resultantAcc = acc;
    resultantAcc = resultantAcc + (1 * accumulatedForces);//1 is invmass

    //update x, y, z as translation
    pos.setX(pos.getX()+vel.getX()*duration.count() + 0.5f*(resultantAcc.getX()*(duration.count()*duration.count())));
    pos.setY(pos.getY()+vel.getY()*duration.count() + 0.5f*(resultantAcc.getY()*(duration.count()*duration.count())));
    pos.setZ(pos.getZ()+vel.getZ()*duration.count() + 0.5f*(resultantAcc.getZ()*(duration.count()*duration.count())));
    //pos = pos + vel*duration.count() + 0.5f*(resultantAcc*(duration.count()*duration.count()));

    //need to convert vel and acc to quaternions to update orientation


    //new velocity half update
    //vel = verletHalfVelocity(vel, resultantAcc, duration.count());

    //acceleration lambda use
    //resultantAcc = verletAcceleration( existingTime, pos );

    // update velocity using Velocity Verlet
    vel = vel + (resultantAcc+resultantAcc)*(duration.count())*0.5;
    //new velocity half update
    //vel = verletHalfVelocity(vel, resultantAcc, duration.count());

    // update velocity using Euler integration
    //vel = vel + duration.count() * resultantAcc;

    // incorporate damping
    vel = vel * damping;

    clearForces();

  }
  

  void RigidBody::integrateO(fseconds duration) {

    //Position based on Velocity Verlet
    vec3 resultantAcc = angacc;

    // Convert the angular velocity to a quaternion for MATHS
    Quaternion vq( angvel ); 

    // Do said maths
    orientation = orientation + ( (0.5f * duration.count()) * vq * orientation );

    //update x, y, z as translation
    //orientation.setX( orientation.getX() + ( ( 0.5f * duration.count() ) * orientation.getX() * angvel.getX() ) );
    //orientation.setY( orientation.getY() + ( ( 0.5f * duration.count() ) * orientation.getY() * angvel.getY() ) );
    //orientation.setZ( orientation.getZ() + ( ( 0.5f * duration.count() ) * orientation.getZ() * angvel.getZ() ) );
    //orientation.setX(orientation.getX()+angvel.getX()*duration.count() + 0.5f*(resultantAcc.getX()*(duration.count()*duration.count())));
    //orientation.setY(orientation.getY()+angvel.getY()*duration.count() + 0.5f*(resultantAcc.getY()*(duration.count()*duration.count())));
    //orientation.setZ(orientation.getZ()+angvel.getZ()*duration.count() + 0.5f*(resultantAcc.getZ()*(duration.count()*duration.count())));
    //pos = pos + vel*duration.count() + 0.5f*(resultantAcc*(duration.count()*duration.count()));

    // update velocity using Velocity Verlet
    angvel = angvel + (resultantAcc+resultantAcc)*(duration.count())*0.5;

    // incorporate damping
    angvel = angvel * damping;

    clearForces();

  }

  void RigidBody::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }

  void RigidBody::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

  void RigidBody::applyTorque(const vec3 &point, const vec3& torque) {
    mat33 rotationMatrix = orientation.getMatrix(); // Get rotation matrix from orientation
    mat33 rotationTranspose = orientation.getMatrix();
    rotationTranspose.transpose();

    // The tensor in world coordinates
    mat33 worldTensor = rotationMatrix * inverseTensor;
    worldTensor = worldTensor * rotationTranspose;

    worldTensor.print();

    /*angacc.setX(angacc.getX()+torque.getX()/inertiaTensor[0]);
    angacc.setY(angacc.getY()+torque.getY()/inertiaTensor[4]);
    angacc.setZ(angacc.getZ()+torque.getZ()/inertiaTensor[8]);*/
  }

}
