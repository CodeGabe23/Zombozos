#include <iostream>
#include <raylib.h>
#include <cmath>

int main(void)
{
    // Initialization
    const int screenWidth = 1500;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

	
	// Bring in assets now!
	// bus
	Model misty = LoadModel("assets/Misty.obj");
	for (int i = 0; i < misty.materialCount; i++)
	{
		 misty.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = (Texture2D){0};  // no texture
		 misty.materials[i].maps[MATERIAL_MAP_DIFFUSE].color = (Color){ 255, 200, 150, 255 };  // skin
	}

	for (int i = 0; i < misty.materialCount; i++)
	{
		misty.materials[i].maps[MATERIAL_MAP_DIFFUSE].color = RED;
		printf("Material %d: RED\n", i);
	}

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
	float cameraPosX = 0.0f, cameraPosY = 10.0f, cameraPosZ = 10.0f;
	float cameraUpX = 0.0f, cameraUpY = 1.0f, cameraUpZ = 0.0f;      // rotation towards the target cube
																	 //
	// cube orbit parameters
	float orbitAngle = 0.0f, orbitRadius = 10.0, cameraHeight = 10.0f;
	float speed = 1.5f;
	float dt = GetFrameTime();

	camera.position = (Vector3){ cameraPosX, cameraPosY, cameraPosZ }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };					   // Camera looking at point
    camera.up = (Vector3){ cameraUpX, cameraUpY, cameraUpZ };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;											   // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;							   // Camera mode type


	// Define a 3d cube
	float cubePosX = 0.0f, cubePosY = 0.0f, cubePosZ = 0.0f;
    Vector3 cubePosition = { cubePosX, cubePosY, cubePosZ };


    SetTargetFPS(165);               // Set our game to run at 60 frames-per-second
    
	// Main game loop
    
while (!WindowShouldClose())

{
    float dt = GetFrameTime();  // fresh every frame
    
    if (IsKeyDown(KEY_A)) orbitAngle -= speed * dt;
    if (IsKeyDown(KEY_D)) orbitAngle += speed * dt;
    
    // Compute position on circle around cube
    camera.position.x = cosf(orbitAngle) * orbitRadius;
    camera.position.z = sinf(orbitAngle) * orbitRadius;
    camera.position.y = cameraHeight;
    
    // target stays fixed on cube
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up     = (Vector3){ 0.0f, 1.0f, 0.0f };
    
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
            Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

			//draw bus
			DrawModel(misty, (Vector3){0.0f, 0.0f, 0.0f}, 0.025f, WHITE);

            //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
            DrawGrid(10, 1.0f);
        EndMode3D();
        
        DrawText(TextFormat("Angle: %.1f rad", orbitAngle), 10, 40, 20, DARKGRAY);
        DrawFPS(10, 10);
    EndDrawing();
}


    // De-Initialization
    CloseWindow();        // Close window and OpenGL context
	UnloadModel(misty);

    return 0;
}
