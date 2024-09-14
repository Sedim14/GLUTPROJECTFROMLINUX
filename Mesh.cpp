#include "Mesh.h"
#include <GL/freeglut.h>
#include <iostream>
#include "Vector3D.h"
#include <vector>
#include <cstdio>  // For FILE, fopen, fclose, fscanf
#include "matrixTransformations.h"

void Mesh::loadVertices(const char* obj) {
    FILE* file = nullptr;

    // Open the .obj file using fopen
    if ((file = fopen(obj, "r")) != nullptr) {
        std::cout << "File opened successfully" << std::endl;
        char type;
        float x, y, z;
        int result;

        // Read data from the file using fscanf
        while ((result = fscanf(file, "%c %f %f %f", &type, &x, &y, &z)) != EOF) {
            if (result == 4 && type == 'v') {
                vertices.push_back(Vector3D(x, y, z));
            }
        }

        // Close the file
        fclose(file);
    }
    else {
        std::cerr << "The .obj file was not found" << std::endl;
    }
}

void Mesh::createFaces(const char* obj)
{
    FILE* file = nullptr;

    // Open the .obj file using fopen
    if ((file = fopen(obj, "r")) != nullptr) {
        char type;
        int v1, v2, v3;  // Use int for vertex indices
        int result;

        // Read data from the file using fscanf
        while ((result = fscanf(file, "%c %d %d %d", &type, &v1, &v2, &v3)) != EOF) {
            if (result == 4 && type == 'f') {
                std::vector<Vector3D*> face = {&vertices[v1 - 1], &vertices[v2 - 1], &vertices[v3 - 1]};
                faces.push_back(face);
            }
        }

        // Close the file
        fclose(file);
    }
    else {
        std::cerr << "The .obj file was not found" << std::endl;
    }
}

void Mesh::drawMesh(const std::vector<Vector3D>& colors)
{
    glBegin(GL_TRIANGLES);

    int iColor = 0;

    for (int face = 0; face < faces.size(); face++)
    {
        if (iColor >= colors.size()) {
            iColor = 0;
        }

        // Set color for the current face
        Vector3D currentColor = colors[iColor];
        glColor3f(currentColor.getX(), currentColor.getY(), currentColor.getZ());

        // Draw all the vertices of the current face
        std::vector<Vector3D*> currentFace = faces[face];
        for (int i = 0; i < currentFace.size(); i++) {
            Vector3D* currentVertex = currentFace[i];
            glVertex3f(currentVertex->getX(), currentVertex->getY(), currentVertex->getZ());
        }

        iColor++;
    }
    
    glEnd();
}

void Mesh::updateVertices()
{
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = rotateX(vertices[i], angleX);
        vertices[i] = rotateY(vertices[i], angleY);
    }
}
