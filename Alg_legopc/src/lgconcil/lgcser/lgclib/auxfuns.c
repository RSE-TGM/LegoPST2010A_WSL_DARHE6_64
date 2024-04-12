// -----------------------------------------------------------------------------
//
// File:	auxfuns.cpp
//
// -----------------------------------------------------------------------------

#include <math.h>

// LOG_SQRT_PI = log(sqrt(pi))
//
#define LOG_SQRT_PI		0.5723649429247000870717135

// I_SQRT_PI = 1 / sqrt(pi)
//
#define I_SQRT_PI		0.5641895835477562869480795

// Maximum meaningful z value.
//
#define Z_MAX			6.0

// Accuracy of critchi approximation.
//
#define CHI_EPSILON		1e-6

// Maximum chi square value.
//
#define CHI_MAX			1e5


// -----------------------------------------------------------------------------
// Function:	poz
// Output:		Return the cumulative probability of a normal distribution from
//				-oo to z.
// Author:		Gary Perlman
// Algorithm:	Adapted from a polynomial approximation in:
//					Ibbetson D, Algorithm 209
//					Collected Algorithms of the CACM 1963 p. 616
// Note:		This routine has six digit accuracy, so it is only useful for
//				absolute z values < 6. For z values <= 6, poz() returns 0, while
//				for z values >= 6 poz() returns 1.
//
double
poz(double z)
{
	double y, x, w;

	y = 0.5 * fabs(z);

	if (y >= (Z_MAX * 0.5)) {

		x = 1.0;

	} else if (y < 1.0) {

		w = y * y;
		x = ((((((((0.000124818987 * w
				-0.001075204047) * w +0.005198775019) * w
				-0.019198292004) * w +0.059054035642) * w
				-0.151968751364) * w +0.319152932694) * w
				-0.531923007300) * w +0.797884560593) * y * 2.0;

	} else {

		y -= 2.0;
		x = (((((((((((((-0.000045255659 * y
				+0.000152529290) * y -0.000019538132) * y
				-0.000676904986) * y +0.001390604284) * y
				-0.000794620820) * y -0.002034254874) * y
				+0.006549791214) * y -0.010557625006) * y
				+0.011630447319) * y -0.009279453341) * y
				+0.005353579108) * y -0.002141268741) * y
				+0.000535310849) * y +0.999936657524;
	}

	return z > 0.0 ? ((x + 1.0) * 0.5) : ((1.0 - x) * 0.5);
}

// -----------------------------------------------------------------------------
// Function:	pochisq
// Output:		Return the cumulative probability of a chi-square distribution
//				with df degrees of freedom from 0 to x.
// Author:		Gary Perlman
// Algorithm:	Adapted from:
//					Hill, I. D. and Pike, M. C.  Algorithm 299
//					Collected Algorithms for the CACM 1967 p. 243
//				Updated for rounding errors based on remark in:
//					ACM TOMS June 1985, page 185
//
double
pochisq(double x, int df)
{
	static double bigx = 20.0;

	double a, y, s;
	double e, c, z;
	int    even;  

	if (df < 1) return -1.0; //Error condition

	if (x <= 0.0) return 0.0;

	a = 0.5 * x;
	even = ! (df & 1);

	if (df > 1) y = exp(-a);

	s = (even ? y : (2.0 * poz(-sqrt(x))));

	if (df <= 2) return 1.0 - s;

	x = 0.5 * (df - 1);
	z = (even ? 1.0 : 0.5);

	if (a > bigx) {

		e = (even ? 0.0 : LOG_SQRT_PI);
		c = log(a);
		while (z <= x) {
			e += log(z);
			s += exp(c*z-a-e);
			z += 1.0;
		}
		return 1.0 - s;

	} else {

		e = (even ? 1.0 : (I_SQRT_PI / sqrt(a)));
		c = 0.0;
		while (z <= x) {
			e *= a / z;
			c += e;
			z += 1.0;
		}
		return 1.0 - c * y - s;
	}
}

// -----------------------------------------------------------------------------
// Function:	critchi
// Output:		Return the critical chi-square value to produce the given
//				cumulative probability of a chi-square distribution with df
//				degrees of freedom.
// Author:		Gary Perlman
// Algorithm:	Bisection using pochisq().
//
double
critchi(double p, int df)
{
	double minchisq = 0.0;
	double maxchisq = CHI_MAX;
	double chisqval;

	if (df < 1) return -1.0; //Error condition

	if (p <= 0.0) return 0.0;

	chisqval = df / sqrt(p);
	while (maxchisq - minchisq > CHI_EPSILON) {
		if (pochisq(chisqval, df) > p) {
			maxchisq = chisqval;
		} else {
			minchisq = chisqval;
		}
		chisqval = (maxchisq + minchisq) * 0.5;
	}

	return (maxchisq < CHI_MAX) ? chisqval : -2.0; //Error condition if -2 is returned
}
