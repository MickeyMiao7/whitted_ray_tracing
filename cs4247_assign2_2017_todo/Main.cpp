//============================================================
// STUDENT NAME: Miao Qi
// MATRIC NO.  : A0159327X
// NUS EMAIL   : e0046706@u.nus.edu
// COMMENTS TO GRADER:
// For task 3, the object I render is called carbon molecule or buckyball (it is like a football). It has 60 vertexes. Computing the coordinate of the vertexes and generating the edges are very
// complex. Here, I consider the whole object into 8 levels, and then construct it. 
// It takes about 20 seconds on my computer to generate the image.
//
// ============================================================
//
// FILE: Main.cpp


#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "Util.h"
#include "Vector3d.h"
#include "Color.h"
#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Surface.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Scene.h"
#include "Raytrace.h"

using namespace std;


// Constants for Scene 1.
static const int imageWidth1 = 640;
static const int imageHeight1 = 480;
static const int reflectLevels1 = 0;  // 0 -- object does not reflect scene.
static const int hasShadow1 = true;

// Constants for Scene 2.
static const int imageWidth2 = 640;
static const int imageHeight2 = 480;
static const int reflectLevels2 = 1;  // 0 -- object does not reflect scene.
static const int hasShadow2 = true;




///////////////////////////////////////////////////////////////////////////
// Raytrace the whole image of the scene and write it to a file.
///////////////////////////////////////////////////////////////////////////

void RenderImage( const char *imageFilename, const Scene &scene, int reflectLevels, bool hasShadow )
{
	int imgWidth = scene.camera.getImageWidth();
	int imgHeight = scene.camera.getImageHeight();

	Image image( imgWidth, imgHeight );	// To store the result of ray tracing.

	double startTime = Util::GetCurrRealTime();
	double startCPUTime = Util::GetCurrCPUTime();

	// Generate image.
	for ( int y = 0; y < imgHeight; y++ )
	{
		double pixelPosY = y + 0.5;

		for ( int x = 0; x < imgWidth; x++ )
		{
			double pixelPosX = x + 0.5;
			Ray ray = scene.camera.getRay( pixelPosX, pixelPosY );
			Color pixelColor = Raytrace::TraceRay( ray, scene, reflectLevels, hasShadow );
			pixelColor.clamp();
			image.setPixel( x, y, pixelColor );
		}
		// printf( "%d ", y );
	}

	double stopCPUTime = Util::GetCurrCPUTime();
	double stopTime = Util::GetCurrRealTime();
	printf( "CPU time taken = %.1f sec\n", stopTime - startTime ); 
	printf( "Real time taken = %.1f sec\n", stopTime - startTime ); 

	// Write image to file.
	image.writeToFile( imageFilename );
}




// Forward declarations. These functions are defined later in the file.

void DefineScene1( Scene &scene, int imageWidth, int imageHeight );
void DefineScene2( Scene &scene, int imageWidth, int imageHeight );




void WaitForEnterKeyBeforeExit( void )
{
    fflush( stdin );
    getchar();
}




int main()
{
	atexit( WaitForEnterKeyBeforeExit );



// Define Scene 1.

	Scene scene1;
	DefineScene1( scene1, imageWidth1, imageHeight1 );

// Render Scene 1.

	printf( "Render Scene 1...\n" );
	RenderImage( "out1.png", scene1, reflectLevels1, hasShadow1 );
	printf( "Image completed.\n" );



// Define Scene 2.

	Scene scene2;
	DefineScene2( scene2, imageWidth2, imageHeight2 );

// Render Scene 2.

	printf( "Render Scene 2...\n" );
	RenderImage( "out2.png", scene2, reflectLevels2, hasShadow2 );
	printf( "Image completed.\n" );


	printf( "All done.\n" );
	return 0;
}





///////////////////////////////////////////////////////////////////////////
// Modeling of Scene 1.
///////////////////////////////////////////////////////////////////////////

void DefineScene1( Scene &scene, int imageWidth, int imageHeight )
{
	scene.backgroundColor = Color( 0.2f, 0.3f, 0.5f );

	scene.amLight.I_a = Color( 1.0f, 1.0f, 1.0f ) * 0.25f;

// Define materials.

	scene.numMaterials = 5;
	scene.material = new Material[ scene.numMaterials ];

	// Light red.
	scene.material[0].k_d = Color( 0.8f, 0.4f, 0.4f );
	scene.material[0].k_a = scene.material[0].k_d;
	scene.material[0].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
	scene.material[0].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
	scene.material[0].n = 64.0f;

	// Light green.
	scene.material[1].k_d = Color( 0.4f, 0.8f, 0.4f );
	scene.material[1].k_a = scene.material[0].k_d;
	scene.material[1].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
	scene.material[1].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
	scene.material[1].n = 64.0f;

	// Light blue.
	scene.material[2].k_d = Color( 0.4f, 0.4f, 0.8f ) * 0.9f;
	scene.material[2].k_a = scene.material[0].k_d;
	scene.material[2].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
	scene.material[2].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 2.5f;
	scene.material[2].n = 64.0f;

	// Yellow.
	scene.material[3].k_d = Color( 0.6f, 0.6f, 0.2f );
	scene.material[3].k_a = scene.material[0].k_d;
	scene.material[3].k_r = Color( 0.8f, 0.8f, 0.8f ) / 1.5f;
	scene.material[3].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
	scene.material[3].n = 64.0f;

	// Gray.
	scene.material[4].k_d = Color( 0.6f, 0.6f, 0.6f );
	scene.material[4].k_a = scene.material[0].k_d;
	scene.material[4].k_r = Color( 0.6f, 0.6f, 0.6f );
	scene.material[4].k_rg = Color( 0.8f, 0.8f, 0.8f ) / 3.0f;
	scene.material[4].n = 128.0f;


// Define point light sources.

	scene.numPtLights = 2;
	scene.ptLight = new PointLightSource[ scene.numPtLights ];

	scene.ptLight[0].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.6f;
	scene.ptLight[0].position = Vector3d( 100.0, 120.0, 10.0 );

	scene.ptLight[1].I_source = Color( 1.0f, 1.0f, 1.0f ) * 0.6f;
	scene.ptLight[1].position = Vector3d( 5.0, 80.0, 60.0 );


// Define surface primitives.

	scene.numSurfaces = 15;
	scene.surfacep = new SurfacePtr[ scene.numSurfaces ];

	scene.surfacep[0] = new Plane( 0.0, 1.0, 0.0, 0.0, &(scene.material[2]) ); // Horizontal plane.
	scene.surfacep[1] = new Plane( 1.0, 0.0, 0.0, 0.0, &(scene.material[4]) ); // Left vertical plane.
	scene.surfacep[2] = new Plane( 0.0, 0.0, 1.0, 0.0, &(scene.material[4]) ); // Right vertical plane.
	scene.surfacep[3] = new Sphere( Vector3d( 40.0, 20.0, 42.0 ), 22.0, &(scene.material[0]) ); // Big sphere.
	scene.surfacep[4] = new Sphere( Vector3d( 75.0, 10.0, 40.0 ), 12.0, &(scene.material[1]) ); // Small sphere.

	// Cube +y face.
	scene.surfacep[5] = new Triangle( Vector3d( 50.0, 20.0, 90.0 ), Vector3d( 50.0, 20.0, 70.0 ),
		                              Vector3d( 30.0, 20.0, 70.0 ), &(scene.material[3]) );
	scene.surfacep[6] = new Triangle( Vector3d( 50.0, 20.0, 90.0 ), Vector3d( 30.0, 20.0, 70.0 ),
		                              Vector3d( 30.0, 20.0, 90.0 ), &(scene.material[3]) );

	// Cube +x face.
	scene.surfacep[7] = new Triangle( Vector3d( 50.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 70.0 ),
		                              Vector3d( 50.0, 20.0, 90.0 ), &(scene.material[3]) );
	scene.surfacep[8] = new Triangle( Vector3d( 50.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 90.0 ),
		                              Vector3d( 50.0, 0.0, 90.0 ), &(scene.material[3]) );

	// Cube -x face.
	scene.surfacep[9] = new Triangle( Vector3d( 30.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 90.0 ),
		                              Vector3d( 30.0, 20.0, 70.0 ), &(scene.material[3]) );
	scene.surfacep[10] = new Triangle( Vector3d( 30.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 70.0 ),
		                              Vector3d( 30.0, 0.0, 70.0 ), &(scene.material[3]) );

	// Cube +z face.
	scene.surfacep[11] = new Triangle( Vector3d( 50.0, 0.0, 90.0 ), Vector3d( 50.0, 20.0, 90.0 ),
		                              Vector3d( 30.0, 20.0, 90.0 ), &(scene.material[3]) );
	scene.surfacep[12] = new Triangle( Vector3d( 50.0, 0.0, 90.0 ), Vector3d( 30.0, 20.0, 90.0 ),
		                              Vector3d( 30.0, 0.0, 90.0 ), &(scene.material[3]) );

	// Cube -z face.
	scene.surfacep[13] = new Triangle( Vector3d( 30.0, 0.0, 70.0 ), Vector3d( 30.0, 20.0, 70.0 ),
		                              Vector3d( 50.0, 20.0, 70.0 ), &(scene.material[3]) );
	scene.surfacep[14] = new Triangle( Vector3d( 30.0, 0.0, 70.0 ), Vector3d( 50.0, 20.0, 70.0 ),
		                              Vector3d( 50.0, 0.0, 70.0 ), &(scene.material[3]) );


// Define camera.

	scene.camera = Camera( Vector3d( 150.0, 120.0, 150.0 ), Vector3d( 45.0, 22.0, 55.0 ), Vector3d( 0.0, 1.0, 0.0 ),
				   (-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, 
				   imageWidth, imageHeight );
}





///////////////////////////////////////////////////////////////////////////
// Modeling of Scene 2.
///////////////////////////////////////////////////////////////////////////

void DefineScene2( Scene &scene, int imageWidth, int imageHeight )
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

	scene.backgroundColor = Color(0.8f, 0.8f, 0.8f);

	scene.amLight.I_a = Color(1.0f, 1.0f, 1.0f) * 0.5f;

	// Define materials.

	scene.numMaterials = 5;
	scene.material = new Material[scene.numMaterials];

	// Light bean red
	scene.material[0].k_d = Color(1.0f, 0.05f, 0.0f);
	scene.material[0].k_a = scene.material[0].k_d;
	scene.material[0].k_r = Color(0.8f, 0.8f, 0.8f) / 1.5f;
	scene.material[0].k_rg = Color(0.8f, 0.8f, 0.8f) / 3.0f;
	scene.material[0].n = 64.0f;

	// Light blue
	scene.material[1].k_d = Color(0.0f, 0.8f, 1.0f);
	scene.material[1].k_a = scene.material[1].k_d;
	scene.material[1].k_r = Color(0.5f, 0.5f, 0.5f) / 1.5f;
	scene.material[1].k_rg = Color(0.8f, 0.8f, 0.8f) / 3.0f;
	scene.material[1].n = 64.0f;

	// Light .
	scene.material[2].k_d = Color(0.61f, 0.86f, 1.0f) * 1.0f;
	scene.material[2].k_a = scene.material[2].k_d;
	scene.material[2].k_r = Color(0.9f, 0.9f, 0.9f) / 1.0f ;
	scene.material[2].k_rg = Color(0.8f, 0.8f, 0.8f) / 2.0f;
	scene.material[2].n = 64.0f;

	// Yellow.
	scene.material[3].k_d = Color(0.0f, 0.16f, 0.47f);
	scene.material[3].k_a = scene.material[3].k_d;
	scene.material[3].k_r = Color(0.8f, 0.8f, 0.8f) / 8.0f;
	scene.material[3].k_rg = Color(0.8f, 0.8f, 0.8f) / 10.0f;
	scene.material[3].n = 64.0f;

	// Gray.
	scene.material[4].k_d = Color(0.6f, 0.6f, 0.6f);
	scene.material[4].k_a = scene.material[0].k_d;
	scene.material[4].k_r = Color(0.6f, 0.6f, 0.6f);
	scene.material[4].k_rg = Color(0.8f, 0.8f, 0.8f) / 3.0f;
	scene.material[4].n = 128.0f;


	// Define point light sources.

	scene.numPtLights = 2;
	scene.ptLight = new PointLightSource[scene.numPtLights];

	scene.ptLight[0].I_source = Color(1.0f, 1.0f, 1.0f) * 0.6f;
	scene.ptLight[0].position = Vector3d(30.0, 300.0, 30.0);

	scene.ptLight[1].I_source = Color(1.0f, 1.0f, 1.0f) * 0.3f;
	scene.ptLight[1].position = Vector3d(100.0, 70.0, 100.0);


	Vector3d v11(0.343, 0, 0.939);//0
	Vector3d v12(0.106, 0.326, 0.939);//1
	Vector3d v13(-0.278, 0.202, 0.939);//2
	Vector3d v14(-0.278, -0.202, 0.939);//3
	Vector3d v15(0.106, -0.326, 0.939);//4

	Vector3d v21(0.687, 0, 0.727);//5
	Vector3d v22(0.212, 0.653, 0.727);//6
	Vector3d v23(-0.555, 0.403, 0.727);//7
	Vector3d v24(-0.555, -0.403, 0.727);//8
	Vector3d v25(0.212, -0.653, 0.727);//9

	Vector3d v31(0.793, -0.326, 0.515);//10
	Vector3d v32(0.793, 0.326, 0.515);//11
	Vector3d v33(0.555, 0.654, 0.515);//12
	Vector3d v34(-0.065, 0.855, 0.515);//13
	Vector3d v35(-0.450, 0.730, 0.515);//14
	Vector3d v36(-0.833, 0.202, 0.515);//15
	Vector3d v37(-0.833, -0.202, 0.515);//16
	Vector3d v38(-0.450, -0.730, 0.515);//17
	Vector3d v39(-0.065, -0.855, 0.515);//18
	Vector3d v310(0.555, -0.654, 0.515);//19

	Vector3d v41(0.965, -0.202, 0.172);//20
	Vector3d v42(0.965, 0.202, 0.172);//21
	Vector3d v43(0.490, 0.855, 0.172);//22
	Vector3d v44(0.106, 0.980, 0.172);//23
	Vector3d v45(-0.662, 0.730, 0.172);//24
	Vector3d v46(-0.900, 0.404, 0.172);//25
	Vector3d v47(-0.900, -0.404, 0.172);//26
	Vector3d v48(-0.662, -0.730, 0.172);//27
	Vector3d v49(0.106, -0.980, 0.172);//28
	Vector3d v410(0.490, -0.855, 0.172);//29



	Vector3d v51(0.899, 0.403, -0.172);//30
	Vector3d v52(0.661, 0.730, -0.172);//31
	Vector3d v53(-0.106, 0.979, -0.172);//32
	Vector3d v54(-0.490, 0.855, -0.172);//33
	Vector3d v55(-0.964, 0.201, -0.172);//34
	Vector3d v56(-0.965, -0.202, -0.172);//35
	Vector3d v57(-0.490, -0.855, -0.172);//36
	Vector3d v58(-0.106, -0.979, -0.172);//37
	Vector3d v59(0.6611, -0.730, -0.172);//38
	Vector3d v510(0.898, -0.403, -0.172);//39

	Vector3d v61(0.833, 0.202, -0.515);//40
	Vector3d v62(0.449, 0.729, -0.515);//41
	Vector3d v63(0.0645, 0.855, -0.515);//42
	Vector3d v64(-0.555, 0.653, -0.515);//43
	Vector3d v65(-0.793, 0.326, -0.515);//44
	Vector3d v66(-0.792, -0.325, -0.515);//45
	Vector3d v67(-0.555, -0.653, -0.515);//46
	Vector3d v68(0.0650, -0.855, -0.515);//47
	Vector3d v69(0.449, -0.729, -0.515);//48
	Vector3d v610(0.833, -0.202, -0.515);//49

	Vector3d v71(0.555, 0.403, -0.727);//50
	Vector3d v72(-0.212, 0.652, -0.727);//51
	Vector3d v73(-0.685, 0, -0.727);//52
	Vector3d v74(-0.2126, -0.652, -0.727);//53
	Vector3d v75(0.555, -0.403, -0.727);//54

	Vector3d v81(0.277, 0.201, -0.939);//55
	Vector3d v82(-0.105, 0.326, -0.939);//56
	Vector3d v83(-0.343, 0, -0.939);//57
	Vector3d v84(-0.106, -0.326, -0.939);//58
	Vector3d v85(0.277, -0.201, -0.939);//59

	Vector3d vertex[] = {
		v11, v12, v13, v14, v15,
		v21, v22, v23, v24, v25,
		v31, v32, v33, v34, v35, v36, v37, v38, v39, v310,
		v41, v42, v43, v44, v45, v46, v47, v48, v49, v410,
		v51, v52, v53, v54, v55, v56, v57, v58, v59, v510,
		v61, v62, v63, v64, v65, v66, v67, v68, v69, v610,
		v71, v72, v73, v74, v75, 
		v81, v82, v83, v84, v85,	
	};








	// Define surface primitives.

	scene.numSurfaces = 2 +
		60 +
		5 * 6 +
		5 * 6 +
		15 * 6 +
		15 * 6 +

		10 * 6 +

		15 * 6 +
		15 * 6 +
		5 * 6 +
		5 * 6
		;
	scene.surfacep = new SurfacePtr[scene.numSurfaces];

	scene.surfacep[0] = new Plane(0.0, 1.0, 0.0, 0.0, &(scene.material[3])); // Horizontal plane.
	scene.surfacep[1] = new Plane(1.0, 0.0, 0.0, 0.0, &(scene.material[2])); // Left vertical plane.
	scene.surfacep[2] = new Plane(0.0, 0.0, 1.0, 0.0, &(scene.material[2])); // Right vertical plane.
	int counter = 3;
	
	int radius = 5;
	int half = radius / 1.2;

	Vector3d translate(100, 70, 100);
	Vector3d scale(50.0, 50.0, 50.0);

	for (int i = 0; i < 60; i++) {
		vertex[i] *= scale;
		vertex[i] += translate;
		scene.surfacep[counter] = new Sphere(vertex[i], radius, &(scene.material[0]));
		counter += 1;
		
	}

	
	// level 1
	for (int i = 0; i < 5; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[(i + 1) % 5];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	// level 2
	for (int i = 5; i < 10; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i - 5];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	


	// level 3
	for (int i = 10; i < 20; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i / 2];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	
	for (int i = 10; i < 20; i+=2) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = i == 10 ? vertex[19] : vertex[i - 1];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}






	// level 4
	for (int i = 20; i < 30; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i - 10];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	for (int i = 20; i < 30; i += 2) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i +1];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}
	


	// level 4.5
	for (int i = 30; i < 40; i++ ) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = i ==39  ? vertex[20] : vertex[i - 9];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}


	
	// level 5
	for (int i = 30; i < 40; i += 2) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i + 1];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}


	for (int i = 30; i < 40; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i + 10];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	




	// level 6
	for (int i = 40; i < 50; i += 2) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = i == 40 ? vertex[49] : vertex[i - 1];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}
	

	for (int i = 40; i < 50; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[(i - 40) / 2 + 50];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}

	
	// level 7
	for (int i = 50; i < 55; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = vertex[i + 5];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);

		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}
	
	
	// level 8
	for (int i = 55; i < 60; i++) {
		Vector3d vertex1 = vertex[i];
		Vector3d vertex2 = i == 59 ? vertex[55] : vertex[i + 1];
		Vector3d midPoint(vertex1 / 2 + vertex2 / 2);
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(-half, 0, 0), vertex1 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, -half, 0), vertex1 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex1 + Vector3d(0, 0, -half), vertex1 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(-half, 0, 0), vertex2 + Vector3d(half, 0, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, -half, 0), vertex2 + Vector3d(0, half, 0), midPoint, &(scene.material[1]));
		counter += 1;
		scene.surfacep[counter] = new Triangle(vertex2 + Vector3d(0, 0, -half), vertex2 + Vector3d(0, 0, half), midPoint, &(scene.material[1]));
		counter += 1;
	}
	
	
	scene.camera = Camera(Vector3d(330.0, 20, 330.0), Vector3d(100, 70, 100), Vector3d(0.0, 1.0, 0.0),
		(-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, imageWidth, imageHeight);
	//scene.camera = Camera(Vector3d(350.0, 200, 400.0), Vector3d(100, 70, 100), Vector3d(0.0, 1.0, 0.0),
		//(-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, imageWidth, imageHeight);
	//scene.camera = Camera(Vector3d(350.0, 300, 400.0), Vector3d(100, 30, 100), Vector3d(0.0, 1.0, 0.0),
		//(-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, imageWidth, imageHeight);
//	scene.camera = Camera(Vector3d(50.0, 30.0, -300.0), Vector3d(50.0, 50.0, 50.0), Vector3d(0.0, 1.0, 0.0),
	//	(-1.0 * imageWidth) / imageHeight, (1.0 * imageWidth) / imageHeight, -1.0, 1.0, 3.0, imageWidth, imageHeight);

}
