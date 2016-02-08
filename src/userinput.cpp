#include "userinput.h"
#include "utils.h"
#include <algorithm>


void KeyHandler::RegisterKey(SDLKey key)
{
    keys_.push_back(key);
}

void KeyHandler::DeregisterKey(SDLKey key)
{
    this->keys_.erase(std::remove(this->keys_.begin(),
                                  this->keys_.end(), key),
                      this->keys_.end());
}


UserInput::UserInput()
 :  quit_(true)
{

}


bool UserInput::AddHandler(KeyHandler* handler)
{
    size_t num_handlers = this->key_handlers_.size();
    for (size_t i = 0; i < num_handlers; ++i)
    {
        if (this->key_handlers_[i] == handler)
        {
            return true;
        }
    }

    this->key_handlers_.push_back(handler);
    return true;
}

void UserInput::RemoveHandler(KeyHandler* handler)
{
    this->key_handlers_.erase(std::remove(this->key_handlers_.begin(),
                                          this->key_handlers_.end(), handler),
                              this->key_handlers_.end());
}

void UserInput::Start(void)
{
    this->quit_ = false;
    this->runner_.reset(new std::thread(&UserInput::Listen, this));
    this->runner_->join();
}

void UserInput::Stop(void)
{
    this->quit_ = true;
}

void UserInput::Listen(void)
{
    while(!this->quit_)
    {
        size_t num_hdls = this->key_handlers_.size();
        if (num_hdls > 0)
        {
            SDL_Event ev;
            SDLKey key;
            uint8_t type;
            bool need_emit = false;
            while(SDL_PollEvent(&ev))
            {
                if (ev.type == SDL_KEYDOWN)
                {
                    key = ev.key.keysym.sym;
                    type = ev.type;
                    need_emit = true;
                    break;
                }
                else if (ev.type == SDL_KEYUP)
                {
                    need_emit = true;
                    type = ev.type;
                    break;
                }
            }

            if (need_emit)
            {
                for(size_t i = 0; i < num_hdls; ++i)
                {
                    auto handler = this->key_handlers_[i];
                    auto keys = handler->GetKeys();
                    size_t keys_size = keys.size();
                    for(size_t j = 0; j < keys_size; ++j)
                    {
                        if (keys[j] == key)
                        {
                            handler->OnMessage(key, type);
                        }
                    }
                }
            }
        }

        phi_sleep(30);
    }
}
