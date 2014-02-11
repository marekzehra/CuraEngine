#include <stdio.h>

#include "settings.h"

#define STRINGIFY(_s) #_s
#define SETTING(name) _index.push_back(_ConfigSettingIndex(STRINGIFY(name), &name))
#define SETTING2(name, altName) _index.push_back(_ConfigSettingIndex(STRINGIFY(name), &name)); _index.push_back(_ConfigSettingIndex(STRINGIFY(altName), &name))

ConfigSettings::ConfigSettings()
{
    
    filamentDiameter = 2890;
    filamentFlow = 100;
    initialLayerThickness = 300;
    layerThickness = 200;
    extrusionWidth = 400;
    insetCount = 2;
    downSkinCount = 6;
    upSkinCount = 6;
    initialSpeedupLayers = 4;
    initialLayerSpeed = 20;
    printSpeed = 50;
    infillSpeed = 50;
    moveSpeed = 200;
    fanFullOnLayerNr = 2;
    skirtDistance = 6000;
    skirtLineCount = 1;
    skirtMinLength = 0;
    sparseInfillLineDistance = 100 * extrusionWidth / 20;
    infillOverlap = 15;
    objectPosition.X = 102500;
    objectPosition.Y = 102500;
    objectSink = 0;
    supportAngle = 45;
    supportEverywhere = 1;
    supportLineDistance = sparseInfillLineDistance;
    supportExtruder = -1;
    supportXYDistance = 700;
    supportZDistance = 150;
    retractionAmount = 4500;
    retractionSpeed = 45;
    retractionAmountExtruderSwitch = 14500;
    retractionMinimalDistance = 1500;
    minimalExtrusionBeforeRetraction = 100;
    enableOozeShield = 0;
    enableCombing = 1;
    wipeTowerSize = 0;
    multiVolumeOverlap = 0;
    
    minimalLayerTime = 5;
    minimalFeedrate = 10;
    coolHeadLift = 1;
    fanSpeedMin = 100;
    fanSpeedMax = 100;
    
    raftMargin = 5000;
    raftLineSpacing = 1000;
    raftBaseThickness = 0;
    raftBaseLinewidth = 0;
    raftInterfaceThickness = 0;
    raftInterfaceLinewidth = 0;
    
    spiralizeMode = 0;
    fixHorrible = 0;
    gcodeFlavor = GCODE_FLAVOR_REPRAP;
    
    memset(extruderOffset, 0, sizeof(extruderOffset));
    
    startCode =
    "M109 S210     ;Heatup to 210C\n"
    "G21           ;metric values\n"
    "G90           ;absolute positioning\n"
    "G28           ;Home\n"
    "G1 Z15.0 F300 ;move the platform down 15mm\n"
    "G92 E0        ;zero the extruded length\n"
    "G1 F200 E5    ;extrude 5mm of feed stock\n"
    "G92 E0        ;zero the extruded length again\n";
    endCode =
    "M104 S0                     ;extruder heater off\n"
    "M140 S0                     ;heated bed heater off (if you have it)\n"
    "G91                            ;relative positioning\n"
    "G1 E-1 F300                    ;retract the filament a bit before lifting the nozzle, to release some of the pressure\n"
    "G1 Z+0.5 E-5 X-20 Y-20 F9000   ;move Z up a bit and retract filament even more\n"
    "G28 X0 Y0                      ;move X/Y to min endstops, so the head is out of the way\n"
    "M84                         ;steppers off\n"
    "G90                         ;absolute positioning\n";
    
    SETTING(layerThickness);
    SETTING(initialLayerThickness);
    SETTING(filamentDiameter);
    SETTING(filamentFlow);
    SETTING(extrusionWidth);
    SETTING(insetCount);
    SETTING(downSkinCount);
    SETTING(upSkinCount);
    SETTING(sparseInfillLineDistance);
    SETTING(infillOverlap);
    SETTING(skirtDistance);
    SETTING(skirtLineCount);
    SETTING(skirtMinLength);

    SETTING(initialSpeedupLayers);
    SETTING(initialLayerSpeed);
    SETTING(printSpeed);
    SETTING(infillSpeed);
    SETTING(inset0Speed);
    SETTING(insetXSpeed);
    SETTING(moveSpeed);
    SETTING(fanFullOnLayerNr);
    
    SETTING(supportAngle);
    SETTING(supportEverywhere);
    SETTING(supportLineDistance);
    SETTING(supportXYDistance);
    SETTING(supportZDistance);
    SETTING(supportExtruder);
    
    SETTING(retractionAmount);
    SETTING(retractionSpeed);
    SETTING(retractionAmountExtruderSwitch);
    SETTING(retractionMinimalDistance);
    SETTING(minimalExtrusionBeforeRetraction);
    SETTING(enableCombing);
    SETTING(enableOozeShield);
    SETTING(wipeTowerSize);
    SETTING(multiVolumeOverlap);
    SETTING2(objectPosition.X, posx);
    SETTING2(objectPosition.Y, posy);
    SETTING(objectSink);

    SETTING(raftMargin);
    SETTING(raftLineSpacing);
    SETTING(raftBaseThickness);
    SETTING(raftBaseLinewidth);
    SETTING(raftInterfaceThickness);
    SETTING(raftInterfaceLinewidth);
    
    SETTING(minimalLayerTime);
    SETTING(minimalFeedrate);
    SETTING(coolHeadLift);
    SETTING(fanSpeedMin);
    SETTING(fanSpeedMax);
    
    SETTING(fixHorrible);
    SETTING(spiralizeMode);
    SETTING(gcodeFlavor);
    
    SETTING(extruderOffset[1].X);
    SETTING(extruderOffset[1].Y);
    SETTING(extruderOffset[2].X);
    SETTING(extruderOffset[2].Y);
    SETTING(extruderOffset[3].X);
    SETTING(extruderOffset[3].Y);
}

#undef STRINGIFY
#undef SETTING

bool ConfigSettings::setSetting(const char* key, const char* value)
{
    for(unsigned int n=0; n < _index.size(); n++)
    {
        if (strcasecmp(key, _index[n].key) == 0)
        {
            *_index[n].ptr = atoi(value);
            return true;
        }
    }
    if (strcasecmp(key, "startCode") == 0)
    {
        this->startCode = value;
        return true;
    }
    if (strcasecmp(key, "endCode") == 0)
    {
        this->endCode = value;
        return true;
    }
    return false;
}
