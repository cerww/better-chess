#pragma once

enum class Keys {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	N1, N2, N3, N4, N5, N6, N7, N8, N9, N0,
	NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
	LALT, RALT, LSHIFT, RSHIFT, ESC, SPACE, END, HOME, PAGEDOWN,
	PAGEUP, INSERT, UP, DOWN, LEFT, RIGHT, COLON, ENTER, BACKSPACE,
	DASH, EQUAL, TAB, MAX
};

enum class mouseB { MIDDLE, LEFT, RIGHT, MAX };

enum class Type {UNKNOWN,keyRelease,keyPress,mouseUp,mouseDown,mouseMove};

class event{
public: 
	event() = default;
	event(Type t_mouseType,mouseB t_button) : type(t_mouseType), button(t_button) {};
	event(Type t_keyType,Keys t_key) : type(t_keyType), key(t_key) {};
	Type type;
	union {
		Keys key;
		mouseB button;
	};
private:

};