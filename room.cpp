#pragma once
#include "dependencies.hpp"

Room::Room() {
	create_Room();
}

void create_Room() {
	
	//create the camera with eye in position (-1, 0, 0)
	Camera camera(glm::vec3(-1.0, 0.0, 0.0));
	//create the scene

	//Here we add all cordinates for the room and add all the objects like camera, mirror, balls etc
	
	//All cordiantes for the room

	// roof
	const glm::vec3 P0{0.0f, 6.0f, 5.0f};
	const glm::vec3 P1{-3.0f, 0.0f, 5.0f};
	const glm::vec3 P2{0.0f, -6.0f, 5.0f};
	const glm::vec3 P3{10.0f, -6.0f, 5.0f};
	const glm::vec3 P4{13.0f, 0.0f, 5.0f};
	const glm::vec3 P5{10.0f, 6.0f, 5.0f};

	//floor
	const glm::vec3 P6{0.0f, 6.0f, -5.0f};
	const glm::vec3 P7{-3.0f, 0.0f, -5.0f};
	const glm::vec3 P8{0.0f, -6.0f, -5.0f};
	const glm::vec3 P9{10.0f, -6.0f, -5.0f};
	const glm::vec3 P10{13.0f, 0.0f, -5.0f};
	const glm::vec3 P11{10.0f, 6.0f, -5.0f};


}