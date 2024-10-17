#ifndef PLUGIN_CONFIG_H
#define PLUGIN_CONFIG_H

#define CPLUG_COMPANY_NAME "Hermes"
#define CPLUG_COMPANY_EMAIL ""
#define CPLUG_PLUGIN_NAME "TableSaw"
#define CPLUG_PLUGIN_URI "http://github.com/BenjaminQuiedeville/TableSaw"
#define CPLUG_PLUGIN_VERSION "0.0.1"

#define CPLUG_IS_INSTRUMENT 0

#define CPLUG_NUM_INPUT_BUSSES 1
#define CPLUG_NUM_OUTPUT_BUSSES 1
#define CPLUG_WANT_MIDI_INPUT 1
#define CPLUG_WANT_MIDI_OUTPUT 1

#define CPLUG_WANT_GUI 1
#define CPLUG_GUI_RESIZABLE 1

// See list of categories here: https://steinbergmedia.github.io/vst3_doc/vstinterfaces/group__plugType.html
#define CPLUG_VST3_CATEGORIES "Effect|Stereo"

#define CPLUG_VST3_TUID_COMPONENT 'cplg', 'comp', 'xmpl', 0
#define CPLUG_VST3_TUID_CONTROLLER 'cplg', 'edit', 'xmpl', 0

#define CPLUG_AUV2_VIEW_CLASS CPLUGExampleView
#define CPLUG_AUV2_VIEW_CLASS_STR "TableSawView"
static const unsigned kAudioUnitProperty_UserPlugin = 'plug';

#define CPLUG_CLAP_ID "com.hermes.tablesaw"
#define CPLUG_CLAP_DESCRIPTION "TableSaw"
#define CPLUG_CLAP_FEATURES CLAP_PLUGIN_FEATURE_INSTRUMENT, CLAP_PLUGIN_FEATURE_STEREO

#define CPLUG_NUM_PARAMS 4

#endif // PLUGIN_CONFIG_H
