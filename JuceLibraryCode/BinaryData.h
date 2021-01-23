/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   decodingMatrix_json;
    const int            decodingMatrix_jsonSize = 16261;

    extern const char*   irsOrd1_wav;
    const int            irsOrd1_wavSize = 1932;

    extern const char*   irsOrd2_wav;
    const int            irsOrd2_wavSize = 4292;

    extern const char*   irsOrd3_wav;
    const int            irsOrd3_wavSize = 7596;

    extern const char*   irsOrd4_wav;
    const int            irsOrd4_wavSize = 11844;

    extern const char*   irsOrd5_wav;
    const int            irsOrd5_wavSize = 17036;

    extern const char*   irsOrd6_wav;
    const int            irsOrd6_wavSize = 23172;

    extern const char*   irsOrd7_wav;
    const int            irsOrd7_wavSize = 30252;

    extern const char*   hp_png;
    const int            hp_pngSize = 56543;

    extern const char*   owl_back_png;
    const int            owl_back_pngSize = 105111;

    extern const char*   owl_back_hp_png;
    const int            owl_back_hp_pngSize = 118609;

    extern const char*   owl_front_hp_png;
    const int            owl_front_hp_pngSize = 7312;

    extern const char*   owl_plan_png;
    const int            owl_plan_pngSize = 6539;

    extern const char*   owl_plan_hp_png;
    const int            owl_plan_hp_pngSize = 6334;

    extern const char*   owl_profile_png;
    const int            owl_profile_pngSize = 7392;

    extern const char*   owl_profile_hp_png;
    const int            owl_profile_hp_pngSize = 7338;

    extern const char*   pause_png;
    const int            pause_pngSize = 4155;

    extern const char*   play_png;
    const int            play_pngSize = 1649;

    extern const char*   speaker_png;
    const int            speaker_pngSize = 55230;

    extern const char*   sphere_png;
    const int            sphere_pngSize = 16672;

    extern const char*   stop_png;
    const int            stop_pngSize = 2503;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 21;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
