#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl3w.h>
#include <vector>
#include <random>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int g_initialWidth = 2048;
int g_initialHeight = 2048;


const char * fShaderCode = "#version 330 core \n      \
out vec4 FragColor;\n                                  \
void main()\n                                          \
{\n                                                    \
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n       \
};\n                                                   \
";

const char * vShaderCode = "#version 330 core \n     \
layout (location = 0)in vec2 vert;\n                                     \
void main()\n                                         \
{\n                                                   \
    gl_Position = vec4(vert.x,vert.y,0.0,1.0);\n             \
}\n                                                   \
";


int main(int argc,const char ** argv)
{
	int count = 1000 * 2;  // a 2d point
	if(argc == 2){
		count = std::strtol(argv[1],0,10);
		std::cout<<count<<" point(s)\n";
	}


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
	glfwCreateWindow(g_initialWidth, g_initialHeight, "OpenGL Demo", NULL, NULL);
		

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	gl3wInit();

	if (!gl3wIsSupported(4, 4))
	{
		std::cout << "OpenGL 4.4 or later must be needed\n";
		return 0;
	}

    //// Init OpenGL Resource

	std::default_random_engine e;
	std::uniform_real_distribution<float> u(-1,1);

	std::vector<float> vertices;
	std::cout<<"Generating "<<count<<" point(s)...\n";
	for(int i = 0 ; i < count;i++){
		vertices.push_back(u(e));
	}
	std::cout<<"Generating done.\n";


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	unsigned int VBO ,VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//
	glUseProgram(shaderProgram);

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
 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP,0,count/2);
        ///
	
		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}
    
	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}