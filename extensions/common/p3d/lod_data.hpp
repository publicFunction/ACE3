#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    namespace p3d {
        class lod_proxy {
        public:
            struct
            {
                std::string                 name;        //"\ca\a10\agm65" (.p3d is implied) <<note the leading filename backslash
                ace::transform_matrix       Transform;           //see Generic FileFormat Data Types
                uint32_t                    sequence_id;     //
                uint32_t                    named_selection_id; //see P3D Named Selections
                                                     //////// ARMA ONLY (ODOLV4x) ///////
                int32_t                     bone_id;
                uint32_t                    section_id;        //see P3D_Lod_Sections
            }
        };

        class lod_info
        {
        public:
            lod_info();
            lod_info(std::fstream &);
            ~lod_info();

            std::vector<lod_proxy>        proxies;              // see P3D Lod Proxies
            //uint32_t                      nLodItems;
            std::vector<uint32_t>         items;               // potentially compressed
           // uint32_t                      nBoneLinks;
            /**
            LodBoneLink                   LodBoneLinks[nBoneLinks];
            uint32_t                      LodPointCount;
            LodPointFlags                 LodPointFlags;                     // Potentially compressed
            float                         UnknownFloat1;
            float                         UnknownFloat2;
            ace::vector3<float>           MinPos;
            ace::vector3<float>           MaxPos;
            ace::vector3<float>           AutoCenterPos;
            float                         Sphere;                            // same as geo or mem values in modelinfo, if this lod is geo or memlod of course
            uint32_t                      NoOfTextures;
            std::vector<std::string>      LodPaaTextureNames;  //"ca\characters\hhl\hhl_01_co.paa"
            uint32_t                      NoOfMaterials;
            LodMaterial                   LodMaterials[NoOfMaterials];
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
