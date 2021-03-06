

double HinvNew(int family, int n, double u, double v, double theta, double nu)
{
	int j;
	double* hinv;

	// #COMMENTED For undefined Calloc
	//hinv = Calloc(*n,double);
	hinv = calloc(n, sizeof(double));

	for (int i = 0; i < n; i++)
	{
		if (u[i] < UMIN) u[i] = UMIN;
		else if (u[i] > UMAX) u[i] = UMAX;
		if (v[i] < UMIN) v[i] = UMIN;
		else if (v[i] > UMAX) v[i] = UMAX;
	}

	for (j = 0; j < n; j++)
	{
		if (family == 0)
		{
			hinv[j] = u[j];
		}
		else if (family == 1) //gaussian
		{
			hinv[j] = pnorm(qnorm(u[j], 0.0, 1.0, 1, 0) * sqrt(1.0 - pow(theta, 2.0)) + theta * qnorm(v[j], 0.0, 1.0, 1, 0), 0.0, 1.0, 1, 0);
		}
		else if (family == 2) //student
		{
			double temp1, temp2, mu, var;
			temp1 = qt(u[j], *nu + 1.0, 1, 0); temp2 = qt(v[j], *nu, 1, 0); mu = theta * temp2; var = ((*nu + (temp2 * temp2)) * (1.0 - (theta * (theta)))) / (*nu + 1.0);
			hinv[j] = pt((sqrt(var) * temp1) + mu, *nu, 1, 0);
		}
		else if (family == 3) //clayton
		{
			if (theta < XEPS) {
				hinv[j] = u[j];
			}
			else if (theta < 75) {
				hinv[j] = pow(pow(u[j] * pow(v[j], theta + 1.0), -theta / (theta + 1.0)) + 1.0 - pow(v[j], -theta), -1.0 / (theta));
			}
			else {
				double nu = 0.0;
				HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);
			}
		}
		else if (family == 4) //gumbel - must turn to numerical inversion
		{
			qcondgum(&u[j], &v[j], theta, &hinv[j]);
		}
		else if (family == 5) //frank - numerical inversion
		{
			//hinv[j] = -1/(*theta)*log(1-(1-exp(-*theta)) / ((1/u[j]-1)*exp(-*theta*v[j])+1));
			double nu = 0.0;

            // #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);
			HNumInv(&family, &u[j], &v[j], theta, &nu, &hinv[j]);
		}
		else if (family == 6) //joe - numerical inversion
		{
			if (theta < 30)
			{
				qcondjoe(&u[j], &v[j], theta, &hinv[j]);
			}
			else
			{
				double nu = 0.0;

		    // #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);

				HNumInv(&family, &u[j], &v[j], theta, &nu, &hinv[j]);
			}
		}
		else if (family == 7) //BB1
		{

			// #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);


			HNumInv(&family, &u[j], &v[j], theta, nu, &hinv[j]);
		}
		else if (family == 8) //BB6
		{

			  // #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);

			HNumInv(&family, &u[j], &v[j], theta, nu, &hinv[j]);
		}
		else if (family == 9) //BB7
		{

			  // #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);

			HNumInv(&family, &u[j], &v[j], theta, nu, &hinv[j]);
		}
		else if (family == 10) //BB8
		{

			// #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);

			HNumInv(family, &u[j], &v[j], theta, nu, &hinv[j]);
		}
		else if (family == 13)
		{
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			hinv[j] = pow(pow(u[j] * pow(v[j], theta + 1.0), -theta / (theta + 1.0)) + 1.0 - pow(v[j], -theta), -1.0 / (theta));
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 14) //rotated gumbel (180?) - must turn to numerical inversion
		{
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			qcondgum(&u[j], &v[j], theta, &hinv[j]);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 16) //rotated joe (180?) - must turn to numerical inversion
		{
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			if (theta < 40)
			{
				qcondjoe(&u[j], &v[j], theta, &hinv[j]);
			}
			else
			{
				int jj = 6;
				double nu = 0.0;

				HNumInv(&jj, &u[j], &v[j], theta, &nu, &hinv[j]);
			}
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 17) //rotated BB1 (180?) - must turn to numerical inversion
		{
			int jj = 7;
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			HNumInv(&jj, &u[j], &v[j], theta, nu, &hinv[j]);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 18) //rotated BB6 (180?) - must turn to numerical inversion
		{
			int jj = 8;
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			HNumInv(&jj, &u[j], &v[j], theta, nu, &hinv[j]);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 19) //rotated BB7 (180?) - must turn to numerical inversion
		{
			int jj = 9;
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			HNumInv(&jj, &u[j], &v[j], theta, nu, &hinv[j]);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 20) //rotated BB8 (180?) - must turn to numerical inversion
		{
			int jj = 10;
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			HNumInv(&jj, &u[j], &v[j], theta, nu, &hinv[j]);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (family == 41)	// 1-parametric asymmetric copula (Harry Joe)
		{
			double de = theta;
			double tem1, y;
			tem1 = qgamma(1.0 - v[j], de, 1, 1, 0);
			y = pow(tem1 - log(u[j]), de) - pow(tem1, de);
			y = pow(y, (1.0 / de));
			hinv[j] = 1.0 - pgamma(y, de, 1, 1, 0);
		}
		else if (family == 51)	// rotated (180) 1-parametric asymmetric copula (Harry Joe)
		{
			double de = theta;
			double tem1, y;
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
			tem1 = qgamma(1.0 - v[j], de, 1, 1, 0);
			y = pow(tem1 - log(u[j]), de) - pow(tem1, de);
			y = pow(y, (1.0 / de));
			hinv[j] = 1.0 - pgamma(y, de, 1, 1, 0);
			hinv[j] = 1 - hinv[j];
			u[j] = 1 - u[j];
			v[j] = 1 - v[j];
		}
		else if (((family) / 100 == 1) | ((*family) / 100 == 2)) //Tawn
		{

           // #SUJAYGHOSH family is a pointer in the orginal code
			// hence it should take a address ( &parameter )
			// HNumInv(family, &u[j], &v[j], theta, &nu, &hinv[j]);


			HNumInv(&family, &u[j], &v[j], theta, nu, &hinv[j]);
		}

		out[j] = MAX(MIN(hinv[j], UMAX), UMIN);
	}
	Free(hinv);
}


