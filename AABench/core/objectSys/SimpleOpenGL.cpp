/* ----------------------------------------------------------------------------
// Simple sample to prove that Assimp is easy to use with OpenGL.
// It takes a file name as command line parameter, loads it using standard
// settings and displays it.
//
// If you intend to _use_ this code sample in your app, do yourself a favour
// and replace immediate mode calls with VBOs ...
//
// The vc8 solution links against assimp-release-dll_win32 - be sure to
// have this configuration built.
// ----------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/* the global Assimp scene object */
const C_STRUCT aiScene* scene = NULL;
GLuint scene_list = 0;
C_STRUCT aiVector3D scene_min, scene_max, scene_center;

/* current rotation angle */
static float angle = 0.f;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

// recursive function called from get bounding box
void get_bounding_box_for_node(const C_STRUCT aiNode* node, C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max, C_STRUCT aiMatrix4x4* trans)
{
  C_STRUCT aiMatrix4x4 prev;
  unsigned int n = 0, t;

  prev = *trans;
  aiMultiplyMatrix4(trans, &node->mTransformation);

  for (; n < node->mNumMeshes; ++n) {
    const C_STRUCT aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
    for (t = 0; t < mesh->mNumVertices; ++t) {

      C_STRUCT aiVector3D tmp = mesh->mVertices[t];
      aiTransformVecByMatrix4(&tmp, trans);

      min->x = aisgl_min(min->x, tmp.x);
      min->y = aisgl_min(min->y, tmp.y);
      min->z = aisgl_min(min->z, tmp.z);

      max->x = aisgl_max(max->x, tmp.x);
      max->y = aisgl_max(max->y, tmp.y);
      max->z = aisgl_max(max->z, tmp.z);
    }
  }

  for (n = 0; n < node->mNumChildren; ++n)
  {
    get_bounding_box_for_node(node->mChildren[n], min, max, trans);
  }
  *trans = prev;
}


// get bounding box
void get_bounding_box(C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max)
{
  C_STRUCT aiMatrix4x4 trans;
  aiIdentityMatrix4(&trans);

  min->x = min->y = min->z = 1e10f;
  max->x = max->y = max->z = -1e10f;
  get_bounding_box_for_node(scene->mRootNode, min, max, &trans);
}

// conversions
void color4_to_float4(const C_STRUCT aiColor4D* c, float f_out[4])
{
  f_out[0] = c->r;
  f_out[1] = c->g;
  f_out[2] = c->b;
  f_out[3] = c->a;
}

void set_float4(float f_out[4], float a, float b, float c, float d)
{
  f_out[0] = a;
  f_out[1] = b;
  f_out[2] = c;
  f_out[3] = d;
}

// apply material
void apply_material(const C_STRUCT aiMaterial* mtl)
{
  float c[4];

  GLenum fill_mode;
  int ret1, ret2;
  C_STRUCT aiColor4D diffuse;
  C_STRUCT aiColor4D specular;
  C_STRUCT aiColor4D ambient;
  C_STRUCT aiColor4D emission;
  ai_real shininess, strength;
  int two_sided;
  int wireframe;
  unsigned int max;

  // a default color
  set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);

  // get color from our material
  if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
    color4_to_float4(&diffuse, c);

  // upload color to our graphics in this diffuse slot
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

  // a default specular
  set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
  // set specular from material
  if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
    color4_to_float4(&specular, c);

  // upload to graphics using specular slot
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

  // default ambient
  set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
  // set ambient from our material
  if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
    color4_to_float4(&ambient, c);
  // upload ambient result
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

  // default color
  set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
  // get material color
  if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
    color4_to_float4(&emission, c);
  // upload to emission slot
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

  // get material float array as shininess
  max = 1;
  ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
  if (ret1 == AI_SUCCESS) {
    // get the shinniness strength
    max = 1;
    ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);

    // upload results
    if (ret2 == AI_SUCCESS) {
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
    }
    else {
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
  }
  else
  {
    //upload default result of 0 shininess
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

    // zero specular if there is no shininess
    set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
  }

  max = 1;
  if (AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
  {
    fill_mode = wireframe ? GL_LINE : GL_FILL;
  }
  else
  {
    fill_mode = GL_FILL;
  }

  glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

  max = 1;
  if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
  {
    glDisable(GL_CULL_FACE);
  }
  else
  {
    glEnable(GL_CULL_FACE);
  }
}

///* CUT */
//void recursive_render(const C_STRUCT aiScene* sc, const C_STRUCT aiNode* nd)
//{
//  unsigned int i;
//  unsigned int n = 0, t;
//  C_STRUCT aiMatrix4x4 m = nd->mTransformation;
//
//  /* update transform */
//  aiTransposeMatrix4(&m);
//  glPushMatrix();
//  glMultMatrixf((float*)&m);
//
//  /* draw all meshes assigned to this node */
//  for (; n < nd->mNumMeshes; ++n) {
//    const C_STRUCT aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
//
//    apply_material(sc->mMaterials[mesh->mMaterialIndex]);
//
//    if (mesh->mNormals == NULL) {
//      glDisable(GL_LIGHTING);
//    }
//    else {
//      glEnable(GL_LIGHTING);
//    }
//
//    for (t = 0; t < mesh->mNumFaces; ++t) {
//      const C_STRUCT aiFace* face = &mesh->mFaces[t];
//      GLenum face_mode;
//
//      switch (face->mNumIndices) {
//      case 1: face_mode = GL_POINTS; break;
//      case 2: face_mode = GL_LINES; break;
//      case 3: face_mode = GL_TRIANGLES; break;
//      default: face_mode = GL_POLYGON; break;
//      }
//
//      glBegin(face_mode);
//
//      for (i = 0; i < face->mNumIndices; i++) {
//        int index = face->mIndices[i];
//        if (mesh->mColors[0] != NULL)
//          glColor4fv((GLfloat*)&mesh->mColors[0][index]);
//        if (mesh->mNormals != NULL)
//          glNormal3fv(&mesh->mNormals[index].x);
//        glVertex3fv(&mesh->mVertices[index].x);
//      }
//
//      glEnd();
//    }
//
//  }
//
//  /* draw all children */
//  for (n = 0; n < nd->mNumChildren; ++n) {
//    recursive_render(sc, nd->mChildren[n]);
//  }
//
//  glPopMatrix();
//}

///* CUT */
//void do_motion(void)
//{
//  static GLint prev_time = 0;
//  static GLint prev_fps_time = 0;
//  static int frames = 0;
//
//  int time = glutGet(GLUT_ELAPSED_TIME);
//  angle += (time - prev_time) * 0.01;
//  prev_time = time;
//
//  frames += 1;
//  if ((time - prev_fps_time) > 1000) /* update every seconds */
//  {
//    int current_fps = frames * 1000 / (time - prev_fps_time);
//    printf("%d fps\n", current_fps);
//    frames = 0;
//    prev_fps_time = time;
//  }
//
//
//  glutPostRedisplay();
//}

///* CUT */
//void display(void)
//{
//  float tmp;
//
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  gluLookAt(0.f, 0.f, 3.f, 0.f, 0.f, -5.f, 0.f, 1.f, 0.f);
//
//  /* rotate it around the y axis */
//  glRotatef(angle, 0.f, 1.f, 0.f);
//
//  /* scale the whole asset to fit into our view frustum */
//  tmp = scene_max.x - scene_min.x;
//  tmp = aisgl_max(scene_max.y - scene_min.y, tmp);
//  tmp = aisgl_max(scene_max.z - scene_min.z, tmp);
//  tmp = 1.f / tmp;
//  glScalef(tmp, tmp, tmp);
//
//  /* center the model */
//  glTranslatef(-scene_center.x, -scene_center.y, -scene_center.z);
//
//  /* if the display list has not been made yet, create a new one and
//     fill it with scene contents */
//  if (scene_list == 0) {
//    scene_list = glGenLists(1);
//    glNewList(scene_list, GL_COMPILE);
//    /* now begin at the root node of the imported data and traverse
//       the scenegraph by multiplying subsequent local transforms
//       together on GL's matrix stack. */
//    recursive_render(scene, scene->mRootNode);
//    glEndList();
//  }
//
//  glCallList(scene_list);
//
//  glutSwapBuffers();
//
//  do_motion();
//}

/*
----------------------------------------------------------------------------
*/
int loadasset(const char* path)
{
  /* we are taking one of the postprocessing presets to avoid
     spelling out 20+ single postprocessing flags here. */
  scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

  if (scene) {
    get_bounding_box(&scene_min, &scene_max);
    scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
    scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
    scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
    return 0;
  }
  return 1;
}

/* ---------------------------------------------------------------------------- */
int run()
{
  C_STRUCT aiLogStream stream;

  //glutInitWindowSize(900, 600);
  //glutInitWindowPosition(100, 100);
  //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  //glutInit(&argc, argv);

  //glutCreateWindow("Assimp - Very simple OpenGL sample");
  //glutDisplayFunc(display);
  //glutReshapeFunc(reshape);

  /* get a handle to the predefined STDOUT log stream and attach
     it to the logging system. It remains active for all further
     calls to aiImportFile(Ex) and aiApplyPostProcessing. */
  stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
  aiAttachLogStream(&stream);

  /* ... same procedure, but this stream now writes the
     log messages to assimp_log.txt */
  stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE, "assimp_log.txt");
  aiAttachLogStream(&stream);

  /* the model name can be specified on the command line. If none
    is specified, we try to locate one of the more expressive test
    models from the repository (/models-nonbsd may be missing in
    some distributions so we need a fallback from /models!). */
    //if (0 != loadasset(argc >= 2 ? argv[1] : "../../test/models-nonbsd/X/dwarf.x")) {
    //  if (argc != 1 || (0 != loadasset("../../../../test/models-nonbsd/X/dwarf.x") && 0 != loadasset("../../test/models/X/Testwuson.X"))) {
    //    return -1;
    //  }
    //}

    //glClearColor(0.1f, 0.1f, 0.1f, 1.f);

    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);    /* Uses default lighting parameters */

    //glEnable(GL_DEPTH_TEST);

    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glEnable(GL_NORMALIZE);

    /* XXX docs say all polygons are emitted CCW, but tests show that some aren't. */
    //if (getenv("MODEL_IS_BROKEN"))
      //glFrontFace(GL_CW);

    //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    //glutGet(GLUT_ELAPSED_TIME);
    //glutMainLoop();

    /* cleanup - calling 'aiReleaseImport' is important, as the library
        keeps internal resources until the scene is freed again. Not
        doing so can cause severe resource leaking. */
  aiReleaseImport(scene);

  /* We added a log stream to the library, it's our job to disable it
     again. This will definitely release the last resources allocated
     by Assimp.*/
  aiDetachAllLogStreams();
  return 0;
}