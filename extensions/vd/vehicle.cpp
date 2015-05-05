#pragma once

#include "vehicle.hpp"
#include "controller.hpp"

using namespace ace::simulation;

namespace ace {
    namespace vehicledamage {
        vehicle::vehicle(uint32_t id, ace::simulation::object_p object_) : object(object_) {
            bt_mesh = std::make_shared<btTriangleMesh>();
            
            // Build the mesh from object faces
            // TODO: LOD!?
            // P3d store in x,z,y format
            for (auto & face : object_->lods[6]->faces) {
                bt_mesh->addTriangle(
                    btVector3(face->vertices[0]->x(), face->vertices[0]->z(), face->vertices[0]->y()),
                    btVector3(face->vertices[1]->x(), face->vertices[1]->z(), face->vertices[1]->y()),
                    btVector3(face->vertices[2]->x(), face->vertices[2]->z(), face->vertices[2]->y())
                );
            }

            bt_shape = std::make_shared<btBvhTriangleMeshShape>(bt_mesh.get(), true, true);

            bt_object = std::make_shared<btCollisionObject>();
            bt_object->setCollisionShape(bt_shape.get());
            
            bt_object->setUserIndex(id);
            bt_object->setUserPointer((void *)this);

            controller::get().bt_world->addCollisionObject(bt_object.get());
        }
        vehicle::~vehicle() {
            controller::get().bt_world->removeCollisionObject(bt_object.get());
        }

        float vehicle::thickness(const ace::vector3<float> & position, const ace::vector3<float> & direction) {
            float result = -1.0f;

            btVector3 bt_from(position.x(), position.y(), position.z());
            btVector3 bt_dir(direction.x(), direction.y(), direction.z());
            btVector3 bt_to(bt_from + (bt_dir * 100));

            btCollisionWorld::AllHitsRayResultCallback allResults(bt_from, bt_to);
            controller::get().bt_world->rayTest(bt_from, bt_to, allResults);

            // get the first and last result on the target object, give results
            assert(allResults.m_hitPointWorld.size() == 2);

            if (allResults.m_hitPointWorld.size() == 2) {
                result = allResults.m_hitPointWorld[0].distance(allResults.m_hitPointWorld[1]);
            } else {
                // @TODO:
                // We dont support multi-surface hits yet
                
            }

            return result;
        }

        std::vector<ace::vector3<float>> vehicle::selection_position(const uint32_t lod, const std::string &name, const SELECTION_SEARCH_TYPE searchType) {
            named_selection_p selection;
            std::vector<ace::vector3<float>> result;

            if ((selection = selection_by_name(lod, name)) == nullptr)
                return result;

            switch (searchType) {
                case SELECTION_SEARCH_TYPE::AVERAGE_CENTER: {
                    ace::vector3<float> average;
                    std::vector<ace::vector3<float>> results;

                    for (auto & a : selection->vertices) {
                        for (auto & b : selection->vertices) {
                            if (a != b) {
                                average = average + ace::vector3<float>::lerp(static_cast<ace::vector3<float>>(*a), static_cast<ace::vector3<float>>(*b), 0.5f);
                            }
                        }
                    }

                    average = average / results.size();
                    result.push_back(average);

                    break;
                }  
            }
            

            return result;
        }
        std::vector<ace::vector3<float>> vehicle::selection_by_name_vertices(const uint32_t lod, const std::string &name) {
            std::vector<ace::vector3<float>> result;

            ace::simulation::named_selection_p selection = selection_by_name(lod, name);

            for (auto & vertex : selection->vertices) {
                result.push_back( static_cast<ace::vector3<float>>(*vertex) );
            }

            return result;
        }
        ace::simulation::named_selection_p vehicle::selection_by_name(const uint32_t lod, const std::string &name) {
            named_selection_p result;
            
            if (lod != -1) {
                std::map<std::string, named_selection_p>::iterator iter = object->lods[lod]->selections.find(name);
                if (iter == object->lods[lod]->selections.end()) {
                    return nullptr;
                }
                result = iter->second;
            } else {
                for (auto & lod : object->lods) {
                    std::map<std::string, named_selection_p>::iterator iter = lod.second->selections.find(name);
                    if (iter == lod.second->selections.end()) {
                        continue;
                    } else {
                        result = iter->second;
                    }
                    
                }
            }

            return result;
        }
    }
};