using System;

namespace CVA
{
	public enum InterpolationType
	{
		LINEAR
	}

	public enum ExtrapolationType
	{
		NEAR,
		LINEAR
	}

	public class EnumToString
	{
		public EnumToString ()
		{
		}

		static string InterpolationTypeToString(InterpolationType eInterpolationType)
		{
			if (eInterpolationType == InterpolationType.LINEAR)
			{
				return "LINEAR";
			}
			throw new MyException ("Interpolation Type not recognized");
		}

		static InterpolationType StringToInterpolationType(string cInterpolationType)
		{
			if (cInterpolationType == "LINEAR")
			{
				return InterpolationType.LINEAR;
			}
			throw new MyException ("String is not an interpolation type");
		}

		static string ExtrapolationTypeToString(ExtrapolationType eExtrapolationType)
		{
			if (eExtrapolationType == ExtrapolationType.LINEAR) {
				return "LINEAR";
			} else if (eExtrapolationType == ExtrapolationType.NEAR) {
				return "NEAR";
			}
			throw new MyException ("Extrapolation is not recognized");
		}
	}
}

