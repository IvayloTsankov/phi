#include "inputhandler.h"
#include "effects.h"
#include "slog/slog.h"
#include "sdl.h"
#include <utility>

#include "userinput.h"
extern UserInput* user_input;


InputHandler::InputHandler(std::unique_ptr<Image> image)
:   curr_effect_(NULL),
    image_(image.release())
{
    this->RegisterKey(SDLK_q);
    this->RegisterKey(SDLK_ESCAPE);
}


void InputHandler::OnMessage(SDLKey key, uint8_t type)
{
    SLOG("User input: %d %d", key, type);
    if (type == SDL_KEYUP)
    {
        return;
    }

    if (key == SDLK_ESCAPE)
    {
        user_input->Stop();
        return;
    }

    if (key == SDLK_q)
    {
        this->ResetState();
        SLOG("Leave the effect")
        return;
    }

    if (this->curr_effect_ == NULL)
    {
        auto effect = this->effects_.find(key);
        if (effect != this->effects_.end())
        {
            this->curr_effect_ = effect->second;
            SLOG("Enter the effect")
            return;
        }
    }
    else
    {
        if (this->image_.get() == NULL)
        {
            SLOG("Try to execute effect without image");
            user_input->Stop();
            return;
        }

        this->curr_effect_(this->image_.get(), key, type);
        display_vfb(this->image_->buffer, this->image_->width, this->image_->height);
    }
}


void InputHandler::Bind(SDLKey keypress, Effect effect)
{
    this->effects_.insert(std::make_pair(keypress, effect));
    this->RegisterKey(keypress);
}

void InputHandler::RemoveBind(SDLKey keypress)
{
    auto effect = this->effects_.find(keypress);
    if (effect != this->effects_.end())
    {
        this->effects_.erase(effect);
    }
}
