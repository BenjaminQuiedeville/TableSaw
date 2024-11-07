#ifndef FAUST_INTERFACE_H
#define FAUST_INTERFACE_H

#include "faust/gui/UI.h"

struct MyPlugin;

struct FaustInterface : public UI {

    MyPlugin *plugin = nullptr;
    int parameter_count = 0;

    void openTabBox(const char* label) {}
    void openHorizontalBox(const char* label) {}
    void openVerticalBox(const char* label) {}
    void closeBox() {}
    void addButton(const char* label, FAUSTFLOAT* zone) {}
    void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);    

    int getParamsCount() { 
        return parameter_count;
    }
        
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
};


#endif // FAUST_INTERFACE_H
