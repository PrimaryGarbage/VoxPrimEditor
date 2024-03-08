#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "GLFW/glfw3.h"
#include "exception.hpp"
#include "input_utils.hpp"
#include "glm/glm.hpp"
#include "logger.hpp"
#include <vector>
#include <unordered_map>

namespace prim
{

class Input final
{
private:
	static const int keysCount = 350;
	static std::unordered_map<const GLFWwindow*, Input*> inputObjectsMapping;

	Logger logger;
	PressInfo keys[keysCount];
	MouseInfo mouse;
	const GLFWwindow* window;
	std::vector<Gamepad> gamepads;
	std::vector<Action> actions;
	std::vector<Axis> axes;
	std::string charInput;	// utf8 text

	// glfw callbacks
	static void keyCallback_s(GLFWwindow* window, int key, int scancode, int action, int mods); 
	static void charCallback_s(GLFWwindow* window, unsigned int codepoint);
	static void cursorPositionCallback_s(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback_s(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback_s(GLFWwindow* window, double xoffset, double yoffset);
	static void joystickCallback_s(int jid, int event);

	void keyCallback(int key, int scancode, int action, int mods); 
	void charCallback(unsigned int codepoint);
	void cursorPositionCallback(double xpos, double ypos);
	void mouseButtonCallback(int button, int action, int mods);
	void scrollCallback(double xoffset, double yoffset);
	void joystickCallback(int jid, int event);
	void insertCodepointIntoString(unsigned int codepoint, std::string& str);
	void registerAllGamepads();
	void createDefaultActionsAndAxes();
public:
	Input(GLFWwindow* window);
	~Input();

	// call to update input state (preferably at the start of the loop)
	void update();
	
	bool isPressed(const Key key);
	bool isPressed(const MouseButton button);
	bool isPressed(const GamepadButton button, const int gamepadId = 0);
	bool isPressed(const std::string actionName);
	bool isJustPressed(const Key key);
	bool isJustPressed(const MouseButton button);
	bool isJustPressed(const GamepadButton button, const int gamepadId = 0);
	bool isJustPressed(const std::string actionName);
	bool isJustReleased(const Key key);
	bool isJustReleased(const MouseButton button);
	bool isJustReleased(const GamepadButton button, const int gamepadId = 0);
	bool isJustReleased(const std::string actionName);

	float getAxis(const GamepadAxis axis, const int gamepadId = 0);
	float getAxis(const std::pair<Key, Key> keys);
	float getAxis(const std::pair<MouseButton, MouseButton> buttons);
	float getAxis(const std::pair<GamepadButton, GamepadButton> buttons);
	float getAxis(const std::string axisName);

	glm::vec2 getCursorPos();

	void addAction(const std::string name, std::initializer_list<ActionCause> actionCauses);
	void addAxis(const std::string name, std::initializer_list<AxisCause> axisCauses);
	void removeAction(const std::string name);
	void removeAxis(const std::string name);

	std::string getChars();
};

} // namespace prim

#endif // __INPUT_HPP__