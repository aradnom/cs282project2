/*
  Main program.
*/

#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject3D.h"
#include "simphys/rigid_body.h"
#include "simphys/vec3.h"

int main(int argc, char **argv) {

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  sim.setClock(clock_ptr);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>(); 
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::RigidBody p;
  simphys::Mesh s;
  simphys::SimObject3D testObject(p,s);
  auto obj_ptr = std::make_shared<simphys::SimObject3D>(testObject);
  auto objState = testObject.getState();
  objState->setPosition(simphys::vec3{0, 5, 0});
  objState->setVelocity(simphys::vec3{0.0, 0.0, 0});
  objState->setAcceleration(simphys::vec3{0, -0.1, 0});
  objState->applyTorque(simphys::vec3{0, -0.1, 0},simphys::vec3{0, -1.0, 0});

  // add object to the world.
  world_ptr->add(obj_ptr);

  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
