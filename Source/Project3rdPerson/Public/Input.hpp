//
//  Input.h
//  World
//
//  Created by Adam James Leuer on 4/24/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Input__
#define __SpriteFight__Input__

#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <initializer_list>
#include <list>

#include "GameState.hpp"
#include "GameInterface.h"

#include "Configuration.h"

using namespace std ;

typedef void* Event ;
typedef void* KeyCode ;
typedef void* ScanCode ;

class EventRegisterBase {
	
protected:
	
	
	/**
	 * See member_callBackFunction.
	 */
	GameInterface * memberToCallOn ;
	
	/**
	 * A pointer to the function to be called
	 * when the requested keyboard input is detected. This variable holds
	 * pointers to member functions
	 */
	void (GameInterface::*member_callBackFunction)() ;
	
	/**
	 * A pointer to the function to be called
	 * when the requested keyboard input is detected. This variable points
	 * to static or global functions (member_callOn should be a nullptr in any
	 * EventRegisterBase where a callBackFn, and not a member_callBackFn, is held)
	 */
	
	/* void (*callBackFunction)() ; */ //old version
	
	function<void (void)> callBackFunction ;
	
	/**
	 * In the rare case that our callback function takes an argument,
	 * we will use arg to store it
	 */
	void * arg = nullptr ; //null except in rare cases
	
	friend class InputController ;
	
	EventRegisterBase() {}
	
	/**
	 * Copy constructor
	 */
	EventRegisterBase(const EventRegisterBase & other) :
		memberToCallOn(other.memberToCallOn),
		member_callBackFunction(other.member_callBackFunction),
		callBackFunction(other.callBackFunction) {}
	
	/**
	 * Move constructor
	 */
	EventRegisterBase(EventRegisterBase && other) :
		memberToCallOn(other.memberToCallOn),
		member_callBackFunction(std::move(other.member_callBackFunction)),
		callBackFunction(std::move(other.callBackFunction)) {}
	
	EventRegisterBase(GameInterface * callOn, void (GameInterface::*cb)()) :
		memberToCallOn(callOn),
		member_callBackFunction(cb),
		callBackFunction(nullptr) {}
	
	template<typename T>
	EventRegisterBase(GameInterface * callOn, void (GameInterface::*cb)(), T arg0) :
		memberToCallOn(callOn),
		member_callBackFunction(cb),
		arg(arg0),
		callBackFunction(nullptr) {}
	
	EventRegisterBase(function<void (void)> cb) :
		memberToCallOn(nullptr),
		member_callBackFunction(nullptr),
		callBackFunction(cb) {}
	
public:
	
	void callBack() ;
	
} ;

/**
 * An implementation of EventRegisterBase with the ability to handle any type of SDL_Event.
 */
class EventRegister : public EventRegisterBase {
	
protected:
	/**
	 * The string representing the keyboard key
	 * the client wishes to listen for
	 */
	EventType eventType ;
	
	friend class InputController ;
	
	
public:
	
	EventRegister() {}
	
	EventRegister(const EventRegister & other) :
		EventRegisterBase(other),
		eventType(other.eventType) {}
	
	EventRegister(EventRegister && other) :
		EventRegisterBase(std::move(other)),
		eventType(other.eventType) {}
    
	EventRegister(GameInterface * callOn, void (GameInterface::*cb)(), EventType eventType) :
		EventRegisterBase(callOn, cb),
		eventType(eventType) {}
	
	template<class T>
	EventRegister(GameInterface * callOn, void (GameInterface::*cb)(), T * arg0, EventType eventType) :
		EventRegisterBase(callOn, cb, arg0),
		eventType(eventType) {}
	
	EventRegister(function<void (void)> cb, EventType eventType) :
		EventRegisterBase(cb),
		eventType(eventType) {}
	
	~EventRegister() {}
	
	void handleEvent(const Event * currentEvent) ;
	
} ;

/**
 * Whether a KeyInputRegister should evaluate all requested key presses inclusively, or exclusively.
 * In other words, if the client wishes to call a given function when, say, either "G", or SDL_SCANCODE_KP_PLUS, or
 * "T" are pressed, but not neccessarily all of them, they should use KeypressEvaluationMethod::any. If they want a certain
 * function called when *all* of those keys are used at once, they should use EvaluationMethod::all.
 */
enum class KeypressEvaluationMethod {
	exactlyOne,
	all,
	any
} ;

/**
 * An implementation of EventRegisterBase specialized for handling keyboard input.
 */
class KeyInputRegister : public EventRegisterBase {
	
protected:
	
	vector<ScanCode> scanCodes ;
	
	/**
	 * The string representing the keyboard key
	 * the client wishes to listen for
	 */
	vector<string> requestedKeyboardChars ;
	
	vector<KeyCode> requestedKeyCodes ;
	
	KeypressEvaluationMethod requestedKeyEvalMethod ;
	
	/**
	 * This enumeration represents whether this KeyInputRegister references
	 */
	enum class KeyIdenMethod {
		keyChar = 0,
		keyCode = 1,
		both = (keyChar & keyCode)
	} keyIDMethod ;
	
	/**
	 * Recursively checks the keyboard state against all ScanCodes corresponding to requested keys, and
	 * turns true if all are pressed, or false otherwise.
	 */
	bool checkForPressedKeys(const unsigned char * keyboardState, vector<ScanCode>::iterator scanCode) ;
	
    virtual void handleKeyboardInput(const unsigned char * keyboardState) ;
	
	friend class InputController ;
	
public:
	
	KeyInputRegister() {} ;
    
	KeyInputRegister(const KeyInputRegister & other) :
		EventRegisterBase(),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(vector<string>(other.requestedKeyboardChars)),
		requestedKeyCodes(vector<KeyCode>(other.requestedKeyCodes)),
		requestedKeyEvalMethod(other.requestedKeyEvalMethod),
		keyIDMethod(other.keyIDMethod)
	{
			
		for (auto i = 0 ; (i < requestedKeyboardChars.size()) || (i < requestedKeyCodes.size()) ; i++) {
			if (i < requestedKeyboardChars.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
				scanCodes.push_back(scanCode) ;
			}
			if (i < requestedKeyCodes.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyCodes.at(i)) ;
				scanCodes.push_back(scanCode) ;
			}
		}
	}
	
	KeyInputRegister(KeyInputRegister && other) :
		EventRegisterBase(std::move(other)),
		scanCodes(std::move(other.scanCodes)),
		requestedKeyboardChars(std::move(other.requestedKeyboardChars)),
		requestedKeyCodes(std::move(other.requestedKeyCodes)),
		requestedKeyEvalMethod(other.requestedKeyEvalMethod),
		keyIDMethod(std::move(other.keyIDMethod)) {}
    
    KeyInputRegister(GameInterface * callOn, void (GameInterface::*cb)(), initializer_list<string> keyChar, KeypressEvaluationMethod m) :
		EventRegisterBase(callOn, cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(keyChar),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::keyChar)
	{
		for (auto i = 0 ; i < requestedKeyboardChars.size() ; i++) {
			ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
			scanCodes.push_back(scanCode) ;
		}
	}
	
	template<class T>
	KeyInputRegister(GameInterface * callOn, void (GameInterface::*cb)(), T * arg0, initializer_list<string> keyChar, KeypressEvaluationMethod m) :
		EventRegisterBase(callOn, cb, arg0),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(keyChar),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::keyChar)
	{
		for (auto i = 0 ; i < requestedKeyboardChars.size() ; i++) {
			ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
			scanCodes.push_back(scanCode) ;
		}
	}
	
	KeyInputRegister(function<void (void)> cb, initializer_list<string> keyChar, KeypressEvaluationMethod m) :
		EventRegisterBase(cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(keyChar),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::keyChar)
	{
		for (auto i = 0 ; i < requestedKeyboardChars.size() ; i++) {
			ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
			scanCodes.push_back(scanCode) ;
		}
	}
	
	KeyInputRegister(GameInterface * callOn, void (GameInterface::*cb)(), initializer_list<KeyCode> keyCode, KeypressEvaluationMethod m) :
		EventRegisterBase(callOn, cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyCodes(keyCode),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::keyCode)
	{
		for (auto i = 0 ; i < requestedKeyCodes.size() ; i++) {
			ScanCode scanCode = getScanCodeFor(requestedKeyCodes.at(i)) ;
			scanCodes.push_back(scanCode) ;
		}
	}
	
	KeyInputRegister(function<void (void)> cb, initializer_list<KeyCode> keyCode) :
		EventRegisterBase(cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyCodes(keyCode),
		keyIDMethod(KeyIdenMethod::keyCode)
	{
		for (auto i = 0 ; i < requestedKeyCodes.size() ; i++) {
			ScanCode scanCode = getScanCodeFor(requestedKeyCodes.at(i)) ;
			scanCodes.push_back(scanCode) ;
		}
	}
	
	KeyInputRegister(GameInterface * callOn, void (GameInterface::*cb)(), initializer_list<string> keyChar, initializer_list<KeyCode> keyCode, KeypressEvaluationMethod m) :
		EventRegisterBase(callOn, cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(keyChar),
		requestedKeyCodes(keyCode),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::both)
	{
		for (auto i = 0 ; (i < requestedKeyboardChars.size()) || (i < requestedKeyCodes.size()) ; i++) {
			if (i < requestedKeyboardChars.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
				scanCodes.push_back(scanCode) ;
			}
			if (i < requestedKeyCodes.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyCodes.at(i)) ;
				scanCodes.push_back(scanCode) ;
			}
		}
	}
	
	KeyInputRegister(function<void (void)> cb, initializer_list<string> keyChar, initializer_list<KeyCode> keyCode, KeypressEvaluationMethod m) :
		EventRegisterBase(cb),
		scanCodes(vector<ScanCode>()),
		requestedKeyboardChars(keyChar),
		requestedKeyCodes(keyCode),
		requestedKeyEvalMethod(m),
		keyIDMethod(KeyIdenMethod::both)
	{
		for (auto i = 0 ; (i < requestedKeyboardChars.size()) || (i < requestedKeyCodes.size()) ; i++) {
			if (i < requestedKeyboardChars.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyboardChars.at(i).c_str()) ;
				scanCodes.push_back(scanCode) ;
			}
			if (i < requestedKeyCodes.size()) {
				ScanCode scanCode = getScanCodeFor(requestedKeyCodes.at(i)) ;
				scanCodes.push_back(scanCode) ;
			}
		}
	}
	
	virtual ~KeyInputRegister() {}
	
	static ScanCode getScanCodeFor(const char* c) { return 0 ; } /* wrapper (just in case
																							   I forget how to get scancodes!) */
	static ScanCode getScanCodeFor(KeyCode code) { return 0 ; }
	
} ;


/**
 * SwitchableKeyInputRegister is a variant of KeyInputRegister that can hold multiple callback functions
 * (and members to call those functions on), as well as several different keyboard keys at the same time.
 * This is in contrast to the single function pointer held in any KeyInputRegister. The real advantage of SwitchableKeyInputRegister
 * is its ability to choose different callbacks based on a descending order of priority that is set when the SwitchableKeyInputRegister
 * is created. A SwitchableKeyInputRegister is part of a linked-list of pointers to KeyInputRegisters or other SwitchableKeyInputRegisters, 
 * and each one is able to "shut off" subsequent members in its list from providing their callback functions. The list should be initialized
 * with the highest priority KeyInputRegisters at the front, with the fallback, lower priority ones following. Any KeyInputRegister or
 * SwitchableKeyInputRegister's callback function will only be called if callback function belonging to the KeyInputRegister prior to it
 * in the list was not.
 */
class SwitchableKeyInputRegister : public KeyInputRegister, public std::list<SwitchableKeyInputRegister *> {
	
} ;


class InputController {
	
protected:
	
	/**
	 * Associates keys with callback functions.
	 */
	static vector<EventRegister *> * eventListenerRegistry ;
	
	/**
	 * Associates keys with callback functions.
	 */
	static vector<KeyInputRegister *> * keyInputRegistry ;
	
	static Event * event ;
	
	/**
	 * Holds pointers to the state of each key on the keyboard. Initialized once, but valid for the scope of the program.
	 */
	static const unsigned char * keys ;
	static int keyArraySize ;
	
	static void listenForKeypress() ;
	
	static void listenForEvents() ;
	
	InputController() ;
	
public:
	
	static void registerForEvent(EventRegister * reg) ;
	static void registerForKeypress(KeyInputRegister * reg) ;
	template<typename T>
	static void registerFor(T * event_or_keypress) ; //convenience function
	static void deregister(GameInterface * registeredObject) ;
	
	static void init() ;
	static void update() ;
	static void exit() ;
	
} ;

/**
template<class T>
void InputController::registerFor(T * event_or_keypress) {
	static_assert(((typeid(T) == typeid(EventRegister)) || (typeid(T) == typeid(KeyInputRegister))), "Class T must be one of either EventRegister or KeyInputRegister") ;
	
	if (typeid(T) == typeid(EventRegister)) {
		registerForEvent(event_or_keypress) ;
	}
	else if (typeid(T) == typeid(KeyInputRegister)) {
		registerForKeypress(event_or_keypress) ;
	}
} */

#endif /* defined(__SpriteFight__Input__) */
