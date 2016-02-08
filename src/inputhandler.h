#ifndef PHI_INPUT_HANDLER_H_
#define PHI_INPUT_HANDLER_H_

#include "userinput.h"
#include "image.h"
#include <map>
#include <memory>


typedef void (*Effect) (Image* image, SDLKey key, uint8_t type);

class InputHandler: public KeyHandler
{
public:
    InputHandler(std::unique_ptr<Image> image);

    virtual void OnMessage(SDLKey key, uint8_t type);

    void Bind(SDLKey keypress, Effect effect);
    void RemoveBind(SDLKey keypress);

    void ResetState(void) { curr_effect_ = NULL; }


private:
    Effect curr_effect_;
    std::map<SDLKey, Effect> effects_;
    std::unique_ptr<Image> image_;
};

#endif // PHI_INPUT_HANDLER_H_
