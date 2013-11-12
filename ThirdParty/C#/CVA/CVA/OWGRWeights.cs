using System.Collections.Generic; // for list

namespace CVA
{
	public class OWGRWeights : Weights
	{
		public OWGRWeights () : base( new Interpolator(MakeInterpolator()))
		{
		}

		protected static /*override*/ Interpolator MakeInterpolator()
		{
			List<double> X = new List<double>(), Y = new List<double>();
			X.Add (0.25);
			X.Add (2);

			Y.Add (1.0);
			Y.Add (0.0);

			return new Interpolator (ref X, ref Y);
		}
	}
}

