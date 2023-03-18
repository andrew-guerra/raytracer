#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <math.h>
#include <vector>

#include "PPMGenerator.h"
#include "vectors.h"

#define REQUIRED_KEYWORDS {"eye", "viewdir", "updir", "hfov", "imsize", "bkgcolor"}
#define NUM_REQUIRED_KEYWORDS 6
#define NUM_OPTIONAL_KEYWORDS 9

using namespace std;

static string requiredKeywords[] = {"eye", "viewdir", "updir", "hfov", "imsize", "bkgcolor"};
static string optionalKeywords[] = {"mtlcolor", "light", "attlight", "depthcueing", "spiral", "projection", "sphere", "triangle", "texture"};


// returns if string text is a valid file name
bool isFileName(string text) {
	// uses regex pattern to ensure valid file name 
	return regex_match(text, regex("[a-zA-Z0-9\\-_]+\\.[a-zA-Z]+"));
}

// returns if string text is an integer
bool isInt(string text) {
	return regex_match(text, regex("[+-]?[0-9]+"));
}

bool isFloat(string text) {
	return regex_match(text, regex("[+-]?([0-9]*[.])?[0-9]+"));
}

// returns bool of if next string is a keyword
bool validateKeyword(ifstream& specFileStream, string keyword) {
	string input;
	specFileStream >> input;

	return input == keyword;
}

bool getVector(ifstream& specFileStream, vector3_t& vector) {
	string x, y, z;

	if(specFileStream.peek() == EOF) {
		cout << "Invalid vector format for ";
		return false;
	}
	specFileStream >> x;

	if(specFileStream.peek() == EOF || !isFloat(x)) {
		cout << "Invalid vector format for ";
		return false;
	}
	specFileStream >> y;

	if(specFileStream.peek() == EOF || !isFloat(y)) {
		cout << "Invalid vector format for ";
		return false;
	}
	specFileStream >> z;

	if(!isFloat(z)) {
		cout << "Invalid vector format for ";
		return false;
	}

	vector.x = stof(x);
	vector.y = stof(y);
	vector.z = stof(z);

	return true;
} 

bool getHorizontalFOV(ifstream& specFileStream, float& horizontalFOV) {
	string fov;
	
	if(specFileStream.peek() == EOF) {
		cout << "Invalid fov format" << endl;
		return false;
	}
	specFileStream >> fov;

	if(!isFloat(fov)) {
		cout << "Invalid fov format" << endl;
		return false;
	}

	horizontalFOV = stof(fov);

	return true;
}

// returns integer dimensions in integer pointer in form [width, height]
// returns NULL if invalid inputs
bool getImageDimensions(ifstream& specFileStream, sceneSpecs_t& sceneSpecs) {
	string width, height;
	
	if(specFileStream.peek() == EOF) {
		cout << "Invalid dimensions format" << endl;
		return false;
	}

	// reads in width and height
	specFileStream >> width;

	if(specFileStream.peek() == EOF) {
		cout << "Invalid dimensions format" << endl;
		return false;
	}

	specFileStream >> height;
	
	// checks to ensure width and height are well formed integers
	if(!(isInt(width) && isInt(height))) {
		cout << "Program expected integers for width and height" << endl;
		return false;
	}

	// parse dimensions and place in pointer
	sceneSpecs.imageWidth = stoi(width);
	sceneSpecs.imageHeight = stoi(height);

	return true;
} 

// returns true is color was properly read from fileStream into color reference
bool getColor(ifstream& specFileStream, color_t& color) {
	string red, green, blue;
	float redFloat, greenFloat, blueFloat;
	
	if(specFileStream.peek() == EOF) {
		cout << "Invlaid color format ";
		return false;
	}
	specFileStream >> red;

	if(specFileStream.peek() == EOF) {
		cout << "Invlaid color format for ";
		return false;
	}
	specFileStream >> green;

	if(specFileStream.peek() == EOF) {
		cout << "Invlaid color format for ";
		return false;
	}
	specFileStream >> blue;

	if(!(isFloat(red) && isFloat(green) && isFloat(blue))) {
		cout << red << " " << green << " " << blue << std::endl;
		cout << "Program expected floats for red, green, and blue for ";
		return false;
	}
	
	redFloat = stof(red);
	greenFloat = stof(green);
	blueFloat = stof(blue);
	
	if((redFloat < 0 || redFloat > 1) || (greenFloat < 0 || greenFloat > 1) || (blueFloat < 0 || blueFloat > 1)) {
		cout << "Program expected rgb values to be between 0-1 for ";
		return false;
	}

	color.red = float(redFloat);
	color.green = float(greenFloat);
	color.blue = float(blueFloat);

	return true;
}

// return true if str is a required keyword
bool isRequiredKeyword(string str) {
	for(int i = 0; i < NUM_REQUIRED_KEYWORDS; i++) {
		if(str == requiredKeywords[i]) {
			return true;
		} 
	}

	return false;
}

// return true if str is a optional keyword
bool isOptionalKeyword(string str) {
	for(int i = 0; i < NUM_OPTIONAL_KEYWORDS; i++) {
		if(str == optionalKeywords[i]) {
			return true;
		} 
	}

	return false;
}

bool getProjection(ifstream& specFileStream, bool& isParallel) {
	if(!validateKeyword(specFileStream, "parallel")) {
		cout << "Invalid format for ";
		return false;
	}

	isParallel = true;

	return true;
}

bool getLight(ifstream& specFileStream, vector<light_t*>& lights) {
	light_t* light = (light_t*) malloc(sizeof(light_t));

	if(!getVector(specFileStream, light->vector)) {
		return false;
	}

	string w;
	if(specFileStream.peek() == EOF) {
		cout << "Expected w for ";
		return false;
	}
	specFileStream >> w;

	if(!getColor(specFileStream, light->color)) {
		return false;
	}

	if(!isInt(w)) {
		cout << "Invlaid format for ";
		return false;
	} 

	light->w = stoi(w);
	light->c1 = 1;
	light->c2 = 0;
	light->c3 = 0;
	lights.push_back(light);

	return true;
}

bool getAttenuationLight(ifstream& specFileStream, vector<light_t*>& lights) {
	light_t* light = (light_t*) malloc(sizeof(light_t));
	
	if(!getVector(specFileStream, light->vector)) {
		return false;
	}

	string w;
	if(specFileStream.peek() == EOF) {
		cout << "Expected w for ";
		return false;
	}
	specFileStream >> w;

	if(!getColor(specFileStream, light->color)) {
		return false;
	}

	if(!isInt(w)) {
		cout << "Invlaid format for ";
		return false;
	} 

	light->w = stoi(w);

	string c1, c2, c3;
	if(specFileStream.peek() == EOF) {
		cout << "Expected c1 for ";
		return false;
	}
	specFileStream >> c1;

	if(specFileStream.peek() == EOF) {
		cout << "Expected c2 for ";
		return false;
	}
	specFileStream >> c2;

	if(specFileStream.peek() == EOF) {
		cout << "Expected c3 for ";
		return false;
	}
	specFileStream >> c3;

	if(!isFloat(c1) && !isFloat(c2) && !isFloat(c3)) {
		cout << "Invlaid format for ";
		return false;
	}

	light->c1 = stof(c1);
	light->c2 = stof(c2);
	light->c3 = stof(c3);
	lights.push_back(light);

	return true;
}

bool getDepthCueing(ifstream& specFileStream, sceneSpecs_t& sceneSpecs) {
	if(!getColor(specFileStream, sceneSpecs.depthcueColor)) {
		return false;
	}

	string alphaMax, alphaMin, dMax, dMin;
	if(specFileStream.peek() == EOF) {
		cout << "Expected alpha max for ";
		return false;
	}
	specFileStream >> alphaMax;

	if(specFileStream.peek() == EOF) {
		cout << "Expected alpha min for ";
		return false;
	}
	specFileStream >> alphaMin;

	if(specFileStream.peek() == EOF) {
		cout << "Expected distance max for ";
		return false;
	}
	specFileStream >> dMax;

	if(specFileStream.peek() == EOF) {
		cout << "Expected distance max for ";
		return false;
	}
	specFileStream >> dMin;

	if(!isFloat(alphaMax) && !isFloat(alphaMin) && !isFloat(dMax) && !isFloat(dMin)) {
		cout << "Invlaid format for ";
		return false;
	}

	sceneSpecs.alphaMax = stof(alphaMax);
	sceneSpecs.alphaMin = stof(alphaMin);
	sceneSpecs.dFar = stof(dMax);
	sceneSpecs.dNear = stof(dMin);

	return true;
}

bool getMaterialColor(ifstream& specFileStream, materialColor_t& materialColor) {
	if(!getColor(specFileStream, materialColor.diffuseColor)) {	
		cout << "diffuse color for ";
		return false;
	}

	if(!getColor(specFileStream, materialColor.specularColor)) {
		cout << "specular color for ";
		return false;
	}

	string ka, kd, ks;
	string n;

	if(specFileStream.peek() == EOF) {
		cout << "ambient for ";
		return false;
	}
	specFileStream >> ka;

	if(specFileStream.peek() == EOF) {
		cout << "diffuse for ";
		return false;
	}
	specFileStream >> kd;

	if(specFileStream.peek() == EOF) {
		cout << "specular for ";
		return false;
	}
	specFileStream >> ks;

	if(specFileStream.peek() == EOF) {
		cout << "diffuse falloff for ";
		return false;
	}
	specFileStream >> n;

	if(!(isFloat(ka) && isFloat(ka) && isFloat(ka) && isInt(n))) {
		cout << "Invlaid format for ";
		return false;
	}

	materialColor.ambient = stof(ka);
	materialColor.diffuse = stof(kd);
	materialColor.specular = stof(ks);
	materialColor.specularFalloff = stoi(n);

	return true;
}

bool loadTexture(string filename, texture_t* texture) {
	ifstream textureStream;
	textureStream.open(filename);

	if(!textureStream) {
		cout << "Texture \"" << filename << "\" cannot be found " << endl;
		textureStream.close();
		
		return NULL;
	} 

	int max_size = 512;
	char line[max_size];
	int width, height, maxColor;

	if(textureStream.good()) {
		textureStream.getline(line, 256);

		if(sscanf(line, "P3 %d %d %d", &width, &height, &maxColor) == 3) {
			texture->width = width;
			texture->height = height;
			texture->textureColors = (color_t**) malloc(sizeof(color_t*) * height);
			
			for(int i = 0; i < height; i++) {
				texture->textureColors[i] = (color_t*) malloc(sizeof(color_t) * width);
			
				for(int j = 0; j < width; j++) {
					int red, green, blue;

					if(!textureStream.good()) {
						cout <<"Texture \"" << filename << "\" has invalid color data " << endl;
					}
					textureStream >> red;
					
					if(!textureStream.good()) {
						cout <<"Texture \"" << filename << "\" has invalid color data " << endl;
					}
					textureStream >> green;

					if(!textureStream.good()) {
						cout <<"Texture \"" << filename << "\" has invalid color data " << endl;
					}
					textureStream >> blue;

					texture->textureColors[i][j].red = (red * 1.0) / maxColor;
					texture->textureColors[i][j].green = (green * 1.0) / maxColor;
					texture->textureColors[i][j].blue = (blue * 1.0) / maxColor;
				}
			}
		} else {
			cout << "Texture \"" << filename << "\" has invalid PPM header " << endl;
			textureStream.close();
		
			return false;
		}
	} else {
		cout << "Texture \"" << filename << "\" is empty " << endl;
		textureStream.close();
		return false;
	}

	textureStream.close();

	return true;
}

bool getTexture(ifstream& specFileStream, texture_t* texture) {
	string filename;

	if(specFileStream.peek() == EOF) {
		cout << "texture file name for ";
		return false;
	}

	specFileStream >> filename;

	if(!isFileName(filename)) {
		cout << "invalid file name for ";
		return false;
	}

	if(!loadTexture(filename, texture)) {
		return false;
	}

	return true;
}

bool getSphere(ifstream& specFileStream, materialColor_t* materialColor, vector<sphere_t*>& spheres) {
	vector3_t position;
	string radius;

	getVector(specFileStream, position);
	specFileStream >> radius;
			
	if(!isFloat(radius)) {
		cout << "Expected float for radius for " << endl;
		return false;
	}

	sphere_t* sphere = (sphere_t*) malloc(sizeof(sphere_t));
	sphere->position = position;
	sphere->radius = stof(radius);
	sphere->materialColor = materialColor;
	sphere->isTextured = false;
	sphere->texture = NULL;
	sphere->isTextured = false;

	spheres.push_back(sphere);

	return true;
}

bool getSphere(ifstream& specFileStream, materialColor_t* materialColor, texture_t* texture, vector<sphere_t*>& spheres) {
	vector3_t position;
	string radius;

	getVector(specFileStream, position);
	specFileStream >> radius;

	if(!isFloat(radius)) {
		cout << "Expected float for radius for " << endl;
		return false;
	}
	
	sphere_t* sphere = (sphere_t*) malloc(sizeof(sphere_t));
	sphere->position = position;
	sphere->radius = stof(radius);
	
	sphere->materialColor = materialColor;
	sphere->texture = texture;
	sphere->isTextured = texture != NULL;

	spheres.push_back(sphere);

	return true;
}

bool getVertices(ifstream& specFileStream, vector<vector3_t*>& vertices) {
	vector3_t* vertexVector;
	while(specFileStream.peek() != EOF) {
		vertexVector = (vector3_t*) malloc(sizeof(vector3_t));
		if(!getVector(specFileStream, *vertexVector)) {
			cout << "Expected vertex for ";
			return false;
		}

		vertices.push_back(vertexVector);

		int currPos = specFileStream.tellg();

		if(validateKeyword(specFileStream, "v")) {
			continue;
		}
		
		specFileStream.seekg(currPos);
		break;
	}

	return true;
}

bool getNormals(ifstream& specFileStream, vector<vector3_t*>& normals) {
	vector3_t* normalVector;
	while(specFileStream.peek() != EOF) {
		normalVector = (vector3_t*) malloc(sizeof(vector3_t));
		if(!getVector(specFileStream, *normalVector)) {
			cout << "Expected vertex for ";
			return false;
		}

		normals.push_back(normalVector);
		
		int currPos = specFileStream.tellg();

		if(validateKeyword(specFileStream, "vn")) {
			continue;
		}
		
		specFileStream.seekg(currPos);
		break;
	}

	return true;
}

bool getVertexTextureCoordinates(ifstream& specFileStream, vector<textureCoordinate_t*>& textureCoordinates) {
	textureCoordinate_t* textureCoordinate;
	string coord1, coord2;
			
	while(specFileStream.peek() != EOF) {
		if(specFileStream.peek() == EOF) {
			cout << "Expected u coordinate for ";
			return false;
		}
		specFileStream >> coord1;

		if(specFileStream.peek() == EOF) {
			cout << "Expected v coordinate for ";
			return false;
		}
		specFileStream >> coord2;
		
		if(!(isInt(coord1) && isInt(coord2))) {
			cout << "Expected texture coordinates for ";
			return false;
		}
		
		textureCoordinate = (textureCoordinate_t*) malloc(sizeof(textureCoordinate_t));
		textureCoordinate->u = stof(coord1);
		textureCoordinate->v = stof(coord2);
		
		textureCoordinates.push_back(textureCoordinate);

		int currPos = specFileStream.tellg();

		if(validateKeyword(specFileStream, "vt")) {
			continue;
		}

		specFileStream.seekg(currPos);
		break;
	}

	return true;
}

vector<string> tokenize(string str, string delimiter) {
	vector<string> tokens;

	char* token = strtok((char*) str.c_str(), (char*) delimiter.c_str());
	string tokenStr;

	while(token != NULL) {
		tokenStr = token;
		tokens.push_back(tokenStr);
		token = strtok(NULL, (char*) delimiter.c_str());
	}

	return tokens;
}

bool getFaces(ifstream& specFileStream, materialColor_t* materialColor, texture_t* texture, sceneSpecs_t& specs) {
	triangle_t* triangle;
	string faceStr1, faceStr2, faceStr3;

	while(specFileStream.peek() != EOF) {
		triangle = (triangle_t*) malloc(sizeof(triangle_t));
		
		if(specFileStream.peek() == EOF) {
			cout << "Expected index 1 for ";
			return false;
		}
		specFileStream >> faceStr1;

		if(specFileStream.peek() == EOF) {
			cout << "Expected index 2 for ";
			return false;
		}
		specFileStream >> faceStr2;

		if(specFileStream.peek() == EOF) {
			cout << "Expected index 3 for ";
			return false;
		}
		specFileStream >> faceStr3;

		if(texture == NULL) {
			if(faceStr1.find("//") != string::npos && faceStr2.find("//") != string::npos && faceStr3.find("//") != string::npos) {
				vector<string> tokensFaceStr1 = tokenize(faceStr1, "//");
				vector<string> tokensFaceStr2 = tokenize(faceStr2, "//");
				vector<string> tokensFaceStr3 = tokenize(faceStr3, "//");
				
				if(!(isInt(tokensFaceStr1.at(0)) && isInt(tokensFaceStr2.at(0)) && isInt(tokensFaceStr3.at(0)))) {
					cout << "Expected integer vertex indices for ";
					return false;
				}

				if(!(isInt(tokensFaceStr1.at(1)) && isInt(tokensFaceStr2.at(1)) && isInt(tokensFaceStr3.at(1)))) {
					cout << "Expected integer normal indices for ";
					return false;
				}

				triangle->pointIndices[0] = stoi(tokensFaceStr1.at(0));
				triangle->pointIndices[1] = stoi(tokensFaceStr2.at(0));
				triangle->pointIndices[2] = stoi(tokensFaceStr3.at(0));

				triangle->normalIndices[0] = stoi(tokensFaceStr1.at(1));
				triangle->normalIndices[1] = stoi(tokensFaceStr2.at(1));
				triangle->normalIndices[2] = stoi(tokensFaceStr3.at(1));
			} else {
				if(!(isInt(faceStr1) && isInt(faceStr2) && isInt(faceStr3))) {
					cout << "Expected integer vertex indices for ";
					return false;
				}

				triangle->pointIndices[0] = stoi(faceStr1);
				triangle->pointIndices[1] = stoi(faceStr2);
				triangle->pointIndices[2] = stoi(faceStr3);

				triangle->normalIndices[0] = -1;
				triangle->normalIndices[1] = -1;
				triangle->normalIndices[2] = -1;
			}
			
			triangle->textureCoordinatesIndices[0] = -1;
			triangle->textureCoordinatesIndices[1] = -1;
			triangle->textureCoordinatesIndices[2] = -1;
			triangle->isTextured = false;
			
		} else {
			vector<string> tokensFaceStr1 = tokenize(faceStr1, "/");
			vector<string> tokensFaceStr2 = tokenize(faceStr2, "/");
			vector<string> tokensFaceStr3 = tokenize(faceStr3, "/");

			if(tokensFaceStr1.size() == 2 && tokensFaceStr2.size() == 2 && tokensFaceStr3.size() == 2) {
				if(!(isInt(tokensFaceStr1.at(0)) && isInt(tokensFaceStr2.at(0)) && isInt(tokensFaceStr3.at(0)))) {
					cout << "Expected integer vertex indices for ";
					return false;
				}

				if(!(isInt(tokensFaceStr1.at(1)) && isInt(tokensFaceStr2.at(1)) && isInt(tokensFaceStr3.at(1)))) {
					cout << "Expected integer texture indices for ";
					return false;
				}

				triangle->pointIndices[0] = stoi(tokensFaceStr1.at(0));
				triangle->pointIndices[1] = stoi(tokensFaceStr2.at(0));
				triangle->pointIndices[2] = stoi(tokensFaceStr3.at(0));

				triangle->textureCoordinatesIndices[0] = stoi(tokensFaceStr1.at(1));
				triangle->textureCoordinatesIndices[1] = stoi(tokensFaceStr2.at(1));
				triangle->textureCoordinatesIndices[2] = stoi(tokensFaceStr3.at(1));

				triangle->normalIndices[0] = -1;
				triangle->normalIndices[1] = -1;
				triangle->normalIndices[2] = -1;

			} else if(tokensFaceStr1.size() == 3 && tokensFaceStr2.size() == 3 && tokensFaceStr3.size() == 3) {
				if(!(isInt(tokensFaceStr1.at(0)) && isInt(tokensFaceStr2.at(0)) && isInt(tokensFaceStr3.at(0)))) {
					cout << "Expected integer vertex indices for ";
					return false;
				}

				if(!(isInt(tokensFaceStr1.at(1)) && isInt(tokensFaceStr2.at(1)) && isInt(tokensFaceStr3.at(1)))) {
					cout << "Expected integer texture indices for ";
					return false;
				}

				if(!(isInt(tokensFaceStr1.at(2)) && isInt(tokensFaceStr2.at(2)) && isInt(tokensFaceStr3.at(2)))) {
					cout << "Expected integer normal indices for ";
					return false;
				}

				triangle->pointIndices[0] = stoi(tokensFaceStr1.at(0));
				triangle->pointIndices[1] = stoi(tokensFaceStr2.at(0));
				triangle->pointIndices[2] = stoi(tokensFaceStr3.at(0));

				triangle->textureCoordinatesIndices[0] = stoi(tokensFaceStr1.at(1));
				triangle->textureCoordinatesIndices[1] = stoi(tokensFaceStr2.at(1));
				triangle->textureCoordinatesIndices[2] = stoi(tokensFaceStr3.at(1));

				triangle->normalIndices[0] = stoi(tokensFaceStr1.at(2));
				triangle->normalIndices[1] = stoi(tokensFaceStr2.at(2));
				triangle->normalIndices[2] = stoi(tokensFaceStr3.at(2));
			} else {
				cout << "Too many index aruments for ";
				return false;
			}

			triangle->texture = texture;
			triangle->isTextured = true;
		} 
		
		triangle->materialColor = materialColor;
		specs.triangles.push_back(triangle);
		
		int currPos = specFileStream.tellg();

		if(validateKeyword(specFileStream, "f")) {
			continue;
		}

		string keyword;
		specFileStream >> keyword;	
		specFileStream.seekg(currPos);

		if(isRequiredKeyword(keyword) || isOptionalKeyword(keyword) || specFileStream.peek() == EOF) {
			return true;
		}

		return false;
	}

	return true;
}

bool getTriangles(ifstream& specFileStream, materialColor_t* materialColor, sceneSpecs_t& specs) {
	vector3_t* vertexVector;
	triangle_t* triangle;
	string index1, index2, index3;

	if(!getVertices(specFileStream, specs.vertices)) {
		cout << "triangle for ";
		return false;
	}

	int currPos = specFileStream.tellg();

	if(validateKeyword(specFileStream, "vn")) {
		if(!getNormals(specFileStream, specs.normals)) {
			cout << "triangle for ";
			return false;
		}
	} else {
		specFileStream.seekg(currPos);
	}

	if(validateKeyword(specFileStream, "f")) {
		if(!getFaces(specFileStream, materialColor, NULL, specs)) {
			cout << "triangle for ";
			return false;
		}
	} else {
		cout << "expected faces for ";
		return false;
	}

	return true;
}

bool getTriangles(ifstream& specFileStream, materialColor_t* materialColor, texture_t* texture, sceneSpecs_t& specs) {
	vector3_t* vertexVector;
	triangle_t* triangle;
	string index1, index2, index3;

	if(!getVertices(specFileStream, specs.vertices)) {
		cout << "triangle for ";
		return false;
	}

	int currPos = specFileStream.tellg();

	while(specFileStream.peek() != EOF) {
		currPos = specFileStream.tellg();
		if(validateKeyword(specFileStream, "vn")) {
			if(!getNormals(specFileStream, specs.normals)) {
				cout << "triangle for ";
				return false;
			}
			continue;
		} else {
			specFileStream.seekg(currPos);
		}

		if(validateKeyword(specFileStream, "vt")) {
			if(!getVertexTextureCoordinates(specFileStream, specs.textureCoordinates)) {
				cout << "triangle for ";
				return false;
			}
			continue;
		} else {
			specFileStream.seekg(currPos);
		}

		if(validateKeyword(specFileStream, "f")) {
			specFileStream.seekg(currPos);
			break;
		}

		cout << "Expected f for ";
		return false;
	}

	if(validateKeyword(specFileStream, "f")) {
		if(!getFaces(specFileStream, materialColor, texture, specs)) {
			cout << "triangle for ";
			return false;
		}
	} else {
		cout << "expected faces for ";
		return false;
	}

	return true;
}

bool getTextureObjects(ifstream& specFileStream, materialColor_t* materialColor, sceneSpecs_t& specs) {
	sphere_t* sphere;
	texture_t* texture;
	vector3_t position;
	string radius;

	while(specFileStream.peek() != EOF) {
		texture = (texture_t*) malloc(sizeof(texture_t));

		getTexture(specFileStream, texture);
		specs.textures.push_back(texture);

		while(specFileStream.peek() != EOF) {
			int currPos = specFileStream.tellg();
			string keyword;
			specFileStream >> keyword;
			
			specFileStream.seekg(currPos);

			if(validateKeyword(specFileStream, "sphere")) {
 				if(!getSphere(specFileStream, materialColor, texture, specs.spheres)) {
					cout << "invalid sphere" << endl;
					return false;
				}

				continue;
			}

			specFileStream.seekg(currPos);	

			if(validateKeyword(specFileStream, "v")) {
				if(!getTriangles(specFileStream, materialColor, texture, specs)) {
					cout << "for triangle ";
					return false;
				}

				continue;
			}

			if(isRequiredKeyword(keyword) || isOptionalKeyword(keyword) || specFileStream.peek() == EOF) {
				return true;
			}

			return false;
		}
	}

	return true;
 }

// returns true if spheres were properly read from fileStream into spheres reference
bool getSceneObjects(ifstream& specFileStream, sceneSpecs_t& specs) {
	sphere_t* sphere;
	materialColor_t* materialColor;
	vector3_t position;
	string radius;

	while(specFileStream.peek() != EOF) {
		materialColor = (materialColor_t*) malloc(sizeof(materialColor_t));

		getMaterialColor(specFileStream, *materialColor);
		specs.materialColors.push_back(materialColor);

		while(specFileStream.peek() != EOF) {
			int currPos = specFileStream.tellg();
			string keyword;
			specFileStream >> keyword;
			
			specFileStream.seekg(currPos);

			if(validateKeyword(specFileStream, "sphere")) {
				if(!getSphere(specFileStream, materialColor, NULL, specs.spheres)) {
					cout << "for sphere ";
					return false;
				}

				continue;
			}

			specFileStream.seekg(currPos);	

			if(validateKeyword(specFileStream, "v")) {
				if(!getTriangles(specFileStream, materialColor, specs)) {
					cout << "for triangle ";
					return false;
				}

				continue;
			}

			specFileStream.seekg(currPos);	
			
			if(validateKeyword(specFileStream, "texture")) {
				if(!getTextureObjects(specFileStream, materialColor, specs)) {
					cout << "for triangle ";
					return false;
				}

				continue;
			}

			if(isRequiredKeyword(keyword) || isOptionalKeyword(keyword) || specFileStream.peek() == EOF) {
				return true;
			}

			return false;
		}
	}

	return true;
 }

// return string filename if arguuments are valid for program
// returns empty string otherwise
string ensureValidArguments(int argc, char** argv) {
	// check for one argument (file name)
	if(argc < 2) {
		cout << "Program expected file name arugment" << endl;
		return "";
	}
	
	// ensure file name is valid
	if(!isFileName(argv[1])) {
		cout << "Program expected well formed filename" << endl;
		return "";
	}

	// return filename without extension
	char tempfilename[strlen(argv[1])];
	strcpy(tempfilename, argv[1]);
	
	char filename[strlen(argv[1])];
	strcpy(filename, strtok(tempfilename, "."));

	return filename;
}

// writes header of image file, returns image file stream
ofstream* makeHeader(ofstream* imageFile, int width, int height) {
    *imageFile << "P3 " << width << " " << height << " " << 255 << endl;
    return imageFile;
}


// writes color data to image file
void writeImageData(ofstream* imageFile, color_t** pixels, int imageWidth, int imageHeight) {
	// writes colors to image file
	for(int row = 0; row < imageHeight; row++) {
		for(int col = 0; col < imageWidth; col++) {
			*imageFile << round(pixels[row][col].red * 255.0) << " ";
			*imageFile << round(pixels[row][col].green * 255.0) << " ";
			*imageFile << round(pixels[row][col].blue * 255.0);
			
			*imageFile << endl;
		}
	}
}

sceneSpecs_t generateSpiral(sceneSpecs_t specs) {
	float sampleRate = 0.3927, radius = 1;
	int numSamples = 75;
	vector3_t spherePosition = specs.viewOriginVector;
	spherePosition = addVectors(addVectors(spherePosition, multiplyCoefficient(specs.viewDirectionVector, 15)), multiplyCoefficient(negative(specs.upVector), numSamples / 2));
	float z = spherePosition.z;

	for(int i = 0; i < numSamples; i++) {
		sphere_t* currSphere = (sphere_t*) malloc(sizeof(sphere_t));
		spherePosition.x = 5 * cos(i * (M_PI / 8.0)  + (M_PI / 2));
		spherePosition.z = z +  5 *sin(i * (M_PI / 8.0) + (M_PI / 2));;

		currSphere->materialColor = specs.materialColors.at(0);
		currSphere->materialColorIndex = 0;
		currSphere->radius = radius;
		currSphere->position = spherePosition;
	

		specs.spheres.push_back(currSphere);
		spherePosition = addVectors(spherePosition, multiplyCoefficient(specs.upVector, radius));
	}

	spherePosition = addVectors(addVectors(specs.viewOriginVector, multiplyCoefficient(specs.viewDirectionVector, 15)), multiplyCoefficient(negative(specs.upVector), numSamples / 2));

	for(int i = 0; i < numSamples; i++) {
		sphere_t* currSphere = (sphere_t*) malloc(sizeof(sphere_t));
		spherePosition.x = 5 * cos(i* (M_PI / 8.0) + (3 * M_PI / 2));
		spherePosition.z = z + 5 * sin(i * (M_PI / 8.0) + (3 * M_PI / 2));

		currSphere->materialColor = specs.materialColors.at(1);
		currSphere->materialColorIndex = 0;
		currSphere->radius = radius;
		currSphere->position = spherePosition;
	

		specs.spheres.push_back(currSphere);
		spherePosition = addVectors(spherePosition, multiplyCoefficient(specs.upVector, radius));
	}

	return specs;
}

// returns sceneSpecs_t struct from file, sets wellFormed flag in sceneSpec_t to false if invalid
// formats in scene specification document
sceneSpecs_t getSceneSpecifications(int argc, char** argv, string& filename) {
	filename = ensureValidArguments(argc, argv);
	sceneSpecs_t specs;

	// if filename is empty string, invalid arguments
	if(filename.compare("") == 0) {
		specs.wellFormed = false;
		return specs; 
	}	
	
	ifstream specFileStream;
	specFileStream.open(argv[1]);

	if(!specFileStream) {
		cout << "File \"" << argv[1] << "\" cannot be found" << endl;
		specFileStream.close();
		specs.wellFormed = false;
		
		return specs;
	} 

	//initialize depthcue
	specs.alphaMin = 1;
	specs.alphaMax = 1;
	specs.dNear = std::numeric_limits<double>::infinity();
	specs.dFar = std::numeric_limits<double>::infinity();

	//initialize vertices for 1 indexing
	specs.vertices.push_back(NULL);

	//intitalize textureCoordinates for 1 indexing
	specs.textureCoordinates.push_back(NULL);

	//intitalize normals for 1 indexing
	specs.normals.push_back(NULL);

	bool requiredKeywordsEncountered[NUM_REQUIRED_KEYWORDS] = {false};
	bool encounteredKeyword = false;
	int position;

	while(specFileStream.peek() != EOF) {
		for(int i = 0; i < NUM_REQUIRED_KEYWORDS; i++) {
			position = specFileStream.tellg();
			
			if(encounteredKeyword) {
				break;
			}

			if(validateKeyword(specFileStream, requiredKeywords[i])) {
				requiredKeywordsEncountered[i] = true;
				encounteredKeyword = true;
				switch(i) {
					case 0:
						if(!getVector(specFileStream, specs.viewOriginVector)) { cout << "eye" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 1: 
						if(!getVector(specFileStream, specs.viewDirectionVector)) { cout << "viewdir" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 2: 
						if(!getVector(specFileStream, specs.upVector)) { cout << "updir" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 3: 
						if(!getHorizontalFOV(specFileStream, specs.horizontalFOV)) { cout << "hfov" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 4: 
						if(!getImageDimensions(specFileStream, specs)) { cout << "imsize" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 5: 
						if(!getColor(specFileStream, specs.backgroundColor)) { cout << "bckcolor" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
				}
			} else {
				specFileStream.seekg(position);	
			}
		}

		for(int i = 0; i < NUM_OPTIONAL_KEYWORDS; i++) {
			position = specFileStream.tellg();
			
			if(encounteredKeyword) {
				break;
			}
			
			if(validateKeyword(specFileStream, optionalKeywords[i])) {
				
				encounteredKeyword = true;
				switch(i) {
					case 0:
						if(!getSceneObjects(specFileStream, specs)) { cout << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					/*case 1:
						if(!getSceneObjects(specFileStream, specs.textures, specs.spheres, specs.triangles, specs.vertices)) { cout << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;*/
					case 1: 
						if(!getLight(specFileStream, specs.lights)) { cout << "light" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 2: 
						if(!getAttenuationLight(specFileStream, specs.lights)) { cout << "attlight" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 3: 
						if(!getDepthCueing(specFileStream, specs)) { cout << "depthcueing" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
					case 4: 
						specs = generateSpiral(specs); encounteredKeyword = true;
						break;
					case 5: 
						if(!getProjection(specFileStream, specs.isParallel)) { cout << "projection" << endl; specs.wellFormed = false; specFileStream.close(); return specs; };
						break;
				}
			} else {
				specFileStream.seekg(position);	
			}
		}

		if(!encounteredKeyword) {
			string token;
			specFileStream >> token;

			if(token != "") {
				cout << "Unexpected token \"" << token << "\"" << endl;	
			specs.wellFormed = false;
			specFileStream.close();
			return specs;
			}
		}

		encounteredKeyword = false;
	}

	for(int i = 0; i < NUM_REQUIRED_KEYWORDS; i++) {
		if(!requiredKeywordsEncountered[i]) {
			cout << "Expected \"" << requiredKeywords[i] << "\" keyword" << endl;
			specs.wellFormed = false;
			specFileStream.close();
			return specs;
		} 
	}

	specs.wellFormed = true;
	specFileStream.close();
	
	return specs;
}

// writes pixel colors to PPM image file
void writePPMFile(string filename, color_t** pixels, int width, int height) {
	ofstream imageFile;
	imageFile.open(filename + ".ppm");
    
	makeHeader(&imageFile, width, height);
	writeImageData(&imageFile, pixels, width, height);
	
	imageFile.close();
}
