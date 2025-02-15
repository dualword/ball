// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: piecewisePolynomial.C,v 1.9 2003/08/26 09:17:51 oliver Exp $
//

#include <BALL/MATHS/piecewisePolynomial.h>

#include <cmath>

using namespace std;

namespace BALL
{
	
	PiecewisePolynomial::PiecewisePolynomial() 
		:	PiecewiseFunction(),
			degree_(0)
	{
	}

	PiecewisePolynomial::PiecewisePolynomial(const PiecewisePolynomial& poly)
		:	PiecewiseFunction(poly),
			degree_(poly.degree_)
	{
	}

	PiecewisePolynomial::PiecewisePolynomial(Size degree, 
			const std::vector<Interval>& intervals, 
			const std::vector<Coefficients>& coefficients) 
		:	PiecewiseFunction(intervals, coefficients),
			degree_(degree)
	{
	}


	PiecewisePolynomial::~PiecewisePolynomial() 
	{
		clear();

		valid_ = false;
	}


	void PiecewisePolynomial::set(Size degree,
			const std::vector<Interval>& intervals,
			const std::vector<Coefficients>& coeffs) 
	{
		PiecewiseFunction::set(intervals, coeffs);
		degree_ = degree;
	}


	void PiecewisePolynomial::clear() 
	{
		degree_ = 0;

		PiecewiseFunction::clear();
	}


	PiecewisePolynomial& PiecewisePolynomial::operator =
		(const PiecewisePolynomial& poly) 
	{
		PiecewiseFunction::operator = (poly);
		degree_ = poly.degree_;

		return *this;
	}


	void PiecewisePolynomial::setDegree(Size degree) 
	{
		degree_ = degree;
	}


	Size PiecewisePolynomial::getDegree() const 
	{
		return degree_;
	}


	double PiecewisePolynomial::operator () (double x) const 
	{
		// ?????
		if (!isInRange(x))
		{
			Log.error() << "PiecewisePolynomial::operator () (): x is not in range" 
				<< endl;
			return 0;
		}
		else
		{
			Position k = getIntervalIndex(x);
			double val = 0.0;
			double sub = intervals_[k].first;
			for (Size i = 0; i < degree_; ++i)
			{
				val += coefficients_[k][i] * pow((x - sub), (int) i);
			}
			return val;
		}
	}


	bool PiecewisePolynomial::operator == (const PiecewisePolynomial& poly)
		const 
	{
		return (PiecewiseFunction::operator == (poly)
			&& (degree_ == poly.degree_));
	}


	void PiecewisePolynomial::dump(ostream& stream, Size /* depth */) const
		 
	{
		stream << "[PiecewisePolynomial: degree " << degree_ << "]" << endl;
		PiecewiseFunction::dump();
	}

}
