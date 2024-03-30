// objectbase.hpp

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "../qbutils.hpp"
#include "../ray.hpp"
#include "../gtfm.hpp"
#include "../qbVector.h"
#include "../qbVector2.h"
#include "../qbVector3.h"
#include "../qbVector4.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace qbRT
{
	/* Forward-declare the material base class. This will be
		overriden later. */
	class MaterialBase;
	
	// Define constants for UV mapping types.
	constexpr int uvSPHERE = 0;
	constexpr int uvPLANE = 1;
	constexpr int uvCYLINDER = 2;
	constexpr int uvBOX = 3;	

	class ObjectBase
	{
		public:
			// Constructor and destructor.
			ObjectBase();
			virtual ~ObjectBase();
			
			// Function to test for intersections.
			virtual bool TestIntersection(const Ray &castRay, qbRT::DATA::hitData &hitData);
			
			// ***
			// Function to get the extents of the object.
			virtual void GetExtents(qbVector2<double> &xLim, qbVector2<double> &yLim, qbVector2<double> &zLim);
			virtual void GetExtents(const qbRT::GTform &parentTransformMatrix, qbVector2<double> &xLim, qbVector2<double> &yLim, qbVector2<double> &zLim);
			std::vector<qbVector3<double>> ConstructCube(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);			
			
			// Function to set the transform matrix.
			void SetTransformMatrix(const qbRT::GTform &transformMatrix);
			qbRT::GTform GetTransformMatrix();
			
			// Function to test whether two floating-point numbers are close to being equal.
			bool CloseEnough(const double f1, const double f2);
			
			// Function to assign a material.
			bool AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial);
			
			// Function to compute UV space.
			void ComputeUV(const qbVector3<double> &localPOI, qbVector2<double> &uvCoords);			
			
		// Public member variables.
		public:
			// The user-defined tag for this object.
			std::string m_tag;
		
			// The base colour of the object.
			qbVector3<double> m_baseColor {3};
			
			// The geometric transform applied to the object.
			qbRT::GTform m_transformMatrix;
			
			// A reference to the material assigned to this object.
			std::shared_ptr<qbRT::MaterialBase> m_pMaterial;
			
			// A flag to indicate whether this object has a material or not.
			bool m_hasMaterial = false;
			
			// A flag to indicate whether this object is visible.
			bool m_isVisible = true;
			
			// Store the (u,v) coordinates from a detected intersection.
			qbVector2<double> m_uvCoords;
			
			// Control what type of UV mapping to apply to this object.
			int m_uvMapType = qbRT::uvSPHERE;			
			
			// ***
			// Bounding box GTform.		
			qbRT::GTform m_boundingBoxTransform;
			
			// Bounding box padding.
			double m_boundingBoxPadding = 0.0;			
	};
}

#endif