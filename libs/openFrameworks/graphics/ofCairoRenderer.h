#pragma once


#include <cairo-features.h>
#include <cairo-pdf.h>
#include <cairo-svg.h>
#include <cairo.h>
#include <deque>
#include <stack>
#include "ofMatrix4x4.h"
#include "ofBaseTypes.h"
#include "ofShape.h"



class ofCairoRenderer: public ofBaseRenderer{
public:
	ofCairoRenderer();
	~ofCairoRenderer();

	enum Type{
		PDF,
		SVG,
		PNG
	};
	void setup(string filename, Type type=ofCairoRenderer::PDF, bool multiPage=true, bool b3D=false);
	void close();

	void draw(ofShape & path);
	void draw(ofPolyline & poly);
	void draw(ofShapeTessellation & shape);
	void draw(ofPrimitive & vertexData);
	void useShapeColor(bool bUseShapeColor);

	bool rendersPathDirectly(){
		return true;
	}

	//--------------------------------------------
	// transformations
	void pushView();
	void popView();

	// setup matrices and viewport (upto you to push and pop view before and after)
	// if width or height are 0, assume windows dimensions (ofGetWidth(), ofGetHeight())
	// if nearDist or farDist are 0 assume defaults (calculated based on width / height)
	void viewport(ofRectangle viewport);
	void viewport(float x = 0, float y = 0, float width = 0, float height = 0, bool invertY = true);
	void setupScreenPerspective(float width = 0, float height = 0, int orientation = 0, bool vFlip = true, float fov = 60, float nearDist = 0, float farDist = 0);
	void setupScreenOrtho(float width = 0, float height = 0, bool vFlip = true, float nearDist = -1, float farDist = 1);
	ofRectangle getCurrentViewport();
	int getViewportWidth();
	int getViewportHeight();

	void setCoordHandedness(ofHandednessType handedness);
	ofHandednessType getCoordHandedness();

	//our openGL wrappers
	void pushMatrix();
	void popMatrix();
	void translate(float x, float y, float z = 0);
	void translate(const ofPoint & p);
	void scale(float xAmnt, float yAmnt, float zAmnt = 1);
	void rotate(float degrees, float vecX, float vecY, float vecZ);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);
	void rotate(float degrees);

	// screen coordinate things / default gl values
	void setupGraphicDefaults();
	void setupScreen();

	// bg color
	ofColor & getBgColor();
	bool bClearBg();
	void background(const ofColor & c);
	void background(float brightness);
	void background(int hexColor, float _a=255.0f);
	void background(int r, int g, int b, int a=255);

	void setBackgroundAuto(bool bManual);		// default is true

	void clear(float r, float g, float b, float a=0);
	void clear(float brightness, float a=0);
	void clearAlpha();

	cairo_t * getCairoContext();
	cairo_surface_t * getCairoSurface();


private:
	void drawPath(const ofShape & path,bool is_subpath=false);
	cairo_matrix_t * getCairoMatrix();
	void setCairoMatrix();
	ofVec3f transform(ofVec3f vec);

	deque<ofPoint> curvePoints;
	bool bUseShapeColor;
	cairo_t * cr;
	cairo_surface_t * surface;
	bool bBackgroundAuto;
	ofColor bgColor;

	stack<cairo_matrix_t> matrixStack;
	cairo_matrix_t tmpMatrix;

	Type type;
	int page;
	bool multiPage;

	// 3d transformation
	bool b3D;
	ofMatrix4x4 projection;
	ofMatrix4x4 modelView;
	ofRectangle viewportRect;

	stack<ofMatrix4x4> projectionStack;
	stack<ofMatrix4x4> modelViewStack;
	stack<ofRectangle> viewportStack;
};