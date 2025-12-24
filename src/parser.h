// .bin
// 1 int size camera
// camera
// 1 byte number of lighting
// 1 byte number of objects
// 1 int size light or object
// у объекта может быть материал, но пока он отсутствует
// if object has triangles, в нем будут указаны адресса расположения геометрических данных, они будут идти в конце файла 

void parse_material();
void parse_object();
void parse_light();
void parse_scene();