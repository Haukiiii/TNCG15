#include "dependencies.hpp"

Room::Room() {
	create_Room();
}

void Room::create_Room() {
	
	//create the camera with eye in position (-1, 0, 0)
	Camera camera(glm::vec3(-1.0, 0.0, 0.0));
	//create the scene
	Scene scene;
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

	//Materials
	Diffuse wallMaterial{red, 0.2};
	Diffuse floorMaterial{green, 0.2};
	Diffuse ceilingMaterial{blue, 0.2};
	Mirror mirror{};
	

	Triangle wall11{P0, P1, P6, &wallMaterial};
	Triangle wall12{P1, P7, P6, &wallMaterial};

	Triangle wall21{P1, P2, P7, &wallMaterial};
	Triangle wall22{P2, P8, P7, &wallMaterial};

	Triangle wall31{P2, P3, P8,  &wallMaterial};
	Triangle wall32{P3, P9, P8, &wallMaterial};

	Triangle wall41{P3, P4, P9, &mirror};
	Triangle wall42{P4, P10, P9, &mirror};

	Triangle wall51{P4, P5, P10, &wallMaterial};
	Triangle wall52{P5, P11, P10, &wallMaterial};

	Triangle wall61{P5, P0, P11, &wallMaterial};
	Triangle wall62{P0, P6, P11, &wallMaterial};

	// Create triangles for the ceiling and floor
	Triangle ceiling1{P0, P5, P1, &ceilingMaterial};
	Triangle ceiling2{P5, P4, P1, &ceilingMaterial};
	Triangle ceiling3{P1, P4, P3, &ceilingMaterial};
	Triangle ceiling4{P3, P2, P1, &ceilingMaterial};

	Triangle floor1{P6, P7, P11, &floorMaterial};
	Triangle floor2{P7, P8, P11, &floorMaterial};
	Triangle floor3{P8, P9, P11, &floorMaterial};
	Triangle floor4{P9, P10, P11, &floorMaterial};

	scene.addPolygon(&wall11);
	scene.addPolygon(&wall12);
	scene.addPolygon(&wall21);
	scene.addPolygon(&wall22);
	scene.addPolygon(&wall31);
	scene.addPolygon(&wall32);
	scene.addPolygon(&wall41);
	scene.addPolygon(&wall42);
	scene.addPolygon(&wall51);
	scene.addPolygon(&wall52);
	scene.addPolygon(&wall61);
	scene.addPolygon(&wall62);
	scene.addPolygon(&ceiling1);
	scene.addPolygon(&ceiling2);
	scene.addPolygon(&ceiling3);
	scene.addPolygon(&ceiling4);
	scene.addPolygon(&floor1);
	scene.addPolygon(&floor2);
	scene.addPolygon(&floor3);
	scene.addPolygon(&floor4);

	std::cout << "Rendering scene\n";
	auto start_time{ std::chrono::high_resolution_clock::now() };
	camera.render(scene, 0, res, 0, res);

	auto end_time{ std::chrono::high_resolution_clock::now() };
	std::cout << "----------------------------\n";
	auto seconds{ std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() };
	auto minutes = std::floor(seconds / 60);
	seconds = seconds % 60;
	std::cout << "Rendered in " << minutes << " minutes and " << seconds << " seconds.\n";
	std::cout << "----------------------------\n";
}