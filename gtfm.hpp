#ifndef GTFM_H
#define GTFM_H

#include "qbVector.h"
#include "qbVector2.h"
#include "qbVector3.h"
#include "qbVector4.h"
#include "qbMatrix.h"
#include "ray.hpp"

namespace qbRT
{
	// Define direction flag values.
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;
	
	class GTform
	{
		public:
			// Constructor & destructor.
			GTform();
			~GTform();
			
			// Construct from three vectors.
			GTform(const qbVector3<double> &translation, const qbVector3<double> &rotation, const qbVector3<double> &scale);
			
			// Construct from a pair of matrices.
			GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
			
			// Function to set translation, rotation and scale components.
			void SetTransform(	const qbVector3<double> &translation,
													const qbVector3<double> &rotation,
													const qbVector3<double> &scale);
													
			void SetTransform(	const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
													
			// Functions to return the transform matrices.
			qbMatrix2<double> GetForward();
			qbMatrix2<double> GetBackward();
			
			// Function to apply the transform.
			qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
			qbVector3<double> Apply(const qbVector3<double> &inputVector, bool dirFlag);
			qbVector3<double> ApplyNorm(const qbVector3<double> &inputVector);
			
			// Function to return the normal transform matrix.
			qbMatrix2<double> GetNormalTransform();
			
			// Overload operators.
			friend GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs);
			
			// Overload the assignment operator.
			GTform operator= (const GTform &rhs);
			
			// Function to print transform matrix to STDOUT.
			void PrintMatrix(bool dirFlag);
			
			// Function to allow printing of vectors.
			static void PrintVector(const qbVector3<double> &vector);
			
		private:
			void Print(const qbMatrix2<double> &matrix);
			void ExtractLinearTransform();
			
		private:
			qbMatrix2<double> m_fwdtfm {4, 4};
			qbMatrix2<double> m_bcktfm {4, 4};
			qbMatrix2<double> m_lintfm {3, 3};
	};
}

#endif