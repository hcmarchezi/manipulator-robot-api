# manipulator-robot-api

This project contains a C++ API that lets you build a manipulator robot as a kinematic chain of links.
The API lets the developer to:
* Create link types with geometry description from 3DS files
* Describe manipulator robots as a chain of links where each link is connected to a link type
* Describe robot trajectories as a series of initial-to-end joint positions in time for each joint
* Given the trajectory above generate a polynomial trajectory to move the joints

A sample application (see picture below) was built to illustrate its usage and it can be found in application folder in the repository.
![Alt text](https://dl.dropboxusercontent.com/u/23592712/CDN/robotbuilder/robot-manipulator-app.png "Sample application")


