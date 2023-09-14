
Room::Room() {
	create_Room();
}

void create_Room() {
	//Here we add all cordinates for the room and add all the objects like camera, mirror, balls etc
	
	//All cordiantes for the room

	// roof
	const glm::vec3 P0 = glm::vec3(0.0f, 6.0f, 5.0f);
	const glm::vec3 P1 = glm::vec3(-3.0f, 0.0f, 5.0f);
	const glm::vec3 P2 = glm::vec3(0.0f, -6.0f, 5.0f);
	const glm::vec3 P3 = glm::vec3(10.0f, -6.0f, 5.0f);
	const glm::vec3 P4 = glm::vec3(13.0f, 0.0f, 5.0f);
	const glm::vec3 P5 = glm::vec3(10.0f, 6.0f, 5.0f);

	//floor
	const glm::vec3 P0 = glm::vec3(0.0f, 6.0f, -5.0f);
	const glm::vec3 P1 = glm::vec3(-3.0f, 0.0f, -5.0f);
	const glm::vec3 P2 = glm::vec3(0.0f, -6.0f, -5.0f);
	const glm::vec3 P3 = glm::vec3(10.0f, -6.0f, -5.0f);
	const glm::vec3 P4 = glm::vec3(13.0f, 0.0f, -5.0f);
	const glm::vec3 P5 = glm::vec3(10.0f, 6.0f, -5.0f);


	//Eye
	const glm::vec3 eye = glm::vec3(-1.0f, 0.0f, 0.0f);
	//camera
	const glm::vec3 camera = glm::vec3(0.0f, 0.0f, 0.0f);
}