#pragma once

#include "ace_common.h"
#include "vector.hpp"
#include "skeleton.hpp"

#include <sstream>

namespace ace {
    namespace p3d {

        enum LodTypes
        {
            LODTYPE_VIEW_GUNNER = 0x447a0000,					//1000
            LODTYPE_VIEW_PILOT = 0x44898000,					//1100
            LODTYPE_VIEW_CARGO = 0x44960000,					//1200
                                                                ///////////////////////////////////////////////////////////////////////////
                                                                // shadow volumes 10000..
                                                                // edits  20000....
                                                                //////////////////////////////////////////////////////////////////////////
                                                                LODTYPE_GEOMETRY = 0x551184e7,					//10000000000000   1.0e13
                                                                LODTYPE_BOUYANCY = 0x559184e7,					//20000000000000   2e13
                                                                LODTYPE_PHYSX_OLD = 0x55da475b,					//30000000000000   3e13
                                                                LODTYPE_PHYSX = 0x561184e7,						//40000000000000   4.0e13
                                                                LODTYPE_MEMORY = 0x58635fa9,						//1000000000000000 1.0e15
                                                                LODTYPE_LAND_CONTACT = 0x58e35fa9,				//2000000000000000 2.0e15
                                                                LODTYPE_ROADWAY = 0x592a87bf,						//3000000000000000 3
                                                                LODTYPE_PATHS = 0x59635fa9,						//4000000000000000 4
                                                                LODTYPE_HITPOINTS = 0x598e1bca,					//5000000000000000 5
                                                                LODTYPE_VIEW_GEOMETRY = 0x59aa87bf,				//6000000000000000 6
                                                                LODTYPE_FIRE_GEOMETRY = 0x59c6f3b4,				//7000000000000000 7
                                                                LODTYPE_VIEW_CARGO_GEOMETRY = 0x59e35fa9,			//8000000000000000 8
                                                                LODTYPE_VIEW_CARGO_FIRE_GEOMETRY = 0x59ffcb9e,	//9000000000000000  9.0e15
                                                                LODTYPE_VIEW_COMMANDER = 0x5a0e1bca,				//10000000000000000 1.0e16
                                                                LODTYPE_VIEW_COMMANDER_GEOMETRY = 0x5a1c51c4,		//11000000000000000 1.1e16
                                                                LODTYPE_VIEW_COMMADER_FIRE_GEOMETRY = 0x5a2a87bf,	//12000000000000000 1.2e16
                                                                LODTYPE_VIEW_PILOT_GEOMETRY = 0x5a38bdb9,			//13000000000000000 1.3e16
                                                                LODTYPE_VIEW_PILOT_FIRE_GEOMETRY = 0x5a46f3b4,	//14000000000000000 1.4e16
                                                                LODTYPE_VIEW_GUNNER_GEOMETRY = 0x5a5529af,		//15000000000000000 1.5e16
                                                                LODTYPE_VIEW_GUNNER_FIRE_GEOMETRY = 0x5a635fa9,	//16000000000000000 1.6e16
                                                                LODTYPE_SUB_PARTS = 0x5a7195a4,					//17000000000000000 1.7e16
                                                                LODTYPE_SHADOW_VOLUME_VIEW_CARGO = 0x5a7fcb9e,	//18000000000000000 1.8e16
                                                                LODTYPE_SHADOW_VOLUME_VIEW_PILOT = 0x5a8700cc,	//19000000000000000,1.9e16
                                                                LODTYPE_SHADOW_VOLUME_VIEW_GUNNER = 0x5a8e1bca,	//20000000000000000 2.0e16
                                                                LODTYPE_WRECK = 0x5a9536c7,						//21000000000000000 2.1e16
        };

        class model_info {
        public:
            model_info();
            model_info(std::fstream &, const uint32_t lod_count);
            ~model_info();


        public:
            float               *lod_resolutions;//LodTypes[Header.NoOfLods];// alias resolutions
            uint32_t            index;                    // appears to be a bit flag, 512, 256 eg
            float               lod_sphere_mem;
            float               lod_sphere_geo;             // mostly same as MemLodSphere
            uint32_t            point_flags[3];            // typically 00 00 00 00  00 00 00 00 00 00 0C 00 eg (last is same as user point flags)
            ace::vector3<float>  offset_1;                   // model offset (unknown functionality),//mostly same as offset2
            uint32_t            map_icon_color;             // RGBA 32 color
            uint32_t            map_selected_color;         // RGBA 32 color
            float               view_density;              //

            ace::vector3<float>  bbox_min_pos;          // minimum coordinates of bounding box
            ace::vector3<float>  bbox_max_pos;          // maximum coordinates of bounding box. Generally the complement of the 1st
                                                        // pew.GeometryBounds in Pew is bboxMinPosition-bboxMaxPosition for X and Z
                                                        // pew.ResolutionBounds mostly the same
            ace::vector3<float>  center_of_gravity;          // pew.GeometryAutoCenterPos (and mostly pew.ResolutionAutoCenterPos too)
            ace::vector3<float>  offset_2;                  // mostly same as Offset1 often same as CentreOfGravity (but it isn't ResolutionPos)
            ace::vector3<float>  cog_offset;                // see below
            ace::vector3<float>  mass_vectors[3];      // for ODOL7 this is a mixture of floats and index values
                                                       //// if Arma3 /////////////////
            uint8_t             thermal_profile_2[24];
            ///////////////////////////////
            bool                autocenter;
            bool                lock_autocenter;
            bool                allow_occlude;
            bool                allow_occluded;
            bool                allow_animation;
            ///////////ARMA/VBS2 ////////////
            uint8_t             u_bytes_1[6];      //
            uint8_t             thermal_profile[24];       // 
            uint32_t            u_long_1;              // V48 and beyond
                                                        //uint8_t             thermal_profile[24];      // TOH only (v52) see above for arma3

            skeleton            skeleton;                 //

            uint8_t             u_byte_1;
            uint32_t            u_floats_1_size;                  // always zero for arma
            float               *u_floats_1;   // potentially compressed
            float               mass;
            float               mass_reciprocal;           // see note
            float               mass_alt;                  // see note
            float               mass_alt_reciprocoal;        // see note
            uint8_t             u_bytes_2[14];    // see note generally FF FF FF FF FF FF FF FF FF FF FF FF
            uint8_t             u_short_1;              // often same as NoOfLods
            bool                u_bool_1;              // generally set if ascii below has strings
            std::string         class_type;             // asciiz      ClassType;                // class="House" See Named Properties
            std::string         destruct_type;     //DestructType;             // damage="Tent" See Named Properties
            bool                u_bool_2;             // rarely true
            bool                u_bool_3;             // rarely true
            uint32_t            u_long_2;                  //
            uint8_t             *default_indicators;//default_indicators[NoOfLods][12]; //generally FF FF FF FF FF FF FF FF FF FF FF FF
        };


    };
};