#include "dependencies.hpp"
/* This file contains all the setup of the room itself, as well as the objects contained in the room. */
Room::Room() {
	create_Room();
}

void Room::create_Room() {
	
	std::cout << "----Creating camera----" << std::endl;
	Camera camera(glm::vec3(-1.0, 0.0, 0.0));

	std::cout << "----Creating scene----" << std::endl;
	Scene scene;

	//Materials
	std::cout << "----Creating materials----" << std::endl;
	Diffuse wallMaterial1{lightgray, 0.2}; // Back left
	Diffuse wallMaterial2{lightgray, 0.2}; // Back right
	Diffuse wallMaterial3{green, 0.5}; // Center left
	Diffuse wallMaterial4{red, 0.5}; // Center right
	Diffuse wallMaterial5{lightgray, 0.2}; // Front left
	Diffuse wallMaterial6{lightgray, 0.2}; // Front right

	Diffuse ceilingMaterial{lightgray, 0.5};
	Diffuse floorMaterial{lightgray, 0.5};

	Mirror mirror{};
	Diffuse boxMaterial{yellow, 0.2};
	Diffuse boxMaterial2{yellow, 0.6}; //Easier to spot color-bleeding in tests
	Diffuse border{black, 0.2};
	Diffuse sphereMaterial{ yellow, 0.2 };
	Transparent transparentMaterial{ white, REFLECTIVE_INDEX_GLASS };
	Transparent transparentMaterial2{ white, REFLECTIVE_INDEX_GLASS };

	LightSource light{white, 90};

	//Here we add all cordinates for the room and add all the objects like camera, mirror, balls etc

	//----All cordiantes for the room (TODO -> floor and ceiling mixed up for some reason?)----//
	// floor
	const glm::vec3 P0{0.0f, 6.0f, 5.0f};
	const glm::vec3 P1{-3.0f, 0.0f, 5.0f}; 
	const glm::vec3 P2{0.0f, -6.0f, 5.0f}; 
	const glm::vec3 P3{10.0f, -6.0f, 5.0f}; 
	const glm::vec3 P4{13.0f, 0.0f, 5.0f};
	const glm::vec3 P5{10.0f, 6.0f, 5.0f};
	const glm::vec3 PC{5.0f, 0.0f, 5.0f}; //center vertex
	//ceiling 
	const glm::vec3 P6{0.0f, 6.0f, -5.0f};
	const glm::vec3 P7{-3.0f, 0.0f, -5.0f};
	const glm::vec3 P8{0.0f, -6.0f, -5.0f};
	const glm::vec3 P9{10.0f, -6.0f, -5.0f};
	const glm::vec3 P10{13.0f, 0.0f, -5.0f};
	const glm::vec3 P11{10.0f, 6.0f, -5.0f};
	const glm::vec3 PF{5.0f, 0.0f, -5.0f}; //center vertex

	//light
	
	const glm::vec3 P12{ 6.0f, 1.0f, -4.8f };
    const glm::vec3 P13{ 5.0f, -1.0f, -4.8f };
    const glm::vec3 P14{ 5.0f, 1.0f, -4.8f };
    const glm::vec3 P15{ 6.0f, -1.0f, -4.8f };
	/*
	const glm::vec3 P12{ 6.0f, 5.0f, -4.98f }; //light attenuation test(move light to right side)
    const glm::vec3 P13{ 5.0f, 3.0f, -4.98f };
    const glm::vec3 P14{ 5.0f, 5.0f, -4.98f };
    const glm::vec3 P15{ 6.0f, 3.0f, -4.98f };
	*/
	//light border
	const glm::vec3 P17{ 5.0f, 1.0f, 4.8f };
    const glm::vec3 P18{ 5.0f, 1.0f, 4.8f };
    const glm::vec3 P19{ 5.0f, -1.0f, 4.8f };
    const glm::vec3 P20{ 5.0f, -1.0f, 4.8f };
    const glm::vec3 P21{ 6.0f, 1.0f, 4.8f };
    const glm::vec3 P22{ 6.0f, 1.0f, 4.8f };
    const glm::vec3 P23{ 6.0f, -1.0f, 4.8f };
    const glm::vec3 P24{ 6.0f, -1.0f, 4.8f };
	
	std::cout << "----Setting up the room----" << std::endl;	
	//----Floor (with normals pointing up)----//
	Triangle floor1{P0, PC, P1, &floorMaterial};
	Triangle floor2{P1, PC, P2, &floorMaterial};
	Triangle floor3{P2, PC, P3, &floorMaterial};
	Triangle floor4{P3, PC, P4, &floorMaterial};
	Triangle floor5{P4, PC, P5, &floorMaterial};
	Triangle floor6{P5, PC, P0, &floorMaterial};

	//----Ceiling (with normals pointing down)----//
	Triangle ceiling1{P6, P7, PF, &ceilingMaterial};
	Triangle ceiling2{P7, P8, PF, &ceilingMaterial};
	Triangle ceiling3{P8, P9, PF, &ceilingMaterial};
	Triangle ceiling4{P9, P10, PF, &ceilingMaterial};
	Triangle ceiling5{P10, P11, PF, &ceilingMaterial};
	Triangle ceiling6{P11, P6, PF, &ceilingMaterial};

	//----Walls----//

	Triangle wall11{P3, P4, P9, &mirror}; //Back left wall (furthest from camera)
	Triangle wall12{P4, P10, P9, &mirror};

	Triangle wall21{P4, P5, P10, &wallMaterial2}; // Back right wall (furthest from camera)
	Triangle wall22{P5, P11, P10, &wallMaterial2};
	
	Triangle wall31{P2, P3, P8,  &wallMaterial3}; //Center Left wall
	Triangle wall32{P3, P9, P8, &wallMaterial3};

	Triangle wall41{P5, P0, P11, &wallMaterial4}; //Center right wall
	Triangle wall42{P0, P6, P11, &wallMaterial4};

	Triangle wall51{P1, P2, P7, &wallMaterial5}; //Front left wall (closest to camera)
	Triangle wall52{P2, P8, P7, &wallMaterial5}; 

	Triangle wall61{P0, P1, P6, &wallMaterial6}; //Front right wall (closest to camera)
	Triangle wall62{P1, P7, P6, &wallMaterial6};

	//----Lights----//
	Triangle light1{ P13, P12, P14, &light };
    Triangle light2{ P15, P12, P13, &light };

	//----Light Border----//
	Triangle triangle21{ P17, P18, P19, &border };
    Triangle triangle22{ P17, P19, P20, &border };
    Triangle triangle23{ P17, P21, P18, &border };
    Triangle triangle24{ P18, P21, P22, &border };
    Triangle triangle25{ P21, P23, P22, &border };
    Triangle triangle26{ P21, P24, P23, &border };
    Triangle triangle27{ P19, P23, P24, &border };
    Triangle triangle28{ P19, P24, P20, &border };
	
	std::cout << "----Adding Polygons----" << std::endl;
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
	scene.addPolygon(&ceiling5);
	scene.addPolygon(&ceiling6);
	scene.addPolygon(&floor1);
	scene.addPolygon(&floor2);
	scene.addPolygon(&floor3);
	scene.addPolygon(&floor4);
	scene.addPolygon(&floor5);
	scene.addPolygon(&floor6);

	scene.addLightSource(&light1);
    scene.addLightSource(&light2);

   /*  scene.addPolygon(&triangle21);
    scene.addPolygon(&triangle22);
    scene.addPolygon(&triangle23);
    scene.addPolygon(&triangle24);
    scene.addPolygon(&triangle25);
    scene.addPolygon(&triangle26);
    scene.addPolygon(&triangle27);
    scene.addPolygon(&triangle28); */

	// add box
	Box b1 = Box(glm::vec3(6.0f, -1.0f, 2.0f), 2.5f, 2.5f, 2.5f, &transparentMaterial2);
	scene.addBox(&b1);

	//Box b2 = Box(glm::vec3(7.2f, 2.5f, 2.5f), 5.0f, 1.5f, 1.5f, &boxMaterial2);
	//scene.addBox(&b2);
	
	// add sphere
	Sphere s1{ glm::vec3(5.0f, 3.0f, 1.9f), 1.5f, &transparentMaterial };
	scene.addPolygon(&s1);

	//Sphere s2{ glm::vec3(6.0f, -3.0f, 1.9f), 1.0f, &sphereMaterial };
	//scene.addPolygon(&s2);

	Sphere s3{ glm::vec3(-3.0f, 0.0f, 1.9f), 1.0f, &sphereMaterial };
	scene.addPolygon(&s3);

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
