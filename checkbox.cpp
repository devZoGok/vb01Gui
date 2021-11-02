#include "checkbox.h"

using namespace vb01;
using namespace std;

namespace vb01Gui{
    Checkbox::CheckboxButton::CheckboxButton(Checkbox *ch, Vector2 pos, Vector2 size, string name, bool separate) : Button(pos, size, name, "", -1, separate) {
        checkbox = ch;
    }
    
    void Checkbox::CheckboxButton::onClick() {
        checkbox->check();
    }

    Checkbox::Checkbox(Vector2 pos){
        this->pos = pos;
        checkboxButton = new CheckboxButton(this, pos, Vector2(length,length), "CheckboxButton", false);
    }
    
    Checkbox::~Checkbox() {

    }
    
    void Checkbox::update() {
				/*
        driver->draw2DRectangle(SColor(255, 100, 100, 100), rect<s32>(pos.X, pos.Y, pos.X + length, pos.Y + length), nullptr);

        if (checked) {
            driver->draw2DLine(pos, vector2d<s32>(pos.X + length, pos.Y + length),SColor(255,255,255,255));
            driver->draw2DLine(vector2d<s32>(pos.X,pos.Y+length), vector2d<s32>(pos.X + length, pos.Y), SColor(255, 255, 255, 255));
        }
				*/
    }
}
