#pragma once

#include "ace_common.h"

#include "vector.hpp"
#include "transform_matrix.hpp"
#include "compressed.hpp"

namespace ace {
    namespace p3d {

        class proxy {
        public:
            proxy();
            proxy(std::istream &);

            std::string                 name;        //"\ca\a10\agm65" (.p3d is implied) <<note the leading filename backslash
            ace::transform_matrix       transform;           //see Generic FileFormat Data Types
            uint32_t                    sequence_id;     //
            uint32_t                    named_selection_id; //see P3D Named Selections
                                                    //////// ARMA ONLY (ODOLV4x) ///////
            int32_t                     bone_id;
            uint32_t                    section_id;        //see P3D_Lod_Sections
        };

        class stage_texture {
        public:
            stage_texture();
            stage_texture(std::istream &, uint32_t);

            uint32_t    filter;
            std::string file;
            uint32_t    transform_id; 
            bool        wtf;
        };
 
        class material {
        public:
            material();
            material(std::istream &);

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
            
            std::vector<stage_texture> texture_stages;
            std::vector<std::pair<uint32_t, transform_matrix>> transform_stages;
        };

        class edge_set {
        public:
            std::vector<uint16_t> mlod;
            std::vector<uint16_t> vertex;
        };

        class face {
        public:
            face();
            face(std::istream &);

            uint32_t                         flags;            //ODOL7 ONLY see P3D Point and Face Flags
            uint16_t                         texture;         //ODOL7 ONLY
            uint8_t                          type;             // 3==Triangle or 4==Box
            std::vector<uint16_t>            vertex_table;
        };

        class section {
        public:
            section();
            section(std::istream &);

            uint32_t face_offsets[2];     // from / to region of LodFaces used
            uint32_t material_offsets[2]; // ODOLV4x only
            uint32_t common_points_user_value;  // see P3D Point and Face Flags
                                          // 0xC9 -> LodPoints 0x0C90003F
                                          // LodPointFlags are in a separate table for arma, and in the VertexTable for ofp (odol7)
            uint16_t common_texture;     //
            uint32_t common_face_flags;        // see P3D Point and Face Flags
                                          ///////// // ODOLV4x only//////
            int32_t  material_index;
            //if MaterialIndex == -1
           // {
            //    byte ExtraByte;
            //}
            uint8_t         extra;
            uint32_t        u_long_1;             // generally 2
            float           u_float_resolution_1;
            float           u_float_resolution_2;     // generally 1000.0
        };

        class named_selection {
        public:
            named_selection();
            named_selection(std::istream &);

            std::string                     name;                       // "rightleg" or "neck" eg
            std::vector<uint16_t>           faces;             // indexing into the LodFaces Table
            uint32_t                        Always0Count;
            bool                            is_selectional;                       //Appears in the sections[]= list of a model.cfg
            std::vector<uint32_t>           sections;          //IsSectional must be true. Indexes into the LodSections Table
            std::vector<uint16_t>           vertex_table;
            std::vector<uint8_t>            vertices_weights;  // if present they correspond to (are exentsions of) the VertexTableIndexes
        };

        class frame {
        public:
            frame();
            frame(std::istream &);

            float                               time;
            std::vector<ace::vector3<float>>    bone_positions;
        };

        class uv {
        public:
            uv();
            uv(std::istream &);

            float                           uv_scale[4];
            compressed<float>    data;
        };

        class c_vertex_table {
        public:
            c_vertex_table();
            c_vertex_table(std::istream &, uint32_t);
            
            uint32_t                         size;

            compressed<uint32_t>             point_flags;                     // Potentially compressed
            std::vector<uv>                  uvsets;

            std::vector<ace::vector3<float>> points;
            /*
            uint32_t                         NoOfPoints;
            
            uint32_t                         nNormals;
            (A2)LodNormals                LodNormals[nNormals];
            uint32_t                         nMinMax;
            (A2)LodMinMax                 MinMax[nMinMax];                   //optional
            uint32_t                         nProperties;
            VertProperty                  VertProperties[nProperties];       //optional related to skeleton
            uint32_t                         Count;
            UnknownVtxStruct              UnknownVtxStructs[Count];          //optional
            */
 
        };

        class lod_info {
        public:
            lod_info();
            lod_info(std::istream &, uint32_t);
            ~lod_info();

            uint32_t                            id;

            std::vector<proxy>                  proxies;              // see P3D Lod Proxies
            std::vector<uint32_t>               items;               // potentially compressed
            std::vector<std::vector<uint32_t>>  bone_links;
            uint32_t                            point_count;
            uint32_t                            u_float_1;
            
            float                               u_float_2;
            float                               u_float_3;
            ace::vector3<float>                 min_pos;
            ace::vector3<float>                 max_pos;
            ace::vector3<float>                 autocenter_pos;
            float                               sphere;                            // same as geo or mem values in modelinfo, if this lod is geo or memlod of course
            std::vector<std::string>            textures;  //"ca\characters\hhl\hhl_01_co.paa"
            std::vector<material>               materials;

            edge_set                            edges;
            
            uint32_t                            u_count;
            uint32_t                            offset_sections;            // see below
            uint16_t                            u_short_1;

            uint32_t                            faces_allocation_size;
            std::vector<face>                   faces;
            std::vector<section>                sections;

            std::vector<named_selection>        selections;

            std::map<std::string, std::string>  named_properties;

            std::vector<frame>                       frames;
            
            uint32_t                      icon_color;
            uint32_t                      selected_color;
            uint32_t                      u_residue;
            uint8_t                       u_byte_1;
            uint32_t                      vertex_table_size;

            c_vertex_table                  vertices;

            /*
                            //(including these 4 bytes)
            LodPointFlags                 LodPointFlags;                     // Potentially compressed
            VertexTable                   VertexTable;*/
        };


    }
}
