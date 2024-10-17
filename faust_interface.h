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
    
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
        parameter_count++;
        
        std::string label_str(label);
        
        int index = 0;
        
        if (label_str == param_labels[kGain]) { index = kGain; }
        else if (label_str == param_labels[kLow])  { index = kLow; }
        else if (label_str == param_labels[kHigh]) { index = kHigh; }
        else if (label_str == param_labels[kVol])  { index = kVol; }
        else { assert(false && "addHorizontalSlider wrong parameter name"); }
        
        plugin->faust_param_zones[index] = zone;
        ParamInfo *parameter = &plugin->paramInfo[index];
        
        assert(parameter->max == max);
        assert(parameter->min == min);
        assert(parameter->defaultValue == init);

    }
    
    int getParamsCount() { 
        return parameter_count;
    }
        
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
};


#endif // FAUST_INTERFACE_H
