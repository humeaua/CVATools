using System;

namespace CVA
{
	public enum EnumBasis{
		ACTACT,
		THIRTY360EURO,
		THIRTY360US,
		ACT365FIXED,
		ACT360,
		ACT364,
		ACT365L,
		UNITARY
	}

	public class MyBasis
	{
		#region Implementation
		EnumBasis eBasis;
		#endregion

		public MyBasis (EnumBasis eBasis0)
		{
			eBasis = eBasis0;
		}

		public EnumBasis Basis
		{
			get
			{
				return eBasis;
			}
			set
			{
				eBasis = value;
			}
		}
	}
}

