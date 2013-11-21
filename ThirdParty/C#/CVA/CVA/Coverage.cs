using System;

namespace CVA
{
	public class Coverage
	{
		#region Implementation
		DateTime sStart, sEnd;
		EnumBasis eBasis;
		#endregion

		public Coverage (DateTime sStart0, DateTime sEnd0, EnumBasis eBasis0)
		{
			Start = sStart0;
			End = sEnd0;
			Basis = eBasis0;
		}

		public DateTime Start
		{
			get { return sStart; }
			set { sStart = value; }
		}

		public DateTime End
		{
			get { return sEnd; }
			set { sEnd = value; }
		}

		public EnumBasis Basis
		{
			get { return eBasis; }
			set { eBasis = value; }
		}

		public double GetCoverage()
		{
			switch (eBasis) 
			{
			case EnumBasis.ACT365FIXED:
				{
					TimeSpan elapsedtime = new TimeSpan (End.Ticks - Start.Ticks);
					return elapsedtime.Days / 365.0;
				}
			default:
				return 0;
			}
		}
	}
}

