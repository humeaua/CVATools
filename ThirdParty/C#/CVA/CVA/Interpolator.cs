using System.Collections.Generic; // for list
using System;

namespace CVA
{
	public class Interpolator
	{
		#region Implementation
		private List<double> X;
		private List<double> Y;
		private string cInterpolationMethod;
		private string cExtrapolationMethod;
		#endregion

		private void SetDefaultInterpolationMethod()
		{
			cInterpolationMethod = "LINEAR";
		}

		private void SetDefaultExtrapolationMethod()
		{
			cExtrapolationMethod = "NEAR";
		}

		public Interpolator()
		{
			X = new List<double> ();
			Y = new List<double> ();
			SetDefaultExtrapolationMethod ();
			SetDefaultInterpolationMethod ();
		}

		public Interpolator( Interpolator sInterp0)
		{
			X = sInterp0.X;
			Y = sInterp0.Y;
			cInterpolationMethod = sInterp0.cInterpolationMethod;
			cExtrapolationMethod = sInterp0.cExtrapolationMethod;
		}

		public Interpolator (ref List<double> X0, ref List<double> Y0)
		{
			if (X0.Count != Y0.Count) 
			{
				throw new MyException ("Variables and values have to have the same number of elements");
			}
			if (X0.Count == 0) 
			{
				throw new MyException ("Variables and values cannot be empty");
			}
			X = X0;
			Y = Y0;
			SetDefaultExtrapolationMethod ();
			SetDefaultInterpolationMethod ();
		}

		/*static List<double> Variables
		{
			get
			{
				return &X; 
			}
			set
			{
				&X = value; 
			}
		}*/

		public double Interp(double x)
		{
			switch (cExtrapolationMethod.ToUpper ()) 
			{
			case "NEAR":
				if (x <= X [0])
					return Y [0];
				if (x >= X [X.Count - 1])
					return Y [X.Count - 1];
			default:
				break;
			}
			switch (cInterpolationMethod.ToUpper()) 
			{
			case "LINEAR":
			case "LIN":
				return InterpLin (x);
			default:
				throw new MyException ("Interpolation Type not recognized. Must input a correct interpolation type");
			}
		}

		public Tuple<int,int> Indexes(double x)
		{
			if (x < X [0])
				return new Tuple<int,int> (0, 1);
			else if (x > X [X.Count - 1])
				return new Tuple<int,int> (X.Count - 2, X.Count - 1);
			else 
			{
				for (int i = 0; i < X.Count - 1; ++i) 
				{
					if (X [i] <= x && x <= X [i + 1]) {
						return new Tuple<int,int> (i, i + 1);
					}
				}
			}
			throw new MyException ("LookUp failed in Indexes");
		}

		private double InterpLin(double x)
		{
			Tuple<int,int> indexes = Indexes (x);
			if (X [indexes.Item1] == X [indexes.Item2]) 
			{
				return (Y [indexes.Item1] + Y [indexes.Item2]) / 2.0;
			}
			else
			{
				return Y [indexes.Item1] + (Y [indexes.Item2] - Y [indexes.Item1]) / (X [indexes.Item2] - X [indexes.Item1]) * (x - X [indexes.Item1]);
			}
		}
	}
}

