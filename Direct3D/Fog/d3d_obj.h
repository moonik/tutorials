#ifndef D3D_OBJ_H
#define D3D_OBJ_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <assert.h>
#include "vertex_types.h"
#include "camera.h"

// Our 3D Object that allows for rendering and setting 
// projection, view, and world matrices
class CD3DObj
{
public:

	CD3DObj() { /* do nothing */ } // Constructor

	static bool init(HWND hwnd); // Initializes our 3D Object

	static void begin(); // Begins a scene
	static void end(); // Ends a scene

	// Sets all rendering states such as z-buffering, culling, etc
	// to a default state
	static void setDefaultRenderState();
	
	// Fog methods -- Return true on success, false otherwise
	static bool setFogColor(DWORD color);
	static bool setPixelFogMode(D3DFOGMODE mode);
	static bool setVertexFogMode(D3DFOGMODE mode);
	static bool setFogStart(float start);
	static bool setFogEnd(float end);
	static bool setFogDensity(float density);
	
	// Turns fog on or off
	static bool setFogActive(bool onOrOff);

	// Goes between windowed and full screen
	static bool toggleFullScreen();

	// Renders a list of SVertex as triangles
	static bool render(SVertex *vertList, int numVerts);

	// Renders a indexed list of SVertex as triangles
	static bool render(SVertex *vertList, int numVerts, WORD *indexList, int numIndices);

	// Renders a list of SVertex as line segments
	static bool renderLine(SVertex *vertList, int numVerts);

	// Functions to set either the projection, view, or world matrix
	static void setProjMatrix(float fov, float aspectRatio, float nearClip, float farClip);
	static void setViewMatrix(const CPos &eye, const CPos &target);
	static void setViewMatrix(const CCamera *camera);
	static void setWorldMatrix(const D3DXMATRIX *matrix);

	// Clears the viewport color and z-buffer
	static bool clear(int color = D3DCOLOR_XRGB(0,0,0), float zDepth = 1.0f);

	static void deinit(); // Free up our 3D Object

	~CD3DObj() { /* do nothing */ }; // Deconstuctor

	// This is our D3D interface used to create other D3D objects/interfaces.
	static IDirect3D9 *mInterface;

	// This is our D3D device which allows "direct" access to the graphics card
	// It is our main device for primitive rendering functionality
	static IDirect3DDevice9 *mDevice;

private:

	static HRESULT mResult; // Used for error checking
	static bool mFullScreen; // True if we're full screen, false otherwise
	static HWND mHWND; // Copy of the window's hwnd

	// Perspective matrix parameters
	static float mFOV; // Field of view
	static float mNearClip; // Near clip plane
	static float mFarClip; // Far clip plane
	static float mAspectRatio; // Width / Height of viewable screen

	static bool createDevice(); // Creates the IDirect3DDevice9
	static void setPresentationParams(D3DPRESENT_PARAMETERS &params); // Fills D3DPRESENT_PARAMETERS
	
	// We make the copy constructor and assignment operator private because
	// we do NOT want anyone accidentally making a copy of this class
	CD3DObj(const CD3DObj &obj) {}
	CD3DObj& operator =(CD3DObj &obj) { return *this; }
};

// Here we define our global 3D object
extern CD3DObj *g3D;

#endif

/*#ifndef D3D_OBJ_H
#define D3D_OBJ_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3d9caps.h>
#include "vertex_types.h"
#include "camera.h"

const float kPi = 3.14159265f;
const float kPiOver180 = kPi / 180.0f;

#define DEG2RAD(x) (x * kPiOver180) // Converts degrees to radians

// Creates an ARGB color
#define ARGB(A, R, G, B) ( (int)((A & 0xFF) << 24 | \
								 (R & 0xFF) << 16 | \
								 (G & 0xFF) << 8 | \
								 (B & 0xFF)) )
								 
// Gets the A, R, G, and B from an ARGB color								 
#define GET_A(c) ((c >> 24) & 0xFF)
#define GET_R(c) ((c >> 16) & 0xFF)
#define GET_G(c) ((c >> 8) & 0xFF)
#define GET_B(c) (c & 0xFF)

const float kFOV = DEG2RAD(60); // Default Field Of View
const float kNearClip = 1.0f; // Default Near Clip Plane
const float kFarClip = 8192.0f; // Default Far Clip Plane

// Here is our 3D Object to handle all of our 3D needs -- It will create our needed D3D interfaces
// and allow us to render a list or vertices of a vertex type that we created
class CD3DObj
{
	public:

		CD3DObj(); // Constructor

		bool init(HWND hwnd); // Initializes our 3D Object
		void initToDefaultParams(); // Initializes all parameters to a default value

		void begin(); // Begins a scene
		void end(); // Ends a scene

		void setViewMatrix(const CCamera *camera); // Sets the view matrix based on "camera"
		void setProjMatrix(); // Sets the projection matrix
		void setWorldMatrix(int which, D3DXMATRIX *matrix); // Sets a world matrix
		
		// Fog methods -- Return true on success, false otherwise
		bool setFogStatus(bool onOrOff);
		bool setFogColor(int color);
		bool setPixelFogMode(D3DFOGMODE mode);
		bool setVertexFogMode(D3DFOGMODE mode);
		bool setFogStart(float start);
		bool setFogEnd(float end);
		bool setFogDensity(float density);

		// Renders the passed in vertex list using the passed in index list
		bool render(SVertex *vList, int vertCount, WORD *iList, int indexCount);

		// Clears the viewport's color and Z-buffer 
		bool clear(int color = D3DCOLOR_XRGB(0,0,0), float zDepth = 1.0f);

		~CD3DObj(); // Deconstructor
		
	private:

		// We'll use this to create other D3D objects/interfaces.
		IDirect3D9 *d3d_interface;
		
		// We'll use this for all our rendering needs
		IDirect3DDevice9 *d3d_device;

		float fov; // Field of view
		float aspect_ratio; // Aspect ratio
		float near_clip; // Near clip plane
		float far_clip; // Far clip plane
		
		HRESULT result; // Used for error checking

		// We make the copy constructor and assignment operator private because
		// we do NOT want anyone accidentally making a copy of this class
		CD3DObj(const CD3DObj &obj) {}
		CD3DObj& operator =(CD3DObj &obj) { return *this; }
};

// Our global 3D object
extern CD3DObj *g3D;

#endif*/
