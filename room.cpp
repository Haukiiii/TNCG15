#include "dependencies.hpp"

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
	Diffuse wallMaterial{red, 0.2};
	Diffuse ceilingMaterial{green, 0.2};
	Diffuse floorMaterial{blue, 0.2};
	Mirror mirror{};
	Diffuse boxMaterial{yellow, 0.2};
	LightSource light{white, 30};
	Diffuse sphereMaterial{ yellow, 0.2 };
	Diffuse transparentMaterial{ black, REFLECTIVE_INDEX_GLASS };

	//Here we add all cordinates for the room and add all the objects like camera, mirror, balls etc




	// Define the vertices of the BOOOX
	/* ------- New box function 
	const glm::vec3 B0(-0.125f, -0.125f, -0.125f); // Bottom-back-left corner
	const glm::vec3 B1(0.125f, -0.125f, -0.125f);  // Bottom-back-right corner
	const glm::vec3 B2(0.125f, 0.125f, -0.125f);   // Bottom-front-right corner
	const glm::vec3 B3(-0.125f, 0.125f, -0.125f);  // Bottom-front-left corner
	const glm::vec3 B4(-0.125f, -0.125f, 0.125f);  // Top-back-left corner
	const glm::vec3 B5(0.125f, -0.125f, 0.125f);   // Top-back-right corner
	const glm::vec3 B6(0.125f, 0.125f, 0.125f);    // Top-front-right corner
	const glm::vec3 B7(-0.125f, 0.125f, 0.125f);   // Top-front-left corner

	// Calculate the rotation matrix
	const float rotationAngle{60};
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	*/
	// Apply the rotation to each vertex

	/* ------- New box function 
	const glm::vec3 rotB0 = glm::vec3(rotationMatrix * glm::vec4(B0, 1.0f));
	const glm::vec3 rotB1 = glm::vec3(rotationMatrix * glm::vec4(B1, 1.0f));
	const glm::vec3 rotB2 = glm::vec3(rotationMatrix * glm::vec4(B2, 1.0f));
	const glm::vec3 rotB3 = glm::vec3(rotationMatrix * glm::vec4(B3, 1.0f));
	const glm::vec3 rotB4 = glm::vec3(rotationMatrix * glm::vec4(B4, 1.0f));
	const glm::vec3 rotB5 = glm::vec3(rotationMatrix * glm::vec4(B5, 1.0f));
	const glm::vec3 rotB6 = glm::vec3(rotationMatrix * glm::vec4(B6, 1.0f));
	const glm::vec3 rotB7 = glm::vec3(rotationMatrix * glm::vec4(B7, 1.0f));
	
	
	Triangle box0{rotB0, rotB1, rotB2, &boxMaterial}; // BOTTOM 
	Triangle box1{rotB0, rotB2, rotB3, &boxMaterial}; 
	Triangle box2{rotB4, rotB5, rotB6, &boxMaterial}; // TOP
	Triangle box3{rotB4, rotB6, rotB7, &boxMaterial}; 
	Triangle box4{rotB0, rotB4, rotB7, &boxMaterial}; // LEFT
	Triangle box5{rotB0, rotB7, rotB3, &boxMaterial}; 
	Triangle box6{rotB1, rotB5, rotB6, &boxMaterial}; // RIGHT
	Triangle box7{rotB1, rotB6, rotB2, &boxMaterial}; 
	Triangle box8{rotB0, rotB1, rotB5, &boxMaterial}; // BACK
	Triangle box9{rotB0, rotB5, rotB4, &boxMaterial}; 
	Triangle box10{rotB2, rotB6, rotB7, &boxMaterial}; // FRONT
	Triangle box11{rotB2, rotB7, rotB3, &boxMaterial};  
	*/

	/* Triangle box0{B0, B1, B2, &boxMaterial}; // BOTTOM 
	Triangle box1{B0, B2, B3, &boxMaterial}; 
	Triangle box2{B4, B5, B6, &boxMaterial}; // TOP
	Triangle box3{B4, B6, B7, &boxMaterial}; 
	Triangle box4{B0, B4, B7, &boxMaterial}; // LEFT
	Triangle box5{B0, B7, B3, &boxMaterial}; 
	Triangle box6{B1, B5, B6, &boxMaterial}; // RIGHT
	Triangle box7{B1, B6, B2, &boxMaterial}; 
	Triangle box8{B0, B1, B5, &boxMaterial}; // BACK
	Triangle box9{B0, B5, B4, &boxMaterial}; 
	Triangle box10{B2, B6, B7, &boxMaterial}; // FRONT
	Triangle box11{B2, B7, B3, &boxMaterial};  
 
	scene.addPolygon(&box1);
	scene.addPolygon(&box2);
	scene.addPolygon(&box3);
	scene.addPolygon(&box4);
	scene.addPolygon(&box5);
	scene.addPolygon(&box6);
	scene.addPolygon(&box7);
	scene.addPolygon(&box8);
	scene.addPolygon(&box9);
	scene.addPolygon(&box10);
	scene.addPolygon(&box11);
*/

	

	//All cordiantes for the room (TODO -> floor and ceiling mixed up for some reason?)
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
	
	std::cout << "----Setting up the room----" << std::endl;

	//------TESTAR NYA KOORDINATER-------//
	
	// Triangles for the floor (with normals pointing up)
	Triangle floor1{P0, PC, P1, &floorMaterial};
	Triangle floor2{P1, PC, P2, &floorMaterial};
	Triangle floor3{P2, PC, P3, &floorMaterial};
	Triangle floor4{P3, PC, P4, &floorMaterial};
	Triangle floor5{P4, PC, P5, &floorMaterial};
	Triangle floor6{P5, PC, P0, &floorMaterial};

	// Triangles for the ceiling (with normals pointing down)
	Triangle ceiling1{P6, P7, PF, &ceilingMaterial};
	Triangle ceiling2{P7, P8, PF, &ceilingMaterial};
	Triangle ceiling3{P8, P9, PF, &ceilingMaterial};
	Triangle ceiling4{P9, P10, PF, &ceilingMaterial};
	Triangle ceiling5{P10, P11, PF, &ceilingMaterial};
	Triangle ceiling6{P11, P6, PF, &ceilingMaterial};

	//------TESTAR NYA KOORDINATER-------//

	//Triangle yeet{glm::vec3{6.0f, 1.0f, 3.0f}, glm::vec3{4.0f, -4.0f, 3.0f}, glm::vec3{4.0f, 1.0f, 3.0f}, &floorMaterial};

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
	/* Triangle floor1{P0, P5, P1, &floorMaterial};
	Triangle floor2{P5, P4, P1, &floorMaterial};
	Triangle floor3{P1, P4, P3, &floorMaterial};
	Triangle floor4{P3, P2, P1, &floorMaterial};

	Triangle ceiling1{P6, P7, P11, &ceilingMaterial};
	Triangle ceiling2{P7, P8, P11, &ceilingMaterial};
	Triangle ceiling3{P8, P9, P11, &ceilingMaterial};
	Triangle ceiling4{P9, P10, P11, &ceilingMaterial}; */
	
	Triangle light1{ P13, P12, P14, &light };
    Triangle light2{ P15, P12, P13, &light };
	
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

	Diffuse border{ white, 0.2 };

	//light border test if neccesary....*****
	const glm::vec3 P17{ 5.0f, 1.0f, 4.8f };
    const glm::vec3 P18{ 5.0f, 1.0f, 5.0f };
    const glm::vec3 P19{ 5.0f, -1.0f, 5.0f };
    const glm::vec3 P20{ 5.0f, -1.0f, 4.8f };
    const glm::vec3 P21{ 6.0f, 1.0f, 4.8f };
    const glm::vec3 P22{ 6.0f, 1.0f, 5.0f };
    const glm::vec3 P23{ 6.0f, -1.0f, 5.0f };
    const glm::vec3 P24{ 6.0f, -1.0f, 4.8f };

    Triangle triangle21{ P17, P18, P19, &border };
    Triangle triangle22{ P17, P19, P20, &border };
    Triangle triangle23{ P17, P21, P18, &border };
    Triangle triangle24{ P18, P21, P22, &border };
    Triangle triangle25{ P21, P23, P22, &border };
    Triangle triangle26{ P21, P24, P23, &border };
    Triangle triangle27{ P19, P23, P24, &border };
    Triangle triangle28{ P19, P24, P20, &border };

   /*  scene.addPolygon(&triangle21);
    scene.addPolygon(&triangle22);
    scene.addPolygon(&triangle23);
    scene.addPolygon(&triangle24);
    scene.addPolygon(&triangle25);
    scene.addPolygon(&triangle26);
    scene.addPolygon(&triangle27);
    scene.addPolygon(&triangle28); */


	// add box
	Box b1 = Box(glm::vec3(5.0f, -3.0f, 4.0f), 2.0f, 1.5f, 1.5f, &boxMaterial);
	scene.addBox(&b1);
	
	// add sphere
	Sphere s1{ glm::vec3(5.0f, -3.0f, 1.9f), 1.0f, &transparentMaterial };
	scene.addPolygon(&s1);

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
