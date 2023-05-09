# Raytracer

Initially developed for the CSCI 5607 course at the University of Minnesota - Twin Cities.

## Supports the following features:
- Spheres
- 3D models in `.obj` format
- Point and directional lights
- Shading
- Shadows
- Illumination via [Phong Illumination Model](https://en.wikipedia.org/wiki/Phong_reflection_model)
- Texture mapping
- Reflections
- Refractions

## How to run:
Scene descriptor files are to be imported into the `/resource` folder.

Sample scene descriptor files are provided already.

### Run Steps
- Build program with `make`
- Run `make run filepath=INSERT_FILE_PATH` with `/resourses` to file argument or run generated `raytracing` executible with a scene descriptor file command line argument

### Scene Descriptor Format
Scene descriptor files are made up of a series of attributes seperated by newlines. Attributes can be associated with other attributes.
All colors channels (RGB) are defined on a scale of \[0.0, 1.0\].
<br><br>
Scene descriptor files are to be stored as `.txt` files.

| attribute | description |
| --------- | ----------- |
| **eye** x y z | Positions eye at the point (x, y, z). |
| **viewdir** x_dir y_dir z_dir | Alligns view direction vector with (x_dir, y_dir, z_dir). |
| **updir** x_up y_up z_up | Alligns up direction vector with (x_up, y_up, z_up). |
| **hfov** hfov_degrees | Sets horizontal field of view to hfov_degrees degrees. |
| **imsize** width height | Sets dimensions of rendered image to width and height. |
| **bkgcolor** r g b | Sets background color to (r, g, b). |
| **light** x y z r g b point | Creates a light of a color (r,g, b), if point == 0 then light is a point light source at (x, y, z), else directional light with directional vector (x, y, z). |
| **mtlcolor** r_diffuse g_diffuse b_diffuse r_specular g_specular b_specular ambient diffuse specular n | Creates a material color of ambient color (r_diffuse g_diffuse b_diffuse), diffuse color (r_diffuse g_diffuse b_diffuse), and specular color (r_specular, g_specular, b_specular). ambient defines the intensity the ambient color, diffuse defines the intensity of the diffuse color, specular defines the intensity of the specular hightlight (all on a scale \[0.0-1.0\]). n definies falloff of specular hightlight on a scale of \[0.0-max size of double\]. All scene objects after **mtlcolor** will have the material color applied to them. |
| **texture** texture_path | Creates a texture defined at a file at texure_path (must be a `.ppm` file). All scene objects after **texture** will have the texture applied to them. |
| **sphere** x y z r | Creates a sphere scene object at position (x, y, z) with a radius r. |
| **v**  x_dir y_dir z_dir | Defines a vertex at point (x, y, z). |
| **vn** x y z | Defines a vertex normal in direction (x_dir, y_dir, z_dir). |
| **vt** u v | Defines a vertex texture coordinate at texture point (u, v). |
| **f** v0/vn0/vt0 v1/vn1/vt1 v2/vn2/vt2 | Defines a triangle scene object with vertices (verticies\[v0\], vertices\[v1\], vertices\[v2\]), where vertices is the list of vertices in the order defined in file with the v0, v1, and v2 being indices of the vertices. Normals for each vertex is defnined as (normals\[vn0\], normals\[vn1\], normals\[vn2\]), where normals is the list of normals in the order defined in file with vn0, vn1, and vn2 being indices of the normals. Texture coordinates for each vertex is defnined as (texure_coords\[vt0\], texure_coords\[vt1\], texure_coords\[vt2\]), where texure_coords is the list of texture coordinates in the order defined in file with vt0, vt1, and vt2 being indices of the texture coordinates. **f** can be defined without vertex normals as **f** v0/vt0 v1/vt1 v2/vt2. |
