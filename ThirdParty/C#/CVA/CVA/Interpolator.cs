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

		public List<double> Variables
		{
			get
			{
				if (X == null)
				{
					X = new List<double>();
				}
				if (X.Count < 1)
				{
					X.Add(new double());
				}
				return X;
			}
			set { X = value; }
		}

		public List<double> Values
		{
			get
			{
				if (Y == null)
				{
					Y = new List<double>();
				}
				if (Y.Count < 1)
				{
					Y.Add(new double());
				}
				return Y;
			}
			set { Y = value; }
		}

		public double Interp(double x)
		{
			switch (cExtrapolationMethod.ToUpper ()) 
			{
			case "NEAR":
				if (x <= Variables [0])
					return Values [0];
				if (x >= Variables [Variables.Count - 1])
					return Values [Variables.Count - 1];
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
			if (x < Variables [0])
				return new Tuple<int,int> (0, 1);
			else if (x > Variables [Variables.Count - 1])
				return new Tuple<int,int> (Variables.Count - 2, Variables.Count - 1);
			else 
			{
				for (int i = 0; i < Variables.Count - 1; ++i) 
				{
					if (Variables [i] <= x && x <= Variables [i + 1]) {
						return new Tuple<int,int> (i, i + 1);
					}
				}
			}
			throw new MyException ("LookUp failed in Indexes");
		}

		private double InterpLin(double x)
		{
			Tuple<int,int> indexes = Indexes (x);
			if (Variables [indexes.Item1] == Variables [indexes.Item2]) 
			{
				return (Values [indexes.Item1] + Values [indexes.Item2]) / 2.0;
			}
			else
			{
				return Values [indexes.Item1] + (Values [indexes.Item2] - Values [indexes.Item1]) / (Variables [indexes.Item2] - Variables [indexes.Item1]) * (x - Variables [indexes.Item1]);
			}
		}
	}
}

