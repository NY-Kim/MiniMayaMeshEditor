#version 150
// ^ Change this to version 130 if you have compatibility issues

// Refer to the lambert shader files for useful comments

in vec4 vs_Pos;
in vec4 vs_Col;

// Each vertex is influenced by two joints.
// in_weights[0] is the first joint's influence weight,
// and in_weights[1] is the second joint's
in vec2 in_weights;
// Indicates the IDs of the joints that influence this vertex.
// A joint's ID corresponds to the index in the mat4 arrays below
// that stores that joint's bind matrix and current transformation matrix.
in ivec2 in_jointIDs;

uniform mat4 u_Model; // Handle is 0
uniform mat4 u_ViewProj; // Handle is 1

// All of the bind matrices of the skeleton.
// Each element in the array is one joint's bind matrix.
// Handle is 2 through 101
uniform mat4 ua_bindMats[100]; // Only OpenGL 4.3 and up support dynamic array sizes
// All of the current transformation matrices of the skeleton.
// Each element in the array is one joint's current transformation matrix.
// Handle is 102 through 201
uniform mat4 ua_jointMats[100];

out vec4 fs_Col;

void main()
{
    fs_Col = vs_Col;

    vec4 posSum = vec4(0, 0, 0, 0);
    for (int i = 0; i < 2; i++) {
        mat4 bindMat = ua_bindMats[in_jointIDs[i]];
        mat4 overallT = ua_jointMats[in_jointIDs[i]];
        posSum += overallT * bindMat * in_weights[i] * vs_Pos;
    }

    gl_Position = u_ViewProj * (u_Model * posSum);
}
