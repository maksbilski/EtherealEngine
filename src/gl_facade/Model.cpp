#include "Model.hpp"

Model::Model(std::string const &filepath, bool gamma)
    : m_gammaCorrection(gamma) {
  loadModel(filepath);
}

void Model::draw(Shader &shader) {
  for (unsigned int i = 0; i < m_meshes.size(); i++)
    m_meshes[i].draw(shader);
}

void Model::loadModel(std::string const &path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    return;
  }
  m_directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // the node object only contains indices to index the actual objects in
    // the scene. the scene contains all the data, node is just to keep stuff
    // organized (like relations between nodes).
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(processMesh(mesh, scene));
  }
  // after we've processed all of the meshes (if any) we then recursively
  // process each of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }
    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vec;
      // tangent
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.tangent = vector;
      // bitangent
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.bitangent = vector;
    } else
      vertex.texCoords = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }
  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

  std::vector<Texture> diffuseMaps =
      loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  // 2. specular maps
  std::vector<Texture> specularMaps = loadMaterialTextures(
      material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  // 3. normal maps
  std::vector<Texture> normalMaps =
      loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  // 4. height maps
  std::vector<Texture> heightMaps =
      loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat,
                                                 aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);

    bool skip = false;
    for (unsigned int j = 0; j < m_texturesLoaded.size(); j++) {
      if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
        textures.push_back(m_texturesLoaded[j]);
        skip = true;

        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), this->m_directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      m_texturesLoaded.push_back(texture);
    }
  }
  return textures;
};

unsigned int TextureFromFile(const char *filepath,
                             const std::string &directory) {
  std::string filename = std::string(filepath);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 0)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << filepath << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

Cylinder Model::getBoundingCylinder() const {
  if (m_boundingCylinder.has_value()) {
    return m_boundingCylinder.value();
  } else {
    throw std::runtime_error("Tried to access uninitialized bounding cylinder");
  }
}

Sphere Model::getBoundingSphere() const {
  if (m_boundingSphere.has_value()) {
    return m_boundingSphere.value();
  } else {
    throw std::runtime_error("Tried to access uninitialized bounding sphere");
  }
}

glm::vec3 Model::calculateCenter() const {
  glm::vec3 center(0.0f);
  int totalVertices = 0;
  for (auto &mesh : m_meshes) {
    for (auto &vertex : mesh.vertices) {
      center += vertex.position;
      totalVertices++;
    }
  }
  return center / static_cast<float>(totalVertices);
}

void Model::calculateBoundingShapesCenters() {
  m_boundingCylinder = Cylinder();
  m_boundingSphere = Sphere();

  m_boundingCylinder->axis = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 center = calculateCenter();
  m_boundingCylinder->center = center;
  m_boundingSphere->center = center;
}

void Model::calculateBoundingShapes() {
  calculateBoundingShapesCenters();

  float maxHeight = -FLT_MAX;
  float minHeight = FLT_MAX;
  float maxRadiusSq = -FLT_MAX;
  float maxRadiusSqSphere = -FLT_MAX;

  for (const auto &mesh : m_meshes) {
    for (const auto &vertex : mesh.vertices) {
      glm::vec3 projectedVertex =
          glm::dot(vertex.position - m_boundingCylinder->center,
                   m_boundingCylinder->axis) *
              m_boundingCylinder->axis +
          m_boundingCylinder->center;

      float distance =
          glm::distance(m_boundingCylinder->center, projectedVertex);
      maxHeight = glm::max(maxHeight, distance);
      minHeight = glm::min(minHeight, distance);

      glm::vec3 radiusVector = vertex.position - projectedVertex;
      maxRadiusSq = glm::max(maxRadiusSq, glm::dot(radiusVector, radiusVector));

      glm::vec3 sphereRadiusVector = vertex.position - m_boundingSphere->center;
      maxRadiusSqSphere = glm::max(
          maxRadiusSqSphere, glm::dot(sphereRadiusVector, sphereRadiusVector));
    }
  }

  m_boundingCylinder->height = maxHeight - minHeight;
  m_boundingCylinder->radius = glm::sqrt(maxRadiusSq);
  m_boundingSphere->radius = glm::sqrt(maxRadiusSqSphere);
}