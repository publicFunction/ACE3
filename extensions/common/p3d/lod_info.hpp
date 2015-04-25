#pragma once

#include "ace_common.h"

#include "vector.hpp"
#include "transform_matrix.hpp"
#include "compressed_fill.hpp"

namespace ace {
    namespace p3d {
        class proxy {
        public:
            proxy();
            proxy(std::fstream &);

            std::string                 name;        //"\ca\a10\agm65" (.p3d is implied) <<note the leading filename backslash
            ace::transform_matrix       transform;           //see Generic FileFormat Data Types
            uint32_t                    sequence_id;     //
            uint32_t                    named_selection_id; //see P3D Named Selections
                                                    //////// ARMA ONLY (ODOLV4x) ///////
            int32_t                     bone_id;
            uint32_t                    section_id;        //see P3D_Lod_Sections
        };

        class material {
        public:
            material();
            material(std::fstream &);

            std::string                 name;
            std::string                 surface;

            uint32_t    render_flags;
            uint32_t	type;

            float		emissive[4];
            float		ambient[4];
            float		diffuse[4];
            float		forced_diffuse[4];
            float		specular[4];
            float		specular_2[4];
            float		specular_power;

            uint32_t	pixel_shader;
            uint32_t	vertex_shader;

            uint32_t	u_long_1; 
            uint32_t	an_index;
            uint32_t    u_long_2;
            uint32_t    u_long_3;
            
        };

        class edge {};

        class lod_info
        {
        public:
            lod_info();
            lod_info(std::fstream &);
            ~lod_info();

            std::vector<proxy>                  proxies;              // see P3D Lod Proxies
            std::vector<uint32_t>               items;               // potentially compressed
            std::vector<std::vector<uint32_t>>  bone_links;
            uint32_t                            point_count;
            uint32_t                            u_float_1;
            compressed_fill<uint32_t>           point_flags;                     // Potentially compressed
            
            float                               u_float_2;
            float                               u_float_3;
            ace::vector3<float>                 min_pos;
            ace::vector3<float>                 max_pos;
            ace::vector3<float>                 autocenter_pos;
            float                               sphere;                            // same as geo or mem values in modelinfo, if this lod is geo or memlod of course
            std::vector<std::string>            textures;  //"ca\characters\hhl\hhl_01_co.paa"
            std::vector<material>               materials;

            std::vector<edge>                   edges;
                                                     /*
            LodEdges                      LodEdges;                          // compressed see P3D Lod Edges
            uint32_t                      NoOfFaces;
            uint32_t                      OffsetToSectionsStruct;            // see below
            uint16_t                      AlwaysZero;
            LodFace                       LodFace[NoOfFaces];                // see P3D Lod Faces
            uint32_t                      nSections;
            LodSection                    LodSections[nSections];            // see P3D Lod Sections
            uint32_t                      nNamedSelections;
            LodNamedSelection             LodNamedSelections[nNamedSelections]; //See P3D Named Selections potentially compressed
            uint32_t                      nTokens;
            NamedProperty                 NamedProperties[nTokens];          //See Named Properties
            uint32_t                      nFrames;
            LodFrame                      LodFrames[nFrames];                //see P3D Lod Frames
            uint32_t                      IconColor;
            uint32_t                      SelectedColor;
            uint32_t                      UnknownResidue;
            uint8_t                       UnknownArmaByte;
            uint32_t                      sizeOfVertexTable;                 //(including these 4 bytes)
            LodPointFlags                 LodPointFlags;                     // Potentially compressed
            VertexTable                   VertexTable;*/
        };


    }
}
