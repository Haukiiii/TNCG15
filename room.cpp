#include "dependencies.hpp"

Room::Room() {
	create_Room();
}

void Room::create_Room() {
	
	std::cout << "----Creating camera----" << std::endl;
	Camera camera(glm::vec3(-1.0, 0.0, 0.0));

	std::cout << "----Creating scene----" << std::endl;
	Scene scene;
	//Here we add all cordinates for the room and add all the objects like camera, mirror, balls etc
	
	//All cordiantes for the room

	// floor
	const glm::vec3 P0{0.0f, 6.0f, 5.0f};
	const glm::vec3 P1{-3.0f, 0.0f, 5.0f};
	const glm::vec3 P2{0.0f, -6.0f, 5.0f};
	const glm::vec3 P3{10.0f, -6.0f, 5.0f};
	const glm::vec3 P4{13.0f, 0.0f, 5.0f};
	const glm::vec3 P5{10.0f, 6.0f, 5.0f};

	//ceiling 
	const glm::vec3 P6{0.0f, 6.0f, -5.0f};
	const glm::vec3 P7{-3.0f, 0.0f, -5.0f};
	const glm::vec3 P8{0.0f, -6.0f, -5.0f};
	const glm::vec3 P9{10.0f, -6.0f, -5.0f};
	const glm::vec3 P10{13.0f, 0.0f, -5.0f};
	const glm::vec3 P11{10.0f, 6.0f, -5.0f};

	//light
	const glm::vec3 P12{ 6.0f, 1.0f, 4.98f };
    const glm::vec3 P13{ 5.0f, -1.0f, 4.98f };
    const glm::vec3 P14{ 5.0f, 1.0f, 4.98f };
    const glm::vec3 P15{ 6.0f, -1.0f, 4.98f };

	//Materials
	std::cout << "----Creating materials----" << std::endl;
	Diffuse wallMaterial{red, 0.2};
	Diffuse ceilingMaterial{yellow, 0.2};
	Diffuse floorMaterial{blue, 0.2};
	Mirror mirror{};
	LightSource light{white, 50};
	
	std::cout << "----Setting up the room----" << std::endl;

	Triangle yeet{glm::vec3{6.0f, 1.0f, 3.0f}, glm::vec3{4.0f, -4.0f, 3.0f}, glm::vec3{4.0f, 1.0f, 3.0f}, &floorMaterial};

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
	Triangle floor1{P0, P5, P1, &floorMaterial};
	Triangle floor2{P5, P4, P1, &floorMaterial};
	Triangle floor3{P1, P4, P3, &floorMaterial};
	Triangle floor4{P3, P2, P1, &floorMaterial};

	Triangle ceiling1{P6, P7, P11, &ceilingMaterial};
	Triangle ceiling2{P7, P8, P11, &ceilingMaterial};
	Triangle ceiling3{P8, P9, P11, &ceilingMaterial};
	Triangle ceiling4{P9, P10, P11, &ceilingMaterial};
	/*
	Triangle ceiling1{P7, P6, P8, &ceilingMaterial};  // Reverse vertex order
	Triangle ceiling2{P6, P11, P8, &ceilingMaterial};  // Reverse vertex order
	Triangle ceiling3{P11, P9, P8, &ceilingMaterial};  // Reverse vertex order
	Triangle ceiling4{P11, P10, P9, &ceilingMaterial};  // Reverse vertex order 
	*/
	Triangle light1{ P13, P14, P12, &light };
    Triangle light2{ P15, P13, P12, &light };
	
	std::cout << "----Populating scene----" << std::endl;
	//scene.addPolygon(&yeet);
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

	scene.addLightSource(&light1);
    scene.addLightSource(&light2);



	Diffuse border{ white, 0.2 };

	//light border test if neccesary....*****
	const glm::vec3 P17{ 5.0f, 1.0f, 4.98f };
    const glm::vec3 P18{ 5.0f, 1.0f, 5.0f };
    const glm::vec3 P19{ 5.0f, -1.0f, 5.0f };
    const glm::vec3 P20{ 5.0f, -1.0f, 4.98f };
    const glm::vec3 P21{ 6.0f, 1.0f, 4.98f };
    const glm::vec3 P22{ 6.0f, 1.0f, 5.0f };
    const glm::vec3 P23{ 6.0f, -1.0f, 5.0f };
    const glm::vec3 P24{ 6.0f, -1.0f, 4.98f };

    Triangle triangle21{ P17, P18, P19, &border };
    Triangle triangle22{ P17, P19, P20, &border };
    Triangle triangle23{ P17, P21, P18, &border };
    Triangle triangle24{ P18, P21, P22, &border };
    Triangle triangle25{ P21, P23, P22, &border };
    Triangle triangle26{ P21, P24, P23, &border };
    Triangle triangle27{ P19, P23, P24, &border };
    Triangle triangle28{ P19, P24, P20, &border };

    scene.addPolygon(&triangle21);
    scene.addPolygon(&triangle22);
    scene.addPolygon(&triangle23);
    scene.addPolygon(&triangle24);
    scene.addPolygon(&triangle25);
    scene.addPolygon(&triangle26);
    scene.addPolygon(&triangle27);
    scene.addPolygon(&triangle28);

	std::cout << "----Rendering scene----" << std::endl;
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