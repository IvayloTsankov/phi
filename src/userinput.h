#ifndef PHI_USER_INPUT_H_
#define PHI_USER_INPUT_H_

#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include "SDL/SDL.h"


// Inherit to register in UserInput class
class KeyHandler
{
public:
    // type: SDL_KEYDOWN or SDL_KEYUP
    virtual void OnMessage(SDLKey key, uint8_t type) = 0;
    virtual ~KeyHandler() {}

public:
    void RegisterKey(SDLKey key);
    void DeregisterKey(SDLKey key);
    std::vector<SDLKey> GetKeys(void)
    {
        return this->keys_;
    }

private:
    std::vector<SDLKey> keys_;
};


// Call handler's callbacks for registered keys
// NOTE: NOT Thread safe which means that Add/Remove
// handlers when Start() is called is undefined
class UserInput
{
public:
    UserInput();
    ~UserInput() {};

    // Skip 2 or more sequential call
    // (Only one pointer per instalnce
    bool AddHandler(KeyHandler* handler);

    void RemoveHandler(KeyHandler* handler);

    // Start/Stop event listener
    void Start(void);
    void Stop(void);


private:
    void Listen(void);


private: // Disallow copy and operator =
    UserInput(const UserInput&);
    UserInput& operator = (const UserInput&);


private:
    std::vector<KeyHandler*> key_handlers_;
    std::unique_ptr<std::thread> runner_;
    std::atomic<bool> quit_;
};

#endif // PHI_USER_INPUT_H_
