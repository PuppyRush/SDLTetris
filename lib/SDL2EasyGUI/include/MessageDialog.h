//
// Created by chaed on 19. 3. 5.
//

#ifndef SDL2EASYGUI_MESSAGEDIALOG_H
#define SDL2EASYGUI_MESSAGEDIALOG_H

#include <string>

#include "SDL2EasyGUI/include/DisplayInterface.h"
#include "StaticLabel.h"
#include "Button.h"
#include "SDL2EasyGUI/include/SEG_Property.h"

namespace seg {

class MessageDialog : public DisplayInterface
{

public:

    MessageDialog(const std::string& message, MessageDialogKind kind);

    virtual ~MessageDialog()
    {}

    virtual const t_id getDisplayId() const noexcept override final
    {
        return resource::MESSAGE_DIALOG;
    }

    virtual std::underlying_type_t<resource> alert() override;

    virtual void registerEvent() override;

    virtual void onInitialize() override;

    virtual void postCreate(display_ptr display) override
    {}

    virtual void postDestroy(const unique_type unique) override
    {}

    virtual void onClose() override
    {
        DisplayInterface::onClose();
    }

    virtual bool validId(const seg::t_id id) noexcept
    {
        return getWindowID() == id;
    }

    void onClickOk(const void*);

    void onClickYes(const void*);

    void onClickNo(const void*);

private:

    std::string m_message;
    MessageDialogKind m_kind;
};
}

#endif //SDL2EASYGUI_MESSAGEDIALOG_H
