#include "simphys/input_manager.h"
#include "simphys/sim_engine.h"

#include "simphys/rigid_body.h"
#include "simphys/quaternion.h"
#include <GL/glxew.h>
#include <iostream>
#include <utility>

namespace simphys {

  void InputManager::init() {
  }

  void InputManager::setParentEngine(std::shared_ptr<SimEngine> p) {
    parent = p;
  }

  void InputManager::linkRigidBody(std::shared_ptr<RigidBody> in)
     {
      link = in;
     }
 
  void InputManager::poll() {
    XEvent newEvent;

    /*
      If there aren't any X events pending, return.
    */
    if (XPending(dpy) == 0) {
      return;
    }

    XNextEvent(dpy, &newEvent);
    
    switch(newEvent.type) {
    case KeyPress:
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_q) {
	std::cout << "Q pressed. Quitting." << std::endl;
	exit(0);
      }

      if (XLookupKeysym(&newEvent.xkey, 0) == XK_p) {
	std::cout << "P pressed." << std::endl;
	auto clock = parent->clock();
	if (clock->getPaused()) {
	  std::cout << "Setting paused to false." << std::endl;
	  clock->setPaused(false);	  
	} else {
	  std::cout << "Setting paused to true." << std::endl;
	  clock->setPaused(true);
	}
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Return) {
	std::cout << "You hit enter!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_space) {
	std::cout << "You hit space!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Up) {
	cameraZ+=0.1f;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Down) {
	cameraZ-=0.1f;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Left) {
	cameraAngle+=2;
	if(cameraAngle>360)
	   cameraAngle=0;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_Right) {
	cameraAngle-=2;
	if(cameraAngle<0)
	   cameraAngle=360;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_w) {
        if(link->orientation.getX()<360)
	link->orientation.setX(link->orientation.getX()+10.0f);
        else
	link->orientation.setX(10.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_e) {
        if(link->orientation.getX()>-350.0f)
	link->orientation.setX(link->orientation.getX()-10.0f);
        else
	link->orientation.setX(360.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_s) {
        if(link->orientation.getY()<360)
	link->orientation.setY(link->orientation.getY()+10.0f);
        else
	link->orientation.setY(10.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_d) {
        if(link->orientation.getY()>-350.0f)
	link->orientation.setY(link->orientation.getY()-10.0f);
        else
	link->orientation.setY(360.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_r) {
        if(link->orientation.getZ()<360)
	link->orientation.setZ(link->orientation.getZ()+10.0f);
        else
	link->orientation.setZ(10.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_t) {
        if(link->orientation.getZ()>-350.0f)
	link->orientation.setZ(link->orientation.getZ()-10.0f);
        else
	link->orientation.setZ(360.0f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_f) {
        if(link->orientation.getW()<360)
	link->orientation.setW(link->orientation.getW()+0.2f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_g) {
        if(link->orientation.getW()>-360)
	link->orientation.setW(link->orientation.getW()-0.2f);
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_1) {
	std::cout << "You hit 1!" << std::endl;
      }
      
      if (XLookupKeysym(&newEvent.xkey, 0) == XK_BackSpace) {
	std::cout << "You hit backspace!" << std::endl;
      }
std::cout<<link->orientation.getX()<<"  "<<link->orientation.getY()<<"  "<<link->orientation.getZ()<<std::endl;
      
      break;
      
    case MotionNotify:
      mousePos = std::make_pair((newEvent.xmotion).x, (newEvent.xmotion).y);
      break; 
    } 
  }
}
