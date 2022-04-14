
#include "pyramid.h"
#include "pyramid13.h"

#include "basis/containers/serializededata.h"
#include "esinfo/eslog.h"
#include "esinfo/meshinfo.h"
#include "mesh/element.h"
#include "math/matrix.dense.h"

using namespace espreso;

void Pyramid13::setGaussPointsForOrder(int order)
{
	std::vector<double> r, s, t, w;
	if (!Pyramid::gpw(order, r, s, t, w)) {
		eslog::internalFailure("cannot set Gauss points for a given order.\n");
	}

	N->clear(); N->resize(s.size(), MatrixDense(1, nodes));
	dN->clear(); dN->resize(s.size(), MatrixDense(1, nodes));
	weighFactor->assign(w.begin(), w.end());

	for (size_t i = 0; i < r.size(); i++) {
		MatrixDense &m = (*N)[i];

		// basis function
		m(0, 0)  = ((0.5 * (1.0 - t[i])) / 4.0) * ((1.0 - r[i]) * (1.0 - s[i]) * (-1.0 - (0.5 * (1.0 - t[i])) * r[i] - (0.5 * (1.0 - t[i])) * s[i]));
		m(0, 1)  = ((0.5 * (1.0 - t[i])) / 4.0) * ((1.0 + r[i]) * (1.0 - s[i]) * (-1.0 + (0.5 * (1 - t[i]))   * r[i] - (0.5 * (1.0 - t[i])) * s[i]));
		m(0, 2)  = ((0.5 * (1.0 - t[i])) / 4.0) * ((1.0 + r[i]) * (1.0 + s[i]) * (-1.0 + (0.5 * (1.0 - t[i])) * r[i] + (0.5 * (1.0 - t[i])) * s[i]));
		m(0, 3)  = ((0.5 * (1.0 - t[i])) / 4.0) * ((1.0 - r[i]) * (1.0 + s[i]) * (-1.0 - (0.5 * (1.0 - t[i])) * r[i] + (0.5 * (1.0 - t[i])) * s[i]));
		m(0, 4)  = (1.0 - (0.5 * (1.0 - t[i]))) * (1.0 - 2.0 * (0.5 * (1.0 - t[i])));
		m(0, 5)  = (((0.5 * (1.0 - t[i])) * (0.5 * (1.0 - t[i]))) / 2.0) * (1.0 - s[i]) * (1.0 - pow(r[i], 2.0));
		m(0, 6)  = (((0.5 * (1.0 - t[i])) * (0.5 * (1.0 - t[i]))) / 2.0) * (1.0 + r[i]) * (1.0 - pow(s[i], 2.0));
		m(0, 7)  = (((0.5 * (1.0 - t[i])) * (0.5 * (1.0 - t[i]))) / 2.0) * (1.0 + s[i]) * (1.0 - pow(r[i], 2.0));
		m(0, 8)  = (((0.5 * (1.0 - t[i])) * (0.5 * (1.0 - t[i]))) / 2.0) * (1.0 - r[i]) * (1.0 - pow(s[i], 2.0));
		m(0, 9)  = (0.5 * (1.0 - t[i])) * (1.0 - (0.5 * (1.0 - t[i]))) * (1.0 - r[i] - s[i] + r[i] * s[i]);
		m(0, 10) = (0.5 * (1.0 - t[i])) * (1.0 - (0.5 * (1.0 - t[i]))) * (1.0 + r[i] - s[i] - r[i] * s[i]);
		m(0, 11) = (0.5 * (1.0 - t[i])) * (1.0 - (0.5 * (1.0 - t[i]))) * (1.0 + r[i] + s[i] + r[i] * s[i]);
		m(0, 12) = (0.5 * (1.0 - t[i])) * (1.0 - (0.5 * (1.0 - t[i]))) * (1.0 - r[i] + s[i] - r[i] * s[i]);
	}

	for (size_t i = 0; i < r.size(); i++) {
		///dN contains [dNr, dNs, dNt]
		MatrixDense &m = (*dN)[i];

		m(0, 0)  = -(t[i] / 8.0 - 1.0 / 8.0) * (s[i] - 1.0) * (r[i] * (t[i] / 2.0 - 0.5) + s[i] * (t[i] / 2.0 - 0.5) - 1.0) - (t[i] / 2.0 - 0.5) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] - 1.0);
		m(0, 1)  = -(t[i] / 8.0 - 1.0 / 8.0) * (s[i] - 1.0) * (r[i] * (t[i] / 2.0 - 0.5) - s[i] * (t[i] / 2.0 - 0.5) + 1.0) - (t[i] / 2.0 - 0.5) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] - 1.0);
		m(0, 2)  =  (t[i] / 8.0 - 1.0 / 8.0) * (s[i] + 1.0) * (r[i] * (t[i] / 2.0 - 0.5) + s[i] * (t[i] / 2.0 - 0.5) + 1.0) + (t[i] / 2.0 - 0.5) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] + 1.0);
		m(0, 3)  =  (t[i] / 2.0 - 0.5) * (s[i] + 1.0) * (r[i] - 1.0) * (t[i] / 8.0 - 1.0 / 8.0) - (t[i] / 8.0 - 1.0 / 8.0) * (s[i] + 1.0) * (s[i] * (t[i] / 2.0 - 0.5) - r[i] * (t[i] / 2.0 - 0.5) + 1.0);
		m(0, 4)  =  0.0;
		m(0, 5)  =  r[i] * ((t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 0.5)) * (s[i] - 1.0);
		m(0, 6)  = -((pow(s[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 0.5)) / 2.0;
		m(0, 7)  = -r[i] * ((t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 0.5)) * (s[i] + 1.0);
		m(0, 8)  =  ((pow(s[i], 2.0) - 1) * (t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 0.5)) / 2.0;
		m(0, 9)  = -(t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (s[i] - 1.0);
		m(0, 10) =  (t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (s[i] - 1.0);
		m(0, 11) = -(t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (s[i] + 1.0);
		m(0, 12) =  (t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (s[i] + 1.0);

		m(1, 0)  = -(t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (r[i] * (t[i] / 2.0 - 1.0 / 2.0) + s[i] * (t[i] / 2.0 - 1.0 / 2.0) - 1.0) - (t[i] / 2.0 - 1.0 / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] - 1.0);
		m(1, 1)  =  (t[i] / 2.0 - 1.0 / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] - 1.0) - (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (r[i] * (t[i] / 2.0 - 1.0 / 2.0) - s[i] * (t[i] / 2.0 - 1.0 / 2.0) + 1.0);
		m(1, 2)  =  (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (r[i] * (t[i] / 2.0 - 1.0 / 2.0) + s[i] * (t[i] / 2.0 - 1.0 / 2.0) + 1.0) + (t[i] / 2.0 - 1.0 / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] + 1.0);
		m(1, 3)  = -(t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] * (t[i] / 2.0 - 1.0 / 2.0) - r[i] * (t[i] / 2.0 - 1.0 / 2.0) + 1.0) - (t[i] / 2.0 - 1.0 / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] + 1.0);
		m(1, 4)  =  0.0;
		m(1, 5)  =  ((pow(r[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 1.0 / 2.0)) / 2.0;
		m(1, 6)  = -s[i] * (t[i] / 2.0 - 1.0 / 2.0) * (t[i] / 2.0 - 0.5) * (r[i] + 1.0);
		m(1, 7)  = -((pow(r[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 1.0 / 2.0)) / 2.0;
		m(1, 8)  =  s[i] * (t[i] / 2.0 - 0.5) * (t[i] / 2.0 - 0.5) * (r[i] - 1.0);
		m(1, 9)  = -(t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (r[i] - 1.0);
		m(1, 10) =  (t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (r[i] + 1.0);
		m(1, 11) = -(t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (r[i] + 1.0);
		m(1, 12) =  (t[i] / 2.0 - 0.5) * (t[i] / 2.0 + 0.5) * (r[i] - 1.0);

		m(2, 0)  = -((r[i] - 1.0) * (s[i] - 1.0) * (r[i] * (t[i] / 2.0 - 0.5) + s[i] * (t[i] / 2.0 - 0.5) - 1.0)) / 8.0 - (r[i] / 2.0 + s[i] / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] - 1.0);
		m(2, 1)  = -((r[i] + 1.0) * (s[i] - 1.0) * (r[i] * (t[i] / 2.0 - 0.5) - s[i] * (t[i] / 2.0 - 0.5) + 1.0)) / 8.0 - (r[i] / 2.0 - s[i] / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] - 1.0);
		m(2, 2)  =  ((r[i] + 1.0) * (s[i] + 1.0) * (r[i] * (t[i] / 2.0 - 0.5) + s[i] * (t[i] / 2.0 - 0.5) + 1.0)) / 8.0 + (r[i] / 2.0 + s[i] / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] + 1.0) * (s[i] + 1.0);
		m(2, 3)  =  (r[i] / 2.0 - s[i] / 2.0) * (t[i] / 8.0 - 1.0 / 8.0) * (r[i] - 1.0) * (s[i] + 1.0) - ((r[i] - 1.0) * (s[i] + 1.0) * (s[i] * (t[i] / 2.0 - 0.5) - r[i] * (t[i] / 2.0 - 0.5) + 1.0)) / 8.0;
		m(2, 4)  =  t[i] + 0.5;
		m(2, 5)  =  ((pow(r[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (s[i] - 1.0)) / 2.0;
		m(2, 6)  = -((pow(s[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (r[i] + 1.0)) / 2.0;
		m(2, 7)  = -((pow(r[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (s[i] + 1.0)) / 2.0;
		m(2, 8)  =  ((pow(s[i], 2.0) - 1.0) * (t[i] / 2.0 - 0.5) * (r[i] - 1.0)) / 2.0;
		m(2, 9)  =  ((t[i] / 2.0 - 0.5) * (r[i] + s[i] - r[i] * s[i] - 1.0)) / 2.0 + ((t[i] / 2.0 + 0.5) * (r[i] + s[i] - r[i] * s[i] - 1.0)) / 2.0;
		m(2, 10) = -((t[i] / 2.0 - 0.5) * (r[i] - s[i] - r[i] * s[i] + 1.0)) / 2.0 - ((t[i] / 2.0 + 0.5) * (r[i] - s[i] - r[i] * s[i] + 1.0)) / 2.0;
		m(2, 11) = -((t[i] / 2.0 - 0.5) * (r[i] + s[i] + r[i] * s[i] + 1.0)) / 2.0 - ((t[i] / 2.0 + 0.5) * (r[i] + s[i] + r[i] * s[i] + 1.0)) / 2.0;
		m(2, 12) =  ((t[i] / 2.0 - 0.5) * (r[i] - s[i] + r[i] * s[i] - 1.0)) / 2.0 + ((t[i] / 2.0 + 0.5) * (r[i] - s[i] + r[i] * s[i] - 1.0)) / 2.0;
	}
}

void Pyramid13::setBaseFunctions(Element &self)
{
	size_t GPCount = 14, nodeCount = 13;

	self.N = new std::vector<MatrixDense>(GPCount, MatrixDense(1, nodeCount));
	self.dN = new std::vector<MatrixDense>(GPCount, MatrixDense(3, nodeCount));
	self.weighFactor = new std::vector<double>();

	std::vector< std::vector<double> > rst(3, std::vector<double>(GPCount));

	switch (GPCount) {
		case 8: {
			double v = 0.577350269189625953;
			rst[0] = {  v,  v,  v,  v, -v, -v, -v, -v };
			rst[1] = { -v, -v,  v,  v, -v, -v,  v,  v };
			rst[2] = { -v,  v, -v,  v, -v,  v, -v,  v };
			break;
		}
		case 14: {
			double v1 = 0.758786910639329015;
			double v2 = 0.795822425754222018;
			double v3 = 0;
			rst[0] = { -v1,  v1,  v1, -v1, -v1,  v1,  v1, -v1,  v3,  v3,  v2, v3, -v2, v3 };
			rst[1] = { -v1, -v1,  v1,  v1, -v1, -v1,  v1,  v1,  v3, -v2,  v3, v2,  v3, v3 };
			rst[2] = { -v1, -v1, -v1, -v1,  v1,  v1,  v1,  v1, -v2,  v3,  v3, v3,  v3, v2 };
			break;
		}
		default:
			exit(1);
		}

	for (unsigned int i = 0; i < GPCount; i++) {
		MatrixDense &m = (*self.N)[i];

		double r = rst[0][i];
		double s = rst[1][i];
		double t = rst[2][i];

		// basis function
		m(0, 0)  = ((0.5 * (1.0 - t)) / 4.0) * ((1.0 - r) * (1.0 - s) * (-1.0 - (0.5 * (1.0 - t)) * r - (0.5 * (1.0 - t)) * s));
		m(0, 1)  = ((0.5 * (1.0 - t)) / 4.0) * ((1.0 + r) * (1.0 - s) * (-1.0 + (0.5 * (1 - t))   * r - (0.5 * (1.0 - t)) * s));
		m(0, 2)  = ((0.5 * (1.0 - t)) / 4.0) * ((1.0 + r) * (1.0 + s) * (-1.0 + (0.5 * (1.0 - t)) * r + (0.5 * (1.0 - t)) * s));
		m(0, 3)  = ((0.5 * (1.0 - t)) / 4.0) * ((1.0 - r) * (1.0 + s) * (-1.0 - (0.5 * (1.0 - t)) * r + (0.5 * (1.0 - t)) * s));
		m(0, 4)  = (1.0 - (0.5 * (1.0 - t))) * (1.0 - 2.0 * (0.5 * (1.0 - t)));
		m(0, 5)  = (((0.5 * (1.0 - t)) * (0.5 * (1.0 - t))) / 2.0) * (1.0 - s) * (1.0 - pow(r, 2.0));
		m(0, 6)  = (((0.5 * (1.0 - t)) * (0.5 * (1.0 - t))) / 2.0) * (1.0 + r) * (1.0 - pow(s, 2.0));
		m(0, 7)  = (((0.5 * (1.0 - t)) * (0.5 * (1.0 - t))) / 2.0) * (1.0 + s) * (1.0 - pow(r, 2.0));
		m(0, 8)  = (((0.5 * (1.0 - t)) * (0.5 * (1.0 - t))) / 2.0) * (1.0 - r) * (1.0 - pow(s, 2.0));
		m(0, 9)  = (0.5 * (1.0 - t)) * (1.0 - (0.5 * (1.0 - t))) * (1.0 - r - s + r * s);
		m(0, 10) = (0.5 * (1.0 - t)) * (1.0 - (0.5 * (1.0 - t))) * (1.0 + r - s - r * s);
		m(0, 11) = (0.5 * (1.0 - t)) * (1.0 - (0.5 * (1.0 - t))) * (1.0 + r + s + r * s);
		m(0, 12) = (0.5 * (1.0 - t)) * (1.0 - (0.5 * (1.0 - t))) * (1.0 - r + s - r * s);
	}

	for (unsigned int i = 0; i < GPCount; i++) {
		///dN contains [dNr, dNs, dNt]
		MatrixDense &m = (*self.dN)[i];

		double r = rst[0][i];
		double s = rst[1][i];
		double t = rst[2][i];

		// dNr - derivation of basis function
		m(0, 0)  = -(t / 8.0 - 1.0 / 8.0) * (s - 1.0) * (r * (t / 2.0 - 0.5) + s * (t / 2.0 - 0.5) - 1.0) - (t / 2.0 - 0.5) * (t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s - 1.0);
		m(0, 1)  = -(t / 8.0 - 1.0 / 8.0) * (s - 1.0) * (r * (t / 2.0 - 0.5) - s * (t / 2.0 - 0.5) + 1.0) - (t / 2.0 - 0.5) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s - 1.0);
		m(0, 2)  =  (t / 8.0 - 1.0 / 8.0) * (s + 1.0) * (r * (t / 2.0 - 0.5) + s * (t / 2.0 - 0.5) + 1.0) + (t / 2.0 - 0.5) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s + 1.0);
		m(0, 3)  =  (t / 2.0 - 0.5) * (s + 1.0) * (r - 1.0) * (t / 8.0 - 1.0 / 8.0) - (t / 8.0 - 1.0 / 8.0) * (s + 1.0) * (s * (t / 2.0 - 0.5) - r * (t / 2.0 - 0.5) + 1.0);
		m(0, 4)  =  0.0;
		m(0, 5)  =  r * ((t / 2.0 - 0.5) * (t / 2.0 - 0.5)) * (s - 1.0);
		m(0, 6)  = -((pow(s, 2.0) - 1.0) * (t / 2.0 - 0.5) * (t / 2.0 - 0.5)) / 2.0;
		m(0, 7)  = -r * ((t / 2.0 - 0.5) * (t / 2.0 - 0.5)) * (s + 1.0);
		m(0, 8)  =  ((pow(s, 2.0) - 1) * (t / 2.0 - 0.5) * (t / 2.0 - 0.5)) / 2.0;
		m(0, 9)  = -(t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (s - 1.0);
		m(0, 10) =  (t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (s - 1.0);
		m(0, 11) = -(t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (s + 1.0);
		m(0, 12) =  (t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (s + 1.0);
		//  dNs - derivation of basis function
		m(1, 0)  = -(t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (r * (t / 2.0 - 1.0 / 2.0) + s * (t / 2.0 - 1.0 / 2.0) - 1.0) - (t / 2.0 - 1.0 / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s - 1.0);
		m(1, 1)  =  (t / 2.0 - 1.0 / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s - 1.0) - (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (r * (t / 2.0 - 1.0 / 2.0) - s * (t / 2.0 - 1.0 / 2.0) + 1.0);
		m(1, 2)  =  (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (r * (t / 2.0 - 1.0 / 2.0) + s * (t / 2.0 - 1.0 / 2.0) + 1.0) + (t / 2.0 - 1.0 / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s + 1.0);
		m(1, 3)  = -(t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s * (t / 2.0 - 1.0 / 2.0) - r * (t / 2.0 - 1.0 / 2.0) + 1.0) - (t / 2.0 - 1.0 / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s + 1.0);
		m(1, 4)  =  0.0;
		m(1, 5)  =  ((pow(r, 2.0) - 1.0) * (t / 2.0 - 0.5) * (t / 2.0 - 1.0 / 2.0)) / 2.0;
		m(1, 6)  = -s * (t / 2.0 - 1.0 / 2.0) * (t / 2.0 - 0.5) * (r + 1.0);
		m(1, 7)  = -((pow(r, 2.0) - 1.0) * (t / 2.0 - 0.5) * (t / 2.0 - 1.0 / 2.0)) / 2.0;
		m(1, 8)  =  s * (t / 2.0 - 0.5) * (t / 2.0 - 0.5) * (r - 1.0);
		m(1, 9)  = -(t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (r - 1.0);
		m(1, 10) =  (t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (r + 1.0);
		m(1, 11) = -(t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (r + 1.0);
		m(1, 12) =  (t / 2.0 - 0.5) * (t / 2.0 + 0.5) * (r - 1.0);
		//  dNt - derivation of basis function
		m(2, 0)  = -((r - 1.0) * (s - 1.0) * (r * (t / 2.0 - 0.5) + s * (t / 2.0 - 0.5) - 1.0)) / 8.0 - (r / 2.0 + s / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s - 1.0);
		m(2, 1)  = -((r + 1.0) * (s - 1.0) * (r * (t / 2.0 - 0.5) - s * (t / 2.0 - 0.5) + 1.0)) / 8.0 - (r / 2.0 - s / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s - 1.0);
		m(2, 2)  =  ((r + 1.0) * (s + 1.0) * (r * (t / 2.0 - 0.5) + s * (t / 2.0 - 0.5) + 1.0)) / 8.0 + (r / 2.0 + s / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r + 1.0) * (s + 1.0);
		m(2, 3)  =  (r / 2.0 - s / 2.0) * (t / 8.0 - 1.0 / 8.0) * (r - 1.0) * (s + 1.0) - ((r - 1.0) * (s + 1.0) * (s * (t / 2.0 - 0.5) - r * (t / 2.0 - 0.5) + 1.0)) / 8.0;
		m(2, 4)  =  t + 0.5;
		m(2, 5)  =  ((pow(r, 2.0) - 1.0) * (t / 2.0 - 0.5) * (s - 1.0)) / 2.0;
		m(2, 6)  = -((pow(s, 2.0) - 1.0) * (t / 2.0 - 0.5) * (r + 1.0)) / 2.0;
		m(2, 7)  = -((pow(r, 2.0) - 1.0) * (t / 2.0 - 0.5) * (s + 1.0)) / 2.0;
		m(2, 8)  =  ((pow(s, 2.0) - 1.0) * (t / 2.0 - 0.5) * (r - 1.0)) / 2.0;
		m(2, 9)  =  ((t / 2.0 - 0.5) * (r + s - r * s - 1.0)) / 2.0 + ((t / 2.0 + 0.5) * (r + s - r * s - 1.0)) / 2.0;
		m(2, 10) = -((t / 2.0 - 0.5) * (r - s - r * s + 1.0)) / 2.0 - ((t / 2.0 + 0.5) * (r - s - r * s + 1.0)) / 2.0;
		m(2, 11) = -((t / 2.0 - 0.5) * (r + s + r * s + 1.0)) / 2.0 - ((t / 2.0 + 0.5) * (r + s + r * s + 1.0)) / 2.0;
		m(2, 12) =  ((t / 2.0 - 0.5) * (r - s + r * s - 1.0)) / 2.0 + ((t / 2.0 + 0.5) * (r - s + r * s - 1.0)) / 2.0;
	}

	switch (GPCount) {
	case 8: {
		(*self.weighFactor) = std::vector<double> (8, 1.0);
		break;
	}
	case 14: {
		(*self.weighFactor).resize(8, 0.335180055401662);
		(*self.weighFactor).resize(14, 0.886426592797784);
		break;
	}
	default:
		exit(1);
	}

	BaseFunctions::created(self);
}






