---
title: "Model Loading"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---
{% include mathJax.html %}

Let's import 3D models in to our application
<!--more-->

**Table of Contents**
* TOC
{:toc}

## Model Loading
In bigger graphics applications, there are usually lots of complicated and interesting models that are much prettier to look at than a static container. 

However, unlike the container object, we can't really manually define all the vertices, normals, and texture coordinates of complicated shapes like houses, vehicles, or human-like characters. 

What we want instead, is to import these models into the application; models that were carefully designed by 3D artists in tools like Blender, 3DS Max or Maya.

These so called 3D modeling tools allow artists to create complicated shapes and apply textures to them via a process called *uv-mapping.*

The tools then automatically generate all the vertex coordinates, vertex normals, and texture coordinates while exporting them to a model file format we can use. 
{: .notice--success}

and all the technical aspects are hidden in the exported model file.

It is our job to parse these exported model files and extract all the relevant information so we can store them in a format that OpenGL understands. 

A common issue is that there are dozens of different file formats where each exports the model data in its own unique way. 

Model formats like the `Wavefront .obj` only contains model data with minor material information like model colors and diffuse/specular maps, while model formats like the XML-based Collada file format are extremely extensive and contain models, lights, many types of materials, animation data, cameras, complete scene information, and much more. 

The wavefront object format is generally considered to be an *easy-to-parse model* format. 

Luckily for us, there just happens to be a library for this.

## Assimp
A very popular model importing library out there is called Assimp that stands for *Open Asset Import Library*.

Assimp is able to import dozens of different model file formats (and export to some as well) by loading all the model's data into Assimp's generalized data structures. 

As soon as Assimp has loaded the model, we can retrieve all the data we need from Assimp's data structures. 

Because the data structure of Assimp stays the **same**, regardless of the type of file format we imported, it abstracts us from all the different file formats out there.

When importing a model via Assimp it loads the entire model into a **scene** object that contains all the data of the imported model/scene. 

Assimp then has a collection of nodes where each node contains indices to data stored in the scene object where each node can have any number of children. A (simplistic) model of Assimp's structure is shown below:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl57.png)


* All the data of the scene/model is contained in the `Scene` object like all the materials and the meshes. It also contains a reference to the root node of the scene.
* The `Root node` of the scene may contain children nodes (like all other nodes) and could have a set of indices that point to mesh data in the scene object's `mMeshes` array. The scene's `mMeshes` array contains the actual Mesh objects, the values in the mMeshes array of a node are only indices for the scene's meshes array.
* A `Mesh` object itself contains all the relevant data required for rendering, think of vertex positions, normal vectors, texture coordinates, faces, and the material of the object.
* A mesh contains several faces. A `Face` represents a render primitive of the object (triangles, squares, points). A face contains the indices of the vertices that form a primitive. Because the vertices and the indices are separated, this makes it easy for us to render via an index buffer.
* Finally a mesh also links to a `Material` object that hosts several functions to retrieve the material properties of an object. Think of colors and/or texture maps (like diffuse and specular maps).


```cpp
aiScene
├── mRootNode (aiNode)
│   ├── mMeshes[]         --> indices into aiScene::mMeshes[]
│   ├── mChildren[]       --> aiNode[]
│         ├── mMeshes[]   --> more indices
│         └── ...
├── mMeshes[]             --> actual aiMesh objects
├── mMaterials[]          --> material info for meshes

```

**aiScene (Loaded from Assimp)**
Central container holding the entire scene.

Contains:
- $$mRootNode$$: root of the scene hierarchy
- $$mMeshes[]$$: actual mesh data
- $$mMaterials[]$$: actual material definitions

**aiNode (Scene Graph Node)**
Each node can:
- Have a transformation matrix ($$mTransformation$$)
- Refer to mesh indices (into $$scene \rightarrow mMeshes$$)
- Have child nodes (recursive tree structure)
- Used to represent scene hierarchies like parent-child relationships (e.g., bone or object hierarchies)

**aiMesh**
Contains:
- $$mVertices[]$$: positions
- $$mNormals[]$$: normals
- $$mTextureCoords[]$$: UVs
- $$mFaces[]$$: made up of indices (usually triangles)
- $$mMaterialIndex$$: index into $$scene \rightarrow mMaterials[]$$

**aiFace**
Contains:
- $$mNumIndices$$
- $$mIndices[]$$ → typically 3 indices for triangles
- Used to build the index buffer (EBO/IBO) for drawing

Example
Let's say `mVertices[]` has this:

```cpp
// vertex positions
0: (0, 0, 0)
1: (1, 0, 0)
2: (0, 1, 0)
3: (1, 1, 0)
```

And `mFaces[]` has:

```cpp
0: mIndices = [0, 1, 2]
1: mIndices = [1, 3, 2]
```

This means:
* Face 0 is a triangle formed by vertices 0 → 1 → 2
* Face 1 is a triangle formed by vertices 1 → 3 → 2

**aiMaterial**
Defines material properties:
- Colors (ambient, diffuse, specular, etc.)
- Texture maps (e.g., `AI_MATKEY_TEXTURE_DIFFUSE`)
- Shininess, transparency, etc.

### Why there are two `mMeshes[]` one in `aiScene` and one in `mRootNode`?

#### Global Mesh Storage (`scene->mMeshes[]`)

This is the main array of **actual mesh data** in the scene.

```cpp
const aiScene* scene = importer.ReadFile(...);
scene->mMeshes[i]; // Actual aiMesh*
```

It stores all the unique mesh objects in your imported model. These are shared and referenced from nodes.

Think of scene->mMeshes[] as the master list of all mesh data in the file.
{: .notice--success}

#### Mesh References (Indices into scene->mMeshes) (`node->mMeshes[]:`)

Each `aiNode` (like `scene->mRootNode`, or any child node) can contain:

```cpp
node->mMeshes[]; // Array of indices INTO scene->mMeshes[]
```

These are just integer indices, not mesh data. They point into the global mesh array: `scene->mMeshes[index]`.

Think of node->mMeshes[] as pointers that say “this node should render mesh X, Y, Z”.
{: .notice--success}

It's a Scene Graph + Resource Separation pattern:

Role              | What it stores                   | Where it's used
------------------|----------------------------------|-------------------------------
$$scene \rightarrow mMeshes$$ | The actual mesh geometry         | Global pool
$$node \rightarrow mMeshes$$  | Which meshes to render at this node | Scene hierarchy

So:

- All mesh data is stored once in $$scene \rightarrow mMeshes[]$$
- Each node can reference any number of these meshes via $$node \rightarrow mMeshes[]$$
- A mesh can even be used by multiple nodes (shared geometry)

### Loading Objects
What we want to do is: first load an object into a Scene object, **recursively** retrieve the corresponding Mesh objects from each of the nodes (we recursively search each node's children), and process each Mesh object to retrieve the vertex data, indices, and its material properties. 

The result is then a collection of mesh data that we want to contain in a single Model object.

When modeling objects in modeling toolkits, artists generally do not create an entire model out of a single shape. Usually, each model has several sub-models/shapes that it consists of. 

Each of those single shapes is called a mesh. Think of a human-like character: artists usually model the head, limbs, clothes, and weapons all as separate components, and the combined result of all these meshes represents the final model. 

A single mesh is the minimal representation of what we need to draw an object in OpenGL (vertex data, indices, and material properties). A model (usually) consists of several meshes.

If we then want to draw a model, we do not render the model as a whole, but we render all of the individual meshes that the model is composed of. However, before we can start importing models, we first need to actually include Assimp in our project.
{: .notice--warning}

## Mesh (part of a model)
With Assimp we can load many different models into the application, but once loaded they're all stored in Assimp's data structures. 

What we eventually want is to transform that data to a format that OpenGL understands so that we can render the objects. We learned from the previous chapter that a mesh represents a single drawable entity, so let's start by defining a mesh class of our own.

Let's review a bit of what we've learned so far to think about what a mesh should minimally have as its data. 

A mesh should at least need a set of vertices, where each vertex contains a 
* position vector 
* a normal vector
* a texture coordinate vector. 

A mesh should also contain indices for indexed drawing, and material data in the form of textures (diffuse/specular maps).

Now that we set the minimal requirements for a mesh class we can define a vertex in OpenGL:

```cpp
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
}
```

We store each of the required vertex attributes in a struct called `Vertex`. Next to a `Vertex` struct we also want to organize the texture data in a `Texture` struct:

```cpp
struct Texture {
    unsigned int id;
    string type; // e.g., "texture_diffuse"
}; 
```

We store the id of the texture and its type e.g. a diffuse or specular texture.

Knowing the actual representation of a vertex and a texture we can start defining the structure of the mesh class

```cpp
class Mesh {
    public:
        // mesh data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture>      textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  
```

Note that we give a shader to the `Draw` function; by passing the shader to the mesh we can set several uniforms before drawing (like linking samplers to texture units).
{: .notice--success}

The function content of the constructor is pretty straightforward.

```cpp
Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}
```

### Initialization
We do need to setup the appropriate buffers and specify the vertex shader layout via vertex attribute pointers. 

```cpp
void setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}  
```

#### Tip #01

Structs have a great property in C++ that their memory layout is **sequential**. That is, if we were to represent a struct as an array of data, it would only contain the struct's variables in sequential order which directly translates to a float (actually byte) array that we want for an array buffer. 

For example, if we have a filled Vertex struct, its memory layout would be equal to:

```cpp
Vertex vertex;
vertex.Position  = glm::vec3(0.2f, 0.4f, 0.6f);
vertex.Normal    = glm::vec3(0.0f, 1.0f, 0.0f);
vertex.TexCoords = glm::vec2(1.0f, 0.0f);
// = [0.2f, 0.4f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f];
```

Thanks to this useful property we can directly pass a pointer to a large list of Vertex structs as the buffer's data and they translate perfectly to what glBufferData expects as its argument:

```cpp
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
```

#### Tip #02

Naturally the `sizeof` operator can also be used on the struct for the appropriate size in bytes. This should be 32 bytes (8 floats * 4 bytes each).

#### Tip #03

Another great use of structs is a preprocessor directive called `offsetof(s,m)` that takes as its first argument a struct and as its second argument a variable name of the struct. 

The macro returns the byte offset of that variable from the start of the struct. This is perfect for defining the offset parameter of the `glVertexAttribPointer` function:

```cpp
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));  
```

The offset is now defined using the `offsetof` macro that, in this case, sets the byte offset of the normal vector equal to the byte offset of the normal attribute in the struct which is 3 floats and thus 12 bytes.

Using a struct like this doesn't only get us more readable code, but also allows us to easily extend the structure. If we want another vertex attribute we can simply add it to the struct and due to its flexible nature, the rendering code won't break.
{: .notice--success}

### Rendering
The last function we need to define for the `Mesh` class to be complete is its `Draw` function. Before rendering the mesh, we first want to bind the appropriate textures before calling `glDrawElements`. 

However, this is somewhat difficult since we don't know from the start how many (if any) textures the mesh has and what type they may have. 

So how do we set the texture units and samplers in the shaders?

To solve the issue we're going to assume a certain naming convention: each diffuse texture is named `texture_diffuseN`, and each specular texture should be named `texture_specularN` where `N` is any number ranging from 1 to the maximum number of texture samplers allowed.

Let's say we have 3 diffuse textures and 2 specular textures for a particular mesh, their texture samplers should then be called:

```cpp
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
```

By this convention we can define as many texture samplers as we want in the shaders (up to OpenGL's maximum) and if a mesh actually does contain (so many) textures, we know what their names are going to be. 

By this convention we can process any amount of textures on a single mesh and the shader developer is free to use as many of those as he wants by defining the proper samplers.

The resulting drawing code then becomes:

```cpp
void Draw(Shader &shader) 
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
```

We first calculate the N-component per texture type and concatenate it to the texture's type string to get the appropriate uniform name. 

We then locate the appropriate sampler, give it the location value to correspond with the currently active texture unit, and bind the texture. 

This is also the reason we need the shader in the Draw function.

We also added **"material."** to the resulting uniform name because we usually store the textures in a material struct (this may differ per implementation)

The `Mesh` class we just defined is an abstraction for many of the topics we've discussed in the early chapters. In the next chapter we'll create a model that acts as a container for several mesh objects and implements Assimp's loading interface.

## Model (combination of all meshes)

The goal of this chapter is to create another class that represents a model in its entirety, that is, a model that contains multiple meshes, possibly with multiple textures.

A house, that contains a wooden balcony, a tower, and perhaps a swimming pool, could still be loaded as a single model. 

We'll load the model via Assimp and translate it to multiple Mesh objects we've created in the previous chapter.

Model class:

```cpp
class Model 
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader &shader);	
    private:
        // model data
        vector<Mesh> meshes;
        string directory;

        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName);
};
```

The `Model` class contains a vector of Mesh objects and requires us to give it a file location in its constructor. It then loads the file right away via the `loadModel` function that is called in the constructor. 

The private functions are all designed to process a part of Assimp's import routine and we'll cover them shortly. 

We also store the directory of the file path that we'll later need when loading textures.

The `Draw` function is nothing special and basically loops over each of the meshes to call their respective `Draw` function:

```cpp
void Draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}
```

### Importing a 3D model into OpenGL
To import a model and translate it to our own structure, we first need to include the appropriate headers of Assimp:

```cpp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
```

The first function we're calling is `loadModel`, that's directly called from the constructor. Within `loadModel`, we use Assimp to load the model into a data structure of Assimp called a **scene object**. 

You may remember from the first chapter of the model loading series that this is the root object of Assimp's data interface. Once we have the scene object, we can access all the data we need from the loaded model.

```cpp
Assimp::Importer importer;
const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
```

We first declare an Importer object from Assimp's namespace and then call its `ReadFile` function. 

The function expects a file path and several *post-processing* options as its second argument. 

Assimp allows us to specify several options that forces Assimp to do extra calculations/operations on the imported data. 

By setting `aiProcess_Triangulate` we tell Assimp that if the model does not (entirely) consist of triangles, it should transform all the model's primitive shapes to triangles first. 

The `aiProcess_FlipUVs` flips the texture coordinates on the y-axis where necessary during processing (you may remember from the Textures chapter that most images in OpenGL were reversed around the y-axis; this little postprocessing option fixes that for us). 

A few other useful options are:

* `aiProcess_GenNormals`: creates normal vectors for each vertex if the model doesn't contain normal vectors.
* `aiProcess_SplitLargeMeshes`: splits large meshes into smaller sub-meshes which is useful if your rendering has a maximum number of vertices allowed and can only process smaller meshes.
* `aiProcess_OptimizeMeshes` : does the reverse by trying to join several meshes into one larger mesh, reducing drawing calls for optimization

The hard work is in using the returned scene object to translate the loaded data to an array of Mesh objects.

The complete loadModel function is listed here:

```cpp
void loadModel(string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}  
```

After we load the model, we check if the scene and the root node of the scene are not null and check one of its flags to see if the returned data is incomplete. 

If any of these error conditions are met, we report the error retrieved from the importer's `GetErrorString` function and return. We also retrieve the directory path of the given file path.

If nothing went wrong, we want to process all of the scene's nodes. We pass the first node (root node) to the recursive `processNode` function.

Because each node (possibly) contains a set of children we want to first process the node in question, and then continue processing all the node's children and so on. 

This fits a recursive structure, so we'll be defining a recursive function with the exit condition is met when all nodes have been processed.

As you may remember from Assimp's structure, each node contains a set of **mesh indices** where each index points to a specific mesh located in the **scene** object. 

We thus want to retrieve these mesh indices, retrieve each mesh, process each mesh, and then do this all again for each of the node's children nodes. The content of the `processNode` function is shown below:

```cpp
void processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  
```

We first check each of the node's mesh indices and retrieve the corresponding mesh by indexing the scene's `mMeshes` array. 

The returned mesh is then passed to the `processMesh` function that returns a Mesh object that we can store in the meshes list/vector.

Once all the meshes have been processed, we iterate through all of the node's children and call the same `processNode` function for each its children. Once a node no longer has any children, the recursion stops.

### Assimp to Mesh
Translating an `aiMesh` object to a mesh object of our own is not too difficult. All we need to do, is access each of the mesh's relevant properties and store them in our own object. The general structure of the `processMesh` function then becomes:

```cpp
Mesh processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        [...]
        vertices.push_back(vertex);
    }
    // process indices
    [...]
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        [...]
    }

    return Mesh(vertices, indices, textures);
}  
```

Processing a mesh is a 3-part process: 
1. retrieve all the vertex data
2. retrieve the mesh's indices
3. retrieve the relevant material data. 

The processed data is stored in one of the 3 vectors and from those a Mesh is created and returned to the function's caller.

```cpp
glm::vec3 vector; 
vector.x = mesh->mVertices[i].x;
vector.y = mesh->mVertices[i].y;
vector.z = mesh->mVertices[i].z; 
vertex.Position = vector;
```

Note that we define a temporary vec3 for transferring Assimp's data to. This is necessary as Assimp maintains its own data types for vector, matrices, strings etc. and they don't convert that well to glm's data types.

The procedure for normals

```cpp
vector.x = mesh->mNormals[i].x;
vector.y = mesh->mNormals[i].y;
vector.z = mesh->mNormals[i].z;
vertex.Normal = vector; 
```

Texture coordinates are roughly the same, but Assimp allows a model to have up to 8 different texture coordinates per vertex. 

We're not going to use 8, we only care about the first set of texture coordinates. 

We'll also want to check if the mesh actually contains texture coordinates (which may not be always the case):

```cpp
if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
{
    glm::vec2 vec;
    vec.x = mesh->mTextureCoords[0][i].x; 
    vec.y = mesh->mTextureCoords[0][i].y;
    vertex.TexCoords = vec;
}
else
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
```

The vertex struct is now completely filled with the required vertex attributes and we can push it to the back of the `vertices` vector at the end of the iteration. This process is repeated for each of the mesh's vertices.

#### Indices
Assimp's interface defines each mesh as having an array of faces, where each face represents a **single primitive**, which in our case (due to the `aiProcess_Triangulate` option) are always triangles. 

A face contains the indices of the vertices we need to draw in what order for its primitive. So if we iterate over all the faces and store all the face's indices in the `indices` vector we're all set:

```cpp
for(unsigned int i = 0; i < mesh->mNumFaces; i++)
{
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
}  
```

After the outer loop has finished, we now have a complete set of vertices and index data for drawing the mesh via `glDrawElements`. However, to finish the discussion and to add some detail to the mesh, we want to process the mesh's material as well.

#### Material
Similar to nodes, a mesh only contains an **index** to a material object. To retrieve the material of a mesh, we need to index the scene's `mMaterials` array. The mesh's material index is set in its `mMaterialIndex` property, which we can also query to check if the mesh contains a material or not:

```cpp
if(mesh->mMaterialIndex >= 0)
{
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, 
                                        aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
}  
```

We first retrieve the `aiMaterial` object from the scene's mMaterials array. 

Then we want to load the mesh's diffuse and/or specular textures. A material object internally stores an array of texture locations for each texture type. 

The different texture types are all prefixed with `aiTextureType_`. We use a helper function called `loadMaterialTextures` to retrieve, load, and initialize the textures from the material. 

The function returns a vector of Texture structs that we store at the end of the model's `textures` vector.

The `loadMaterialTextures` function iterates over all the texture locations of the given texture type, retrieves the texture's file location and then loads and generates the texture and stores the information in a Vertex struct. It looks like this:

```cpp
vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}  
```

We first check the amount of textures stored in the material via its `GetTextureCount` function that expects one of the texture types we've given. 

We retrieve each of the texture's file locations via the `GetTexture` function that stores the result in an `aiString`. We then use another helper function called `TextureFromFile` that loads a texture (with stb_image.h) for us and returns the texture's ID. 

You can check the complete code listing at the end for its content if you're not sure how such a function is written.

#### An optimization
We're not completely done yet, since there is still a large (but not completely necessary) optimization we want to make. 

Most scenes **re-use** several of their textures onto several meshes; think of a house again that has a granite texture for its walls. 

This texture could also be applied to the floor, its ceilings, the staircase, perhaps a table, and maybe even a small well close by.

Loading textures is not a cheap operation and in our current implementation a new texture is loaded and generated for each mesh, even though the exact same texture could have been loaded several times before. 

This quickly becomes the bottleneck of your model loading implementation.

So we're going to add one small tweak to the model code by storing all of the loaded textures globally. Wherever we want to load a texture, we first check if it hasn't been loaded already. If so, we take that texture and skip the entire loading routine, saving us a lot of processing power. To be able to compare textures we need to store their path as well:
{: .notice--success}

```cpp
struct Texture {
    unsigned int id;
    string type;
    string path;  // we store the path of the texture to compare with other textures
};
```

Then we store all the loaded textures in another vector declared at the top of the model's class file as a private variable:

```cpp
vector<Texture> textures_loaded; 
```

In the `loadMaterialTextures` function, we want to compare the texture path with all the textures in the textures_loaded vector to see if the current texture path equals any of those. 

If so, we skip the texture loading/generation part and simply use the located texture struct as the mesh's texture. The (updated) function is shown below:

```cpp
vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; 
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
} 
```

Now, declare a `Model` object and pass in the model's file location. The model should then automatically load and (if there were no errors) render the object in the render loop using its `Draw` function and that is it. 

No more buffer allocations, attribute pointers, and render commands, just a simple one-liner. If you create a simple set of shaders where the fragment shader only outputs the object's diffuse texture, the result looks a bit like this:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl58.png)
