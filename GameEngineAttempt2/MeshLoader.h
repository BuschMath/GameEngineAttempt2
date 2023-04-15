#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

class MeshLoader {
public:
    MeshLoader() {}
    ~MeshLoader() {}

    bool LoadMesh(const std::string& filePath) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            // Error handling: failed to load mesh file
            return false;
        }

        // Process mesh data
        ProcessNode(scene->mRootNode, scene);

        return true;
    }

    const std::vector<float>& GetVertices() const { return m_vertices; }
    const std::vector<unsigned int>& GetIndices() const { return m_indices; }

private:
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    void ProcessNode(const aiNode* node, const aiScene* scene) {
        // Process all meshes in the node
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(mesh, scene);
        }

        // Process child nodes recursively
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    void ProcessMesh(const aiMesh* mesh, const aiScene* scene) {
        // Process vertex positions
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            const aiVector3D& vertex = mesh->mVertices[i];
            m_vertices.push_back(vertex.x);
            m_vertices.push_back(vertex.y);
            m_vertices.push_back(vertex.z);
        }

        // Process face indices
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            if (face.mNumIndices != 3) {
                // Only support triangles
                continue;
            }
            m_indices.push_back(face.mIndices[0]);
            m_indices.push_back(face.mIndices[1]);
            m_indices.push_back(face.mIndices[2]);
        }
    }
};

#endif // MESH_LOADER_H
