using Extensions; // for MoreDateFunctions
using System; // for DateTime

namespace CVA
{
	public class Coverage
	{
		#region Implementation
		DateTime sStart, sEnd;
		EnumBasis eBasis;
		#endregion

		public Coverage()
		{}

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

		private double GetCoverage()
		{
			switch (eBasis) 
			{
			case EnumBasis.ACT365FIXED:
				{
					TimeSpan elapsedtime = new TimeSpan (End.Ticks - Start.Ticks);
					return elapsedtime.Days / 365.0;
				}
			case EnumBasis.ACTACT:
				{
					TimeSpan elapsedtime = new TimeSpan (End.Ticks - Start.Ticks);
					double dRes = 0.0;
					for (long i = Start.Year; i <= End.Year; i += 1) {
						if (MoreDatesFunctions.IsLeapYear(i))
						{
							dRes += 366.0;
						}
						else 
						{
							dRes += 365.0;
						}
					}
					dRes /= (End.Year - Start.Year + 1);
					return elapsedtime.Days / dRes;
				}
			case EnumBasis.THIRTY360EURO:
				{
					DateTime 	sStartCopy = MoreDatesFunctions.ChangeDateToBondBasisConvention (Start),
								sEndCopy = MoreDatesFunctions.ChangeDateToBondBasisConvention (End);
					return (sEndCopy.Year - sStartCopy.Year) + (sEndCopy.Month - sStartCopy.Month) / 12.0 + (sEndCopy.Day - sStartCopy.Day) / 360.0;
				}
			case EnumBasis.UNITARY:
				return 1.0;
			default:
				throw new MyException ("Unknown basis");
			}
		}

		public double YearFraction(ref DateTime Start0, ref DateTime End0, EnumBasis Basis0)
		{
			Start = Start0;
			End = End0;
			Basis = Basis0;

			return GetCoverage ();
		}
	}
}

