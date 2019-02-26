#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{
    // Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow * window =
	glfwCreateWindow(g_initialWidth, g_initialHeight, "Mixed Render Engine", NULL, NULL);
		

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	gl3wInit();

	if (!gl3wIsSupported(4, 4))
	{
		std::cout << "OpenGL 4.4 or later must be needed\n";
		system("pause");
		return 0;
	}

    //// Init OpenGL Resource

    ///



	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();


        ///TODO::

        ///

	
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}


    
	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}