/****************************************************************************** **																			 ** ** 	Module:		Geometrys.c										 		 ** ** 																		 ** ** 																		 ** ** 	Purpose: 															 ** ** 																		 ** ** 																		 ** ** 																		 ** ** 	Copyright (C) 1992-1995 Apple Computer, Inc.  All rights reserved.	 ** ** 																		 ** ** 																		 ** ** 	Change Log:															 ** ** 																		 ** ** 																		 ** *****************************************************************************/#include <stdlib.h>#include "QD3D.h"#include "QD3DGeometry.h"#include "QD3DTransform.h"#include "QD3DGroup.h"#include "QD3DSet.h"#include "QD3DShader.h"#include "QD3DDrawContext.h"#include "GTShell.h"#include "AttributeSet_Lib.h"#include "QD3DStyle.h"#include "QD3DMath.h"#include "Geometries.h"#include "Textures.h"TextureRec	gTextureEntries[8];/****************************************************************************** **																			 ** **									Defines									 ** **																			 ** *****************************************************************************/#define UVERTICES	11			/* For Scene object */#define VVERTICES	11#define FULLMESH	0			/* Set this to 1 to show a bug in mesh attrib. inheritance (??) *//****************************************************************************** **																			 ** **							Local Declarations								 ** **																			 ** *****************************************************************************/static TQ3GroupObject	BuildBox(	void);		static TQ3GroupObject	BuildGeneralPolygon(	void);	static TQ3GroupObject	BuildLine(	void);	static TQ3GroupObject	BuildMarker(	void);	static TQ3GroupObject	BuildNURBCurve(	void);	static TQ3GroupObject	BuildNURBPatch(	void);	static TQ3GroupObject	BuildTorus(	void);static TQ3GroupObject	BuildCylinder(	void);	static TQ3GroupObject	BuildPoint(	void);	static TQ3GroupObject	BuildPolygon(	void);	static TQ3GroupObject	BuildPolyLine(	void);	static TQ3GroupObject	BuildMesh(	void);	static TQ3GroupObject	BuildCursor(	void);	static TQ3GroupObject	BuildTriangle(	void);	static TQ3GroupObject	BuildTriGrid(	void);	static TQ3GroupObject BuildScene(	void);/****************************************************************************** **																			 ** **							API Routines									 ** **																			 ** *****************************************************************************//*===========================================================================*\ * *	Routine:	BuildGeometry() * *	Comments:	 *\*===========================================================================*/	TQ3GroupObject BuildGeometry(	int type){	TQ3GroupObject	model = NULL;	switch (type) {		case iMarker:			model = BuildMarker();			break;		case iPoint:			model = BuildPoint();			break;		case iLine:			model = BuildLine();			break;		case iPolyline:			model = BuildPolyLine();			break;		case iTriangle:			model = BuildTriangle();			break;		case iPolygon:			model = BuildPolygon();			break;		case iGeneralPolygon:			model = BuildGeneralPolygon();			break;		case iTrigrid:			model = BuildTriGrid();			break;		case iBox:			model = BuildBox();			break;		case iMesh://			model = BuildCursor();			model = BuildMesh();			break;		case iNurbCurve:			model = BuildNURBCurve();			break;		case iNurbPatch:			model = BuildNURBPatch();			break;		case iTorus:			model = BuildTorus();			break;		case iCylinder:			model = BuildCylinder();			break;	}		return (model);	}/****************************************************************************** **																			 ** **							Local Routines									 ** **																			 ** *****************************************************************************//*===========================================================================*\ * *	Routine:	BuildMarker() * *\*===========================================================================*/static TQ3GroupObject BuildMarker(	void){	TQ3GroupObject		model;	TQ3MarkerData		markerData;	TQ3GeometryObject	marker;	TQ3ColorRGB			markerColor;	TQ3Bitmap			*bitmapPtr = &markerData.bitmap;	unsigned char		imageData[] = {							0x7E, 0x3C, 0x3C, 0x66, 0x7E, 0x7C, 0x18,							0x60, 0x60, 0x66, 0x66, 0x60, 0x66, 0x18,							0x7C, 0x3C, 0x60, 0x7E, 0x7C, 0x66, 0x18,							0x60, 0x06, 0x60, 0x66, 0x60, 0x7C, 0x18,							0x60, 0x06, 0x66, 0x66, 0x60, 0x66, 0x00,							0x7E, 0x3C, 0x3C, 0x66, 0x7E, 0x66, 0x18						};		Q3Point3D_Set(&markerData.location, 0, 1, 1);	markerData.xOffset	= -28;	markerData.yOffset	= -3;	markerData.markerAttributeSet = Q3AttributeSet_New();		markerColor.r = 0.8;	markerColor.g = 0.2;	markerColor.b = 0.6;	AttributeSet_AddDiffuseColor(markerData.markerAttributeSet, &markerColor);	bitmapPtr->image	= imageData;	bitmapPtr->width	= 56;	bitmapPtr->height	= 6;	bitmapPtr->rowBytes	= 7;	bitmapPtr->bitOrder	= kQ3EndianBig;		marker = Q3Marker_New(&markerData);	model = Q3OrderedDisplayGroup_New();		if (marker != NULL) {		Q3Group_AddObject(model, marker);				Q3Object_Dispose(marker);	}		Q3Object_Dispose(markerData.markerAttributeSet);	return (model);	}/*===========================================================================*\ * *	Routine:	BuildPoint() * *	Comments:	 *\*===========================================================================*/static TQ3GroupObject BuildPoint(	void){	TQ3GroupObject		model;	TQ3PointData			pointData;	TQ3GeometryObject	pointThang;	TQ3ColorRGB			pointColor;		model = Q3OrderedDisplayGroup_New();	Q3Point3D_Set(&pointData.point, 1, 1, 1);	pointData.pointAttributeSet = NULL;		pointData.pointAttributeSet = Q3AttributeSet_New();			Q3ColorRGB_Set(&pointColor, 0.0, 1.0, 0.0);	AttributeSet_AddDiffuseColor(pointData.pointAttributeSet, &pointColor);	pointThang = Q3Point_New(&pointData);	if (pointThang != NULL) {		Q3Group_AddObject(model, pointThang);		Q3Object_Dispose(pointThang);	}			Q3Object_Dispose(pointData.pointAttributeSet);		return (model);	}/*===========================================================================*\ * *	Routine:	BuildLine() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildLine(	void){	TQ3ColorRGB			lineColor;	TQ3GroupObject		model;	TQ3LineData			lineData;	TQ3GeometryObject	lineThang;	lineData.lineAttributeSet = Q3AttributeSet_New();	lineColor.r = 0.3;	lineColor.g = 0.9;	lineColor.b = 0.9;	AttributeSet_AddDiffuseColor(lineData.lineAttributeSet, &lineColor);	#define DO_TEST_LINE 1#if DO_TEST_LINE	lineData.vertices[0].point.x = -1.0;	lineData.vertices[0].point.y =  0.0;	lineData.vertices[0].point.z =  0.0;	lineData.vertices[0].attributeSet = NULL;		lineData.vertices[1].point.x =  1.0;	lineData.vertices[1].point.y =  0.0;;	lineData.vertices[1].point.z =  0.0;;	lineData.vertices[1].attributeSet = NULL;#else	lineData.vertices[0].point.x = -1.0;	lineData.vertices[0].point.y = -0.5;	lineData.vertices[0].point.z = -0.25;	lineData.vertices[0].attributeSet = NULL;		lineData.vertices[1].point.x =  2.0;	lineData.vertices[1].point.y =  1.5;	lineData.vertices[1].point.z =  2.25;	lineData.vertices[1].attributeSet = NULL;#endif  /*  DO_TEST_LINE  */#undef DO_TEST_LINE	lineThang = Q3Line_New(&lineData);		model = Q3OrderedDisplayGroup_New();		Q3Group_AddObject(model, lineThang);		Q3Object_Dispose(lineData.lineAttributeSet);	Q3Object_Dispose(lineThang);		return (model);	}/*===========================================================================*\ * *	Routine:	BuildPolyLine() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildPolyLine(	void){	TQ3ColorRGB			polyLineColor;	TQ3GroupObject		model;	TQ3PolyLineData		polyLineData;	TQ3GeometryObject	polyLineThang;	static TQ3Vertex3D	points[4] = {							{{ -1.0, -0.5, -0.25 }, NULL },							{{ -0.5,  1.5,  0.45 }, NULL },							{{  0.0,  0.0,  0.0  }, NULL },							{{  1.5,  1.5,  1.0  }, NULL }						};		polyLineData.numVertices 			= 4;	polyLineData.vertices 				= points;	polyLineData.segmentAttributeSet 	= malloc(3 * sizeof(TQ3AttributeSet));		{		unsigned long 	i;		TQ3ColorRGB		segmentColor;				segmentColor.r = 1.0;		segmentColor.g = 0.0;		segmentColor.b = 0.2;				for (i = 0; i < polyLineData.numVertices - 1; i++) {			polyLineData.segmentAttributeSet[i] = NULL;		}				polyLineData.segmentAttributeSet[1] = Q3AttributeSet_New();				AttributeSet_AddDiffuseColor(polyLineData.segmentAttributeSet[1], 									   &segmentColor);	}					polyLineData.polyLineAttributeSet = NULL;	polyLineData.polyLineAttributeSet = Q3AttributeSet_New();	polyLineColor.r = 0.4;	polyLineColor.g = 0.2;	polyLineColor.b = 0.9;	AttributeSet_AddDiffuseColor(polyLineData.polyLineAttributeSet, &polyLineColor);	polyLineThang = Q3PolyLine_New(&polyLineData);		model = Q3OrderedDisplayGroup_New();	Q3Group_AddObject(model, polyLineThang);		Q3Object_Dispose(polyLineData.polyLineAttributeSet);	Q3Object_Dispose(polyLineData.segmentAttributeSet[1]);	free(polyLineData.segmentAttributeSet);	Q3Object_Dispose(polyLineThang);		return (model);}/*===========================================================================*\ * *	Routine:	BuildTriangle() * *	Comments:	 *\*===========================================================================*/static TQ3GroupObject BuildTriangle(	void){	TQ3ColorRGB			triangleColor;	TQ3GroupObject		model;	TQ3TriangleData		triangleData;	TQ3GeometryObject	triangleThang;	static TQ3Vertex3D	vertices[3] = {							{ { -1.0, -0.5, -0.25 }, NULL },							{ {  0.0,  0.0,  0.0  }, NULL },							{ { -0.5,  1.5,  0.45 }, NULL },						};	triangleData.vertices[0] = vertices[0];	triangleData.vertices[1] = vertices[1];	triangleData.vertices[2] = vertices[2];		triangleData.triangleAttributeSet = Q3AttributeSet_New();	triangleColor.r = 0.8;	triangleColor.g = 0.5;	triangleColor.b = 0.2;	AttributeSet_AddDiffuseColor(triangleData.triangleAttributeSet, &triangleColor);	triangleData.vertices[0].attributeSet = Q3AttributeSet_New();	triangleData.vertices[1].attributeSet = Q3AttributeSet_New();	triangleData.vertices[2].attributeSet = Q3AttributeSet_New();	triangleColor.r = 1.0;	triangleColor.g = 0.0;	triangleColor.b = 0.0;	AttributeSet_AddDiffuseColor(triangleData.vertices[0].attributeSet, &triangleColor);	triangleColor.r = 0.0;	triangleColor.g = 1.0;	triangleColor.b = 0.0;	AttributeSet_AddDiffuseColor(triangleData.vertices[1].attributeSet, &triangleColor);	triangleColor.r = 0.0;	triangleColor.g = 0.0;	triangleColor.b = 1.0;	AttributeSet_AddDiffuseColor(triangleData.vertices[2].attributeSet, &triangleColor);	triangleThang = Q3Triangle_New(&triangleData);		model = Q3OrderedDisplayGroup_New();	if (triangleThang != NULL) {		Q3Group_AddObject(model, triangleThang);				Q3Object_Dispose(triangleThang);	}		Q3Object_Dispose(triangleData.vertices[0].attributeSet);	Q3Object_Dispose(triangleData.vertices[1].attributeSet);	Q3Object_Dispose(triangleData.vertices[2].attributeSet);	Q3Object_Dispose(triangleData.triangleAttributeSet);	return (model);	}/*===========================================================================*\ * *	Routine:	BuildPolygon() * *	Comments:	 *\*===========================================================================*/static TQ3GroupObject BuildPolygon(	void){	TQ3GroupObject		model;	TQ3PolygonData		polygonData;	TQ3GeometryObject	polygonThang;	static TQ3Vertex3D	vertices[4] = {							{ { -10.0, 1, 0 }, NULL },							{ { -1.0,  -1.0,  0.0  }, NULL },							{ { 1,  -1.0,  0 }, NULL },							{ { 1.0,  1, 0 }, NULL },						};		polygonData.numVertices 		= 4;	polygonData.vertices 			= vertices;	polygonData.polygonAttributeSet 	= NULL;		polygonThang = Q3Polygon_New(&polygonData);		model = Q3OrderedDisplayGroup_New();	if (polygonThang != NULL) {		Q3Group_AddObject(model, polygonThang);			Q3Object_Dispose(polygonThang);	}	return (model);	}/*===========================================================================*\ * *	Routine:	BuildGeneralPolygon() * *	Comments:	 *\*===========================================================================*/static TQ3GroupObject BuildGeneralPolygon(	void){	TQ3GroupObject					model;	TQ3GeneralPolygonData			genPolyData;	TQ3GeneralPolygonContourData		contours[2];	TQ3GeometryObject				polygonThang;#if 0	static TQ3Vertex3D		vertices1[4] = {								{ { -1.0, -0.5, -0.25 }, NULL },								{ {  0.0,  0.0, -0.25 }, NULL },								{ { -0.5,  1.5, -0.25 }, NULL },								{ { -1.0,  2.5, -0.25 }, NULL }							};							static TQ3Vertex3D		vertices2[4] = {								{ { -0.7, -0.4, -0.25 }, NULL },								{ {  0.2,  0.2, -0.25 }, NULL },								{ { -0.3,  1.2, -0.25 }, NULL },								{ { -1.0,  2.5, -0.25 }, NULL }							};#else	static TQ3Vertex3D		vertices1[3] = {								{ { -1.0,  0.0, 0.0 }, NULL },								{ {  1.0,  0.0, 0.0 }, NULL },								{ {  0.0,  1.7, 0.0 }, NULL }							};							static TQ3Vertex3D		vertices2[3] = {								{ { -1.0,  0.4, 0.0 }, NULL },								{ {  1.0,  0.4, 0.0 }, NULL },								{ {  0.0,  2.1, 0.0 }, NULL }							};#endif	TQ3ColorRGB				color;		contours[0].numVertices 		= 3;	contours[0].vertices 			= vertices1;		contours[1].numVertices 		= 3;	contours[1].vertices 			= vertices2;	genPolyData.numContours 				= 2;	genPolyData.contours 					= contours;	genPolyData.shapeHint					= kQ3GeneralPolygonShapeHintComplex;	genPolyData.generalPolygonAttributeSet 	= Q3AttributeSet_New();		color.r = 1.0; color.g = 1.0; color.b = 1.0;	AttributeSet_AddDiffuseColor(genPolyData.generalPolygonAttributeSet, &color);	vertices1[1].attributeSet = Q3AttributeSet_New();	vertices1[2].attributeSet = Q3AttributeSet_New();		color.r = 0.0; color.g = 0.0; color.b = 1.0;	AttributeSet_AddDiffuseColor(vertices1[1].attributeSet, &color);		color.r = 0.0; color.g = 1.0; color.b = 1.0;	AttributeSet_AddDiffuseColor(vertices1[2].attributeSet, &color);		vertices2[0].attributeSet = Q3AttributeSet_New();	vertices2[2].attributeSet = Q3AttributeSet_New();		color.r = 1.0; color.g = 0.0; color.b = 1.0;	AttributeSet_AddDiffuseColor(vertices2[0].attributeSet, &color);		color.r = 1.0; color.g = 1.0; color.b = 0.0;	AttributeSet_AddDiffuseColor(vertices2[2].attributeSet, &color);		polygonThang = Q3GeneralPolygon_New(&genPolyData);		model = Q3OrderedDisplayGroup_New();		if (polygonThang != NULL) {		Q3Group_AddObject(model, polygonThang);			Q3Object_Dispose(polygonThang);	}	Q3Object_Dispose(vertices1[1].attributeSet);	Q3Object_Dispose(vertices1[2].attributeSet);	Q3Object_Dispose(vertices2[0].attributeSet);	Q3Object_Dispose(vertices2[2].attributeSet);	Q3Object_Dispose(genPolyData.generalPolygonAttributeSet);		return (model);	}/*===========================================================================*\ * *	Routine:	BuildTriGrid() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildTriGrid(	void){	TQ3ColorRGB			triGridColor;	TQ3GroupObject		model;	TQ3TriGridData		triGridData;	TQ3GeometryObject	triGridThang;	unsigned long		numFacets, i;	static TQ3Vertex3D	vertices[12] = {							{ { -1.0,  -1.0,  0.0 }, NULL },							{ { -0.5, -1.0,  0.0 }, NULL },							{ {  0.0,  -1.0,  0.1 }, NULL },							{ {  0.2, -1.3,  0.2 }, NULL },								{ { -1.0,  0.0,  0.0 }, NULL },							{ { -0.5, 0.0,  0.3 }, NULL },							{ {  0.0,  0.2,  0.0 }, NULL },							{ {  0.5, 0.0,  0.0 }, NULL },													{ { -1.0,  1.0,  1.0 }, NULL },							{ { -0.5, 1.0,  0.0 }, NULL },							{ {  0.0,  1.0,  0.0 }, NULL },							{ {  0.7, 1.0,  0.5 }, NULL },						};		triGridData.numRows = 3;	triGridData.numColumns = 4;	triGridData.vertices  = (TQ3Vertex3D *)malloc(12 * sizeof(TQ3Vertex3D));	triGridData.vertices[0] = vertices[0];	triGridData.vertices[1] = vertices[1];	triGridData.vertices[2] = vertices[2];	triGridData.vertices[3] = vertices[3];	triGridData.vertices[4] = vertices[4];	triGridData.vertices[5] = vertices[5];	triGridData.vertices[6] = vertices[6];	triGridData.vertices[7] = vertices[7];	triGridData.vertices[8] = vertices[8];	triGridData.vertices[9] = vertices[9];	triGridData.vertices[10] = vertices[10];	triGridData.vertices[11] = vertices[11];	triGridData.facetAttributeSet = NULL;		triGridData.triGridAttributeSet = Q3AttributeSet_New();		triGridColor.r = 0.8;	triGridColor.g = 0.7;	triGridColor.b = 0.3;	AttributeSet_AddDiffuseColor(triGridData.triGridAttributeSet, &triGridColor);		numFacets = (triGridData.numRows - 1) *  (triGridData.numColumns - 1) *  2 ;	triGridData.facetAttributeSet = malloc(numFacets * sizeof(TQ3AttributeSet));		for (i = 0; i < numFacets; i++) {		triGridData.facetAttributeSet[i] = NULL;	}		triGridColor.r = 1.0;	triGridColor.g = 0.0;	triGridColor.b = 0.5;											  	triGridData.facetAttributeSet[5] = Q3AttributeSet_New();							AttributeSet_AddDiffuseColor(triGridData.facetAttributeSet[5], &triGridColor);		triGridThang = Q3TriGrid_New(&triGridData);		model = Q3OrderedDisplayGroup_New();		Q3Group_AddObject(model, triGridThang);			Q3Object_Dispose(triGridThang);	Q3Object_Dispose(triGridData.triGridAttributeSet);	Q3Object_Dispose(triGridData.facetAttributeSet[5]);	free(triGridData.facetAttributeSet);	return (model);	}/*===========================================================================*\ * *	Routine:	BuildBox() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildBox(	void){	TQ3ColorRGB			faceColor;	TQ3GroupObject		model;	TQ3BoxData			boxData;	TQ3GeometryObject	boxThang;		Q3Point3D_Set(&boxData.origin, 0, 0, 0);	Q3Vector3D_Set(&boxData.orientation, 0, 1, 0);	Q3Vector3D_Set(&boxData.majorAxis, 0, 0, 1);		Q3Vector3D_Set(&boxData.minorAxis, 1, 0, 0);		boxData.boxAttributeSet = Q3AttributeSet_New();	faceColor.r = 0.9;	faceColor.g = 0.9;	faceColor.b = 0.2;	AttributeSet_AddDiffuseColor(boxData.boxAttributeSet, &faceColor);	boxData.faceAttributeSet = NULL;			boxData.faceAttributeSet = malloc(6 * sizeof(TQ3AttributeSet));		{		register unsigned long i;				for (i = 0; i < 6; i++) {			boxData.faceAttributeSet[i] = NULL;		}	}		if(gTextureEntries[0].shader != NULL)	{				boxData.faceAttributeSet[0] = Q3AttributeSet_New();				AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[0],			(TQ3SurfaceShaderObject *)&gTextureEntries[0].shader);	}		if(gTextureEntries[1].shader != NULL)	{				boxData.faceAttributeSet[1] = Q3AttributeSet_New();				AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[1],			(TQ3SurfaceShaderObject *)&gTextureEntries[1].shader);				Q3Object_Dispose(gTextureEntries[1].shader);	}		boxData.faceAttributeSet[2] = Q3AttributeSet_New();	if(gTextureEntries[2].shader != NULL)	{		AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[2],			(TQ3SurfaceShaderObject *)&gTextureEntries[2].shader);	}	faceColor.r = 0.3;	faceColor.g = 0.9;	faceColor.b = 0.9;	AttributeSet_AddDiffuseColor(boxData.faceAttributeSet[2], &faceColor);		boxData.faceAttributeSet[3] = Q3AttributeSet_New();	if(gTextureEntries[3].shader != NULL)	{		AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[3],			(TQ3SurfaceShaderObject *)&gTextureEntries[3].shader);	}	faceColor.r = 0.5;	faceColor.g = 0.5;	faceColor.b = 0.5;	AttributeSet_AddTransparencyColor(boxData.faceAttributeSet[3], &faceColor);	faceColor.r = 0.4;	faceColor.g = 0.4;	faceColor.b = 0.4;	AttributeSet_AddDiffuseColor(boxData.faceAttributeSet[3], &faceColor);		if(gTextureEntries[4].shader != NULL)	{				boxData.faceAttributeSet[4] = Q3AttributeSet_New();				AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[4],			(TQ3SurfaceShaderObject *)&gTextureEntries[4].shader);	}		if(gTextureEntries[5].shader != NULL)	{				boxData.faceAttributeSet[5] = Q3AttributeSet_New();				AttributeSet_AddSurfaceShader(			boxData.faceAttributeSet[5],			(TQ3SurfaceShaderObject *)&gTextureEntries[5].shader);	}		boxThang = Q3Box_New(&boxData);		model = Q3OrderedDisplayGroup_New();	Q3Group_AddObject(model, boxThang);			{		register unsigned long i;				for (i = 0; i < 6; i++) {			if(boxData.faceAttributeSet[i] != NULL)			{				Q3Object_Dispose(boxData.faceAttributeSet[i]);			}		}	}	Q3Object_Dispose(boxData.boxAttributeSet);	free(boxData.faceAttributeSet);	Q3Object_Dispose(boxThang);		return (model);	}/*===========================================================================*\ * *	Routine:	BuildNURBCurve() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildNURBCurve(	void){	TQ3ColorRGB			curveColor;	TQ3GroupObject		model;	TQ3NURBCurveData	curveData;	TQ3GeometryObject	curveThang;	static TQ3RationalPoint4D	points[7] = {							{ 0.0,  0.0,  0.0, 1.0 },							{ 1.0,  1.0,  0.0, 1.0 },							{ 2.0,  0.0,  0.0, 1.0 },							{ 3.0,  1.0,  0.0, 1.0 },							{ 4.0,  0.0,  0.0, 1.0 },							{ 5.0,  1.0,  0.0, 1.0 },							{ 6.0,  0.0,  0.0, 1.0 },						};	static float		knots[11] = {							0, 0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1, 1						};		curveData.order 					= 4;	curveData.numPoints					= 7;	curveData.controlPoints			 	= points;	curveData.knots 					= knots;	curveData.curveAttributeSet 		= Q3AttributeSet_New();		curveColor.r = 0.8;	curveColor.g = 0.2;	curveColor.b = 0.6;	AttributeSet_AddDiffuseColor(curveData.curveAttributeSet, &curveColor);		curveThang = Q3NURBCurve_New(&curveData);		model = Q3OrderedDisplayGroup_New();	Q3Group_AddObject(model, curveThang);		Q3Object_Dispose(curveData.curveAttributeSet);	Q3Object_Dispose(curveThang);		{		unsigned long 		i;		TQ3MarkerData		markerData;		TQ3GeometryObject	markerThang;		TQ3ColorRGB			markerColor;		TQ3Bitmap			*bitmapPtr = &markerData.bitmap;		unsigned char		imageData[] = { 0x20, 0x50, 0x88, 0x50, 0x20 };			bitmapPtr->image 	= imageData;		bitmapPtr->width 	= 5;		bitmapPtr->height 	= 5;		bitmapPtr->rowBytes = 1;		bitmapPtr->bitOrder = kQ3EndianBig;		Q3ColorRGB_Set(&markerColor, 0.1, 1.0, 0.6);		markerData.xOffset	= -2;		markerData.yOffset	= -2;		markerData.markerAttributeSet = Q3AttributeSet_New();				AttributeSet_AddDiffuseColor(markerData.markerAttributeSet, 									   &markerColor);						for (i = 0; i < curveData.numPoints; i++) {			Q3Point3D_Set(&markerData.location, 						  points[i].x / points[i].w,						  points[i].y / points[i].w,						  points[i].z / points[i].w);							markerThang = Q3Marker_New(&markerData);			Q3Group_AddObject(model, markerThang);			Q3Object_Dispose(markerThang);		}				Q3Object_Dispose(markerData.markerAttributeSet);	}	return (model);	}static TQ3GroupObject BuildNURBPatch(	void){	TQ3GroupObject						model;	TQ3NURBPatchData					patchData;	TQ3GeometryObject					patchThang;	TQ3NURBPatchTrimLoopData			trimLoops[2];	TQ3NURBPatchTrimCurveData			trimCurveZero, trimCurveOne;			static TQ3RationalPoint4D	vertices[12] = {							{ -2.0, -2.0, 0, 1.0 },							{ -1.0, -2.0, 1, 1.0 },							{  1.0, -2.0, 0, 1.0 },							{  2.0, -2.0, 0, 1.0 },							{ -2.0, -1.0, 0, 1.0 },							{ -1.0, -1.0, 1, 1.0 },							{  1.0, -1.0, -1, 1.0 },							{  2.0, -1.0, -1, 1.0 },							{ -2.0, -0.0, 0, 1.0 },							{ -1.0, -0.0, 0, 1.0 },							{  1.0, -0.0, 0, 1.0 },							{  2.0, -0.0, 0, 1.0 },						};							static float		vKnots[6] = {							0, 0, 0, 1, 1, 1						};	static float		uKnots[8] = {							0, 0, 0, 0, 1, 1, 1, 1, 						};	static TQ3RationalPoint3D	trimPointsZero[5] = {							{ 0.1, 0.1, 1.0 },							{ 0.9, 0.1, 1.0 },							{ 0.4, 0.4, 1.0 },							{ 0.1, 0.4, 1.0 },							{ 0.1, 0.1, 1.0 },						};				static float		trimKnotsZero[9] = {							0, 0, 0, 0, 0.5, 1, 1, 1, 1							};							static TQ3RationalPoint3D	trimPointsOne[5] = {							{ 0.3, 0.6, 1.0 },							{ 0.9, 0.6, 1.0 },							{ 0.4, 0.9, 1.0 },							{ 0.2, 0.9, 1.0 },							{ 0.3, 0.6, 1.0 },						};				static float		trimKnotsOne[9] = {							0, 0, 0, 0, 0.5, 1, 1, 1, 1							};						trimLoops[0].numTrimCurves 	= 1;	trimLoops[0].trimCurves		= &trimCurveZero;			trimCurveZero.order			= 4;	trimCurveZero.numPoints		= 5;	trimCurveZero.knots			= trimKnotsZero;	trimCurveZero.controlPoints = trimPointsZero;		trimLoops[1].numTrimCurves 	= 1;	trimLoops[1].trimCurves		= &trimCurveOne;			trimCurveOne.order			= 4;	trimCurveOne.numPoints		= 5;	trimCurveOne.knots			= trimKnotsOne;	trimCurveOne.controlPoints 	= trimPointsOne;								patchData.uOrder			= 4;	patchData.vOrder			= 3;	patchData.numColumns		= 4;	patchData.numRows			= 3;	patchData.uKnots			= uKnots;	patchData.vKnots			= vKnots;	patchData.controlPoints 	= vertices;#if 0	patchData.numTrimLoops		= 2;	patchData.trimLoops 		= trimLoops;#else	patchData.numTrimLoops		= 0;	patchData.trimLoops 		= NULL;#endif  /*  ESCHER_VER_15  */		patchData.patchAttributeSet = Q3AttributeSet_New();	{		TQ3ColorRGB	patchColor;				Q3ColorRGB_Set(&patchColor, 0.9, 0.2, 0.9);		AttributeSet_AddDiffuseColor(patchData.patchAttributeSet, &patchColor);	}		patchThang = Q3NURBPatch_New(&patchData);		model = Q3OrderedDisplayGroup_New();		Q3Group_AddObject(model, patchThang);		Q3Object_Dispose(patchThang);	Q3Object_Dispose(patchData.patchAttributeSet);	{		unsigned long 		i;		TQ3MarkerData		markerData;		TQ3GeometryObject	markerThang;		TQ3ColorRGB			markerColor;		TQ3Bitmap			*bitmapPtr = &markerData.bitmap;		unsigned char		imageData[] = { 0x20, 0x50, 0x88, 0x50, 0x20 };			bitmapPtr->image 	= imageData;		bitmapPtr->width 	= 5;		bitmapPtr->height 	= 5;		bitmapPtr->rowBytes = 1;		bitmapPtr->bitOrder = kQ3EndianBig;		Q3ColorRGB_Set(&markerColor, 0.1, 1.0, 0.6);		markerData.xOffset	= -2;		markerData.yOffset	= -2;		markerData.markerAttributeSet = Q3AttributeSet_New();				AttributeSet_AddDiffuseColor(markerData.markerAttributeSet, 									   &markerColor);						for (i = 0; i < patchData.numColumns * patchData.numRows; i++) {			Q3Point3D_Set(&markerData.location, 						  vertices[i].x / vertices[i].w,						  vertices[i].y / vertices[i].w,						  vertices[i].z / vertices[i].w);						  							markerThang = Q3Marker_New(&markerData);			Q3Group_AddObject(model, markerThang);			Q3Object_Dispose(markerThang);		}				Q3Object_Dispose(markerData.markerAttributeSet);	}		return (model);	}/*===========================================================================*\ * *	Routine:	BuildCursor_NewQuadFace() * *	Comments:	Builds a quad face. *\*===========================================================================*/static TQ3MeshFace BuildCursor_NewQuadFace (	TQ3GeometryObject	mesh,	TQ3MeshVertex		vertex[],	int					index0,	int					index1,	int					index2,	int					index3){	TQ3MeshFace			result;	TQ3MeshVertex		v[4];		v[0] = vertex[index0];	v[1] = vertex[index1];	v[2] = vertex[index2];	v[3] = vertex[index3];		result = Q3Mesh_FaceNew(mesh, 4, v, NULL);		return (result);}/*===========================================================================*\ * *	Routine:	BuildCursor_NewQuads() * *	Comments:	Builds a quadralateral from the given points. *\*===========================================================================*/static TQ3Status BuildCursor_NewQuads (	TQ3GeometryObject	mesh,	unsigned long		faceMask,	float x0, float y0, float z0,	float x1, float y1, float z1,	float x2, float y2, float z2,	float x3, float y3, float z3,	float x4, float y4, float z4,	float x5, float y5, float z5,	float x6, float y6, float z6,	float x7, float y7, float z7){	TQ3Vertex3D			point;	TQ3MeshVertex		vertex[8];		/*	 *	Make the vertices	 */		point.attributeSet = NULL;	Q3Point3D_Set(&point.point,x0,y0,z0);	if ((vertex[0] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x1,y1,z1);	if ((vertex[1] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x2,y2,z2);	if ((vertex[2] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x3,y3,z3);	if ((vertex[3] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x4,y4,z4);	if ((vertex[4] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x5,y5,z5);	if ((vertex[5] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x6,y6,z6);	if ((vertex[6] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);	Q3Point3D_Set(&point.point,x7,y7,z7);	if ((vertex[7] = Q3Mesh_VertexNew(mesh,&point)) == NULL) return (kQ3Failure);			/*	 *	Make the faces	 */		if (faceMask & (1<<0)) if (BuildCursor_NewQuadFace(mesh,vertex,0,3,2,1) == NULL) return (kQ3Failure);	if (faceMask & (1<<1)) if (BuildCursor_NewQuadFace(mesh,vertex,4,7,6,5) == NULL) return (kQ3Failure);	if (faceMask & (1<<2)) if (BuildCursor_NewQuadFace(mesh,vertex,4,0,1,5) == NULL) return (kQ3Failure);	if (faceMask & (1<<3)) if (BuildCursor_NewQuadFace(mesh,vertex,7,6,2,3) == NULL) return (kQ3Failure);	if (faceMask & (1<<4)) if (BuildCursor_NewQuadFace(mesh,vertex,4,7,3,0) == NULL) return (kQ3Failure);	if (faceMask & (1<<5)) if (BuildCursor_NewQuadFace(mesh,vertex,5,1,2,6) == NULL) return (kQ3Failure);			return (kQ3Success);}/*===========================================================================*\ * *	Routine:	BuildCursor() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildCursor(	void){	TQ3GeometryObject	mesh			= NULL;	TQ3GroupObject		group			= NULL;		/*	 *	Create the mesh	 */		mesh = Q3Mesh_New ();	if (mesh == NULL) goto bail;		Q3Mesh_DelayUpdates (mesh);			/*	 *	Tip	 */		/*** ??? WOULD THESE BE BETTER DONE WITH MESH CORNERS? ***/		if (BuildCursor_NewQuads (	mesh,							(0<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5),							 0.00,  0.00,  0.00,							 0.00,  0.00,  0.00,							 0.00,  0.00,  0.00,							 0.00,  0.00,  0.00,							 0.50,  0.25,  0.05,							 0.50, -0.25,  0.05,							 0.50, -0.25, -0.05,							 0.50,  0.25, -0.05) != kQ3Success)		goto bail;			/*	 *	Tail	 */		if (BuildCursor_NewQuads (	mesh,							(0<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5),							 0.50,  0.05,  0.05,							 0.50, -0.05,  0.05,							 0.50, -0.05, -0.05,							 0.50,  0.05, -0.05,							 1.00,  0.10,  0.10,							 1.00, -0.10,  0.10,							 1.00, -0.10, -0.10,							 1.00,  0.10, -0.10) != kQ3Success)		goto bail;		Q3Mesh_ResumeUpdates (mesh);			/*	 *	Build the group	 */		group = Q3OrderedDisplayGroup_New ();	if (group == NULL) goto bail;		Q3Group_AddObject (group, mesh);	Q3Object_Dispose (mesh);	mesh = NULL;			return (group);		/*	 *	Error exit	 */		bail:	if (mesh	!= NULL) Q3Object_Dispose (mesh);	if (group	!= NULL) Q3Object_Dispose (group);		return (NULL);}/*===========================================================================*\ * *	Routine:	BuildMesh() * *	Comments:	 *\*===========================================================================*//*	Mesh (		9 # nVertices		{ { -0.5, 	 0.5,	0.0 }, NULL },		{ { -0.5,	-0.5,	0.0 }, NULL },		{ {  0.0,	-0.5, 	0.3 }, NULL },		{ {  0.5, 	-0.5, 	0.0 }, NULL },		{ {  0.5, 	 0.5,	0.0 }, NULL },		{ {  0.0, 	 0.5,	0.3 }, NULL },		{ { -0.4, 	 0.2,	0.0 }, NULL },		{ {  0.0,	 0.0,	0.0 }, NULL },		{ { -0.4, 	-0.2,	0.0 }, NULL },		2 # nFaces		1 # nContours		4 0 1 2 5 # 0		-3 6 7 8 # 2		4 2 3 4 5 # 1	)*/	static TQ3GroupObject BuildMesh(	void){	TQ3ColorRGB			meshColor;	TQ3GroupObject		model;	static TQ3Vertex3D	vertices[9] = {		{ { -0.5, 	 0.5,	0.0 }, NULL },		{ { -0.5,	-0.5,	0.0 }, NULL },		{ {  0.0,	-0.5, 	0.3 }, NULL },		{ {  0.5, 	-0.5, 	0.0 }, NULL },		{ {  0.5, 	 0.5,	0.0 }, NULL },		{ {  0.0, 	 0.5,	0.3 }, NULL },		{ { -0.4, 	 0.2,	0.0 }, NULL },		{ {  0.0,	 0.0,	0.0 }, NULL },		{ { -0.4, 	-0.2,	0.0 }, NULL },						};	static TQ3Param2D	verticesUV[9] = {		{0.0, 1.0}, {0.0, 0.0}, {0.5, 0.0}, {1.0, 0.0},		{1.0, 1.0}, {0.5, 1.0}, {0.1, 0.8}, {0.5, 0.5},		{0.1, 0.4}};			TQ3MeshVertex		meshVertices[9];	TQ3GeometryObject	mesh;	TQ3MeshFace			meshFace;	TQ3AttributeSet	faceAttributes;	unsigned long		i;		mesh = Q3Mesh_New();	Q3Mesh_DelayUpdates( mesh);		for (i = 0; i < 9; i++) {		TQ3AttributeSet vertexASet;				meshVertices[i] = Q3Mesh_VertexNew(mesh, &vertices[i]);		vertexASet = Q3AttributeSet_New();		AttributeSet_AddSurfaceUV(vertexASet, &verticesUV[i]);		Q3Mesh_SetVertexAttributeSet( mesh, meshVertices[i],vertexASet);		Q3Object_Dispose(vertexASet);	}		faceAttributes = Q3AttributeSet_New();	meshColor.r = 0.3;	meshColor.g = 0.9;	meshColor.b = 0.5;	AttributeSet_AddDiffuseColor(faceAttributes, &meshColor);	meshFace = Q3Mesh_FaceNew(mesh, 6, meshVertices, faceAttributes);	Q3Mesh_FaceToContour( mesh,meshFace,Q3Mesh_FaceNew(mesh, 3, &meshVertices[6], NULL));		Q3Mesh_ResumeUpdates( mesh);		model = Q3OrderedDisplayGroup_New();		Q3Group_AddObject(model, mesh);		Q3Object_Dispose(faceAttributes);	Q3Object_Dispose(mesh);		TextureGroup(model) ;	return (model);	}/*===========================================================================*\ * *	Routine:	BuildTorus() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildTorus(	void){	TQ3GroupObject		model;	TQ3TorusData		torusData;	TQ3GeometryObject	torusThang = NULL;	TQ3ColorRGB			color;	Q3Point3D_Set(&torusData.origin,       0.0, 0.0, 0.0);	Q3Vector3D_Set(&torusData.orientation, 0.0, 0.4, 0.0);	Q3Vector3D_Set(&torusData.majorRadius, 0.0, 0.0, 1.0);	Q3Vector3D_Set(&torusData.minorRadius, 1.0, 0.0, 0.0);	torusData.ratio = 0.75;	torusData.uMin = 0.0;	torusData.uMax = 1.0;	torusData.vMin = 0.0;	torusData.vMax = 1.0;	torusData.caps = kQ3EndCapNone;	torusData.interiorAttributeSet = NULL;	torusData.torusAttributeSet = NULL;	/* Add color to bottom */	torusData.torusAttributeSet = Q3AttributeSet_New();	Q3ColorRGB_Set(&color, 0.9, 0.5, 0.0);	AttributeSet_AddDiffuseColor(torusData.torusAttributeSet, &color);		torusThang = Q3Torus_New(&torusData);	model = Q3OrderedDisplayGroup_New();	if (torusThang != NULL) {		Q3Group_AddObject(model, torusThang);			Q3Object_Dispose(torusThang);	}	if (torusData.torusAttributeSet) {		Q3Object_Dispose(torusData.torusAttributeSet);		torusData.torusAttributeSet = NULL;	}	TextureGroup(model);	return model;}/*===========================================================================*\ * *	Routine:	BuildCylinder() * *	Comments:	 *\*===========================================================================*/	static TQ3GroupObject BuildCylinder(	void){	TQ3GroupObject		model;	TQ3CylinderData		cylinderData;	TQ3GeometryObject	cylinderThang = NULL;	TQ3ColorRGB			color;	Q3Point3D_Set(&cylinderData.origin,       0.0,-0.75,0.0);	Q3Vector3D_Set(&cylinderData.orientation, 0.0, 1.0, 0.45);/* z = 0.45 skews the cylinder */	Q3Vector3D_Set(&cylinderData.majorRadius, 0.0, 0.0, 0.75);	Q3Vector3D_Set(&cylinderData.minorRadius, 1.0, 0.0, 0.0);	cylinderData.uMin = 0.0;	cylinderData.uMax = 1.0;	cylinderData.vMin = 0.0;	cylinderData.vMax = 1.0;	cylinderData.caps = kQ3EndCapMaskTop | kQ3EndCapMaskBottom;		cylinderData.interiorAttributeSet = NULL;	cylinderData.topAttributeSet      = NULL;	cylinderData.faceAttributeSet     = NULL;	cylinderData.bottomAttributeSet   = NULL;	cylinderData.cylinderAttributeSet = NULL;	/* Add color to top */	cylinderData.topAttributeSet = Q3AttributeSet_New();	Q3ColorRGB_Set(&color, 0.0, 0.5, 0.9);	AttributeSet_AddDiffuseColor(cylinderData.topAttributeSet, &color);		/* Add color to face */	cylinderData.faceAttributeSet = Q3AttributeSet_New();	Q3ColorRGB_Set(&color, 0.5, 0.9, 0.0);	AttributeSet_AddDiffuseColor(cylinderData.faceAttributeSet, &color);		/* Add color to bottom */	cylinderData.bottomAttributeSet = Q3AttributeSet_New();	Q3ColorRGB_Set(&color, 0.5, 0.0, 0.9);	AttributeSet_AddDiffuseColor(cylinderData.bottomAttributeSet, &color);		/* Add color to cylinder for any remaining parts (the face) *//*	cylinderData.cylinderAttributeSet = Q3AttributeSet_New();	Q3ColorRGB_Set(&color, 0.5, 0.3, 0.0);	AttributeSet_AddDiffuseColor(cylinderData.cylinderAttributeSet, &color);	*/	cylinderThang = Q3Cylinder_New(&cylinderData);	model = Q3OrderedDisplayGroup_New();	if (cylinderThang != NULL) {		Q3Group_AddObject(model, cylinderThang);			Q3Object_Dispose(cylinderThang);	}	if (cylinderData.interiorAttributeSet != NULL) {		Q3Object_Dispose(cylinderData.interiorAttributeSet);		cylinderData.interiorAttributeSet = NULL;	}	if (cylinderData.topAttributeSet != NULL) {		Q3Object_Dispose(cylinderData.topAttributeSet);		cylinderData.topAttributeSet = NULL;	}	if (cylinderData.faceAttributeSet != NULL) {		Q3Object_Dispose(cylinderData.faceAttributeSet);		cylinderData.faceAttributeSet = NULL;	}	if (cylinderData.bottomAttributeSet != NULL) {		Q3Object_Dispose(cylinderData.bottomAttributeSet);		cylinderData.bottomAttributeSet = NULL;	}	if (cylinderData.cylinderAttributeSet != NULL) {		Q3Object_Dispose(cylinderData.cylinderAttributeSet);		cylinderData.cylinderAttributeSet = NULL;	}	TextureGroup(model);	return model;}