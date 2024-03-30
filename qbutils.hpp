#ifndef QBRT_UTILS_H
#define QBRT_UTILS_H

#include <memory>
#include "qbVector.h"
#include "qbVector2.h"
#include "qbVector3.h"
#include "qbVector4.h"
#include "qbMatrix33.h"
#include "qbMatrix44.h"

namespace qbRT
{
	// Forward-declare the object base class.
	class ObjectBase;

	namespace DATA
	{
		struct hitData
		{
			qbVector3<double> poi;
			qbVector3<double> normal;
			qbVector3<double> color;
			qbVector3<double> localPOI;
			qbVector2<double> uvCoords;
			std::shared_ptr<qbRT::ObjectBase> hitObject;
		};
	}

	namespace UTILS
	{
		void PrintVector(const qbVector3<double> &inputVector);
		void PrintMatrix(const qbMatrix33<double> &inputMatrix);
		void PrintMatrix(const qbMatrix44<double> &inputMatrix);
	}
}

#endif

