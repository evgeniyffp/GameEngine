#include "./Window.h"

#include <utils/displayInfo.h>

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::initGLFW() {
    int result = glfwInit();

    std::string info = "Window.cpp => Window::initGLFW() => glfwInit() return " + std::to_string(result);
	displayInfo(info);

    if (result != GLFW_TRUE) {
		glfwTerminate();
		throw info;
	}
}

void Window::initWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLSetting::Version::majorerVersion());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLSetting::Version::minorVersion());
	glfwWindowHint(GLFW_RESIZABLE, true);

	size = vec2(mode->width, mode->height);

	window = glfwCreateWindow(
		size.x, size.y,
		title.c_str(),
		monitor, NULL
    );

	std::string info = "Window.cpp => initWindow() => create window";
	displayInfo(info);
	
    if (window == nullptr) {
		glfwTerminate();
		throw info;
	}

	glfwMakeContextCurrent(window);
	
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwGetFramebufferSize(window, &size.x, &size.y);
	
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    keyboard_control.setWindow(window);
    mouse_control.setWindow(window);
}

Window::Window(std::string _title) : title(std::move(_title)) {}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Window::get() {
    return window;
}

ivec2& Window::get_size_ref() {
    return size;
}

KeyboardControl& Window::getKeyboardControl() {
    return keyboard_control;
}

MouseControl& Window::getMouseControl() {
    return mouse_control;
}

void Window::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::is_closed() {
    return glfwWindowShouldClose(window);
}

void Window::init() {
    initGLFW();
    initWindow();
}

void Window::update() {
	glfwPollEvents();
	keyboard_control.update();
}

